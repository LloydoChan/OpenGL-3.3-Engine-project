//Camera.cpp
//Last modified: 22/01/2013

#include "Camera.h"
#include "Frustum.h"

Camera::Camera(vec3& eyePoint,vec3& lookPoint,vec3& up,bool freeCam):
               m_pos(eyePoint),m_lookPoint(lookPoint),m_upVec(up),m_freeCam(freeCam){
    m_xAngleRotation	=	3.0f;
	m_yAngleRotation	=	PI/2;

	Rebuild();}

void Camera::Rebuild(){
	
	if(m_freeCam){
		m_viewVec.x = cosf(m_xAngleRotation) * sinf(m_yAngleRotation);
		m_viewVec.y = cosf(m_yAngleRotation);
		m_viewVec.z = sinf(m_xAngleRotation) * sinf(m_yAngleRotation);
		m_lookPoint = m_pos + m_viewVec;
		m_leftVec = glm::cross(m_upVec, m_viewVec);
		m_leftVec = glm::normalize(m_leftVec);
	}else{
		m_viewVec = m_lookPoint - m_pos;
		m_viewVec = glm::normalize(m_viewVec);
		m_leftVec = glm::cross(m_upVec, m_viewVec);
		m_leftVec = glm::normalize(m_leftVec);
	}

}

void  Camera::CreateCamMatrix(){

	m_cameraMatrix = glm::lookAt(m_pos,m_lookPoint,m_upVec);

	//Frustum::GetInstance()->Extract(m_pos,m_cameraMatrix);
}

void  Camera::CreateInvertedCam(float reflectionHeight){

	vec3 newPos  = m_pos;
	vec3 newLook = m_lookPoint;
	vec3 newUp   = -m_upVec;

	newPos.y = 2.0f * reflectionHeight - m_pos.y;
	newLook.y = 2.0f * reflectionHeight - m_lookPoint.y;

	m_invertedCamMatrix = glm::lookAt(newPos,newLook,newUp);
}

void Camera::Translate(vec3& amount){
	m_pos += amount;
	Rebuild();}

void Camera::RotateYaw(float amount){
	m_xAngleRotation += glm::radians(amount);

	if(m_xAngleRotation < 0.0f) m_xAngleRotation += 2 * PI;
	if(m_xAngleRotation > 2* PI) m_xAngleRotation -= 2 * PI;

	Rebuild();
}

void Camera::RotatePitch(float amount){

	m_yAngleRotation += glm::radians(amount);

	if(m_yAngleRotation < -PI * 0.125 || m_yAngleRotation > PI * 0.125) 
		m_yAngleRotation -= amount ;

	Rebuild();
}

void Camera::ComboRotate(float amountX,float amountY){
	m_xAngleRotation += glm::radians(amountX);
	m_yAngleRotation += glm::radians(amountY);

	if(m_xAngleRotation < 0.0f) m_xAngleRotation += 2 * PI;

	if(m_xAngleRotation > 2* PI) m_xAngleRotation -= 2 * PI;

	if(m_yAngleRotation < -PI  || m_yAngleRotation > PI ) 
		m_yAngleRotation -= glm::radians(amountY); 

	Rebuild();
}

void	Camera::MoveForward(float amount){
	m_pos += m_viewVec * amount;
	Rebuild();
}

void	Camera::Strafe(float amount){
	m_pos += m_viewVec * amount;
	Rebuild();
}



