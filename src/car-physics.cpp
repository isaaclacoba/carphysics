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
  is_braking_ = false;
  delta_time = 0.00f;
  f_engine_ = 0;
  direction_ = btVector3(1, 0 ,0);
  f_traction_ = direction_ * f_engine_;
  f_braking_ = -direction_ * braking;

  initial_velocity_ = btVector3(0, 0, 0);
  speed_ = std::sqrt(initial_velocity_.getX()* initial_velocity_.getX()+
                     initial_velocity_.getZ()* initial_velocity_.getZ());
  f_drag_ = -drag_ * initial_velocity_ * speed_;
  f_rolling_resistance_ = -rolling_resistance_ * initial_velocity_;


  update_longitudinal_force();

  acceleration_ = f_longitudinal_ / mass_kg_;
  velocity_ = initial_velocity_ + acceleration_ * delta_time;
}

void
Car::update_longitudinal_force() {
  if(is_braking_)
    f_longitudinal_ = f_braking_ + f_drag_ + f_rolling_resistance_;
  else
    f_longitudinal_ = f_traction_ + f_drag_ + f_rolling_resistance_;
}

void
Car::brake() {
  is_braking_ = true;
  update_longitudinal_force();
}
Car::~Car() {

}
