//RigidBody.h - class for RigidBody type
#pragma once
#include <glm/glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\inertia.hpp>
#include <assert.h>

using glm::vec3;
using glm::quat;
using glm::mat3x3;


class RigidBody
{
	public:
		virtual ~RigidBody(){};
		const vec3&   GetLinearMomentum()const {return m_linearMomentum;}
		const vec3&   GetAngularMomentum()const {return m_angularMomentum;}
		const mat3x3& GetOrientation()const {return m_orientation;}
		const vec3&   GetPosition()const {return m_position;}
		const vec3&   GetTorque()const {return m_torque;}

		void SetAngularMomentum(const vec3& newMomentum) {m_angularMomentum = newMomentum;}
		void SetLinearMomentum(const vec3& newMomentum) {m_linearMomentum = newMomentum;}

		void Update(float dt);

		void ApplyForce(vec3& force,vec3& contactPoint);

protected:
		RigidBody(float mass,vec3& position,mat3x3& orientation);

		float m_mass;
		vec3 m_position;
		vec3 m_linearMomentum;
		vec3 m_angularMomentum;

		mat3x3 m_orientation;
		mat3x3 m_inertiaTensor;
		mat3x3 m_inverseInertiaTensor;

		vec3 m_force;
		vec3 m_torque;
};