//Camera.h - camera class!
//last update: 17/07/2012
#pragma once
#include "Includes.h"

namespace OpenGL_3_3Engine
{
	using glm::vec3;
	using glm::mat4;

	class Camera
	{
		public:
			Camera(const vec3& eyePoint,const vec3& lookPoint);

			void Translate(const vec3& translation);
			void TranslateKeepFocus(const vec3& translation);

			void RotateX(float angle);
			void RotateY(float angle);
			void RotateZ(float angle);

			void RotateAroundFocus(float angle);

			void MoveForward(float distance);
			void Strafe(float distance);

			void Reset();

			const mat4& GetMatrix()const {return m_viewMatrix;}

		private:
			void UpdateViewDir();
			void UpdateViewMatrix();

			vec3 m_eyePoint;
			vec3 m_lookVec;
			vec3 m_upVec;
			vec3 m_rightVec;
			vec3 m_lookPoint;

			float m_xRotation;
			float m_yRotation;
			float m_zRotation;

			float m_pointRotation;

			mat4 m_viewMatrix;
	};
};