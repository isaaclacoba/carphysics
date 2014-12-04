// -*- coding:utf-8; tab-width:4; mode:cpp -*-
#include "motionstate.h"

MotionState::MotionState(const btTransform &initialPosition, Ogre::SceneNode *node){
  node_ = node;
  mInitialPosition_ = initialPosition;
}

void MotionState::setNode(Ogre::SceneNode *node) {
      node_ = node;
}

void MotionState::getWorldTransform(btTransform &worldTrans) const {
      worldTrans = mInitialPosition_;
}

void MotionState::setWorldTransform(const btTransform &worldTrans) {
  if(node_ == nullptr)
    return;

  btQuaternion rot = worldTrans.getRotation();
  node_ ->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
  btVector3 pos = worldTrans.getOrigin();
  node_->setPosition(pos.x(), pos.y(), pos.z());
}
