// -*- coding:utf-8; tab-width:4; mode:cpp -*-
#include <bandit/bandit.h>
#include "ironman.h"

using namespace bandit;

go_bandit([] () {
    describe("car physics", []() {
        CarPhysics physics;

        before_each([&]() {
            physics = CarPhysics();
          });

        if("has direction", [&]() {
            Assert::That(physics.direction,
                         Is().EqualTo(btVector(1, 0, 0)));
          });


        it("has traction force", [&]() {

          });
      });
  });

int main(int argc, char *argv[]) {
  return bandit::run(argc, argv);
}
