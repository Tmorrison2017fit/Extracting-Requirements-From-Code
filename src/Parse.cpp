#include <string>
#include <vector>
#include <fstream>
#include "Storage.h"
#include "Parse.h"



// void Parse_Method(File *Cur_File){
//
//
//   int lineIterator;
//   int methodIterator;
//
//   string line;
//
//
//   for (methodIterator = 0; methodIterator <= Cur_File->MethodsInFile.size(); methodIterator++){
//     for (lineIterator = 0; lineIterator <= Cur_File->MethodsInFile[methodIterator].GetLength(); lineIterator++){
//       line = Cur_File->MethodsInFile[methodIterator].GetLine(lineIterator);
//
//       cout << line << endl;
//     }
//   }
//
// }

void Read_File(string file, File *Cur_File){

  fstream FileObj;
  bool inMethod = false;
  int BraceCounter = 0;
  FileObj.open(file,ios::in);
  if (FileObj.is_open()){
      string temp;
      int MethodIndex;
      while(getline(FileObj, temp)){
        if(inMethod == false){ // Not in Method
          if(temp.find("#include") != -1){
            Cur_File->AddLibrary(temp);
          }
          else if((temp.find("#define") != -1) || (temp.find("namespace") != -1)){
            Cur_File->AddPreprocessors(temp);
          }
          else if((temp.find(';') != -1)){
            Cur_File->AddMethodDef(temp);
          }
          else if ((temp.find('(') != -1) && (temp.find(')') != -1)
          && (temp.find(';') == -1)){ // finds function
            File::Method newObj("Temp Name");

            Cur_File->AddMethod(newObj);
            MethodIndex = Cur_File->MethodsInFile.size() - 1;
            if (temp.find('{') == -1){

              Cur_File->MethodsInFile[MethodIndex].AddLine(temp +'\n'+'{');
            }
            else{
              Cur_File->MethodsInFile[MethodIndex].AddLine(temp);
            }
          }
          if(temp.find('{') != -1){
            inMethod = true;
            BraceCounter++;
          }
        }
        else{ // In a method
          Cur_File->MethodsInFile[MethodIndex].AddLine(temp);
          if(temp.find('{') != -1){
            BraceCounter++;
          }
          if(temp.find('}') != -1){
            BraceCounter--;
          }
          if (BraceCounter == 0){
            inMethod = false;
          }
        }



      }
  }
  FileObj.close();

  // Parse_Method(Cur_File);

}
