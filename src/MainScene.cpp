#include "MainScene.h"


//-----------------------------------------------------------------------------------------------------
void MainScene::loadMesh(unsigned _id)
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
void MainScene::loadAllMeshData()
{
  /*std::array<int, 3> numData = {0,0,0};

  for(auto it = m_sceneObjects.begin(); it != m_sceneObjects.end(); ++it)
  {
    if(it->first->isActive())
    {
      //add data
      loadMesh(it->first->getGeo());
    }
  }*/
}

//-----------------------------------------------------------------------------------------------------
void MainScene::init()
{
  Scene::init();
  makeGrid(1);

  /*for (size_t i = 0; i < m_materials.size(); ++i)
  {
    auto& mat = m_materials[i];
    m_shaderLib->createShader(mat->vertexName(), mat->fragName());
    m_shaderLib->useShader(i);
    mat->init(m_shaderLib, i, &m_matrices);
  }
  m_materials[m_currentMaterial]->apply();*/

  m_buffer.init(dynamic_cast<QObject*>(this));
  //generateNewGeometry();
  generateGridGeo();
  // Scope the using declaration
  {
    using namespace SceneMatrices;
    m_matrices[MODEL_VIEW] = glm::translate(m_matrices[MODEL_VIEW], glm::vec3(0.0f, 0.0f, -2.0f));
  }
}
//-----------------------------------------------------------------------------------------------------
/*void MainScene::generateNewGeometry()
{
  makeCurrent();
  m_meshIndex = (m_meshIndex + 1) % m_meshes.size();
  m_buffer.reset(
        sizeof(GLfloat),
        m_meshes[m_meshIndex].getNVertData(),
        m_meshes[m_meshIndex].getNNormData(),
        m_meshes[m_meshIndex].getNUVData()
        );
  loadMesh();
}*/
//-----------------------------------------------------------------------------------------------------
/*void MainScene::nextMaterial()
{
  makeCurrent();
  m_currentMaterial = (m_currentMaterial + 1) % m_materials.size();
  m_materials[m_currentMaterial]->apply();
}*/
//-----------------------------------------------------------------------------------------------------

void MainScene::renderScene()
{
  Scene::renderScene();

  // Scope the using declaration
  {
    using namespace SceneMatrices;
    m_matrices[MODEL_VIEW] = glm::rotate(m_matrices[MODEL_VIEW], glm::radians(-1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  }

  glDrawArrays(GL_QUADS, 0, static_cast<int>(m_bufferObjects.at(0).at(0)));

  //m_materials[m_currentMaterial]->update();
  //for()
    //m_drawData.updateMaterial();
  //glDrawArrays(GL_TRIANGLES, 0, m_meshes[m_meshIndex].getNVertData()/3);
}
//-----------------------------------------------------------------------------------------------------

std::array<int, 3> MainScene::countAllSceneGeo() const
{
  std::array<int, 3> numData = {{0,0,0}};

  for(auto it = m_sceneObjects.begin(); it!=m_sceneObjects.end(); ++it)
  {
    unsigned id = it->getGeo();
    numData.at(0)+=m_drawData.instance()->findGeo(id)->getNVertData();
    numData.at(1)+=m_drawData.instance()->findGeo(id)->getNNormData();
    numData.at(2)+=m_drawData.instance()->findGeo(id)->getNUVData();
  }
  return numData;
}

void MainScene::generateGridGeo()
{
  makeCurrent();
  std::array<int, 3> dataValues;
  dataValues = countAllSceneGeo();
  m_buffer.reset(
        sizeof(GLfloat),
        dataValues.at(0),
        dataValues.at(1),
        dataValues.at(2)
        );
  loadAllMeshData();
}


void MainScene::makeGrid(float s)
{
  for(unsigned i=0; i<m_gridArray.size(); ++i)
  {
    m_gridArray.at(i) = glm::vec3((-s/2)+((s/m_gridSize)*(i%m_gridSize)), 0, (-s/2)+((s/m_gridSize)*(i%m_gridSize)));
  }
}

void MainScene::updateGridSize(unsigned _new)
{
  m_gridSize = _new;
}
