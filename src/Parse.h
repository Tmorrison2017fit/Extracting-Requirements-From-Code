#ifndef PARSE_H
#define PARSE_H


void Parse_Method(File* Cur_File);

void Read_File(string file, File* Cur_File);

// We need an Identify function that will be able to identify if
// the line of code is for initializaiton/assignment, conditional,
// loop, or comment.

#endif
