#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#include "Geometry.h"
#include "BaseObject.h"

using namespace ngl;
class SceneObject : BaseObject
{
public :
  SceneObject()=default;
  ~SceneObject();
  virtual void reset() override;
  virtual std::unique_ptr<BaseObject> clone() override;
  std::unique_ptr<BaseObject> instantiate(Vec3 _pos, Vec3 _rot=Vec3(0,0,0), Vec3 _sc=Vec3(1,1,1));
private :
  Geometry* m_geometry;

};

#endif
