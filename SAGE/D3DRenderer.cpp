#include "D3DRenderer.h"
#include <SDL.h>
#include <SDL_syswm.h>

cD3DRenderer::cD3DRenderer(SDL_Window* window, bool vsync) :
	m_vsync(vsync),
	m_device(nullptr),
	m_context(nullptr),
	m_swapChain(nullptr)
{
	// Get the native window handle
	SDL_SysWMinfo wmi;
	SDL_VERSION(&wmi.version);
	SDL_GetWindowWMInfo(window, &wmi);
	HWND hwnd = wmi.info.win.window;

	DXGI_SWAP_CHAIN_DESC scd = { 0 };
	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = hwnd;                                // the window to be used
	scd.SampleDesc.Count = 4;                               // how many multisamples
	scd.Windowed = TRUE;                                    // windowed/full-screen mode

	// Create the D3D device and swap chain
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&m_swapChain,
		&m_device,
		0,
		&m_context
	);

	if (FAILED(hr))
	{
		// do bad things
	}

	// Create the render target
	ID3D11Texture2D* pBackBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	m_device->CreateRenderTargetView(pBackBuffer, NULL, &m_renderTarget);
	pBackBuffer->Release();
	m_context->OMSetRenderTargets(1, &m_renderTarget, NULL);

	// Init the viewport
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Resize(w, h);
}

cD3DRenderer::~cD3DRenderer()
{
	if (m_renderTarget)
		m_renderTarget->Release();
	if (m_swapChain)
		m_swapChain->Release();
	if (m_device)
		m_device->Release();
	if (m_context)
		m_context->Release();
}

void cD3DRenderer::Clear(float r, float g, float b, float a)
{
	float color[4] = { r,g,b,a };
	m_context->ClearRenderTargetView(m_renderTarget, color);
}

void cD3DRenderer::Present()
{
	m_swapChain->Present(static_cast<UINT>(m_vsync), 0);		// 1 for vsync
}

void cD3DRenderer::Resize(int w, int h)
{
	D3D11_VIEWPORT viewport = { 0 };
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (FLOAT)w;
	viewport.Height = (FLOAT)h;

	m_context->RSSetViewports(1, &viewport);
}

void cD3DRenderer::DrawPrimitives(ePrimitiveType type, int start, int count)
{
	switch (type)
	{
	case TriangleList:
		m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case TriangleStrip:
		m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		break;
	}
	m_context->Draw(count, start);
}