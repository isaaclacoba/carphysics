// -*- coding:utf-8; tab-width:4; mode:cpp -*-
#include "car.h"

Car::Car() {

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
Car::initialize(Physics::shared physics, Scene::shared scene) {
  init_graphic_bodies(scene);
  init_physic_bodies(physics);

  init_raycast_car(physics);

  m_wheelShape = new btCylinderShapeX(btVector3(wheelWidth,wheelRadius,wheelRadius));

  add_wheel(true, btVector3(CUBE_HALF_EXTENTS-(0.3*wheelWidth), connectionHeight,
                            2*CUBE_HALF_EXTENTS-wheelRadius));

  add_wheel(true, btVector3(-CUBE_HALF_EXTENTS+(0.3*wheelWidth), connectionHeight,
                            2*CUBE_HALF_EXTENTS-wheelRadius));


  add_wheel(false, btVector3(-CUBE_HALF_EXTENTS+(0.3*wheelWidth), connectionHeight,
                             -2*CUBE_HALF_EXTENTS+wheelRadius));

  add_wheel(false, btVector3(CUBE_HALF_EXTENTS-(0.3*wheelWidth),connectionHeight,
                             -2*CUBE_HALF_EXTENTS+wheelRadius));
  configure_wheels();
}

void
Car::init_graphic_bodies(Scene::shared scene) {
  chassis_node_ = scene->create_node("chassis_node");
  chassis_entity_ = scene->create_entity("chassis_entity",
                                         "Frank_body.mesh");
}

void
Car::init_physic_bodies(Physics::shared physics) {
  btTransform tr;
  tr.setIdentity();

  btCollisionShape* chassisShape = new btBoxShape(btVector3(1.f,0.5f,2.f));
  btCompoundShape* compound = new btCompoundShape();
  m_collisionShapes.push_back(compound);
  btTransform localTrans;
  localTrans.setIdentity();
  //localTrans effectively shifts the center of mass with respect to the chassis
  localTrans.setOrigin(btVector3(0,1,0));
  compound->addChildShape(localTrans, chassisShape);

  tr.setOrigin(btVector3(0,0.f,0));
  m_carChassis =  physics->
    create_rigid_body(btTransform(btQuaternion(0, 0, 0, 1),
                                  btVector3(0, 1, 0)),
                      chassis_node_, compound, 800);
  m_carChassis->setDamping(0.2,0.2);
  m_carChassis->setActivationState(DISABLE_DEACTIVATION);

}

void
Car::init_raycast_car(Physics::shared physics) {
  m_vehicleRayCaster = new btDefaultVehicleRaycaster(physics->dynamicsWorld_);
  m_vehicle = new btRaycastVehicle(m_tuning, m_carChassis, m_vehicleRayCaster);

  physics->dynamicsWorld_->addVehicle(m_vehicle);
}

void
Car::add_wheel(bool is_front, btVector3 connection_point) {
  m_vehicle->addWheel(connection_point, wheelDirectionCS0,
                      wheelAxleCS,suspensionRestLength,wheelRadius,
                      m_tuning, is_front);
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
