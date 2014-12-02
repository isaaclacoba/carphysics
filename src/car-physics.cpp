// -*- coding:utf-8; tab-width:4; mode:cpp -*-
#include "car-physics.h"


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


void
Physics::stepSimulation(float deltaT, int maxSubSteps) {
  dynamicsWorld_->stepSimulation(deltaT, maxSubSteps);
}

Car::Car(): Physics() {
  f_engine_ = 0;
  direction_ = btVector3(1, 0 ,0);
  f_traction_ = direction_ * f_engine_;

  velocity_ = btVector3(1, 0, 1);
  speed_ = std::sqrt(velocity_.getX()*velocity_.getX()+
                     velocity_.getZ()*velocity_.getZ());
  f_drag_ = -drag_ * velocity_ * speed_;
  f_rolling_resistance_ = -rolling_resistance_ * velocity_;
}

Car::~Car() {

}
