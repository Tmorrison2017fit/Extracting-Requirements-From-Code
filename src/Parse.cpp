#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include "Storage.h"
#include "Parse.h"


//Reads the input File and stores the contents in a File class object
void Read_File(string file, File *Cur_File){

  fstream FileObj;
  bool inMethod = false;
  int BraceCounter = 0;
  int split;
  int newline;
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
          else if(temp.find("//") != -1){
            Cur_File->AddComment(temp);
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
          if(temp.find("//") != -1){
            if(temp.find(';') != -1){
              string commentTemp = temp;
              split = temp.find("//");
              Cur_File->AddComment(commentTemp.erase(0,split));
              Cur_File->MethodsInFile[MethodIndex].AddLine(temp.erase(split,temp.size()-1));
            }
            else{
              Cur_File->AddComment(temp);
            }
          }
          else{
            Cur_File->MethodsInFile[MethodIndex].AddLine(temp);
          }
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

  //Parse_File_Methods(Cur_File);

}


// //Get rid of every character that is not a space or an alphabetical character
// bool bad_chars(char c){
//   return c != ' ' && !isalpha(c);
// }
//
// //Replace all bad characters in a line with a space
// string ReplaceBadChars(string badString){
//   replace_if(badString.begin(), badString.end(), bad_chars, ' ');
//   return badString;
// }
//
//
// //GRABS ALL WORDS FROM FUNCTIONS AS KEYWORDS FOR NOW
//
// //Grab all of the keywords from the methods in a file
// void Parse_File_Methods(File *Cur_File){
//   int lineIterator;
//   int methodIterator;
//   string line;
//
//   //Temporary place to store keywords from functions, this can be updated to fit the storage class
//   unordered_set<string> Method_Keywords;
//
//   unordered_set<string>:: iterator tokenIterator;
//
//   //Handle all whitespace for now, this can be updated to check for strings in quotes
//   regex re("\\s");
//
//   //Since we start at 0, all the sizes and lengths need to be decreased by 1
//   for (methodIterator = 0; methodIterator <= Cur_File->MethodsInFile.size() - 1; methodIterator++){
//     for (lineIterator = 0; lineIterator <= Cur_File->MethodsInFile[methodIterator].GetLength() - 1; lineIterator++){
//       line = Cur_File->MethodsInFile[methodIterator].GetLine(lineIterator);
//
//
//       //There is no reason to read blank lines
//       if(line.length() == 0){
//         continue;
//       }
//
//       //cout << "BAD LINE: " << line << endl;
//
//       //Cut out all the bad characters in the input line
//       line = ReplaceBadChars(line);
//
//       //Output the cleaned line to stdout
//       cout << "CLEANED LINE: " << line <<endl;
//
//       //Split the line by whitespace, and then put the words of the line in an unordered set
//       sregex_token_iterator first{line.begin(), line.end(), re, -1}, last;
//       unordered_set<string> tokens{first, last};
//
//       //Output the words gathered to stdout
//       cout << "Words in line:" << endl;
//       string::iterator stringIterator;
//       for(tokenIterator = tokens.begin(); tokenIterator != tokens.end(); tokenIterator++){
//         cout << (*tokenIterator)  << endl;
//       }
//
//       cout << endl << endl;
//
//     }
//   }
// }
