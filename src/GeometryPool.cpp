#include "GeometryPool.h"

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
    if(m_geo.at(r).getName() == _name)
    {
      //remove element
    }
  }
}

bool GeometryPool::checkValidity(const unsigned _id)
{
  bool ret = true;
  if(_id >= m_geo.size())
  {
    ret = false;
    std::cout<<"Requested object id is out of scope.\n";
  }
  else
  {
    unsigned u=0;
    std::vector<unsigned> positions;
    for(unsigned r=0; r<m_geo.size(); ++r)
    {
      if(m_geo.at(r).getID() == _id)
      {
        ++u;
        positions.push_back(r);
        if(m_geo.at(r).getName() == "")
        {
          m_geo.at(r).setName("UnnamedObject");
        }
      }
    }
    if(u>1)
    {
      //fix duplicate ids
    }
  }
  return ret;
}
