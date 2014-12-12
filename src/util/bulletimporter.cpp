// -*- coding:utf-8; tab-width:4; mode:cpp -*-
#include "bulletimporter.h"
#include <cstring>

BulletImporter::BulletImporter(btDiscreteDynamicsWorld* dynamicsWorld) {
  	file_loader_ = new btBulletWorldImporter(dynamicsWorld);
}

BulletImporter::~BulletImporter() {
  delete file_loader_;
}

bool
BulletImporter::load(std::string name){
  return file_loader_->loadFile(name.c_str());
}
