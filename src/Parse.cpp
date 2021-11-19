#include <string>
#include <vector>
#include <fstream>
#include "Storage.h"
#include "Parse.h"
#include "freeling.h"

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


/*Set desired options for the morphological analyzer*/

freeling::maco_options my_maco_options(const wstring &lang, const wstring &lpath) {

  //Create options holder
  freeling::maco_options opt(lang);

  //Provide files for morphological submodules. Note that it is not necessary
  //to set modules for files that will not be used

  opt.UserMapFile = L"";
  opt.LocutionsFile = lpath + L"locucions.dat";
  opt.AffixFile = lpath + L"afixos.dat";
  opt.ProbabilityFile = lpath + L"probabilitats.dat";
  opt.DictionaryFile = lpath + L"dicc.src";
  opt.NPdataFile = lpath + L"np.dat";
  opt.PunctuationFile = lpath + L"../common/punct.dat";

  return opt;
}

//Get rid of every character that is not a space or an alphabetical character
bool bad_chars(char c){
  return c != ' ' && !isalpha(c);
}

//Replace all bad characters in a line with a space
string ReplaceBadChars(string badString){
  replace_if(badString.begin(), badString.end(), bad_chars, ' ');
  return badString;
}



//GRABS ALL WORDS FROM FUNCTIONS AS KEYWORDS FOR NOW

//Grab all of the keywords from the methods in a file
void Parse_File_Methods(File *Cur_File){
    int lineIterator;
    int methodIterator;
    string line;

    //Set the locale for freeling to use, UTF-8
    freeling::util::init_locale(L"default");

    //Set the default language to English text
    wstring lang = L"en";
 
    //Set the default path where FreeLing is located, this may be system dependent
    wstring ipath = L"/usr/local/";

    //Path to language data
    wstring lpath = ipath + L"/share/freeling/" + lang + L"/";


    //Create tokenizer and splitter objects
    freeling::tokenizer tk(lpath + L"tokenizer.dat");
    freeling::splitter sp(lpath + L"splitter.dat");


    //Create a morphological analyzer object with the required attributes
    freeling::maco_options opt = my_maco_options(lang, lpath);
    freeling::maco morfo(opt);


    //then, (de)activate required modules
    morfo.set_active_options( false,  //UserMap
                              true, //NumbersDetection
                              true, //PunctuationDetection
                              true, //DatesDetetction
                              true, //DictionarySearch
                              true, //AffixAnalysis
                              false,  //CompoundAnalysis
                              true, //RetokContractions
                              true, //MultiwordDetection
                              true, //NERecognition
                              false,  //QuantitiesDetection
                              true);  //ProbabilitiesAssignment


    //Create an HMM_Tagger object, with retokenization ability, and forced
    //to choose only one tag per word)
    freeling::hmm_tagger tagger(lpath + L"tagger.dat", true, FORCE_TAGGER);



    //Temporary place to store keywords from functions, this can be updated to fit the storage class
    unordered_set<string> Method_Keywords;

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

      }
    }

    //Tokenize input data and split into list of words
    //list<freeling::word> lw = tk.tokenize(INPUT_DATA);

    //Split list of words into sentence, get a list of sentences
    //list<freeling::sentence> ls = sp.split(lw);


    //Perform monosyntactic analysis and disambiguation
    //morfo.analyze(ls);
    //tagger.analyze(ls);

    //Do whatever output with the processed sentences
    //ProcessSentences(ls);
}
