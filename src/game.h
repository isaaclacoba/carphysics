#ifndef GAME_H
#define GAME_H
#include <memory>

#include "car.h"

#include "input.h"
#include "timer.h"

class Game {
  Timer timer_;

  Scene::shared scene_;
  EventListener::shared input_;
  Physics::shared physics_;

public:
  Game();
  virtual ~Game();

  void start();

private:
  void game_loop();
  void create_ground();
  void create_car();
};


#endif
