/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSPhysics.h

*/

#ifndef _RSPHYSICS_H_
#define _RSPHYSICS_H_

namespace rs::Physics {
    class PhysicsSystem {
    public:
        bool Initialize();
        void Update();
        void Shutdown();

        void EnableRigidBody(int, bool);

        // TODO: Position, we should change to a quanternion
        Vector3 GetRigidBodyPosition(int);
        Vector3 GetRigidBodyRotation(int);

        void SetRigidBodyPosition(int, Vector3);
        void SetRigidBodyRotation(int, Vector3);

        void SetRigidBodyVelocity(int, Vector3);

        void addRigidBody(std::shared_ptr<Instance>);
    };

    extern PhysicsSystem *g_RSPhysics;
} // namespace rs::Physics

#endif // _RSPHYSICS_H_
