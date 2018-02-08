#include "CubeShader.h"


D3D11_INPUT_ELEMENT_DESC cbShaderInputLayoutDesc[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};
UINT numElements = ARRAYSIZE(cbShaderInputLayoutDesc);

CubeShader::CubeShader()
{
	cbShaderInputData.WVP = XMMatrixIdentity();
}


CubeShader::~CubeShader()
{
	vs->Release();
	ps->Release();
	vertLayout->Release();
	cbShaderInputBuffer->Release();
}

void CubeShader::Initiatilize(D3DCore* d3dCore)
{
	//Compile Shaders from shader file
	auto VS_Buffer = ReadData("VertexShader.cso");
	auto PS_Buffer = ReadData("PixelShader.cso");

	//Create the Shader Objects
	d3dCore->d3d11Device->CreateVertexShader(VS_Buffer.data(), VS_Buffer.size(), NULL, &vs);
	d3dCore->d3d11Device->CreatePixelShader(PS_Buffer.data(), PS_Buffer.size(), NULL, &ps);

	d3dCore->d3d11Device->CreateInputLayout(cbShaderInputLayoutDesc, numElements, VS_Buffer.data(),
		VS_Buffer.size(), &vertLayout);

	D3D11_BUFFER_DESC cbShaderInputBufferDesc;
	ZeroMemory(&cbShaderInputBufferDesc, sizeof(D3D11_BUFFER_DESC));

	cbShaderInputBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	cbShaderInputBufferDesc.ByteWidth = sizeof(cbShaderInputData);
	cbShaderInputBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbShaderInputBufferDesc.CPUAccessFlags = 0;
	cbShaderInputBufferDesc.MiscFlags = 0;

	d3dCore->d3d11Device->CreateBuffer(&cbShaderInputBufferDesc, NULL, &cbShaderInputBuffer);
}

static std::vector<char> ReadData(char const* filename)
{
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char>  result(pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	return result;
}