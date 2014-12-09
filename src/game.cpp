// -*- coding:utf-8; tab-width:4; mode:cpp -*-
#include "game.h"

Game::Game() {
  scene_ = std::make_shared<Scene>();
  input_ = std::make_shared<EventListener>(scene_->window_);
  physics_ = std::make_shared<Physics>();
}

Game::~Game() {
}

void
Game::start() {
  create_ground();
  create_car();
  game_loop();
}

void
Game::game_loop() {
  float delta_time;

  while(!input_->exit_) {
    delta_time += timer_.get_delta_time();
    if(delta_time >= 0.017) {
      input_->capture();
      input_->check_events();
      physics_->step_simulation(delta_time, 2);
      scene_->render_one_frame();
      delta_time = 0.f;
    }
  }
}

void
Game::create_ground() {
  scene_->create_ground();
  Ogre::SceneNode* ground = scene_->get_node("ground");
  btCollisionShape* groundShape = new btBoxShape(btVector3(50,3,50));
  physics_->create_rigid_body(btTransform(btQuaternion(0, 0, 0, 1),
                                         btVector3(0, 1, 0)),
                             ground, groundShape, 0);
}
void
Game::create_car() {
  Car car;
  car.initialize(physics_, scene_);
}
