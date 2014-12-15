#ifndef GAME_H
#define GAME_H
#include <memory>

#include "car.h"

#include "input.h"
#include "timer.h"
#include "meshstrider.h"

class Game {
  Timer timer_;
  Car::shared car_;

  Scene::shared scene_;
  EventListener::shared input_;
  Physics::shared physics_;


public:
  Game();
  virtual ~Game();

  void start();

private:
  void game_loop();
  void create_ground(Ogre::Vector3 position, std::string name);
  void create_car();
  void register_hooks();
};


#endif
