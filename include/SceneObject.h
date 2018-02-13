#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#include "Geometry.h"
#include "BaseObject.h"

using namespace ngl;
class SceneObject : BaseObject
{
public :
  SceneObject()=default;
  SceneObject(Geometry* _geo)
  {m_geometry = _geo;}

  ~SceneObject();
  virtual void reset() override;
  void setGeometry(Geometry* _new);
private :
  Geometry* m_geometry;
};

#endif
