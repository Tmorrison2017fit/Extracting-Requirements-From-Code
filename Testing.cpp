#include <string>
#include <fstream>
#include "Parse.h"



void Parse_File(string file, File *Cur_File){
  //cout << Cur_File->List[0].GetName() << endl;

  fstream FileObj;

  FileObj.open(file,ios::in);
  if (FileObj.is_open()){
      
      string temp;
      string lastLine;

      while(getline(FileObj, temp)){
         Cur_File->List[0].AddLine(temp);

        //Skip all include and empty lines for now
        if(temp.find("#") != string::npos || temp.empty()){
          continue;
        }

        //Look for lines that start with a brakect
        else if (temp.find("{") != string::npos){
          cout << "FUNCTION FOUND AT: " << temp << endl;
        }

        lastLine = temp;
        cout << "\n" << "CURRENT LINE IS: " << temp << endl;     
      }

    }
      FileObj.close();

  cout << "\n" << "\n" << "\n" << file << "\n" << "\n" << "\n";

}
