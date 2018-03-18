#include <QtTest/QtTest>
#include "mockDataContainer.cpp"

class testObjectManager : public QObject
{
  Q_OBJECT
private:
  std::unique_ptr<mockDataContainer> Data;
private Q_SLOTS:
  void test_constructA();
};
