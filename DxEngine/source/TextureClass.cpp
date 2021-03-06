////////////////////////////////////////////////////////////////////////////////
// Filename: TextureClass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "TextureClass.h"
#include "DDSTextureLoader.h"

TextureClass::TextureClass()
	: m_texture(nullptr)
{
}

TextureClass::TextureClass(const TextureClass& other)
{
}


TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;
	
	// Load the texture in.
	result = CreateDDSTextureFromFile(device, filename, nullptr, &m_texture);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void TextureClass::Shutdown()
{
	// Release the texture resource.
	if (m_texture)
	{
		m_texture->Release();
		m_texture = nullptr;
	}

	return;
}

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}
