#ifndef PARSE_H
#define PARSE_H


//Reads a file from the input, and stores it in a File class object
void Read_File(string file, File* Cur_File);


//Grabs keywords from each method that exists in a File object
void Parse_File_Methods(File* Cur_File);

//Checks if a character in a line is a bad character
bool bad_chars(char c);

//Replaces all bad characters in a string, and returns that string modified
string ReplaceBadChars(string inputString);


/*
We need some Text Analysis tool that can determine which words are important
to the file, and which words can be ignored
*/
#endif
