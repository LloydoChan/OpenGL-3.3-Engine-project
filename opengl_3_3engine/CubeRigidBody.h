//CubeRigidBody.h - a scalable cube that inherits from the rigidbody class
#include "RigidBody.h"


class CubeRigidBody : public RigidBody
{
	public:
		CubeRigidBody(float mass,vec3& position,mat3x3& orientation,vec3& dimensions):m_Dimensions(dimensions),
			RigidBody(mass,position,orientation) 
			{
				m_inertiaTensor = (glm::boxInertia3(mass,dimensions));
				m_inverseInertiaTensor = m_inertiaTensor._inverse();
			};
		~CubeRigidBody(){};
	private:
		vec3 m_Dimensions;
};