// Copyright (C) 2014  ISAAC LACOBA MOLINA
// Minesweeper author: Isaac Lacoba Molina
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
#ifndef CAR_H
#define CAR_H
#include "physics.h"
#include "scene.h"


class Car {
  btRigidBody* m_carChassis;
  btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

  btRaycastVehicle::btVehicleTuning       m_tuning;
  btVehicleRaycaster*     m_vehicleRayCaster;
  btRaycastVehicle*       m_vehicle;
  btCollisionShape*       m_wheelShape;
  Ogre::SceneNode* chassis_node_;
  Ogre::Entity* chassis_entity_;
  std::vector<Ogre::SceneNode*> wheels_nodes_;
  std::vector<Ogre::Entity*> wheels_entities_;

  const int rightIndex = 0;
  const int upIndex = 1;
  const int forwardIndex = 2;

  const float   maxEngineForce = 1000.f;
  const float   maxBreakingForce = 100.f;

  const float    gVehicleSteering = 0.f;
  const float    steeringIncrement = 0.04f;
  const float    steeringClamp = 0.3f;
  const float    wheelRadius = 0.5f;
  const float    wheelWidth = 0.4f;
  const float    wheelFriction = 1000;//BT_LARGE_FLOAT;
  const float    suspensionStiffness = 20.f;
  const float    suspensionDamping = 2.3f;
  const float    suspensionCompression = 4.4f;
  const float    rollInfluence = 0.1f;//1.0f;
  const float    connectionHeight = 0.7f;
  const btVector3 car_dimensions_ = btVector3(1, 0.5f, 2);
  const btScalar suspensionRestLength = btScalar(0.6);

  const btVector3 wheelDirectionCS0 = btVector3(0,-1,0);
  const btVector3 wheelAxleCS = btVector3(-1,0,0);

  float   gEngineForce = 0.f;
  float   gBreakingForce = 0.f;


 public:
  typedef std::shared_ptr<Car> shared;

  Car();
  virtual ~Car();

  void initialize(Physics::shared physics, Scene::shared scene);

 private:
  void init_graphic_bodies(Scene::shared scene);
  void init_physic_bodies(Physics::shared physics);
  void init_raycast_car(Physics::shared physics);
  void add_graphic_wheel(Scene::shared scene, std::string name);
  void add_physic_wheel(bool is_front, btVector3 connection_point);
  void configure_wheels();

};

#endif
