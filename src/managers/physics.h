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

#ifndef PHYSICS_H
#define PHYSICS_H
#include "motionstate.h"

#include <memory>

#include <OgreSceneNode.h>
#include <btBulletDynamicsCommon.h>

class Physics {
  const btVector3 gravity_ = btVector3(0, -9.8, 0);

  btBroadphaseInterface* broadphase_;
  btSequentialImpulseConstraintSolver* solver_;
  btDefaultCollisionConfiguration* collisionConfiguration_;
  btCollisionDispatcher* dispatcher_;


 public:
  typedef std::shared_ptr<Physics> shared;
  btDiscreteDynamicsWorld* dynamicsWorld_;

  Physics();
  virtual ~Physics();
  btRigidBody* create_rigid_body(const btTransform &worldTransform,
                                 Ogre::SceneNode* node,
                                 btCollisionShape* shape,
                                 btScalar mass);
  btCollisionShape* create_shape(btVector3 halfExtent);

  void step_simulation(float deltaT, int maxSubSteps);
};

#endif
