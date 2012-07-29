//Camera.cpp - implementation
//last update 17/07/2012

#include "Camera.h"

namespace OpenGL_3_3Engine
{
	Camera::Camera(const vec3& eyePoint,const vec3& lookPoint)
	{
		m_eyePoint  = eyePoint;
		m_lookPoint = lookPoint;
		m_lookVec = glm::normalize(lookPoint-eyePoint);

		m_xRotation = 180.0f;
		m_yRotation = 270.0f;
		m_zRotation = 0.0f;

		m_pointRotation = 0.0f;

		m_rightVec = glm::normalize(glm::cross(m_lookVec,vec3(0.0f,1.0f,0.0f)));
		m_upVec    = glm::normalize(glm::cross(m_rightVec,m_lookVec));

		m_viewMatrix = glm::lookAt(m_eyePoint,m_lookPoint,m_upVec);
	}

	void Camera::Translate(const vec3& translation)
	{
		m_eyePoint += translation;
		m_lookPoint += translation;
		m_viewMatrix = glm::lookAt(m_eyePoint,m_lookPoint,m_upVec);
	}

	void Camera::TranslateKeepFocus(const vec3& translation)
	{
		m_eyePoint += translation;
		m_viewMatrix = glm::lookAt(m_eyePoint,m_lookPoint,m_upVec);
	}

	void Camera::RotateX(float angle)
	{
		m_xRotation += angle;

		if(m_xRotation > 360.0f)
			m_xRotation -= 360.0f;

		if(m_xRotation < 0.0f)
			m_xRotation += 360.0f;

		m_lookVec.y = glm::sin(glm::radians(m_xRotation));
		m_lookVec.z = glm::cos(glm::radians(m_xRotation));

		float length = glm::length(m_lookPoint - m_eyePoint);
		m_lookPoint = m_eyePoint + (m_lookVec * length);

		m_upVec = glm::cross(m_rightVec,m_lookVec);
		m_viewMatrix = glm::lookAt(m_eyePoint,m_lookPoint,m_upVec);
	}

	void Camera::RotateY(float angle)
	{
		m_yRotation += angle;

		if(m_yRotation > 360.0f)
			m_yRotation -= 360.0f;

		if(m_yRotation < 0.0f)
			m_yRotation += 360.0f;

		m_lookVec.x = glm::cos(glm::radians(m_yRotation));
		m_lookVec.z = glm::sin(glm::radians(m_yRotation));

		m_lookPoint = m_eyePoint + m_lookVec;

		m_rightVec   = glm::cross(m_lookVec,m_upVec);
		m_viewMatrix = glm::lookAt(m_eyePoint,m_lookPoint,m_upVec);
	}

	void Camera::RotateZ(float angle)
	{
		m_zRotation += angle;

		if(m_zRotation > 360.0f)
			m_zRotation -= 360.0f;

		if(m_zRotation < 0.0f)
			m_zRotation += 360.0f;

		m_upVec.x = glm::cos(glm::radians(m_zRotation));
		m_upVec.y = glm::sin(glm::radians(m_zRotation));

		m_viewMatrix = glm::lookAt(m_eyePoint,m_lookPoint,m_upVec);
		//UpdateViewMatrix();
	}

	void Camera::RotateAroundFocus(float angle)
	{
		m_pointRotation += angle;

		if(m_pointRotation > 360.0f)
			m_pointRotation -= 360.0f;

		if(m_pointRotation < 0.0f)
			m_pointRotation += 360.0f;


		float magnitude = glm::length(m_lookPoint - m_eyePoint);
		m_eyePoint.x = magnitude * glm::cos(glm::radians(m_pointRotation));
		m_eyePoint.z = magnitude * glm::sin(glm::radians(m_pointRotation));

		m_lookVec  = glm::normalize(m_lookPoint - m_eyePoint);
		m_rightVec = glm::cross(m_lookVec,m_upVec);

		m_viewMatrix = glm::lookAt(m_eyePoint,m_lookPoint,m_upVec);
	}

	void Camera::MoveForward(float distance)
	{
		m_eyePoint  += distance * m_lookVec;
		m_lookPoint += distance * m_lookVec;
		m_viewMatrix = glm::lookAt(m_eyePoint,m_lookPoint,m_upVec);
	}

	void Camera::Strafe(float distance)
	{
		m_eyePoint  += distance * m_rightVec;
		m_lookPoint += distance * m_rightVec;
		m_viewMatrix = glm::lookAt(m_eyePoint,m_lookPoint,m_upVec);
	}


	void Camera::UpdateViewDir()
	{
		
		m_lookVec = m_lookPoint - m_eyePoint;

	}

	void Camera::UpdateViewMatrix()
	{
		m_rightVec = glm::normalize(glm::cross(vec3(0.0f,1.0f,0.0f),m_lookVec));
		m_upVec    = glm::normalize(glm::cross(m_rightVec,m_lookVec));

		m_viewMatrix = glm::lookAt(m_eyePoint,m_lookPoint,m_upVec);
	}

	void Camera::Reset()
	{
		m_upVec    = vec3(0.0f,1.0f,0.0f);
		m_rightVec = vec3(1.0f,0.0f,0.0f);
		m_lookVec  = vec3(0.0f,0.0f,1.0f);

		m_viewMatrix = glm::lookAt(m_eyePoint,m_lookPoint,m_upVec);
	}

}