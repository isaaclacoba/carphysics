#ifndef CAR_PHYSICS_H
#define CAR_PHYSICS_H
#include <memory>

#include <btBulletDynamicsCommon.h>


class Physics {
  const btVector3 gravity_ = btVector3(0, -9.8, 0);

  btBroadphaseInterface* broadphase_;
  btSequentialImpulseConstraintSolver* solver_;
  btDefaultCollisionConfiguration* collisionConfiguration_;
  btCollisionDispatcher* dispatcher_;

  btDiscreteDynamicsWorld* dynamicsWorld_;


public:
  Physics();
    virtual ~Physics();
  void stepSimulation(float deltaT, int maxSubSteps);
};


class Car: public Physics {
public:
  typedef std::shared_ptr<Car> shared;

  btScalar engine_force_;
  btVector3 direction_, traction_force_;


  Car();
  virtual ~Car();
};

#endif
