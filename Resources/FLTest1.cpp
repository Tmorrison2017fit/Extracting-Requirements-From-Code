#include <iostream>
#include "freeling.h"

using namespace std;



//Do whatever is needed with analyzed sentences//
//Right now just print out analyzed words//
void ProcessSentences(const list<freeling::sentence> &ls){


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



/*

Set desired options for the morphological analyzer

*/

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



//Main Program//
int main(int argc, char **argv){

	//Set locale to an UTF8 compatible locale
	freeling::util::init_locale(L"default");

	//Get requested language from arg1, or English if not provided
	wstring lang = L"en";

	if(argc > 1) lang = freeling::util::string2wstring(argv[1]);

	//Get installation path to use from arg2, or use /usr/local if not provided
	wstring ipath = L"/usr/local";

	if (argc > 2) ipath = freeling::util::string2wstring(argv[2]);


	//path to language data
	wstring lpath = ipath + L"/share/freeling/" + lang + L"/";


	//Create analyzers
	freeling::tokenizer tk(lpath + L"tokenizer.dat");
	freeling::splitter sp(lpath + L"splitter.dat");


	//Create the analyzer with the required set of maco_options
	freeling::maco_options opt = my_maco_options(lang, lpath);
	freeling::maco morfo(opt);


	//then, (de)activate required modules
	morfo.set_active_options(	false,	//UserMap
								true,	//NumbersDetection
								true,	//PunctuationDetection
								true,	//DatesDetetction
								true,	//DictionarySearch
								true,	//AffixAnalysis
								false,	//CompoundAnalysis
								true,	//RetokContractions
								true,	//MultiwordDetection
								true,	//NERecognition
								false,	//QuantitiesDetection
								true);	//ProbabilitiesAssignment


	//Create a hmm tagger (with retokenization ability, and forced
	//to choose only one tag per word)

	freeling::hmm_tagger tagger(lpath+L"tagger.dat", true, FORCE_TAGGER);


	//Get all input text in a single file
	wstring text = L"";

	wstring line;

	while(getline(wcin, line)){
		text = text + line + L"\n";
	}

	//tokenize input line into a list of words
	list<freeling::word> lw = tk.tokenize(text);

	//split list of words in sentences, return list of sentences
	list<freeling::sentence> ls = sp.split(lw);


	//perform morphosyntactic analysis and disambiguation
	morfo.analyze(ls);
	tagger.analyze(ls);



	//Do whatever is needed with processed sentences
	ProcessSentences(ls);
}
