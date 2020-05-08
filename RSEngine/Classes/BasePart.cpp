/*

RSEngine
Copyright (c) 2019 Mason Lee Back

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

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
			g_RSPhysics->SetRigidBodyPosition(physicsID, pos);
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
			//g_RSPhysics->SetRigidBodyPosition(physicsID, siz);
		}
	}

	void BasePart::tick()
	{
		if (physicsID != 0 && PhysicsEnabled == true)
		{
			Position = g_RSPhysics->GetRigidBodyPosition(physicsID);
			Rotation = g_RSPhysics->GetRigidBodyRotation(physicsID);
		}

		tickChildren();
	}

} // namespace rs
