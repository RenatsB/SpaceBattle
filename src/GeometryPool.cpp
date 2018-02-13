#include "GeometryPool.h"

GeometryPool* GeometryPool::instance()
{
  if(pInstance == 0)
    {
      pInstance = new GeometryPool;
    }
  return pInstance;
}

bool GeometryPool::loadGeometry(const std::string _path)
{

}

void GeometryPool::removeGeo(const unsigned _id)
{

}

void GeometryPool::removeGeo(const std::string _name)
{
  bool ret = false;
  for(unsigned r=0; r<m_geo.size(); ++r)
  {
    if(m_geo.at(r)->getName() == _name)
    {
      //free(m_geo.at(r));
      //m_geo.r
    }
  }
}

bool GeometryPool::checkValidity(const unsigned _id)
{
  bool ret = true;
  unsigned u=0;
  std::vector<unsigned> positions;
  for(unsigned r=0; r<m_geo.size(); ++r)
  {
    if(m_geo.at(r)->getID() == _id)
    {
      ++u;
      positions.push_back(r);
      if(m_geo.at(r)->getName() == "")
      {
        m_geo.at(r)->setName("UnnamedObject");
      }
    }
  }
  if(u>1)
  {
    //fix duplicate ids
  }
  return ret;
}

void GeometryPool::sortGeometry()
{
  size_t vecSize = m_geo.size();
  for(size_t a=0; a<vecSize; ++a)
  {
    for(size_t b=0; b<vecSize-1; ++b)
    {
      if(m_geo.at(b)->getID() > m_geo.at(b+1)->getID())
      {
        Geometry* temp = m_geo.at(b);
        m_geo.at(b) = m_geo.at(b+1);
        m_geo.at(b+1) = temp;
      }
    }
  }
}
