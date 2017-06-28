#ifndef RENDERER_H
#define RENDERER_H
//
#include <vector>
#include <gl/glew.h>
#include "UcMacros.h"
#include "UcReference.h"
//#include "UcVertexBuffer.h"
//#include "UcIndexBuffer.h"
#include "UcStruct.h"
#include "UcConfig.h"
UC_BEGIN

class RenderQueue
{
public:
	
private:

};

class Renderer : public Reference
{
public:
	typedef std::vector<Renderer*> RenderList;

public:
	//reload functions specificly
	//vertex buffer
	//void bind(const VertexBuffer* vbuf);
	//static void bindAll(const VertexBuffer* vbuf);
	//void unbind(const VertexBuffer* vbuf);
	//static void unbindAll(const VertexBuffer* vbuf);
	//void enable(const VertexBuffer* vbuf, uint streamIndex = 0, uint offset = 0);
	//void disenable(const VertexBuffer* vbuf, uint streamIndex);
	//void lock(const VertexBuffer* vbuf);
	//void unlock(const VertexBuffer* vbuf);
	//void update(const VertexBuffer* vbuf);
	//static void updateAll(const VertexBuffer* vbuf);
	//
	////index buffer
	//void bind(const GLIndexBuffer* vbuf);
	//static void bindAll(const GLIndexBuffer* vbuf);
	//void unbind(const GLIndexBuffer* vbuf);
	//static void unbindAll(const GLIndexBuffer* vbuf);
	//void enable(const GLIndexBuffer* vbuf);
	//void disenable(const GLIndexBuffer* vbuf);

	//
	void render();
	//
	void flush();
	//
	void flush2D();
	//
	void flush3D();
	//
private:
	//
	void _setupBuffers();
	//
	void _setupIndices();
	//
	void _setupVertices();
	//
	void _setupVBO();
	//
	void _setupVAOandVBO();

private:
	uint _vao;
	//0-vertex buffer 1-index buffer 
	uint _vboBuffers[2];

};


UC_END



#endif