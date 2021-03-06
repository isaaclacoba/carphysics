#ifndef CAR_PHYSICS_H
#define CAR_PHYSICS_H
#include <memory>
#include <cmath>

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
  const btScalar mass_kg_ = 1000;
  const btScalar drag_ = 1.15f; //drag coefficient for a short cylinder(wheel)
  const btScalar rolling_resistance_ = 30 * drag_; //approximately
  bool is_braking_;
  btScalar delta_time;
public:
  typedef std::shared_ptr<Car> shared;
  const btScalar f_max_engine_ = 300;

  btScalar f_engine_, speed_;
  btVector3 direction_, initial_velocity_,velocity_,
    f_traction_, f_drag_, f_rolling_resistance_,
    f_longitudinal_, f_braking_, acceleration_;

  Car();
  virtual ~Car();

  void update_longitudinal_force();
  void brake();
 private:
  const btScalar braking = (f_max_engine_) / 2;
};

#endif
