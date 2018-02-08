#pragma once

#include "Window.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>
#include <vector>

using namespace DirectX;

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z,
		float cr, float cg, float cb, float ca)
		: pos(x, y, z), color(cr, cg, cb, ca) {}

	XMFLOAT3 pos;
	XMFLOAT4 color;
};

class D3DCore
{
public:
	D3DCore();
	~D3DCore();

	bool InitializeDirect3d11App(HINSTANCE hInstance, Window* window);

	void RefreshScene();

	void DrawCube(ID3D11Buffer* vertBuffer, ID3D11Buffer* indexBuffer, ID3D11InputLayout* vertLayout,
		ID3D11VertexShader* vs, ID3D11PixelShader* ps, ID3D11Buffer* cbShaderInputBuffer);

	void ShowScene();

public:
	ID3D11Device* d3d11Device;
	ID3D11DeviceContext* d3d11DevCon;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11DepthStencilView* depthStencilView;

private:
	IDXGISwapChain* swapChain;
	ID3D11Texture2D* depthStencilBuffer;
};

