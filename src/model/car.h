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

enum class Direction {right, left};
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

  const float    f_max_engine_ = 3000.f;
  const float    acceleration_ = 10;
  const float    deceleration_ = 10;
  const float    f_max_braking_ = 10.f;
  const float    steering_increment_ = 0.000003f;
  const float    steering_clamp_ = 0.3f;

  const float    gVehicleSteering = 0.f;
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


  bool accelerating_, braking_, turning_;

  float   f_engine_, f_braking_, steering_;

 public:
  typedef std::shared_ptr<Car> shared;

  Car();
  virtual ~Car();

  void initialize(Physics::shared physics, Scene::shared scene,
                  btVector3 position = btVector3(0,0 ,0));
  void accelerate();
  void stop_accelerating();
  void brake();
  void stop_braking();
  void turn(Direction direction);
  void stop_turning();

  void update();

 private:
  void init_graphic_bodies(Scene::shared scene);
  void init_physic_bodies(Physics::shared physics, btVector3 position);
  void init_raycast_car(Physics::shared physics);
  void add_graphic_wheel(Scene::shared scene, std::string name);
  void add_physic_wheel(bool is_front, btVector3 connection_point,
                        int wheel_index);
  void configure_wheels();

  void control_speed();
};

#endif
