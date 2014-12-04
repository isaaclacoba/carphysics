// Minesweeper author: Isaac Lacoba Molina
// Copyright (C) 2014  ISAAC LACOBA MOLINA
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

#ifndef SCENE_H
#define SCENE_H
#include <OgreRoot.h>
#include <OgreLogManager.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreConfigFile.h>
#include <OgreManualObject.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>

#include <memory>



class Scene {

  Ogre::Root* root_;
  Ogre::SceneManager* sceneManager_;

 public:
  typedef std::shared_ptr<Scene> shared;

  Ogre::RenderWindow* window_;
  Ogre::Camera* camera_;
  Ogre::RaySceneQuery* ray_query_;

  Scene();

  Ogre::SceneNode* create_node(std::string name);
  Ogre::Entity* create_entity(std::string mesh);
  Ogre::Entity* create_entity(std::string name, std::string mesh);
  void attach(Ogre::SceneNode* node, Ogre::Entity* entity);
  void add_child(std::string parent, std::string child);
  void remove_child(std::string parent, std::string child);
  void destroy_node(std::string);
  void destroy_all_attached_movable_objects(Ogre::SceneNode* node);

  void create_light(void);
  void create_camera(Ogre::RenderWindow* window);

  Ogre::SceneNode* get_node(std::string node);
  Ogre::SceneNode* create_ground(void);

  Ogre::Ray set_ray_query(float x, float y);

  void render_one_frame(void);

 private:
  void load_resources();
};


#endif
