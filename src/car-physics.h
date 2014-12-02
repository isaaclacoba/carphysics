#ifndef CAR-PHYSICS_H
#define CAR-PHYSICS_H
#include <btBulletDynamicsCommon.h>

class Physics {
  const btVector3 gravity_ = btVector3(0, -9.8, 0);

  btBroadphaseInterface* broadphase_;
  btSequentialImpulseConstraintSolver* solver_;
  btDefaultCollisionConfiguration* collisionConfiguration_;
  btCollisionDispatcher* dispatcher_;

  btDiscreteDynamicsWorld* dynamicsWorld_;


public:
  typedef std::shared_ptr<Physics> shared;

  Physics();
  btRigidBody* create_rigid_body(const btTransform &worldTransform,
         Ogre::SceneNode* node,btCollisionShape* shape, btScalar mass);
  btCollisionShape* create_shape(btVector3 halfExtent);

  void stepSimulation(Ogre::Real deltaT, int maxSubSteps);
};

public:
  Physics();
  virtual ~Physics();
};

class CarPhysics: public Physics {

public:
  CarPhysics();
  virtual ~CarPhysics();
};

#endif
