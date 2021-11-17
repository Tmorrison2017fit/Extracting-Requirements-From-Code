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

        string MethodName; // Name of the current Method
        vector<string> Lines; // Stores the entire Method
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
    void AddComment(string CommentStr);
    string GetMethodDef(int index); // Retrieves Method Def from index
    string GetLibrary(int index); // Retrieves Library from index
    string GetPreprocessors(int index);
    string GetComment(int index);
    int GetMethodDefLen();
    int GetLibraryLen();
    int GetPreprocessorsLen();
    int GetCommentLen();

    vector<Method> MethodsInFile; // List of all the Methods in the Current File
  private:
    string FileName; // Name of the Current File
    vector<string> Libraries; // List of Included Libraries
    vector<string> MethodDefs; // Lists of Methods Definitions
    vector<string> Preprocessors; // Lists of Preprocessors
    vector<string> Comments; // List of Comments
};

File* New_File(string File_Name);

#endif
