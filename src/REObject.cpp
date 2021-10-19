#include <string>
#include <vector>
#include <iostream>
#include "REObject.h"
using namespace std;
Method::Method()
{
}

void Method::SetNum(int num){
  c = num;
}
int  Method::GetNumber(){
  return c;
}

File::File()
{
 FileName = "Whatever";
}

void File::AddMethod(Method NewEntry){
  List.push_back(NewEntry);
}
int File::GetNum(int index){
  return List[index].GetNumber();
}
