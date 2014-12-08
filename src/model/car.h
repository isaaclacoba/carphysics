#ifndef CAR_H
#define CAR_H
#include <OgreEntity.h>

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
  std::vector<Ogre::SceneNode*> wheels_nodes;
  std::vector<Ogre::Entity*> wheels_entities;

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
  const float    CUBE_HALF_EXTENTS = 1;
  const btScalar suspensionRestLength = btScalar(0.6);

  const btVector3 wheelDirectionCS0 = btVector3(0,-1,0);
  const btVector3 wheelAxleCS = btVector3(-1,0,0);

  float   gEngineForce = 0.f;
  float   gBreakingForce = 0.f;


public:
  Car();
  virtual ~Car();

  void initialize(Physics::shared physics, Scene::shared scene);
};

#endif
