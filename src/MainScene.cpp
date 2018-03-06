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
  //generateNewGeometry();
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
//-----------------------------------------------------------------------------------------------------
/*void MainScene::keyPress(QKeyEvent* io_event)
{
  makeCurrent();
  Scene::keyPress(io_event);
  m_drawData.findMat(m_currentMaterial)->handleKey(io_event, context());
}*/
//-----------------------------------------------------------------------------------------------------
/*void MainScene::generateNewGeometry()
{
  makeCurrent();
  m_meshIndex = (m_meshIndex + 1) % m_meshes.size();
  auto& mesh = m_meshes[m_meshIndex];
  m_meshVBO.reset(
        sizeof(GLushort),
        mesh.getNIndicesData(),
        sizeof(GLfloat),
        mesh.getNVertData(),
        mesh.getNUVData(),
        mesh.getNNormData()
        );
  writeMeshAttributes();
  setAttributeBuffers();
}*/
//-----------------------------------------------------------------------------------------------------
/*void MainScene::loadMesh(size_t _id)
{
  static constexpr std::array<const char*, 3> shaderAttribs = {{"inVert", "inNormal", "inUV"}};
  const auto mesh = m_drawData.instance()->findGeo(_id);
  const std::vector<const float*> meshData {
    mesh->getVertexData(), mesh->getNormalsData(), mesh->getUVsData()
  };

  using b = Buffer::BufferType;
  for (const auto buff : {b::VERTEX, b::NORMAL, b::UV})
  {
    m_buffer.append(meshData[buff], buff);
    auto prog = m_shaderLib->getCurrentShader();
    prog->enableAttributeArray(shaderAttribs[buff]);
    prog->setAttributeBuffer(shaderAttribs[buff], GL_FLOAT, m_buffer.offset(buff), 3);
  }
  std::array<int, 3> temp;
  temp.at(0) = mesh->getNVertData(); temp.at(1) = mesh->getNNormData(); temp.at(2) = mesh->getNUVData();
  m_bufferObjects.push_back(temp);
}
//-----------------------------------------------------------------------------------------------------
void MainScene::loadMesh(size_t _meshID, size_t _shaderID)
{
  static constexpr std::array<const char*, 3> shaderAttribs = {{"inVert", "inNormal", "inUV"}};
  const auto mesh = m_drawData.instance()->findGeo(_meshID);
  const std::vector<const float*> meshData {
    mesh->getVertexData(), mesh->getNormalsData(), mesh->getUVsData()
  };

  using b = Buffer::BufferType;
  for (const auto buff : {b::VERTEX, b::NORMAL, b::UV})
  {
    m_buffer.append(meshData[buff], buff);
    auto prog = m_shaderLib->getShader(_shaderID);
    prog->enableAttributeArray(shaderAttribs[buff]);
    prog->setAttributeBuffer(shaderAttribs[buff], GL_FLOAT, m_buffer.offset(buff), 3);
  }
  std::array<int, 3> temp;
  temp.at(0) = mesh->getNVertData(); temp.at(1) = mesh->getNNormData(); temp.at(2) = mesh->getNUVData();
  m_bufferObjects.push_back(temp);
}
//-----------------------------------------------------------------------------------------------------
void MainScene::loadMesh(Mesh _raw, size_t _shaderID)
{
  static constexpr std::array<const char*, 3> shaderAttribs = {{"inVert", "inNormal", "inUV"}};
  const std::vector<const float*> meshData {
    _raw.getVertexData(), _raw.getNormalsData(), _raw.getUVsData()
  };

  using b = Buffer::BufferType;
  for (const auto buff : {b::VERTEX, b::NORMAL, b::UV})
  {
    m_buffer.append(meshDatDemoScenea[buff], buff);
    auto prog = m_shaderLib->getShader(_shaderID);
    prog->enableAttributeArray(shaderAttribs[buff]);
    prog->setAttributeBuffer(shaderAttribs[buff], GL_FLOAT, m_buffer.offset(buff), 3);
  }
  std::array<int, 3> temp;
  temp.at(0) = _raw.getNVertData(); temp.at(1) = _raw.getNNormData(); temp.at(2) = _raw.getNUVData();
  m_bufferObjects.push_back(temp);
}*/
//-----------------------------------------------------------------------------------------------------
/*void MainScene::loadAllMeshData()
{
  makeCurrent();
  m_grid.load("models/Grid.obj");
  std::array<int, 3> dataValues;
  dataValues = countAllSceneGeo();
  m_buffer.reset(
        sizeof(GLfloat),
        m_grid.getNVertData()+dataValues.at(0),
        m_grid.getNNormData()+dataValues.at(1),
        m_grid.getNUVData()+dataValues.at(2)
        );
  loadMesh(m_grid, 0);
  for(auto& obj : m_sceneObjects)
  {
    if(obj.isActive())
    {
      //add data
      loadMesh(obj.getGeo());
    }
  }
}*/

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
}

//-----------------------------------------------------------------------------------------------------

void MainScene::renderScene()
{
  Scene::renderScene();

  // Scope the using declaration
  {
    using namespace SceneMatrices;
    m_matrices[MODEL_VIEW] = glm::rotate(m_matrices[MODEL_VIEW], glm::radians(-1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  }
  m_drawData.instance()->findMat(0)->update();
  m_meshVBO.use();
  glDrawElements(GL_TRIANGLES, m_drawData.instance()->findGeo(0)->getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);
  //size_t bufferIt=1; //1 because 0 is reserved for the grid
  for(size_t i=0; i<m_sceneObjects.size(); ++i)
  {
    if(m_sceneObjects.at(i).isActive())
    {
      m_drawData.instance()->findMat(m_sceneObjects.at(i).findMat())->update();
      //++bufferIt;
      m_meshVBO.use();
      //glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_bufferObjects.at(bufferIt).at(0))/3);
      glDrawElements(GL_TRIANGLES, m_drawData.instance()->findGeo(1+m_sceneObjects.at(i).getGeo())->getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);
    }
  }
  //glDrawElements(GL_TRIANGLES, m_drawData.findGeo(i+1).getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);
}
//-----------------------------------------------------------------------------------------------------

std::array<int, 3> MainScene::countAllSceneGeo() const
{
  std::array<int, 3> numData = {{0,0,0}};

  for(auto it = m_sceneObjects.begin(); it!=m_sceneObjects.end(); ++it)
  {
    size_t id = it->getGeo();
    numData.at(0)+=m_drawData.instance()->findGeo(id)->getNVertData();
    numData.at(1)+=m_drawData.instance()->findGeo(id)->getNNormData();
    numData.at(2)+=m_drawData.instance()->findGeo(id)->getNUVData();
  }
  return numData;
}
