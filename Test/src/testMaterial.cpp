#include "testMaterial.h"
//#include "moc/moc_testMaterial.cpp"
void testMaterial::setName()
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

    QCOMPARE(Mat.getName(), std::string{""});
    Mat.setName(str0);
    QCOMPARE(Mat.getName(), str0);
}
