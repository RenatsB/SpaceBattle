#include "MainScene.h"
#include "MaterialWireframe.h"
#include "MaterialPBR.h"
#include "MaterialPhong.h"
#include "MaterialFractal.h"
#include "MaterialEnvMap.h"

//-----------------------------------------------------------------------------------------------------
void MainScene::writeMeshAttributes(size_t _id)
{
  const auto& mesh = *m_drawData.instance()->findGeo(_id);

  using namespace MeshAttributes;
  for (const auto buff : {VERTEX, UV, NORMAL})
  {
    m_meshVBO.write(mesh.getAttribData(buff), buff);
  }
  m_meshVBO.setIndices(mesh.getIndicesData());
}
//-----------------------------------------------------------------------------------------------------
void MainScene::setAttributeBuffers()
{
  static constexpr int tupleSize[] = {3,2,3};
  auto prog = m_shaderLib->getCurrentShader();

  using namespace MeshAttributes;
  for (const auto buff : {VERTEX, UV, NORMAL})
  {
    prog->enableAttributeArray(buff);
    prog->setAttributeBuffer(buff, GL_FLOAT, m_meshVBO.offset(buff), tupleSize[buff]);
  }

}
//-----------------------------------------------------------------------------------------------------
void MainScene::initGeo()
{
  m_drawData.instance()->geoReserve(3);
  m_drawData.instance()->findGeo(0)->load("models/Grid.obj");
  m_drawData.instance()->findGeo(1)->load("models/cube.obj");
  m_drawData.instance()->findGeo(2)->load("models/Sphere.obj");
  // Create and bind our Vertex Array Object
  m_vao->create();
  m_vao->bind();
  // Create and bind our Vertex Buffer Object
  m_meshVBO.init();
  updateBuffer(0);
}
//-----------------------------------------------------------------------------------------------------
void MainScene::updateBuffer(size_t _id)
{
  makeCurrent();
  auto mesh = m_drawData.instance()->findGeo(_id);
  m_meshVBO.reset(
        sizeof(GLushort),
        mesh->getNIndicesData(),
        sizeof(GLfloat),
        mesh->getNVertData(),
        mesh->getNUVData(),
        mesh->getNNormData()
        );
  writeMeshAttributes(_id);
  setAttributeBuffers();
}
//-----------------------------------------------------------------------------------------------------
void MainScene::initMaterials()
{
  m_drawData.instance()->matReserve(6);
  m_drawData.instance()->matPut(new MaterialWireframe(m_camera, m_shaderLib, &m_matrices));
  m_drawData.instance()->matPut(new MaterialEnvMap(m_camera, m_shaderLib, &m_matrices));
  m_drawData.instance()->matPut(new MaterialPhong(m_camera, m_shaderLib, &m_matrices));
  m_drawData.instance()->matPut(new MaterialPBR(m_camera, m_shaderLib, &m_matrices, {0.5f, 0.0f, 0.0f}, 1.0f, 1.0f, 0.5f, 1.0f));
  m_drawData.instance()->matPut(new MaterialPBR(m_camera, m_shaderLib, &m_matrices, {0.1f, 0.2f, 0.5f}, 0.5f, 1.0f, 0.4f, 0.2f));
  m_drawData.instance()->matPut(new MaterialFractal(m_camera, m_shaderLib, &m_matrices));
  for (size_t i = 0; i < m_drawData.instance()->matSize(); ++i)
  {
    auto mat = m_drawData.instance()->findMat(i);
    auto name = m_shaderLib->loadShaderProg(mat->shaderFileName());
    mat->setShaderName(name);
    mat->apply();
  }
  m_drawData.instance()->findMat(0)->apply();
}

void MainScene::init()
{
  Scene::init();

  initMaterials();
  initGeo();

  // Scope the using declaration
  {
    using namespace SceneMatrices;
    m_matrices[MODEL_VIEW] = glm::translate(m_matrices[MODEL_VIEW], glm::vec3(0.0f, 0.0f, -2.0f));
  }
  createSceneObject("TEST");
}

//-----------------------------------------------------------------------------------------------------

void MainScene::renderScene()
{
  Scene::renderScene();

  // Scope the using declaration
  /*{
    using namespace SceneMatrices;
    m_matrices[MODEL_VIEW] = glm::rotate(m_matrices[MODEL_VIEW], glm::radians(-1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  }*/
  m_drawData.instance()->findMat(0)->update();
  m_meshVBO.use();
  updateBuffer(0);
  glDrawElements(GL_TRIANGLES, m_drawData.instance()->findGeo(0)->getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);
  //size_t bufferIt=1; //1 because 0 is reserved for the grid
  for(size_t i=0; i<m_sceneObjects.size(); ++i)
  {
    if(m_sceneObjects.at(i).isActive())
    {
      m_drawData.instance()->findMat(m_sceneObjects.at(i).findMat())->update();
      //++bufferIt;
      m_meshVBO.use();
      updateBuffer(i+1);
      //glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_bufferObjects.at(bufferIt).at(0))/3);
      glDrawElements(GL_TRIANGLES, m_drawData.instance()->findGeo(1+m_sceneObjects.at(i).getGeo())->getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);
    }
  }
  //glDrawElements(GL_TRIANGLES, m_drawData.findGeo(i+1).getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);
}
//-----------------------------------------------------------------------------------------------------

std::array<int, 4> MainScene::countAllSceneGeo() const
{
  std::array<int, 4> numData = {{0,0,0,0}};

  for(auto it = m_sceneObjects.begin(); it!=m_sceneObjects.end(); ++it)
  {
    size_t id = it->getGeo();
    numData[0]+=m_drawData.instance()->findGeo(id)->getNVertData();
    numData[1]+=m_drawData.instance()->findGeo(id)->getNNormData();
    numData[2]+=m_drawData.instance()->findGeo(id)->getNUVData();
    numData[3]+=m_drawData.instance()->findGeo(id)->getNIndicesData();
  }
  return numData;
}
//-----------------------------------------------------------------------------------------------------
void MainScene::createSceneObject(std::string _name, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _sc, size_t _geo, size_t _mat)
{
  m_sceneObjects.emplace_back(new SceneObject(_name, _pos, _rot, _sc, _geo, _mat));
}
