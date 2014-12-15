// -*- coding:utf-8; tab-width:4; mode:cpp -*-
// Copyright (C) 2014  ISAAC LACOBA MOLINA
// Tinman author: Isaac Lacoba Molina
//
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
  create_ground(Ogre::Vector3(0,0,0), "ground1");
  create_ground(Ogre::Vector3(0,0,20), "ground2");
  create_ground(Ogre::Vector3(20,0,0), "ground3");
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
Game::create_ground(Ogre::Vector3 position, std::string name) {
  scene_->create_ground(position, name);

  Ogre::Entity* ground_entity = static_cast<Ogre::Entity*>
    (scene_->get_node(name)->getAttachedObject(0));
  MeshStrider* strider = new MeshStrider(ground_entity->getMesh().get());

  btCollisionShape* ground_shape = new btBvhTriangleMeshShape(strider,true,true);
  btRigidBody* plane_body = physics_->
    create_rigid_body(btTransform(btQuaternion(0, 0, 0, 1),
                                  btVector3(position.x, position.y + 1, position.z)),
                      scene_->get_node(name),
                      ground_shape, 0);

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
  input_->add_hook({std::make_pair(OIS::KC_D, false)}, EventType::menu,
                   std::bind(&Car::stop_turning, car_));

  input_->add_hook({std::make_pair(OIS::KC_A, true)}, EventType::game,
                   std::bind(&Car::turn, car_, Direction::left));
  input_->add_hook({std::make_pair(OIS::KC_A, false)}, EventType::menu,
                   std::bind(&Car::stop_turning, car_));
}
