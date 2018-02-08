#pragma once

#include "D3DCore.h"

static std::vector<char> ReadData(char const* filename);

struct cbShaderInputStruct
{
	XMMATRIX  WVP;
};

class CubeShader
{
public:
	CubeShader();
	~CubeShader();

	void Initiatilize(D3DCore* d3dCore);

	inline ID3D11VertexShader* GetVertexShader() const
	{
		return vs;
	}

	inline ID3D11PixelShader* GetPixelShader() const
	{
		return ps;
	}

	inline ID3D11InputLayout* GetVertLayout() const
	{
		return vertLayout;
	}

	inline ID3D11Buffer* GetShaderInputBuffer()
	{
		return cbShaderInputBuffer;
	}

public:
	cbShaderInputStruct cbShaderInputData;

private:
	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;
	ID3D11InputLayout* vertLayout;
	ID3D11Buffer* cbShaderInputBuffer;
};

