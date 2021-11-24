#include <string>
#include <vector>
#include <fstream>


//#include <codecvt>

#include "Storage.h"
#include "Parse.h"


//Reads the input File and stores the contents in a File class object
void Read_File(string file, File *Cur_File){

  fstream FileObj;
  bool inMethod = false;
  int BraceCounter = 0;
  int split;
  int newline;
  string MethodName;
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
            // Strips name of Method.
            MethodName = temp;
            split = temp.find('(');
            MethodName = MethodName.erase(split,MethodName.size());
            split = temp.find(' ');
            MethodName = MethodName.erase(0,split+1);

            File::Method newObj(MethodName);

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
}


//Determine if a character is a bad character
//Bad characters are anything besides a-zA-z, 0-9, ", '
bool bad_chars(char c){
  return c != ' ' && !isalnum(c) && c != '\"' && c != '\'';
}



//Replace all bad characters in a line with a space
string ReplaceBadChars(string badString){
  replace_if(badString.begin(), badString.end(), bad_chars, ' ');
  return badString;
}



//TODO: Merge all of the text analyzer stuff into a new seperate file
// Parsing file methods will come down to taking out the bad characters and putting the input in a list
// to send to the TA

//Grab all of the keywords from the methods in a file
void Parse_File_Methods(File *Cur_File){
    int lineIterator;
    int methodIterator;
    string line;


    //Since we start at 0, all the sizes and lengths need to be decreased by 1
    for (methodIterator = 0; methodIterator <= Cur_File->MethodsInFile.size() - 1; methodIterator++){
      for (lineIterator = 0; lineIterator <= Cur_File->MethodsInFile[methodIterator].GetLength() - 1; lineIterator++){
        line = Cur_File->MethodsInFile[methodIterator].GetLine(lineIterator);

        //There is no reason to read blank lines
        if(line.length() == 0){
            continue;
        }


        cout << "BAD LINE: " << line << endl;

        //Cut out all the bad characters in the input line
        line = ReplaceBadChars(line);

        //Output the cleaned line to stdout
        cout << "CLEANED LINE: " << line <<endl;
        cout << endl << endl;

        //If we got rid of all the characters in a line, it will be empty and shouldn't be added
        if(line.length() == 0){
          continue;
        }

        Cur_File->MethodsInFile[methodIterator].AddCleanedLine(line);


      }

    }
}