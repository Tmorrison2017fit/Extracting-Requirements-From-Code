#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <bits/stdc++.h>
#include "Storage.h"
#include "Parse.h"


//Get rid of every character that is not a space or an alphanumeric character
bool bad_chars(char c){
  return c != ' ' && !isalpha(c); 
}


//Get rid of all bad characters and replace them with a space
string ReplaceBadChars(string badString){
  replace_if(badString.begin(), badString.end(), bad_chars, ' ');
  return badString;
}

//GRAB KEYWORDS AND MAYBE DATA TYPES FOR NOW

//Grab all of the words from a method
void Parse_Method(File *Cur_File){
  int lineIterator;
  int methodIterator;
  string line;
  
  unordered_set<string> Method_Keywords;

  unordered_set<string>:: iterator tokenIterator;


  regex re("\\s");

  for (methodIterator = 0; methodIterator <= Cur_File->MethodsInFile.size() - 1; methodIterator++){
    for (lineIterator = 0; lineIterator <= Cur_File->MethodsInFile[methodIterator].GetLength(); lineIterator++){
      line = Cur_File->MethodsInFile[methodIterator].GetLine(lineIterator);

      //cout << "BAD LINE: " << line << endl;
    
      //Cut out all the non-alphanumeric chars in the input line
      line = ReplaceBadChars(line);

      cout << "CLEANED LINE: " << line <<endl;

      //There is no reason to read blank lines
      if(line.length() == 0){
        continue;
      }

      //Split the line by whitespace, and then put the tokens in an unordered set for each line 
      sregex_token_iterator first{line.begin(), line.end(), re, -1}, last;
      unordered_set<string> tokens{first, last}; 
        
      cout << "Words in line:" << endl;
      string::iterator stringIterator; 
      for(tokenIterator = tokens.begin(); tokenIterator != tokens.end(); tokenIterator++){
        cout << (*tokenIterator)  << endl;
      }
        
      cout << endl << endl;

    }
  }
}

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

  Parse_Method(Cur_File);

}
