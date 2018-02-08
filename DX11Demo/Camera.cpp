#include "Camera.h"

Camera::Camera(int width, int height)
{
	camPosition = XMVectorSet(0.0f, 3.0f, -8.0f, 0.0f);
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	
	m_camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);

	fovAngleY = 0.4f;
	aspectRatio = (FLOAT)width / height;
	nearZ = 1.f;
	farZ = 1000.f;

	m_camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);

	m_camProjection = XMMatrixPerspectiveFovLH(fovAngleY * PI, aspectRatio, nearZ, farZ);
}


Camera::~Camera()
{
}
