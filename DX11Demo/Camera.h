#pragma once

#include"D3DCore.h"

#ifndef PI
#define PI 3.14
#endif


class Camera
{
public:
	explicit Camera(int width, int height);
	~Camera();

	inline XMMATRIX GetVPMatrix() const
	{
		return m_camView * m_camProjection;
	}

private:
	XMVECTOR camPosition;
	XMVECTOR camTarget;
	XMVECTOR camUp;

	FLOAT fovAngleY;
	FLOAT aspectRatio;
	FLOAT nearZ;
	FLOAT farZ;

	XMMATRIX m_camView;
	XMMATRIX m_camProjection;
};

