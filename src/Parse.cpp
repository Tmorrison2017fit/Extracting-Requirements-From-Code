#include <string>
#include <fstream>
#include "Storage.h"
#include "Parse.h"

void Parse_File(string file, File *Cur_File){
  cout << Cur_File->List[0].GetName() << endl;

  fstream FileObj;

  FileObj.open(file,ios::in);
  if (FileObj.is_open()){
      string temp;
      while(getline(FileObj, temp)){
          if(temp.length() != 1){
            Cur_File->List[0].AddLine(temp);
          }
      }
    }
      FileObj.close();



}
