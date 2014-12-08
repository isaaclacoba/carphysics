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
  btTransform tr;
  tr.setIdentity();

  Ogre::SceneNode* ground = scene->create_node("ground_node");
  Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

  Ogre::MeshManager::getSingleton().
    createPlane("ground",
                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                plane,200,200,1,1,true,1,20,20, Ogre::Vector3::UNIT_Z);
  Ogre::Entity* ground_entity = scene->create_entity("ground");
  ground_entity->setMaterialName("Ground");
  scene->attach(ground, ground_entity);


  btCollisionShape* groundShape = new btBoxShape(btVector3(50,3,50));
  physics->create_rigid_body(btTransform(btQuaternion(0, 0, 0, 1),btVector3(0, 1, 0)),
                             ground, groundShape, 0);

   btCollisionShape* chassisShape = new btBoxShape(btVector3(1.f,0.5f,2.f));
   m_collisionShapes.push_back(chassisShape);


   btCompoundShape* compound = new btCompoundShape();
   m_collisionShapes.push_back(compound);
   btTransform localTrans;
   localTrans.setIdentity();
   //localTrans effectively shifts the center of mass with respect to the chassis
   localTrans.setOrigin(btVector3(0,1,0));
   compound->addChildShape(localTrans,chassisShape);

   tr.setOrigin(btVector3(0,0.f,0));
   chassis_node_ = scene->create_node("chassis_node");
   chassis_entity_ = scene->create_entity("chassis_entity",
                                          "Frank_body.mesh");

  m_carChassis =  physics->
    create_rigid_body(btTransform(btQuaternion(0, 0, 0, 1),
                                  btVector3(0, 1, 0)),
                      chassis_node_, compound, 800);
   m_carChassis->setDamping(0.2,0.2);

   m_wheelShape = new btCylinderShapeX(btVector3(wheelWidth,wheelRadius,wheelRadius));
   bool isFrontWheel = true;
   btVector3 connectionPointCS0(CUBE_HALF_EXTENTS-(0.3*wheelWidth),
                                connectionHeight,2*CUBE_HALF_EXTENTS-wheelRadius);
   m_vehicle->addWheel(connectionPointCS0, wheelDirectionCS0,
                       wheelAxleCS,suspensionRestLength,wheelRadius,
                       m_tuning, isFrontWheel);

   connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS+(0.3*wheelWidth),connectionHeight,
                                  2*CUBE_HALF_EXTENTS-wheelRadius);
   m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,
                       suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);

   connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS+(0.3*wheelWidth),connectionHeight,
                                  -2*CUBE_HALF_EXTENTS+wheelRadius);
    isFrontWheel = false;
    m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,
                        suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);

    connectionPointCS0 = btVector3(CUBE_HALF_EXTENTS-(0.3*wheelWidth),connectionHeight,
                                   -2*CUBE_HALF_EXTENTS+wheelRadius);
    m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,
                        suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);

    for (int i=0;i<m_vehicle->getNumWheels();i++) {
      btWheelInfo& wheel = m_vehicle->getWheelInfo(i);
      wheel.m_suspensionStiffness = suspensionStiffness;
      wheel.m_wheelsDampingRelaxation = suspensionDamping;
      wheel.m_wheelsDampingCompression = suspensionCompression;
      wheel.m_frictionSlip = wheelFriction;
      wheel.m_rollInfluence = rollInfluence;
    }

}