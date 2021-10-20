#include <string>
#include <fstream>
#include "Storage.h"
#include "Parse.h"

void Parse_File(string file, File *Cur_File){

  fstream FileObj;
  // Working on storing method in the file object
  // Method *NewMethod = New_Method("TempName");
  // Cur_File->AddMethod(*NewMethod);
  FileObj.open(file,ios::in);
  if (FileObj.is_open()){
      string temp;
      while(getline(FileObj, temp)){
         cout << temp << endl;
      }
    }
      FileObj.close();



}
