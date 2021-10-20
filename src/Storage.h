#ifndef STORAGE_H
#define STORAGE_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Method{
  public:
    Method(string MName);
    string GetName();
    string GetLine(int index);
    void AddLine(string Line);
  protected:
    string MethodName;
    //Temporary: just to test storing values until Identify is ready
    vector<string> Lines;
};

class File : public Method{
  public:
    File(string Name_of_File);
    void AddMethod(Method NewEntry);
    //void PrintVector();
    string GetLFMethod(int Method_Index, int Line_Index);
  protected:
    string FileName;
    vector<string> Libraries;
    vector<Method> List;
};

Method* New_Method(string Method_Name);

File* New_File(string File_Name);

#endif
