#include <string>
#include <vector>
#include <iostream>
#include "Storage.h"

using namespace std;

Method::Method(string MName){
  MethodName = MName;
};


string Method::GetName(){
  return MethodName;
};

string Method::GetLine(int index){
  return Lines[index];
};

void Method::AddLine(string Line){
    Lines.push_back(Line);
};


File::File(string Name_of_File){
  FileName = Name_of_File;
};

void File::AddMethod(Method NewEntry){
  List.push_back(NewEntry);
};

string File::GetLFMethod(int Method_Index, int Line_Index){
  return List[Method_Index].GetLine(Line_Index);
};


Method* New_Method(string Method_Name){
  Method *NMethod = new Method(Method_Name);
  return NMethod;
};

File* New_File(string File_Name){
  File *NFile = new File(File_Name);
  return NFile;
};
