#include <iostream>
#include <string>
#include "Storage.cpp"
#include "Parse.cpp"
#include "Storage.h"
#include "Parse.h"

using namespace std;

int main(int argc,char* argv[]){

  // Creates one file, will be changed later for multiple files
  File *TestFile = New_File("Temp File");

  Parse_File(argv[1], TestFile);



  return 0;
}
