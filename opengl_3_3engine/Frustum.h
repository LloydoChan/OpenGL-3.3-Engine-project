//Frustum.h - a class that implements a 3d viewing frustum for culling
//LAST MODIFIED 01/13/2013

#pragma once
#include "Includes.h"
#include "BoundingBox.h"


const float EPSILON = 0.0f;

using glm::mat4x4;
using glm::vec4;

const int INTERSECTING = 1;

class Frustum
{
	public:
		static Frustum* GetInstance();
		const vec3&     GetEyePos()const{return m_pos;}
		const mat4x4&   GetProjectionMatrix()const{return m_projMatrix;}
		const mat4x4&   GetModelViewMatrix()const{return m_modView ;}

		void			Extract(const vec3& eyePoint,const mat4x4& camMatrix,const mat4x4& projMatrix);
		bool			TestPoint(const vec3& point)const;
		bool 			TestSphere(const vec3& point,float radius)const;
		bool			TestBox(const BoundingBox& box)const;
		bool			CheckCube(const vec3& point,float radius);
		bool			CheckRect(const vec3& point,float radius);
		void			DrawFrustum(const mat4x4& view,const mat4x4& proj);

	private:
		void			NormalizePlane(int index);

		Frustum(){};
		~Frustum(){};

		mat4x4			m_modView;
		mat4x4			m_projMatrix;
		vec4			m_planes[6];
		vec3			m_pos;

		static Frustum* m_instance;
};

inline void  Frustum::NormalizePlane(int index){
	float normFactor = m_planes[index][0] * m_planes[index][0] + m_planes[index][1] * m_planes[index][1] + 
		               m_planes[index][2] * m_planes[index][2];
	normFactor = sqrtf(normFactor);
	m_planes[index] /= normFactor;

}