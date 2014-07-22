////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "GraphicsClass.h"


GraphicsClass::GraphicsClass()
	: m_Model(nullptr)
	, m_ColorShader(nullptr)
{
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	//Initialize the Direct3D oject
	bool result = m_D3D.Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Set the initial position of the camera.
	m_Camera.SetPosition(0.0f, 0.0f, -10.0f);

	// Create the model object.
	m_Model = std::make_unique<ModelClass>();
	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D.GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_ColorShader = std::make_unique<ColorShaderClass>();
	if (!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_D3D.GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		m_ColorShader.release();
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		m_Model.release();
	}

	// Release the Direct3D object.
	m_D3D.Shutdown();

	return;
}


bool GraphicsClass::Frame()
{
	// Render the graphics scene.
	bool result = Render();

	return result;
}


bool GraphicsClass::Render()
{
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D.BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera.Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	const XMMATRIX& viewMatrix = m_Camera.GetViewMatrix();
	const XMMATRIX& worldMatrix = m_D3D.GetWorldMatrix();
	const XMMATRIX& projectionMatrix = m_D3D.GetProjectionMatrix();

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D.GetDeviceContext());

	// Render the model using the color shader.
	result = m_ColorShader->Render(m_D3D.GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}
	
	// Present the rendered scene to the screen.
	m_D3D.EndScene();

	return true;
}