#ifndef STORAGE_H
#define STORAGE_H
#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

class Node{
  public:
    Node();
    string Name; // Name of the Node
    Node* Parent; // Pointer to the Node's Parent
    vector <Node*> Children; // Vector of pointers to all of the nodes children.
};

class LinkedList{
  public:
    LinkedList();
    Node* Root; // Head of the Linked List.
    void UpdateRoot(); // Creates the Root.
    void CreateNode(string NodeName, string ParentName); // Creates nodes.
    bool InLinkedList( string NodeName); // Checks to see if something is in the list.
    Node* SearchParent(string ParentName); // Searches for the specified parent.
    void PrintList(); // Prints the List.

};

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


        //Cleaned lines are only going in methods
        int GetCleanedLength();
        string GetCleanedLine(int index);
        void AddCleanedLine(string Line);

      private:

        string MethodName; // Name of the current Method
        vector<string> Lines; // Stores the entire Method

        vector<string> Cleaned_Lines;  //Stores lines after removing bad characters

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

string StripString(string str);

bool MultipleMethods(string str);
void MethodTotal(string str, vector<string> & List);

File* New_File(string File_Name);
#endif
