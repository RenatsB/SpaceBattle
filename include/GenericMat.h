#ifndef MATERIALDATA_H
#define MATERIALDATA_H
#include <memory>

class GenericMat
{
public:
  GenericMat()=default;
  GenericMat(size_t _id):
    m_id(_id),
    m_name("material"+std::to_string(_id))
  {}
  GenericMat(size_t _id, std::string _name):
    m_id(_id),
    m_name(_name)
  {}
  ~GenericMat()=default;
  size_t getMatID() const;
  std::string getMatName() const;
protected:
  size_t m_id;
  std::string m_name;
};

#endif //MATERIALDATA_H
