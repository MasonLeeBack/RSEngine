/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSPhysics.cpp

*/

#include <Classes/RSClasses.h>
#include <Physics/RSPhysics.h>
#include <btBulletDynamicsCommon.h>
#include <Types/RSArray.h>

namespace rs::Physics {
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;

    PhysicsSystem* g_RSPhysics;

    btAlignedObjectArray<btCollisionShape*> collisionShapes;

    typedef struct {
        std::shared_ptr<Instance> phyInstance;
        btRigidBody* body;
        int physicsID;
    } PhysicsObject;

    RSArray<PhysicsObject*> physObjects;

    bool PhysicsSystem::Initialize()
    {
        collisionConfiguration = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfiguration);
        overlappingPairCache = new btDbvtBroadphase();
        solver = new btSequentialImpulseConstraintSolver;
        dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

        return true;
    }

    void PhysicsSystem::Update()
    {
        dynamicsWorld->stepSimulation(1.f / 60.f, 10);
    }

    void PhysicsSystem::Shutdown()
    {
        for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
        {
            btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
            btRigidBody* body = btRigidBody::upcast(obj);
            if (body && body->getMotionState())
            {
                delete body->getMotionState();
            }
            dynamicsWorld->removeCollisionObject(obj);
            delete obj;
        }

        PhysicsObject* phyObj = new PhysicsObject;
        physObjects.push(phyObj);

        //delete dynamics world
        delete dynamicsWorld;

        //delete solver
        delete solver;

        //delete broadphase
        delete overlappingPairCache;

        //delete dispatcher
        delete dispatcher;

        delete collisionConfiguration;
    }

    void PhysicsSystem::EnableRigidBody(int id, bool physEnabled)
    {
        if (physEnabled) {
            physObjects.get(id)->body->setLinearFactor(btVector3(1, 1, 1));
            physObjects.get(id)->body->setAngularFactor(btVector3(1, 1, 1));
        } 
        else {
            physObjects.get(id)->body->setLinearFactor(btVector3(0, 0, 0));
            physObjects.get(id)->body->setAngularFactor(btVector3(0, 0, 0));
            physObjects.get(id)->body->setLinearVelocity(btVector3(0, 0, 0));
            physObjects.get(id)->body->setAngularVelocity(btVector3(0, 0, 0));
        }
    }

    Vector3 PhysicsSystem::GetRigidBodyPosition(int id)
    {
        btTransform trans = physObjects.get(id)->body->getWorldTransform();

        btVector3 origin = trans.getOrigin();

        return Vector3(origin.getX(), origin.getY(), origin.getZ());
    }

    Vector3 QuatToEuler(btQuaternion* quat) {
        double sqw = quat->w() * quat->w();
        double sqx = quat->x() * quat->x();
        double sqy = quat->y() * quat->y();
        double sqz = quat->z() * quat->z();

        return Vector3(
            (float)atan2l(2.0 * (quat->y() * quat->z() + quat->x() * quat->w()), (-sqx - sqy + sqz + sqw)),
            (float)asinl(-2.0 * (quat->x() * quat->z() - quat->y() * quat->w())),
            (float)atan2l(2.0 * (quat->x() * quat->y() + quat->z() * quat->w()), (sqx - sqy - sqz + sqw)));
    }

    Vector3 PhysicsSystem::GetRigidBodyRotation(int id)
    {
        btTransform trans = physObjects.get(id)->body->getWorldTransform();

        btQuaternion rotation = trans.getRotation();
        Vector3 newVec;

        btScalar ang = rotation.getAngle();

        // probably wrong multiplier
        newVec.Z *= 20;
        newVec.Y *= 20;
        newVec.X *= 20;

        return QuatToEuler(&rotation);
    }

    void PhysicsSystem::SetRigidBodyPosition(int id, Vector3 pos)
    {
        btTransform initTransform;

        initTransform.setOrigin(btVector3(pos.X, pos.Y, pos.Z));

        dynamicsWorld->removeRigidBody(physObjects.get(id)->body);

        physObjects.get(id)->body->setWorldTransform(initTransform);
        physObjects.get(id)->body->getMotionState()->setWorldTransform(initTransform);
        

        dynamicsWorld->addRigidBody(physObjects.get(id)->body);


        //

        //physObjects[id]->body->setAngularVelocity(btVector3(0, 0, 0));
        //physObjects[id]->body->setLinearVelocity(btVector3(0, 0, 0));
        //physObjects[id]->body->clearForces();
    }

    void PhysicsSystem::SetRigidBodyRotation(int, Vector3)
    {
    }

    void PhysicsSystem::SetRigidBodyVelocity(int id, Vector3 vel)
    {
        physObjects.get(id)->body->setLinearVelocity(btVector3(vel.X, vel.Y, vel.Z));
    }

    void PhysicsSystem::addRigidBody(std::shared_ptr<Instance> bp)
    {
        std::shared_ptr<BasePart> bpConv = std::reinterpret_pointer_cast<BasePart>(bp);

        btCollisionShape* shape = new btBoxShape(btVector3(bpConv->Size.X/2, bpConv->Size.Y/2, bpConv->Size.Z/2));
        collisionShapes.push_back(shape);

        btTransform tTransform;
        tTransform.setIdentity();
        tTransform.setOrigin(btVector3(bpConv->Position.X, bpConv->Position.Y, bpConv->Position.Z));

        btScalar mass = (1.f);
        
        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            shape->calculateLocalInertia(mass, localInertia);

        //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(tTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);

        body->forceActivationState(DISABLE_DEACTIVATION);

        if (!bpConv->PhysicsEnabled) {
            body->setLinearFactor(btVector3(0, 0, 0));
            body->setAngularFactor(btVector3(0, 0, 0));
        }

        //add the body to the dynamics world
        dynamicsWorld->addRigidBody(body);

        int PhysicsID = physObjects.size();

        PhysicsObject* newPhysObject = new PhysicsObject;
        newPhysObject->body = body;
        newPhysObject->phyInstance = bp;
        newPhysObject->physicsID = PhysicsID;
        
        bpConv->physicsID = PhysicsID;

        physObjects.push(newPhysObject);
    }

} // namespace rs::Physics
