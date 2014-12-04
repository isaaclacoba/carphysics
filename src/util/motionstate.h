#ifndef MOTIONSTATE_H
#define MOTIONSTATE_H
#include <OgreSceneNode.h>
#include <btBulletDynamicsCommon.h>


class MotionState: public btMotionState {
  Ogre::SceneNode* node_;
  btTransform mInitialPosition_;

public:
  MotionState(const btTransform &initialPosition, Ogre::SceneNode *node);
  void setNode(Ogre::SceneNode *node);
  virtual void getWorldTransform(btTransform &worldTrans) const;
  virtual void setWorldTransform(const btTransform &worldTrans);
};

#endif
