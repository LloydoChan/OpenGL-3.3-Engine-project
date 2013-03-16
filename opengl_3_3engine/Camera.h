//camera.h - a simple 3d camera class that can rotate on the x and y axes. 
//This is done via altering the view up and right vectors, not by storing any rotation values
//TODO: Will replace this with a QUATERNION camera to allow 3d rotation with no Gimbal lock
//
//Last Modified: 11/1/2013
#pragma once

#include "Includes.h"
using glm::vec3;
using glm::mat4x4;


class Camera : public Uncopyable
{
	public:
		Camera(vec3& eyePoint,vec3& lookPoint,vec3& up,bool freeCam = true);
		~Camera(){};


		//accessors
		bool				IsFreeMoving()const {return m_freeCam;}
		const vec3&			GetPos()const {return m_pos;}
		const vec3&			GetViewDir()const {return m_viewVec;}
		const vec3&         GetLookPoint()const {return m_lookPoint;}
		const mat4x4&		GetCamMatrix()const {return m_cameraMatrix;}
		const mat4x4&       GetInvertedMatrix()const{return m_invertedCamMatrix;}
		float				GetXAngle()const{return m_xAngleRotation;}
		float				GetYAngle()const{return m_yAngleRotation;}

		void				Rebuild();
		void				CreateCamMatrix();
		void				CreateInvertedCam(float reflectionHeight);
		

		//modifiers
		void				Translate(vec3& newPoint);
		void				MoveForward(float amount);
		void				Strafe(float amount);
		void				RotateYaw(float amount);
		void				RotatePitch(float amount);
		void				ComboRotate(float amountX,float amountY);

	private:

		vec3				m_lookPoint; //position of point you're looking at
		vec3				m_pos; // position of the camera
		vec3				m_viewVec;
		vec3				m_upVec;   
		vec3				m_leftVec; 
		mat4x4				m_cameraMatrix; 
		mat4x4				m_invertedCamMatrix;
		bool				m_freeCam;   

		float               m_xAngleRotation;
		float				m_yAngleRotation;

};