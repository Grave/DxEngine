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

#include "LightShaderClass.h"
#include "LightClass.h"

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
	bool Render(float rotation);

private:
	D3DClass m_D3D;
	CameraClass m_Camera;
	std::unique_ptr<ModelClass> m_Model;

	std::unique_ptr<LightShaderClass> m_LightShader;
	std::unique_ptr<LightClass> m_Light;
};