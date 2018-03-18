#include <string>

class mockMatGeo
{
public:
  void setName(std::string _new);
  std::string getName() const;
  void setID(size_t _new);
  size_t getID() const;
protected:
  std::string m_name="";
  size_t m_id=0;
};

void mockMatGeo::setName(std::string _new)
{
  m_name = _new;
}

std::string mockMatGeo::getName() const
{
  return m_name;
}

void mockMatGeo::setID(size_t _new)
{
  m_id = _new;
}

size_t mockMatGeo::getID() const
{
  return m_id;
}
