#include <string>
#include <vector>
#include <iostream>
#include "Storage.h"

using namespace std;

File::Method::Method(){
};


void File::Method::PutName(string MName){
   MethodName = MName;
};

int File::Method::GetLength(){
  return Lines.size();
};

string File::Method::GetName(){
  return MethodName;
};

string File::Method::GetLine(int index){
  return Lines[index];
};

void File::Method::AddLine(string Line){
    Lines.push_back(Line);
};


File::File(string Name_of_File){
  FileName = Name_of_File;
};

void File::AddMethod(Method NewEntry){
  List.push_back(NewEntry);
};


File* New_File(string File_Name){
  File *NFile = new File(File_Name);
  return NFile;
};
