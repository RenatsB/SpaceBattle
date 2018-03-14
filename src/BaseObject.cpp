#include "BaseObject.h"

void BaseObject::changeID(const size_t _newID)
{
  m_id = _newID;
}

void BaseObject::moveObject (const vec3 _tr)
{
  m_pos += _tr;
  updateMatrix();
}

void BaseObject::setPosition(const vec3 _tr)
{
  m_pos=_tr;
  updateMatrix();
}

void BaseObject::rotateObject (const vec3 _rot)
{
  m_rot += _rot;
  updateMatrix();
}

void BaseObject::setRotation (const vec3 _rot)
{
  m_rot=_rot;
  updateMatrix();
}

void BaseObject::scaleObject (const vec3 _sc)
{
  m_scale += _sc;
  updateMatrix();
}

void BaseObject::setScale (const vec3 _sc)
{
  m_scale=_sc;
  updateMatrix();
}

vec3 BaseObject::getPosition () const
{
  return m_pos;
}

vec3 BaseObject::getRotation () const
{
  return m_rot;
}

vec3 BaseObject::getScale () const
{
  return m_scale;
}

void BaseObject::setActive(bool _new)
{
  m_isActive = _new;
}

bool BaseObject::isActive()
{
  return m_isActive;
}

void BaseObject::updateMatrix()
{
  m_MVmatrix = glm::mat4();
    if(m_parent==nullptr)
    {
      m_MVmatrix = glm::translate(m_MVmatrix, m_pos);
      m_MVmatrix = glm::rotate(m_MVmatrix, glm::radians(m_rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
      m_MVmatrix = glm::rotate(m_MVmatrix, glm::radians(m_rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
      m_MVmatrix = glm::rotate(m_MVmatrix, glm::radians(m_rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
      m_MVmatrix = glm::scale(m_MVmatrix, m_scale);
    }
    else
    {
      m_MVmatrix=m_parent->getMVmatrix();
      m_MVmatrix = glm::translate(m_MVmatrix, m_pos);
      m_MVmatrix = glm::rotate(m_MVmatrix, glm::radians(m_rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
      m_MVmatrix = glm::rotate(m_MVmatrix, glm::radians(m_rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
      m_MVmatrix = glm::rotate(m_MVmatrix, glm::radians(m_rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
      m_MVmatrix = glm::scale(m_MVmatrix, m_scale);
    }

    if(!m_children.empty())
    {
      for(auto child : m_children)
        child->updateMatrix();
    }
}

mat4 BaseObject::getMVmatrix() const
{
  return m_MVmatrix;
}

void BaseObject::addChild(BaseObject* _new)
{
  m_children.emplace_back(_new);
  m_children.at(m_children.size()-1)->updateMatrix();
}

void BaseObject::setParent(BaseObject* _new)
{
  m_parent = _new;
  m_parent->addChild(this);
}

std::string BaseObject::getName() const
{
  return m_name;
}
