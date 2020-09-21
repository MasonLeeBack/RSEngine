/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: BasePart.cpp

*/

#include <Classes/BasePart.h>
#include <Physics/RSPhysics.h>
using namespace rs::Physics;


namespace rs {
	INITIALIZE_INSTANCE_SOURCE(BasePart);

	void BasePart::setPhysicsEnabled(bool phyEnabled)
	{
		PhysicsEnabled = phyEnabled;

		if (physicsID != 0)
		{
			g_RSPhysics->EnableRigidBody(physicsID, phyEnabled);
		}
	}

	void BasePart::setSize(Vector3 siz)
	{
		Size = siz;

		if (physicsID != 0)
		{
			//g_RSPhysics->SetRigidBodyPosition(physicsID, siz);
		}
	}

	void BasePart::setPosition(Vector3 pos)
	{
		Position = pos;

		if (physicsID != 0)
		{
			bool isPhysEnabled = PhysicsEnabled;
			if (isPhysEnabled)
				setPhysicsEnabled(false);

			g_RSPhysics->SetRigidBodyPosition(physicsID, pos);

			if (isPhysEnabled)
				setPhysicsEnabled(true);
		}
	}

	void BasePart::setRotation(Vector3 rot)
	{
		Rotation = rot;

		if (physicsID != 0)
		{
			g_RSPhysics->SetRigidBodyRotation(physicsID, rot);
		}
	}

	void BasePart::setVelocity(Vector3 vel)
	{
		Velocity = vel;

		if (physicsID != 0)
		{
			g_RSPhysics->SetRigidBodyVelocity(physicsID, vel);
		}
	}

	void BasePart::tick()
	{
		if (Name == "MyBasePlate") {
			//printf("am i ticking?");
		}
		
		if (physicsID != 0)
		{
			Position = g_RSPhysics->GetRigidBodyPosition(physicsID);
			Rotation = g_RSPhysics->GetRigidBodyRotation(physicsID);
		}

		tickChildren();
	}

} // namespace rs
