#include "D3DCore.h"

D3DCore::D3DCore()
{
}


D3DCore::~D3DCore()
{
	swapChain->Release();
	d3d11Device->Release();
	d3d11DevCon->Release();
	renderTargetView->Release();
	depthStencilView->Release();
	depthStencilBuffer->Release();
}

bool D3DCore::InitializeDirect3d11App(HINSTANCE hInstance, Window* window)
{
	DXGI_MODE_DESC bufferDesc;

	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = window->GetWindowWidth();
	bufferDesc.Height = window->GetWindowHeight();
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = window->hwnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &d3d11Device, NULL, &d3d11DevCon);

	ID3D11Texture2D* BackBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

	d3d11Device->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView);
	BackBuffer->Release();

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = window->GetWindowWidth();
	depthStencilDesc.Height = window->GetWindowHeight();
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	d3d11Device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	d3d11Device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

	d3d11DevCon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	d3d11DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = window->GetWindowWidth();
	viewport.Height = window->GetWindowHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	d3d11DevCon->RSSetViewports(1, &viewport);

	return true;
}

void D3DCore::RefreshScene()
{
	float bgColor[4] = { (0.0f, 0.0f, 0.0f, 0.0f) };
	d3d11DevCon->ClearRenderTargetView(renderTargetView, bgColor);

	d3d11DevCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void D3DCore::DrawCube(ID3D11Buffer* vertBuffer, ID3D11Buffer* indexBuffer, ID3D11InputLayout* vertLayout,
	ID3D11VertexShader* vs, ID3D11PixelShader* ps, ID3D11Buffer* cbShaderInputBuffer)
{
	d3d11DevCon->VSSetShader(vs, 0, 0);
	d3d11DevCon->PSSetShader(ps, 0, 0);
	d3d11DevCon->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	d3d11DevCon->IASetVertexBuffers(0, 1, &vertBuffer, &stride, &offset);

	d3d11DevCon->IASetInputLayout(vertLayout);

	d3d11DevCon->VSSetConstantBuffers(0, 1, &cbShaderInputBuffer);

	d3d11DevCon->DrawIndexed(36, 0, 0);
}

void D3DCore::ShowScene()
{
	swapChain->Present(0, 0);
}
