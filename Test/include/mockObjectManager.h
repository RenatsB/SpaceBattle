#include "mockSceneObject.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <utility>
class mockObjectManager
{
public:
  mockObjectManager()=default;
  ~mockObjectManager()=default;
  void createObject(const std::string _name);
  void removeObject(const std::string _name);
  void removeObject(const size_t _id);
  void selectObject(const size_t _id);
  void selectObject(const std::string &_name);
  void selectObject(const std::vector<size_t> &_ids);
  void selectObject(const std::vector<std::string> &_names);
  void deselectObject(const size_t _id);
  void deselectObject(const std::string &_name);
  void deselectObject(const std::vector<size_t> &_ids);
  void deselectObject(const std::vector<std::string> &_names);
  bool isSelected(const size_t _id) const;
  bool isSelected(const std::string _name) const;
  void move(unsigned short _axis, float _val);
  void scale(unsigned short _axis, float _val);
  void rotate(unsigned short _axis, float _val);
  glm::vec3 constructTranslateVector(unsigned short _axis, float _val) const;
  void changeGeo(std::pair<size_t, std::string> _geo);
  void changeMat(std::pair<size_t, std::string> _mat);
  mockSceneObject* objectAt(size_t _pos) const;
  bool findObject(const size_t _id) const;
  bool findObject(const std::string &_name) const;
  mockSceneObject* getObject(size_t _id) const;
  mockSceneObject* getObject(std::string _name) const;
  size_t getObjectID(const std::string &_name) const;
  size_t getObjectCount() const;
  void checkObjectIDs();
  size_t getFreeID() const;
  std::vector<size_t> getCurrentIDs()const;
private:
  std::vector<std::unique_ptr<mockSceneObject>> m_sceneObjects;
  std::vector<size_t> m_selected;
};
