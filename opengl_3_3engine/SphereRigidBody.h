//SphereRigidBody.h - header for a sphere rigid body, inherits from RigidBody
#include "RigidBody.h"

class SphereRigidBody: public RigidBody
{
	public:
		SphereRigidBody(float mass,vec3& position,mat3x3& orientation,float radius):
			RigidBody(mass,position,orientation), m_Radius(radius)
			{
				m_inertiaTensor = (glm::sphereInertia3(mass,radius));
				m_inverseInertiaTensor = m_inertiaTensor._inverse();
			};
			~SphereRigidBody(){};
	private:
		float m_Radius;
};