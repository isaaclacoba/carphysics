// -*- coding:utf-8; tab-width:4; mode:cpp -*-
#include "car-physics.h"

Physics::Physics() {

}


Physics::~Physics() {
  delete dynamicsWorld_;
  delete dispatcher_;
  delete collisionConfiguration_;
  delete solver_;
  delete broadphase_;
}

Physics::Physics() {
    btVector3 worldMin(-1000,-1000,-1000);
    btVector3 worldMax(1000,1000,1000);

    broadphase = new btAxisSweep3(worldMin,worldMax);

    solver = new btSequentialImpulseConstraintSolver();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
                        broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(gravity_);
  }

void
Physics::stepSimulation(Ogre::Real deltaT, int maxSubSteps) {
  dynamicsWorld->stepSimulation(deltaT, maxSubSteps);
}

CarPhysics::CarPhysics(): Physics() {

}

CarPhysics::~CarPhysics() {

}
