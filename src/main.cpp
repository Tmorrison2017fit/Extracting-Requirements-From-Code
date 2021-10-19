#include <iostream>
#include "REObject.cpp"
#include "REObject.h"
using namespace std;
int main(void){

  File FileObj;
  Method One;
  Method Two;
  Method Three;
  One.SetNum(5);
  Two.SetNum(556);
  Three.SetNum(4565);

  FileObj.AddMethod(One);
  FileObj.AddMethod(Two);
  FileObj.AddMethod(Three);
  cout << FileObj.GetNum(2);

  return 0;
}
