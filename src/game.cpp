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
  Car car;
  car.initialize(physics_, scene_);
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
      physics_->stepSimulation(delta_time, 2);
      scene_->render_one_frame();
      delta_time = 0.f;
    }
  }
}
