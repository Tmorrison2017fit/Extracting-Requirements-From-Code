#ifndef ANALYZE_H
#define ANALYZE_H


//ALL THIS FREELING STUFF NEEDS TO USE WSTRINGS, SO FIRST CONVERT STRINGS TO WSTRINGS
//ALSO, FL NEEDS LISTS, SO CONVERT VECTORS TO LISTS, THEN LISTS BACK TO VECTORS WHEN DONE


int String2WString(std::wstring &ws, const std::string &s);


freeling::maco_options set_Maco_Options(const wstring &lang, const wstring &lpath);


void Analyze_Text(File *Cur_File);

void PrintSentences(const list<freeling::sentence> &wordList);




/*
One-Liner to Copy All elements of a list into a vector, then erase the list 

Some vector of type T                           Some lists of type T
vector<string> vecName{std::make_move_iterator(std::begin(L)), std::make_move_iterator(std::end(L))};

*/


#endif