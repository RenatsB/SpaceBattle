#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "Scene.h"
#include <unordered_set>
#include "SceneObject.h"
#include "MaterialPBR.h"
#include "MaterialPhong.h"
#include "ShaderLib.h"
#include "DataContainer.h"

struct SOHasher
{
  size_t
  operator()(const SceneObject & obj) const
  {
    return std::hash<unsigned>()(obj.getID());
  }
};

// Custom comparator that compares the string objects by length
struct SOComparator
{
  bool
  operator()(const SceneObject & obj1, const SceneObject & obj2) const
  {
    if (obj1.getID() == obj2.getID())
      return true;
    return false;
  }
};

class MainScene : public Scene
{
  Q_OBJECT
public:
  //-----------------------------------------------------------------------------------------------------
  /// @brief Constructor for DemoScene.
  /// @param [io] io_camera the camera used to view the scene.
  /// @param [io] io_shaderLib the shader library to store and retrieve our shaders.
  /// @param [io] io_parent the parent window to create the GL context in.
  //-----------------------------------------------------------------------------------------------------
  MainScene(
     const std::shared_ptr<Camera> &io_camera,
     const std::shared_ptr<ShaderLib> &io_shaderLib,
     QWidget *_parent
     ) :
   Scene(io_camera, _parent),
   m_shaderLib(io_shaderLib.get())
  {}
  //-----------------------------------------------------------------------------------------------------
  /// @brief Default copy constructor.
  //-----------------------------------------------------------------------------------------------------
  MainScene(const MainScene&) = default;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Default copy assignment operator.
  //-----------------------------------------------------------------------------------------------------
  MainScene& operator=(const MainScene&) = default;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Default move constructor.
  //-----------------------------------------------------------------------------------------------------
  MainScene(MainScene&&) = default;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Default move assignment operator.
  //-----------------------------------------------------------------------------------------------------
  MainScene& operator=(MainScene&&) = default;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Default destructor.
  //-----------------------------------------------------------------------------------------------------
  ~MainScene() override = default;
  virtual void init() override;

public slots:

private:
  void loadMesh(unsigned _id);
  void loadAllMeshData();
  std::array<int, 3> countAllSceneGeo() const;
  virtual void renderScene() override;
  void makeGrid(float s);
  void generateGridGeo();
  void updateGridSize(unsigned _new);

private:
  ShaderLib* m_shaderLib;
  DataContainer m_drawData;
  size_t m_currentMaterial = 0;
  Buffer m_buffer;
  std::vector<std::array<int, 3>> m_bufferObjects;
  unsigned m_gridSize = 28;
  std::array<glm::vec3, 784> m_gridArray;

  std::unordered_set<SceneObject, SOHasher, SOComparator> m_sceneObjects;

};

#endif // MAINSCENE_H
