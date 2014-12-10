// -*- coding:utf-8; tab-width:4; mode:cpp -*-
#include "physics.h"

Physics::Physics() {
    btVector3 worldMin(-1000,-1000,-1000);
    btVector3 worldMax(1000,1000,1000);

    broadphase_ = new btAxisSweep3(worldMin,worldMax);

    solver_ = new btSequentialImpulseConstraintSolver();
    collisionConfiguration_ = new btDefaultCollisionConfiguration();
    dispatcher_ = new btCollisionDispatcher(collisionConfiguration_);

    dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher_,
                        broadphase_, solver_, collisionConfiguration_);
    dynamicsWorld_->setGravity(gravity_);
  }



Physics::~Physics() {
  delete dynamicsWorld_;
  delete dispatcher_;
  delete collisionConfiguration_;
  delete solver_;
  delete broadphase_;
}

btRigidBody*
Physics::create_rigid_body(const btTransform &worldTransform,
                  Ogre::SceneNode* node,
                  btCollisionShape* shape,
                  btScalar mass){
  btVector3 inertia(0 ,0 ,0);

  if(mass != 0)  shape->calculateLocalInertia(mass, inertia);

  MotionState* motionState = new MotionState(worldTransform, node);
  btRigidBody::btRigidBodyConstructionInfo
    rigidBodyCI(mass, motionState, shape, inertia);

  btRigidBody* rigidBody = new btRigidBody(rigidBodyCI);
  dynamicsWorld_->addRigidBody(rigidBody);

  return rigidBody;
}

btCollisionShape*
Physics::create_shape(btVector3 halfExtent){
  return new btBoxShape(halfExtent);
}

btCollisionShape*
Physics::create_compound_shape(btVector3 origin, btCollisionShape* child){
  btCompoundShape* compound = new btCompoundShape();
  btTransform localTrans;
  localTrans.setIdentity();
  localTrans.setOrigin(origin);

  compound->addChildShape(localTrans, child);
  return compound;
}


void
Physics::step_simulation(float deltaT, int maxSubSteps) {
  dynamicsWorld_->stepSimulation(deltaT, maxSubSteps);
}
