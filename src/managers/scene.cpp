// -*- coding:utf-8; tab-width:4; mode:cpp -*-
// Tinman author: Isaac Lacoba Molina
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

#include "scene.h"

Scene::Scene() {
  Ogre::LogManager* logMgr = OGRE_NEW Ogre::LogManager;
  logMgr->createLog("config/ogre.log", true, false, false);
  root_ = new Ogre::Root("config/plugins.cfg", "config/ogre.cfg", "");

  if (not root_->restoreConfig() )
    root_->showConfigDialog();

  window_ = root_->initialise(true, window_title);

  load_resources();

  sceneManager_ = root_->createSceneManager(Ogre::ST_GENERIC);

  create_camera(window_);

  create_light();

  ray_query_ = sceneManager_->createRayQuery(Ogre::Ray());
  ray_query_->setSortByDistance(true);
}

void
Scene::load_resources() {
    Ogre::ConfigFile cf;
  cf.load("config/resources.cfg");

  Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

  Ogre::String secName, typeName, archName;
  while (seci.hasMoreElements()) {
    secName = seci.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); ++i) {
      typeName = i->first;
      archName = i->second;
      Ogre::ResourceGroupManager::getSingleton()
        .addResourceLocation(archName, typeName, secName);
    }
  }

  Ogre::ResourceGroupManager::getSingleton()
    .initialiseAllResourceGroups();
}

Ogre::SceneNode*
Scene::create_node(std::string name) {
  return sceneManager_->createSceneNode(name);
}

Ogre::Entity*
Scene::create_entity(std::string mesh) {
  return sceneManager_->createEntity(mesh, mesh);
}

Ogre::Entity*
Scene::create_entity(std::string name, std::string mesh) {
  return sceneManager_->createEntity(name, mesh);
}


void
Scene::add_child(std::string parent, std::string child) {
  get_node(parent)->addChild(get_node(child));
}

void
Scene::remove_child(std::string parent, std::string child) {
  get_node(parent)->removeChild(child);
}

Ogre::SceneNode*
Scene::get_node(std::string node) {
  if(node == "")
    return sceneManager_->getRootSceneNode();
  else
    return sceneManager_->getSceneNode(node);
}

void
Scene::attach(Ogre::SceneNode* node, Ogre::Entity* entity) {
  node->attachObject(entity);
}

void
Scene::create_light() {
  sceneManager_->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
  sceneManager_->setAmbientLight(Ogre::ColourValue(4.0, 4.0, 4.0));
}

void
Scene::create_camera(Ogre::RenderWindow* window) {
  Ogre::SceneNode* camera_node = create_node("camera_node");
  add_child("", "camera_node");
  camera_ = sceneManager_->createCamera("PlayerCamera");
  camera_->setPosition(Ogre::Vector3(-60 , 60, -60));
  camera_->lookAt(Ogre::Vector3(0, 0, 0));
  camera_->setNearClipDistance(5);
  camera_->setFarClipDistance(300);

  Ogre::Viewport* viewport = window->addViewport(camera_);
  viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

  camera_->setAspectRatio(Ogre::Real(viewport->getActualWidth()) /
                          Ogre::Real(viewport->getActualHeight()));
  camera_node->attachObject(camera_);
}

Ogre::SceneNode*
Scene::create_ground(Ogre::Vector3 position, std::string name, std::string mesh) {
  Ogre::SceneNode* ground_node = create_node(name);
  ground_node->setPosition(position);
  add_child("", name);

  Ogre::Entity* ground_entity = create_entity(name, mesh);
  ground_node->attachObject(ground_entity);

  return ground_node;
}

void
Scene::render_one_frame(void) {
  Ogre::WindowEventUtilities::messagePump();
  root_->renderOneFrame();
  Ogre::Real actual_fps =  window_->getAverageFPS();
  std::cout << actual_fps << std::endl;
}

Ogre::Ray
Scene::set_ray_query(float x, float y) {
  Ogre::Ray ray = camera_->
    getCameraToViewportRay(x/float(window_->getWidth()), y/float(window_->getHeight()));

  ray_query_->setRay(ray);

  return ray;
}

void
Scene::destroy_all_attached_movable_objects(Ogre::SceneNode* i_pSceneNode ) {
  //from: http://www.ogre3d.org/forums/viewtopic.php?f=2&t=53647&start=0
  Ogre::SceneNode::ObjectIterator itObject =
    i_pSceneNode->getAttachedObjectIterator();
   while ( itObject.hasMoreElements() ) {
     Ogre::MovableObject* pObject = static_cast<Ogre::MovableObject*>(itObject.getNext());
      i_pSceneNode->getCreator()->destroyMovableObject( pObject );
   }

   Ogre::SceneNode::ChildNodeIterator itChild =
     i_pSceneNode->getChildIterator();
   while ( itChild.hasMoreElements() ) {
     Ogre::SceneNode* pChildNode = static_cast<Ogre::SceneNode*>(itChild.getNext());
      destroy_all_attached_movable_objects( pChildNode );
   }
}

void
Scene::destroy_node(std::string node) {
  sceneManager_->destroySceneNode(node);
}
