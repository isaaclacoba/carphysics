// Copyright (C) 2014  ISAAC LACOBA MOLINA
// Minesweeper author: Isaac Lacoba Molina
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

#ifndef INPUT_HPP
#define INPUT_HPP
#include <map>
#include <vector>
#include <memory>
#include <unistd.h>

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

enum class EventType{game_event, menu_event};
class EventListener: public Ogre::WindowEventListener,
                           public OIS::KeyListener,
                           public OIS::MouseListener {

  typedef OIS::MouseButtonID MouseKey;
  typedef OIS::KeyCode KeyBoardKey;

  OIS::InputManager* inputManager_;
  OIS::Mouse* mouse_;
  OIS::Keyboard* keyboard_;

  MouseKey mouse_key_pressed_, mouse_key_released_;

  std::map<MouseKey, std::function<void()>> mouse_triggers_;

 public:
  typedef std::shared_ptr<EventListener> shared;
  typedef std::vector<KeyBoardKey> KeyCodes;

  float x, y;
  bool exit_;

  EventListener(Ogre::RenderWindow* window);

  void capture(void);
  void check_events();

  void add_hook(MouseKey key,std::function<void()> callback);
  void add_hook(KeyCodes keystroke, EventType type, std::function<void()> callback);
  void clear_hooks();

  bool keyPressed(const OIS::KeyEvent& arg);
  bool keyReleased(const OIS::KeyEvent& arg);
  bool mouseMoved(const OIS::MouseEvent&  evt);
  bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
  bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);

  void windowClosed(Ogre::RenderWindow* window);

  bool shutdown(void);

 private:
  KeyCodes keys_pressed_, keys_released_;
  std::map<KeyCodes, std::function<void()>> game_triggers_, menu_triggers_;

  void create_input_manager(Ogre::RenderWindow* window);

};
#endif
