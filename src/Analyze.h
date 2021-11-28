#ifndef ANALYZE_H
#define ANALYZE_H


#include "freeling.h"

//ALL THIS FREELING STUFF NEEDS TO USE WSTRINGS, SO FIRST CONVERT STRINGS TO WSTRINGS
//ALSO, FL NEEDS LISTS, SO CONVERT VECTORS TO LISTS, THEN LISTS BACK TO VECTORS WHEN DONE

int String2WString(const std::string &str, std::wstring &wstr);


int WString2String(const std::wstring &wstr, std::string &str);



std::vector<string> List2Vector(std::list<string> &inputList);


std::list<string> Vector2List(std::vector<string> &inputVector);


freeling::maco_options set_Maco_Options(const wstring &lang, const wstring &lpath);


void Analyze_Text(File *Cur_File);

void PrintSentences(const list<freeling::sentence> &wordList);



#endif