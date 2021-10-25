#ifndef PARSE_H
#define PARSE_H

void Parse_File(string file, File* Cur_File);

// We need an Identify function that will be able to identify if
// the line of code is for initializaiton/assignment, conditional,
// loop, or comment.
while (getline(file, line_buffer)){

    	// ********** Check if line is conditional statement **********
      	size_t found = line_buffer.find("if");
      	if(found != std::string::npos) {
      		cout << "conditional if statement\n";
      	}

        found = line_buffer.find("else if");
      	if(found != std::string::npos) {
      		cout << "conditional else if statement\n";
      	}

        found = line_buffer.find("else");
      	if(found != std::string::npos) {
      		cout << "conditional else statement\n";
      	}

        found = line_buffer.find("else");
      	if(found != std::string::npos) {
      		cout << "conditional else statement\n";
      	}

        found = line_buffer.find("switch");
      	if(found != std::string::npos) {
      		cout << "conditional switch statement\n";
      	}


    	// ********** Check if comment **********
        found = line_buffer.find("//");
      	if(found != string::npos) {
      		cout << "Single line comment: \n";
      	}

      	found = line_buffer.find("/*");
      	if(found != string::npos) {
      		cout << "Double line comment: \n";
      	}

    	// ********** Check if initialization or assignment **********
      	found = line_buffer.find(" = ");
      	if(found != string::npos) {
      		cout << "Initialization/Assignment Statement\n";
      	}

      // ********** Check if loop **********
        found = line_buffer.find("for");
      	if(found != string::npos) {
      		cout << "For loop\n";
      	}
        found = line_buffer.find("while");
      	if(found != string::npos) {
      		cout << "While loop\n";
      	}

  }

#endif
