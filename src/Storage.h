#ifndef STORAGE_H
#define STORAGE_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;



class File{
  public:
      File(string Name_of_File);
    //-------------------------------------------
    class Method{
      public:
        Method();
        void PutName(string MName);
        string GetName();
        int GetLength();
        string GetLine(int index);
        void AddLine(string Line);
      private:
        string MethodName;
        //Temporary: just to test storing values until Identify is ready
        vector<string> Lines;
    };
    //-------------------------------------------
    vector<Method> List;
    void AddMethod(Method NewEntry);
    //void PrintVector();
  private:
    string FileName;
    vector<string> Libraries;

};

File* New_File(string File_Name);

#endif
