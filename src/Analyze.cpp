#include <string>


#include <vector>
#include <list>


#include "Storage.h"
#include "Parse.h"
#include "Analyze.h"

#include "freeling.h"




/* 
So all the input should be in ASCII anyways, and we really aren't expecting any special
Unicode Characters, so really we should be able to convert between strings and wstrings
without needing to worry about any UTF-16 inputs
*/

int String2WString(const std::string &str, std::wstring &wstr){

  std::wstring wstrTmp(str.begin(), str.end());

  wstr = wstrTmp;

  return 0;
}


int WString2String(const std::wstring &wstr, std::string &str){

  std::string strTmp(wstr.begin(), wstr.end());

  str = strTmp;

  return 0;
}


/*
So FreeLing needs to use lists of words rather than vectors, so I think it'd be easier to
just convert between the two rather than rework the entire code structure. Since it's calling
on an iterator, the original structure is being replaced by the new one, so it won't have any
massive issues with space, the only thing I'd be worried about is time.

Just the way the functions look, the time would be O(n), and this is being done on every line
*/
std::vector<string> List2Vector(std::list<string> &inputList){

  vector<string> outVect{make_move_iterator(begin(inputList)),
                         make_move_iterator(end(inputList))};

  return outVect;
}


std::list<string> Vector2List(std:: vector<string> &inputVector){

  list<string> outList{make_move_iterator(begin(inputVector)),
                       make_move_iterator(end(inputVector))};

  return outList;
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




void Analyze_Text(File *Cur_File){

    //Set the locale for freeling to use, UTF-8
    freeling::util::init_locale(L"default");

    //Set the default language to English text
    wstring lang = L"en";
 
    //Set the default path where FreeLing is located, this is definitely gonna be system dependent
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


    wstring CleanedInput = L"";
    wstring W_Line;
    string Line;

    for(int methodIterator = 0; methodIterator != Cur_File->MethodsInFile.size() - 1; methodIterator++){

    	for(int lineIterator = 0; lineIterator != Cur_File->MethodsInFile[methodIterator].GetCleanedLength(); lineIterator++){
    		Line = Cur_File->MethodsInFile[methodIterator].GetCleanedLine(lineIterator);

    		String2WString(Line, W_Line);
    		CleanedInput += W_Line + L"\n";
    	}
    }



    //Send it the preliminary cleaned lines, make an attribue to store that 
    //Tokenize input data and split into list of words
    list<freeling::word> wordList= tk.tokenize(CleanedInput);



    //Split list of words into sentences
    list<freeling::sentence> sentenceList = sp.split(wordList);


    morfo.analyze(sentenceList);
    tagger.analyze(sentenceList);


    PrintSentences(sentenceList);

}



void PrintSentences(const list<freeling::sentence> &ls){

  //For each sentence in the list
  for(list<freeling::sentence>::const_iterator is = ls.begin(); is != ls.end(); ++is){

    //For each word in a sentence   
    for(freeling::sentence::const_iterator w = is->begin(); w != is->end(); ++w){


      //Print word form
      wcout << L"word '" << w->get_form() << L"'" << endl;

      //Print possible analysis in word, output lemma and tag
      wcout << L"Possible analysis: {";

      for(freeling::word::const_iterator a = w->analysis_begin(); a != w->analysis_end(); ++a){

        wcout << L" (" << a->get_lemma() << L"," << a->get_tag() << L")";
      } 

      wcout << L" }" << endl;

      //Print analysis selected by the tagger
      wcout << L"  Selected analysis: (" << w->get_lemma() << L", " << w->get_tag() << L")" << endl;

    }

    //Sentence seperator
    wcout << endl;

  }
}