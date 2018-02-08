#pragma once

#include "D3DCore.h"

class CubeMesh
{
public:
	CubeMesh();
	~CubeMesh();

	void Initialize(D3DCore* d3dCore);

	void SetTranslation(float offsetX, float offsetY, float offsetZ);
	void SetRotationWithAxis(XMVECTOR rotateAxis, float angle);
	void SetScale(float scaleX, float scaleY, float scaleZ);

	void ResetLocal2WorldMatrix();

	inline ID3D11Buffer* GetVertBuffer() const
	{
		return vertBuffer;
	}

	inline ID3D11Buffer* GetIndexBuffer() const
	{
		return indexBuffer;
	}

	inline XMMATRIX GetLocal2WorldMatrix() const
	{
		return m_local2World;
	}

private:
	ID3D11Buffer* vertBuffer;
	ID3D11Buffer* indexBuffer;

	XMMATRIX m_local2World;
};

