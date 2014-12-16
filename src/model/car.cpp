// -*- coding:utf-8; tab-width:4; mode:cpp -*-
// Copyright (C) 2014  ISAAC LACOBA MOLINA
// Tinman author: Isaac Lacoba Molina
//
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "car.h"

Car::Car() {
  accelerating_ = turning_ = false;
  f_engine_ = f_braking_ = steering_ = 0.f;
}

Car::~Car() {
  //delete collision shapes
  for (int j=0;j<m_collisionShapes.size();j++)
    {
      btCollisionShape* shape = m_collisionShapes[j];
      delete shape;
    }
}

void
Car::initialize(Physics::shared physics, Scene::shared scene, btVector3 position) {
  init_graphic_bodies(scene);
  init_physic_bodies(physics, position);

  init_raycast_car(physics);

  add_physic_wheel(true, btVector3(car_dimensions_.getX()-(0.3*wheelWidth),
                                   connectionHeight,
                                   car_dimensions_.getZ()-wheelRadius), 0);

  add_physic_wheel(true, btVector3(-car_dimensions_.getX()+(0.3*wheelWidth),
                                   connectionHeight,
                                   car_dimensions_.getZ()-wheelRadius), 1);


  add_physic_wheel(false, btVector3(-car_dimensions_.getX()+(0.3*wheelWidth),
                                    connectionHeight,
                                    -car_dimensions_.getZ()+wheelRadius), 2);

  add_physic_wheel(false, btVector3(car_dimensions_.getX()-(0.3*wheelWidth),
                                    connectionHeight,
                                    -car_dimensions_.getZ()+wheelRadius), 3);
  configure_wheels();
}

void
Car::init_graphic_bodies(Scene::shared scene) {
  chassis_node_ = scene->create_node("chassis_node");
  scene->add_child("", "chassis_node");
  chassis_entity_ = scene->create_entity("chassis_entity",
                                         "Frank_body.mesh");
  scene->attach(chassis_node_,chassis_entity_);

  for (int i = 0; i < 4; ++i) {
    add_graphic_wheel(scene, "wheel" + i);
  }
}

void
Car::init_physic_bodies(Physics::shared physics, btVector3 position) {
  btTransform tr;
  tr.setIdentity();

  btVector3 origin = btVector3(0,1,0);
  btCompoundShape* compound = physics->
    create_compound_shape(origin, physics->create_shape(car_dimensions_));
  m_collisionShapes.push_back(compound);

  tr.setOrigin(btVector3(0,0.f,0));

  m_carChassis =  physics->
    create_rigid_body(btTransform(btQuaternion(0, 0, 0, 1),
                                  position),
                      chassis_node_, compound, 800);
  m_carChassis->setDamping(0.2,0.2);
  m_carChassis->setActivationState(DISABLE_DEACTIVATION);
}

void
Car::init_raycast_car(Physics::shared physics) {
  m_vehicleRayCaster = new btDefaultVehicleRaycaster(physics->dynamics_world_);
  m_vehicle = new btRaycastVehicle(m_tuning, m_carChassis, m_vehicleRayCaster);

  physics->dynamics_world_->addVehicle(m_vehicle);
}

void
Car::add_graphic_wheel(Scene::shared scene, std::string name) {
  wheels_nodes_.push_back(scene->create_node(name));

  std::string parent = "chassis_node";
  scene->add_child(parent, name);

  std::string mesh = "Frank_wheel.mesh";
  wheels_entities_.push_back(scene->create_entity(name, mesh));

  scene->attach(wheels_nodes_.back(), wheels_entities_.back());
}

void
Car::add_physic_wheel(bool is_front, btVector3 connection_point, int wheel_index) {
  m_vehicle->addWheel(connection_point, wheelDirectionCS0,
                      wheelAxleCS,suspensionRestLength,wheelRadius,
                      m_tuning, is_front);
  wheels_nodes_[wheel_index]->translate(connection_point.getX(),
                              -connection_point.getY(),   connection_point.getZ());
}


void
Car::configure_wheels(){
  for (int i=0;i<m_vehicle->getNumWheels();i++) {
    btWheelInfo& wheel = m_vehicle->getWheelInfo(i);
    wheel.m_suspensionStiffness = suspensionStiffness;
    wheel.m_wheelsDampingRelaxation = suspensionDamping;
    wheel.m_wheelsDampingCompression = suspensionCompression;
    wheel.m_frictionSlip = wheelFriction;
    wheel.m_rollInfluence = rollInfluence;
  }
}

void
Car::control_speed() {
  if(!accelerating_ && !braking_)
    f_engine_ = (f_engine_ - f_braking_ <= 0) ? 0 : f_engine_ - deceleration_;
}


void
Car::accelerate() {
  accelerating_ = true;
  f_engine_ = (f_engine_ >= f_max_engine_) ? f_max_engine_: f_engine_ + acceleration_;
}

void
Car::stop_accelerating() {
  accelerating_ = false;
  f_braking_ = deceleration_;
}

void
Car::brake() {
  accelerating_ = false;
  braking_ = true;
  f_braking_ = f_max_braking_;
  f_engine_ = (f_engine_ <= f_max_engine_) ? -f_max_engine_: f_engine_ - acceleration_;
}

void
Car::stop_braking() {
  braking_ = false;
  f_braking_ = deceleration_;
}

void
Car::turn(Direction direction) {
  if(direction == Direction::right)
    steering_ = (steering_ < -steering_clamp_)?
      -steering_clamp_ : steering_ - steering_increment_;
  else
    steering_ = (steering_ > steering_clamp_)?
      steering_clamp_ : steering_ + steering_increment_;
}

void
Car::stop_turning() {
  steering_ = 0;
}

void
Car::update() {
  control_speed();
  m_vehicle->applyEngineForce(f_engine_, 0);
  m_vehicle->applyEngineForce(f_engine_, 1);

  m_vehicle->setSteeringValue(steering_, 0);
  m_vehicle->setSteeringValue(steering_, 1);
}
