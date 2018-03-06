#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#include "DataContainer.h"
#include "BaseObject.h"

class SceneObject : public BaseObject
{
public :
  SceneObject()=default;
  SceneObject(size_t _geo)
  {m_geometry = _geo;}

  ~SceneObject();
  virtual void reset() override;
  virtual void changeID(const size_t _newID) override;
  virtual size_t getID() const override;
  void setGeometry(size_t _new);
  size_t getGeo() const;
  size_t findMat() const;
  void setMat(size_t _new);
private :
  size_t m_geometry;
  size_t m_material = 0;
};

#endif
