#include <string>
#include <vector>
#include <fstream>
#include "Storage.h"
#include "Parse.h"



void Parse_Method(File *Cur_File){

  
  int lineIterator;
  int methodIterator;

  string line;

  
  for (methodIterator = 0; methodIterator <= Cur_File->MethodsInFile.size(); methodIterator++){
    for (lineIterator = 0; lineIterator <= Cur_File->MethodsInFile[methodIterator].GetLength(); lineIterator++){
      line = Cur_File->MethodsInFile[methodIterator].GetLine(lineIterator);

      cout << line << endl;
    }
  }
  
}

void Read_File(string file, File *Cur_File){
  cout << Cur_File->MethodsInFile[0].GetName() << endl;

  fstream FileObj;
  
  FileObj.open(file,ios::in);
  if (FileObj.is_open()){
      string temp;
      while(getline(FileObj, temp)){

        //ParenStack to swtich up between methods change 0 to i
        //Differ between function defs and includes

         Cur_File->MethodsInFile[0].AddLine(temp);
      }
  }
  FileObj.close();

  Parse_Method(Cur_File);

}
