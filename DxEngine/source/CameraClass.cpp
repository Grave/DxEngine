////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "CameraClass.h"

CameraClass::CameraClass()
	: m_position(XMFLOAT3(0, 0, 0))
	, m_rotation(XMFLOAT3(0, 0, 0))
{
}

CameraClass::CameraClass(const CameraClass& other)
{
}

CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
	return;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
	return;
}

XMFLOAT3 CameraClass::GetPosition() const
{
	return m_position;
}


XMFLOAT3 CameraClass::GetRotation() const
{
	return m_rotation;
}

void CameraClass::Render()
{
	/*
	The Render function uses the position and rotation of the camera to
	build and update the view matrix. We first setup our variables for up,
	position, rotation, and so forth. Then at the origin of the scene we
	first rotate the camera based on the x, y, and z rotation of the camera.
	Once it is properly rotated when then translate the camera to the position 
	in 3D space. With the correct values in the position, lookAt, and up we
	can then use the D3DXMatrixLookAtLH function to create the view matrix
	to represent the current camera rotation and translation.
	*/

	// Setup the vector that points upwards.
	XMFLOAT3 up(0, 1.f, 0);

	// Setup the position of the camera in the world.
	XMFLOAT3 lookAt(0, 0, 1.f);

	// Setup where the camera is looking by default.
	const XMFLOAT3& position = m_position;
	
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = XMConvertToRadians(m_rotation.x);
	yaw = XMConvertToRadians(m_rotation.y);
	roll = XMConvertToRadians(m_rotation.z);

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	XMVECTOR vLookAt = XMVector3TransformCoord(XMLoadFloat3(&lookAt), rotationMatrix);
	XMVECTOR vUp = XMVector3TransformCoord(XMLoadFloat3(&up), rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	XMVECTOR vPosition = XMLoadFloat3(&m_position);
	vLookAt = vPosition + vLookAt;

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(vPosition, vLookAt, vUp);

	return;
}

const XMMATRIX& CameraClass::GetViewMatrix() const
{
	return m_viewMatrix;
}
