/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSPhysics.cpp

*/

#include <Classes/RSClasses.h>
#include <Physics/RSPhysics.h>
#include <btBulletDynamicsCommon.h>

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

    std::vector<PhysicsObject*> physObjects;

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

    Vector3 PhysicsSystem::GetRigidBodyPosition(int id)
    {
        btTransform trans = physObjects[id]->body->getWorldTransform();

        btVector3 origin = trans.getOrigin();

        return Vector3(origin.getX(), origin.getY(), origin.getZ());
    }

    Vector3 PhysicsSystem::GetRigidBodyRotation(int id)
    {
        btTransform trans = physObjects[id]->body->getWorldTransform();

        btQuaternion rotation = trans.getRotation();
        Vector3 newVec;

        rotation.getEulerZYX(newVec.Z, newVec.Y, newVec.X);

        // probably wrong multiplier
        newVec.Z *= 90;
        newVec.Y *= 90;
        newVec.X *= 90;

        return newVec;
    }

    void PhysicsSystem::SetRigidBodyPosition(int, Vector3)
    {
    }

    void PhysicsSystem::SetRigidBodyRotation(int, Vector3)
    {
    }

    void PhysicsSystem::addRigidBody(std::shared_ptr<Instance> bp)
    {
        std::shared_ptr<BasePart> bpConv = std::reinterpret_pointer_cast<BasePart>(bp);

        btCollisionShape* shape = new btBoxShape(btVector3(bpConv->Size.X/2, bpConv->Size.Y/2, bpConv->Size.Z/2));
        collisionShapes.push_back(shape);

        btTransform tTransform;
        tTransform.setIdentity();
        tTransform.setOrigin(btVector3(bpConv->Position.X, bpConv->Position.Y, bpConv->Position.Z));

        btScalar mass;

        if (bpConv->PhysicsEnabled) {
            mass = (1.f);
        }
        else {
            mass = (0.);
        }
        
        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            shape->calculateLocalInertia(mass, localInertia);

        //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(tTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);

        //add the body to the dynamics world
        dynamicsWorld->addRigidBody(body);

        int PhysicsID = physObjects.size();

        PhysicsObject* newPhysObject = new PhysicsObject;
        newPhysObject->body = body;
        newPhysObject->phyInstance = bp;
        newPhysObject->physicsID = PhysicsID;
        
        bpConv->physicsID = PhysicsID;

        physObjects.push_back(newPhysObject);
    }

} // namespace rs::Physics
