
#include "MaterialBump.h"
#include "Scene.h"
#include "ShaderLib.h"

void MaterialBump::init()
{
  initBumpMap();
  m_bumpMap->bind(0);

  auto shaderPtr = m_shaderLib->getShader(m_shaderName);
  shaderPtr->setUniformValue("bumpMap", 0);

  initBaseTexture();
  m_texMap->bind(1);
  shaderPtr->setUniformValue("texMap", 1);
  update();
}

void MaterialBump::initBumpMap()
{
  using tex = QOpenGLTexture;
  m_bumpMap.reset(new QOpenGLTexture(tex::Target2D));
  auto map = QImage("images/bricknormals.jpg").mirrored().convertToFormat(QImage::Format_RGB888);
  m_bumpMap->setSize(map.width(), map.height(), map.depth());
  m_bumpMap->setFormat(tex::RGBFormat);
  m_bumpMap->allocateStorage();
  m_bumpMap->setData(tex::RGB, tex::UInt8, map.constBits());
  m_bumpMap->create();
  m_bumpMap->bind(0, tex::ResetTextureUnit);
  m_bumpMap->setWrapMode(tex::Repeat);
  m_bumpMap->setMinMagFilters(tex::Linear, tex::Linear);
}

void MaterialBump::initBaseTexture()
{
  using tex = QOpenGLTexture;
  m_texMap.reset(new QOpenGLTexture(tex::Target2D));
  auto map = QImage("images/bricktexture.jpg").mirrored().convertToFormat(QImage::Format_RGB888);
  m_texMap->setSize(map.width(), map.height(), map.depth());
  m_texMap->setFormat(tex::RGBFormat);
  m_texMap->allocateStorage();
  m_texMap->setData(tex::RGB, tex::UInt8, map.constBits());
  m_texMap->create();
  m_texMap->bind(0, tex::ResetTextureUnit);
  m_texMap->setWrapMode(tex::Repeat);
  m_texMap->setMinMagFilters(tex::Linear, tex::Linear);
}

void MaterialBump::update()
{
  auto shaderPtr = m_shaderLib->getShader(m_shaderName);
  auto eye = m_cam->getCameraEye();
  shaderPtr->setUniformValue("camPos", QVector3D{eye.x, eye.y, eye.z});

  // Scope the using declaration
  {
    using namespace SceneMatrices;
    static constexpr std::array<const char*, 3> shaderUniforms = {{"M", "MVP", "N"}};
    // Send all our matrices to the GPU
    for (const auto matrixId : {MODEL_VIEW, PROJECTION, NORMAL})
    {
      // Convert from glm to Qt
      QMatrix4x4 qmat(glm::value_ptr((*m_matrices)[matrixId]));
      // Need to transpose the matrix as they both use different majors
      shaderPtr->setUniformValue(shaderUniforms[matrixId], qmat.transposed());
    }
  }
}

const char* MaterialBump::shaderFileName() const
{
  return "shaderPrograms/bump.json";
}
