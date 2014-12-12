#ifndef BULLETIMPORTER_H
#define BULLETIMPORTER_H
#include <memory>

#include <btBulletDynamicsCommon.h>
#include <BulletWorldImporter/btBulletWorldImporter.h>

class BulletImporter {
  btBulletWorldImporter* file_loader_;

public:
  typedef std::shared_ptr<BulletImporter> shared;

  BulletImporter(btDiscreteDynamicsWorld* dynamicsWorld);
  virtual ~BulletImporter();

  bool load(std::string file);
};

#endif
