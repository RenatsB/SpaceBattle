#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#include "DataContainer.h"
#include "BaseObject.h"

class SceneObject : public BaseObject
{
public :
  SceneObject(std::string _name = "SceneObject", glm::vec3 _pos=glm::vec3(0,0,0), glm::vec3 _rot=glm::vec3(0,0,0), glm::vec3 _sc=glm::vec3(1,1,1),
              std::pair<size_t, std::string>_geo = {1, "Mesh1"}, std::pair<size_t, std::string>_mat={0, "Material1"}):
    BaseObject(_name, _pos, _rot, _sc),
    m_geometry(_geo.first, _geo.second),
    m_material(_mat.first, _mat.second)
  {}

  SceneObject(std::string _name = "SceneObject", std::pair<size_t, std::string>_geo = {1, "Mesh1"}, std::pair<size_t, std::string>_mat={0, "Material1"}):
    BaseObject(_name),
    m_geometry(_geo.first, _geo.second),
    m_material(_mat.first, _mat.second)
  {}

  ~SceneObject() override = default;
  virtual void reset() override;
  virtual void changeID(const size_t _newID) override;
  virtual size_t getID() const override;
  //void setGeo(size_t _new);
  //void setGeo(std::string _name);
  void setGeo(std::pair<size_t, std::string> &_new);
  //void setMat(size_t _new);
  //void setMat(std::string _name);
  void setMat(std::pair<size_t, std::string> &_new);
  size_t getGeoID() const;
  std::string getGeoName() const;
  size_t getMatID() const;
  std::string getMatName() const;
private :
  std::pair<size_t, std::string> m_geometry = {1, "Mesh1"};
  std::pair<size_t, std::string> m_material = {0, "Material1"};
};

#endif
