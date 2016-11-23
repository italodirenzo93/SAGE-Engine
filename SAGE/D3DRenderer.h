#ifdef _WIN32

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <d3d11.h>
#include <dxgi.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

#include "Renderer.h"

class cD3DRenderer : public iRenderer
{
public:
	cD3DRenderer(struct SDL_Window* window, bool vsync);
	virtual ~cD3DRenderer();

	virtual void Clear(float r, float g, float b, float a) override;
	virtual void Present() override;
	virtual void Resize(int w, int h) override;
	virtual void DrawPrimitives(ePrimitiveType type, int start, int count) override;

private:
	bool						m_vsync;
	ID3D11Device*				m_device;
	ID3D11DeviceContext*		m_context;
	IDXGISwapChain*				m_swapChain;
	ID3D11RenderTargetView*		m_renderTarget;
};

#endif