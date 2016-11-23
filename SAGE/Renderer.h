#ifndef __RENDERER_H__
#define __RENDERER_H__

enum ePrimitiveType
{
	TriangleList,
	TriangleStrip
};

class iRenderer
{
public:
	iRenderer() {}
	virtual ~iRenderer() {}

	virtual void Clear(float r, float g, float b, float a) = 0;
	virtual void Present() = 0;
	virtual void Resize(int w, int h) = 0;
	virtual void DrawPrimitives(ePrimitiveType type, int start, int count) = 0;
};

#endif