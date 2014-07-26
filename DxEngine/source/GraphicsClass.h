////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "stdafx.h"

#include "D3DClass.h"
#include "CameraClass.h"
#include "ModelClass.h"
#include "ColorShaderClass.h"

#include "TextureShaderClass.h"

/**
 * Class name: GraphicsClass
*/
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:
	D3DClass m_D3D;
	CameraClass m_Camera;
	std::unique_ptr<ModelClass> m_Model;
	std::unique_ptr<TextureShaderClass> m_TextureShader;
};