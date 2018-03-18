#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

class mockSceneObject
{
public :
  mockSceneObject()=default;
  mockSceneObject(std::string _name = "SceneObject", glm::vec3 _pos=glm::vec3(0,0,0), glm::vec3 _rot=glm::vec3(0,0,0), glm::vec3 _sc=glm::vec3(1,1,1),
              std::pair<size_t, std::string>_geo = {1, "Mesh1"}, std::pair<size_t, std::string>_mat={0, "Material1"}):
    m_pos(_pos),
    m_rot(_rot),
    m_scale(_sc),
    m_name(_name),
    m_MVmatrix(1),
    m_geometry(_geo.first, _geo.second),
    m_material(_mat.first, _mat.second)
  {}
  mockSceneObject(std::string _name = "SceneObject", std::pair<size_t, std::string>_geo = {1, "Mesh1"}, std::pair<size_t, std::string>_mat={0, "Material1"}):
    m_pos(glm::vec3(0,0,0)),
    m_rot(glm::vec3(0,0,0)),
    m_scale(glm::vec3(1,1,1)),
    m_name(_name),
    m_MVmatrix(1),
    m_geometry(_geo.first, _geo.second),
    m_material(_mat.first, _mat.second)
  {}
  ~mockSceneObject()=default;
  void reset();
  void changeID (const size_t _newID);
  void setName(const std::string _new);
  std::string getName() const;
  void setParent(mockSceneObject* _new);
  mockSceneObject* getParent() const;
  void addChild(mockSceneObject* _new);
  void setChildren(std::vector<mockSceneObject*> _new);
  std::vector<mockSceneObject*> getChildren() const;
  void moveObject (const glm::vec3 _tr);
  void setPosition (const glm::vec3 _tr);
  void rotateObject (const glm::vec3 _rot);
  void setRotation (const glm::vec3 _rot);
  void scaleObject (const glm::vec3 _sc);
  void setScale (const glm::vec3 _sc);
  glm::vec3 getPosition () const;
  glm::vec3 getRotation () const;
  glm::vec3 getScale () const;
  size_t getID () const;
  void setActive(bool _new);
  bool isActive();
  void updateMatrix();
  glm::mat4 getMVmatrix() const;
  void setGeo(std::pair<size_t, std::string> &_new);
  void setMat(std::pair<size_t, std::string> &_new);
  size_t getGeoID() const;
  std::string getGeoName() const;
  size_t getMatID() const;
  std::string getMatName() const;
protected :
  glm::vec3 m_pos = glm::vec3(0,0,0);
  glm::vec3 m_rot = glm::vec3(0,0,0);
  glm::vec3 m_scale = glm::vec3(1,1,1);
  size_t m_id=0;
  mockSceneObject* m_parent = nullptr;
  std::vector<mockSceneObject*> m_children;
  std::string m_name = "SceneObject";
  bool m_isActive = true;
  glm::mat4 m_MVmatrix {1};
  std::pair<size_t, std::string> m_geometry = {1, "Mesh1"};
  std::pair<size_t, std::string> m_material = {1, "Material1"};
};
