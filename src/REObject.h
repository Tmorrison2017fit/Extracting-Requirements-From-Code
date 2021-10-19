#ifndef REOBJECT_H
#define REOBJECT_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Method{
  public:
    Method();
    void SetNum(int num);
    int GetNumber();
  protected:
    int c = 6;
};

class File : public Method{
  public:
    File();
     void AddMethod(Method NewEntry);
     void PrintVector();
     int GetNum(int index);
  protected:
    string FileName;
    vector<Method> List;
};

#endif
