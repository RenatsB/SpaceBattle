#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#include "DataContainer.h"
#include "BaseObject.h"
#include "GenericGeo.h"
#include "GenericMat.h"

class SceneObject : public BaseObject
{
public :
  SceneObject(std::string _name = "SceneObject", glm::vec3 _pos=glm::vec3(0,0,0), glm::vec3 _rot=glm::vec3(0,0,0), glm::vec3 _sc=glm::vec3(1,1,1), GenericGeo* _geo=new GenericGeo, GenericMat* _mat=new GenericMat):
    BaseObject(_name, _pos, _rot, _sc),
    m_geometry(_geo),
    m_material(_mat)
  {}

  ~SceneObject() override = default;
  virtual void reset() override;
  virtual void changeID(const size_t _newID) override;
  virtual size_t getID() const override;
  void setGeometry(size_t _new);
  size_t getGeo() const;
  size_t matFind() const;
  void setMat(size_t _new);
private :
  std::unique_ptr<GenericGeo> m_geometry;
  std::unique_ptr<GenericMat> m_material;
};

#endif
