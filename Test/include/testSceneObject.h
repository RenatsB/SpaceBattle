/*#include <QtTest/QtTest>
#include "SceneObject.h"
#include <utility>

class testSceneObject : public QObject
{
    Q_OBJECT
private:
  SceneObject Obj();//std::string{"Test"}, std::pair<unigned long, std::string>{0,"Mesh"}, std::pair<unsigned long, std::string>{0,"Material"});
private slots:
    void setName();
};

void testSceneObject::setName()
{
    std::string str0 = "Name";
    std::string str1 = "";
    std::string str2 = "\n";
    std::string str3 = "\b";
    char        str4 = '\n';
    float       str5 = 0.45f;
    int         str6 = 12225;
    bool        str7 = false;
    void*       str8 = NULL;
    double      str9 = std::nan("nan");

    QCOMPARE(Obj.getName(), std::string{""});
    Obj.setName(str0);
    QCOMPARE(Obj.getName(), str0);
}
*/
