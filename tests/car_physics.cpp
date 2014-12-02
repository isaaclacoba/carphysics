// -*- coding:utf-8; tab-width:4; mode:cpp -*-
#include <bandit/bandit.h>

#include "car-physics.h"

using namespace bandit;

void
compare_vectors(btVector3 vector, btVector3 vector2) {
  Assert::That(vector.getX(),
               Is().EqualTo(vector2.getX()));
  Assert::That(vector.getY(),
               Is().EqualTo(vector2.getY()));
  Assert::That(vector.getZ(),
                         Is().EqualTo(vector2.getZ()));
}

go_bandit([] () {
    describe("car physics", []() {
        Car::shared car;

        before_each([&]() {
            car = std::make_shared<Car>();
          });

        it("has direction", [&]() {
            compare_vectors(car->direction_, btVector3(1, 0, 0));
          });

        it("has traction force in straight line", [&]() {
            btVector3 direction(1, 0, 0);
            float engine = 0;
            btVector3 f_traction = direction * engine;

            compare_vectors(car->traction_force_, f_traction);
          });

        it("has drag force applied to traction force", [&]() {
            btVector3 velocity(1, 0, 1);
            btScalar speed = std::sqrt(velocity.getX()*velocity.getX()+
                                 velocity.getZ()*velocity.getZ());
            const btScalar drag = 1.15f; //drag coefficient for a short cylinder(wheel)
            btVector3 drag_force = -drag * velocity * speed;

            compare_vectors(car->drag_force_, drag_force);
          });
      });
  });

int main(int argc, char *argv[]) {
  return bandit::run(argc, argv);
}
