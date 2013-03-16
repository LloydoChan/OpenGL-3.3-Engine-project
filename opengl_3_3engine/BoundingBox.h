//BoundingBox.h
//LAST MODIFIED: 01/13/2013


#pragma once
#include "Includes.h"

using glm::vec3;

class BoundingBox
{
	public:
		BoundingBox(){};
		BoundingBox(vec3& min,vec3& max): m_min(min),m_max(max){};

		bool ContainsPoint(const vec3& point)const
		{
			return (point.x >= m_min.x && point.y >= m_min.y && 
				    point.z >= m_min.z && point.x <= m_max.x && 
					point.y <= m_max.y && point.z <= m_max.z);
		}

		void Add(const vec3& v)	{
			if(v.x > m_max.x)	m_max.x = v.x;
			if(v.x < m_min.x)	m_min.x = v.x;
			if(v.y > m_max.y)	m_max.y = v.y;
			if(v.y < m_min.y)	m_min.y = v.y;
			if(v.z > m_max.z)	m_max.z = v.z;
			if(v.z < m_min.z)	m_min.z = v.z;
		};

		void Add(const BoundingBox& bb)	{
			if(bb.m_max.x > m_max.x)	m_max.x = bb.m_max.x;
			if(bb.m_min.x < m_min.x)	m_min.x = bb.m_min.x;
			if(bb.m_max.y > m_max.y)	m_max.y = bb.m_max.y;
			if(bb.m_min.y < m_min.y)	m_min.y = bb.m_min.y;
			if(bb.m_max.z > m_max.z)	m_max.z = bb.m_max.z;
			if(bb.m_min.z < m_min.z)	m_min.z = bb.m_min.z;
		}

		void Translate(const vec3& v) {
			m_min += v;
			m_max += v;
		}

		inline vec3			GetCenter()const{return (m_min + m_max)/2.0f;}
		vec3				m_min;
		vec3				m_max;
};