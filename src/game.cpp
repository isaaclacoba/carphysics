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

  register_hooks();
  game_loop();
}

void
Game::game_loop() {
  float delta_time;

  while(!input_->exit_) {
    delta_time += timer_.get_delta_time();
    input_->capture();
    input_->check_events();
    if(delta_time >= 0.017) {
      car_->update();
      physics_->step_simulation(delta_time, 2);
        scene_->render_one_frame();
        delta_time = 0.f;
    }
  }
}

void
Game::create_ground() {
  scene_->create_ground();

  btCollisionShape* groundShape = physics_->create_shape(btVector3(50, 1, 50));
  btRigidBody* plane_body = physics_->create_rigid_body(btTransform(btQuaternion(0, 0, 0, 1),
                                         btVector3(0, 1, 0)),
                              scene_->get_node("ground"), groundShape, 0);
  plane_body->setRestitution(0.2);
  plane_body->setFriction(0.5f);
}

void
Game::create_car() {
  car_ = std::make_shared<Car>();
  car_->initialize(physics_, scene_);
}

void
Game::register_hooks() {
  input_->add_hook({std::make_pair(OIS::KC_ESCAPE, true)}, EventType::menu,
                   std::bind(&EventListener::shutdown, input_));
  input_->add_hook({std::make_pair(OIS::KC_W, true)}, EventType::game,
                   std::bind(&Car::accelerate, car_));
 input_->add_hook({std::make_pair(OIS::KC_W, false)}, EventType::menu,
                   std::bind(&Car::stop_accelerating, car_));
  input_->add_hook({std::make_pair(OIS::KC_S, true)}, EventType::game,
                     std::bind(&Car::brake, car_));
  input_->add_hook({std::make_pair(OIS::KC_S, false)}, EventType::menu,
                   std::bind(&Car::stop_braking, car_));
  input_->add_hook({std::make_pair(OIS::KC_D, true)}, EventType::game,
                   std::bind(&Car::turn, car_, Direction::right));
  input_->add_hook({std::make_pair(OIS::KC_A, true)}, EventType::game,
                   std::bind(&Car::turn, car_, Direction::left));
  input_->add_hook({std::make_pair(OIS::KC_D, false)}, EventType::game,
                   std::bind(&Car::stop_turning, car_));
  input_->add_hook({std::make_pair(OIS::KC_A, false)}, EventType::game,
                   std::bind(&Car::stop_turning, car_));
}
