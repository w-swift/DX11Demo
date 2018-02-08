#include "CubeMesh.h"

Vertex vertData[] =
{
	Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
	Vertex(-1.0f, +1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f),
	Vertex(+1.0f, +1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
	Vertex(+1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
	Vertex(-1.0f, -1.0f, +1.0f, 0.0f, 1.0f, 1.0f, 1.0f),
	Vertex(-1.0f, +1.0f, +1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
	Vertex(+1.0f, +1.0f, +1.0f, 1.0f, 0.0f, 1.0f, 1.0f),
	Vertex(+1.0f, -1.0f, +1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
};

DWORD indices[] = {
	// front face
	0, 1, 2,
	0, 2, 3,

	// back face
	4, 6, 5,
	4, 7, 6,

	// left face
	4, 5, 1,
	4, 1, 0,

	// right face
	3, 2, 6,
	3, 6, 7,

	// top face
	1, 5, 6,
	1, 6, 2,

	// bottom face
	4, 0, 3,
	4, 3, 7
};

CubeMesh::CubeMesh()
{
	m_local2World = XMMatrixIdentity();
}


CubeMesh::~CubeMesh()
{
	indexBuffer->Release();
	vertBuffer->Release();
}

void CubeMesh::Initialize(D3DCore * d3dCore)
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 8;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertData;
	d3dCore->d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertBuffer);

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * 12 * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexBufferData;
	indexBufferData.pSysMem = indices;
	d3dCore->d3d11Device->CreateBuffer(&indexBufferDesc, &indexBufferData, &indexBuffer);
}

void CubeMesh::SetTranslation(float offsetX, float offsetY, float offsetZ)
{
	m_local2World *= XMMatrixTranslation(offsetX, offsetY, offsetZ);
}

void CubeMesh::SetRotationWithAxis(XMVECTOR rotateAxis, float angle)
{
	m_local2World *= XMMatrixRotationAxis(rotateAxis, angle);
}

void CubeMesh::SetScale(float scaleX, float scaleY, float scaleZ)
{
	m_local2World *= XMMatrixScaling(scaleX, scaleY, scaleZ);
}

void CubeMesh::ResetLocal2WorldMatrix()
{
	m_local2World = XMMatrixIdentity();
}

