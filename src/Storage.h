#ifndef STORAGE_H
#define STORAGE_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;


class File{
  public:
    //-------------------------------------------
    class Method{
      public:
        Method(string MName);
        string GetName();
        int GetLength();
        string GetLine(int index);
        void AddLine(string Line);
        void AddLoopRange(int begin, int finish);
        vector<int> GetLoopRange(int index);
      private:
        string MethodName;

        vector<string> Lines; // Stores file line by line
        vector<int> Variables; // Stores line number of where the variable are at
        vector<vector<int>> Loops;

    };
    //-------------------------------------------
    File(string Name_of_File);
    void AddFileName(string Name);
    void AddMethod(Method NewEntry); // Add a New Method
    void AddMethodDef(string NewDef); // Add a New Method Definition
    void AddLibrary(string NewLib); // Add a New Library
    void AddPreprocessors(string preProc);
    string GetMethodDef(int index); // Retrieves Method Def from index
    string GetLibrary(int index); // Retrieves Library from index
    string GetPreprocessors(int index);
    int GetMethodDefLen();
    int GetLibraryLen();
    int GetPreprocessorsLen();
    vector<Method> MethodsInFile; // List of all the Methods in the Current File

  private:
    string FileName; // Name of the Current File
    vector<string> Libraries; // Stores Included Libraries
    vector<string> MethodDefs; // Stores Methods Definitions
    vector<string> Preprocessors;
    vector<string> Comments;
};

File* New_File(string File_Name);

#endif
