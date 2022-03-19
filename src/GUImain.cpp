#include <iostream>
#include <string>
#include <vector>
#include "Storage.h"
//#include "Storage.cpp"

#include "Parse.h"
//#include "Parse.cpp"

//#include "Analyze.h"
//#include "Analyze.cpp"



using namespace std;

void printFunction(File *FileObj);

vector<string> GUIMain(string Name){

  LinkedList* LogicTree = new LinkedList(); // Creates the Linked List Object.
  File* TestFile = New_File(Name);
  TestFile->AddFileName(Name);
  Read_File(Name, TestFile, LogicTree);
  //Parse_File_Methods(TestFile);
  return (LogicTree->RetrieveList());
  //LogicTree->PrintList(); // Prints the Linked List that was created in Read_File();
  // vector<string> Results;
  // int MethodDefs = TestFile->GetMethodDefLen();
  // int preProcLen = TestFile->GetPreprocessorsLen();
  // int LibLen = TestFile->GetLibraryLen();
  // int MethodLen = TestFile->MethodsInFile.size();
  // int CommentLen = TestFile->GetCommentLen();
  // for( int i = 0; i < LibLen ; i++){
  //   Results.push_back(TestFile->GetLibrary(i));
  // }
  //
  // for( int i = 0; i < LibLen ; i++){
  //   Results.push_back(TestFile->GetLibrary(i));
  // }
  //
  // for( int i = 0; i < preProcLen ; i++){
  //   Results.push_back(TestFile->GetPreprocessors(i));
  // }
  //
  // for( int i = 0; i < MethodDefs ; i++){
  //   Results.push_back(TestFile->GetMethodDef(i));
  // }
  // for( int i = 0; i < MethodLen ; i++){
  //   int Lines = TestFile->MethodsInFile[i].GetLength();
  //   for( int j = 0; j < Lines;j++){
  //     Results.push_back(TestFile->MethodsInFile[i].GetLine(j));
  //   }
  // }
  //
  // for( int i = 0; i < CommentLen ; i++){
  //   Results.push_back(TestFile->GetComment(i));
  // }
  // return Results;
}

void printFunction(File *FileObj){

  cout << endl;

}
