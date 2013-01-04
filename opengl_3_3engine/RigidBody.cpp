//RigidBody.cpp - 
//Last Updated 25/09/2012

#include "RigidBody.h"

using glm::vec3;
using glm::quat;


RigidBody::RigidBody(float mass,vec3& position,mat3x3& orientation): 
		             m_mass(mass),m_position(position),m_orientation(orientation),m_linearMomentum(vec3(0.0f,0.0f,0.0f)),
					 m_angularMomentum(vec3(0.0f,0.0f,0.0f))
{
	assert(m_mass > 0.0f && "mass is equal to or lower than zero in the constructor");
}

void RigidBody::Update(float dt)
{
	
	m_linearMomentum += m_force * dt;
	m_position += m_linearMomentum/m_mass * dt;

	//angular update

	m_angularMomentum += m_torque * dt;

	mat3x3 R(m_orientation);
	mat3x3 RT = glm::transpose(R);
	mat3x3 I = R * m_inverseInertiaTensor * RT;

	vec3 angularVelocity = I._inverse() * m_angularMomentum;


	float angle = sqrt(glm::dot(angularVelocity,angularVelocity)) * dt;
	R = (mat3x3)glm::rotate(glm::mat4x4(R),angle,glm::normalize(angularVelocity));

	m_orientation = R;
}

//takes a force and a contact point relative in local space,
//so if the force is gravity it should act on the center of mass (0,0,0) for these
//simple simulations
void RigidBody::ApplyForce(vec3& force,vec3& contactPoint)
{
	//force is dP/dt
	//so...

	m_force +=  force;


	//torque is force * distance to r so...
	m_torque += glm::cross(contactPoint-m_position,force);
	

	//use a numeric threshold - if the new values of force and/or
	//torque are under the threshold in any direction set that direction's
	//total to 0.0f
	float threshold = 0.0001f;
	for(int direction = 0; direction < 3; direction++)
	{
		if(m_force[direction] < threshold && m_force[direction] > -threshold) m_force[direction] = 0.0f;
		if(m_torque[direction] < threshold && m_torque[direction] > -threshold) m_torque[direction] = 0.0f;
	}

}