#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#include "DataContainer.h"
#include "BaseObject.h"

class SceneObject : BaseObject
{
public :
  SceneObject()=default;
  SceneObject(unsigned _geo)
  {m_geometry = _geo;}

  ~SceneObject();
  virtual void reset() override;
  virtual void changeID(const unsigned _newID) override;
  virtual unsigned getID() const override;
  void setGeometry(unsigned _new);
  unsigned getGeo() const;
private :
  unsigned m_geometry;
};

#endif
