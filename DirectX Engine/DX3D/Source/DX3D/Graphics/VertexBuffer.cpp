#include <DX3D/Graphics/VertexBuffer.h>

dx3d::VertexBuffer::VertexBuffer(const VertexBufferDesc& desc,const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc),m_vertexSize(desc.vertexSize)
{
	// ---------------------- Validate Args -------------------------
	if (!desc.vertexList) DX3DLogThrowInvalidArg("No vertext list provided")
	if (!desc.vertexListSize) DX3DLogThrowInvalidArg("No vertext list size must be non-zero")
	if (!desc.vertexSize) DX3DLogThrowInvalidArg("No vertext size must be non-zero")


	// ---------------- Create buffer desc ---------------------------
	D3D11_BUFFER_DESC buffDesc{};
	
	buffDesc.ByteWidth = desc.vertexListSize * desc.vertexSize ; // size of buffer in bytes 
	// note : vertexSize is size of single vertex in bytes and vertexListSize is number of vertices

	buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; 
	//  tells D3D11 device that this buffer is to be used as a vertex buffer


	// --------------- create buffer intialization desc -----------------
	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = desc.vertexList; 
	// pointer to vertex data to initialize the buffer with

	// --------------- create vertex buffer using device -------------------
	DX3DGraphicsLogThrowOnFail( m_device.CreateBuffer(
		&buffDesc,
		&initData,
		&m_buffer // output parameter 
		),"CreateBuffer Failed");
}
