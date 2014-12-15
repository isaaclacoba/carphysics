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
//

#include "input.h"

EventListener::EventListener(Ogre::RenderWindow* window) {
  x = y = 0;
  exit_ = false;

  create_input_manager(window);

  keyboard_ = static_cast<OIS::Keyboard*>
    (inputManager_->createInputObject(OIS::OISKeyboard, true));
  mouse_ = static_cast<OIS::Mouse*>
    (inputManager_->createInputObject(OIS::OISMouse, true));

  keyboard_->setEventCallback(this);
  mouse_->setEventCallback(this);
  Ogre::WindowEventUtilities::addWindowEventListener(window, this);
}

void
EventListener::add_hook(EventListener::KeyEvents keystroke,
                        EventType type, std::function<void()> callback) {

  if(type == EventType::game
     && !game_triggers_[keystroke])
      game_triggers_[keystroke] = callback;
  else if(!menu_triggers_[keystroke]) {
      menu_triggers_[keystroke] = callback;
  }
}

void
EventListener::add_hook(MouseKey key,  std::function<void()> callback) {
    if(!mouse_triggers_[key])
      mouse_triggers_[key] = callback;
}

void
EventListener::capture(void) {
    keyboard_->capture();
    mouse_->capture();
}

void
EventListener::check_events(void) {
  if(mouse_triggers_[mouse_key_pressed_]) {
    mouse_triggers_[mouse_key_pressed_]();
    mouse_key_pressed_ =  std::make_pair(OIS::MB_Button7, false);
  }

  if(menu_triggers_[events_]){
    menu_triggers_[events_]();

  }

  if(game_triggers_[events_])
    game_triggers_[events_]();
  else
    events_.clear();


}

bool
EventListener::shutdown() {
    exit_ = true;
    return true;
}

void
EventListener::clear_hooks() {
  mouse_triggers_.clear();
}

bool
EventListener::keyPressed(const OIS::KeyEvent& arg) {
  remove_key_from_buffer(std::make_pair(arg.key, false));
  events_.push_back(std::make_pair(arg.key, true));
  return true;
}

bool
EventListener::keyReleased(const OIS::KeyEvent& arg) {
  remove_key_from_buffer(std::make_pair(arg.key, true));
  events_.push_back(std::make_pair(arg.key, false));
   return true;
}

bool
EventListener::mouseMoved(const OIS::MouseEvent& evt) {
    return true;
  }
bool
EventListener::mousePressed(const OIS::MouseEvent& evt,
                            OIS::MouseButtonID id) {
  x = evt.state.X.abs;
  y = evt.state.Y.abs;
  mouse_key_pressed_ = std::make_pair(id, true);
  return true;
}

bool
EventListener::mouseReleased(const OIS::MouseEvent& evt,
                             OIS::MouseButtonID id) {
  return true;
}

void
EventListener::windowClosed(Ogre::RenderWindow* window){
  exit_ = true;
}

void
EventListener::create_input_manager(Ogre::RenderWindow* window) {
  typedef std::pair<std::string, std::string> parameter;
    OIS::ParamList parameters;
    size_t xid = 0;

    window->getCustomAttribute("WINDOW", &xid);
    parameters.insert(parameter("WINDOW", std::to_string(xid)));
    parameters.insert(parameter("x11_mouse_grab", "false"));
    parameters.insert(parameter("x11_mouse_hide", "false"));
    parameters.insert(parameter("x11_keyboard_grab", "false"));
    parameters.insert(parameter("XAutoRepeatOn", "false"));

    inputManager_ = OIS::InputManager::createInputSystem(parameters);
}

void
EventListener::remove_key_from_buffer(KeyBoardKey event) {
    auto keyevent = find (events_.begin(), events_.end(), event);
    if(keyevent == events_.end())
      return;
    events_.erase(keyevent);
}
