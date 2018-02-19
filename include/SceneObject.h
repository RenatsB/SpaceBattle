#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#include "DataContainer.h"
#include "BaseObject.h"

//using namespace ngl;
class SceneObject : BaseObject
{
public :
  SceneObject()=default;
  SceneObject(unsigned _geo)
  {m_geometry = _geo;}

  ~SceneObject();
  virtual void reset() override;
  void setGeometry(unsigned _new);
private :
  unsigned m_geometry;
};

#endif
