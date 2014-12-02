// -*- coding:utf-8; tab-width:4; mode:cpp -*-
//all formulas are taken from:
// http://www.asawicki.info/Mirror/Car%20Physics%20for%20Games/Car%20Physics%20for%20Games.html

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

            compare_vectors(car->f_traction_, f_traction);
          });

        it("has drag force applied to traction force", [&]() {
            btVector3 velocity(1, 0, 1);
            btScalar speed = std::sqrt(velocity.getX()*velocity.getX()+
                                 velocity.getZ()*velocity.getZ());
            const btScalar drag = 1.15f; //drag coefficient for a short cylinder(wheel)
            btVector3 f_drag = -drag * velocity * speed;

            compare_vectors(car->f_drag_, f_drag);
          });

        it("has rolling resistance becouse of wheels", [&]() {
            const btScalar drag = 1.15f;
            const btScalar rolling_resistance = 30 * drag;
            btVector3 velocity(1, 0, 1);

            btVector3 f_rolling_resistance = -rolling_resistance * velocity;

            compare_vectors(car->f_rolling_resistance_, f_rolling_resistance);
          });

        it("longitudinal force are equal to sum of these three above forces", [&] () {
            btVector3 direction(1, 0, 0);
            float engine = 0;
            btVector3 f_traction = direction * engine;

            btVector3 velocity(1, 0, 1);
            btScalar speed = std::sqrt(velocity.getX()*velocity.getX()+
                                 velocity.getZ()*velocity.getZ());
            const btScalar drag = 1.15f; //drag coefficient for a short cylinder(wheel)
            btVector3 f_drag = -drag * velocity * speed;

            const btScalar rolling_resistance = 30 * drag;
            btVector3 f_rolling_resistance = -rolling_resistance * velocity;

            btVector3 f_longitudinal = f_traction + f_drag + f_rolling_resistance;

            compare_vectors(car->f_longitudinal_, f_longitudinal);

          });
      });
  });

int main(int argc, char *argv[]) {
  return bandit::run(argc, argv);
}
