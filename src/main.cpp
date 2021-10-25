#include <iostream>
#include <string>
#include "Storage.cpp"
#include "Parse.cpp"
#include "Storage.h"
#include "Parse.h"

using namespace std;

int main(int argc,char* argv[]){

  // Allocates Memory to the File Class.
  File *TestFile = New_File(argv[0]);
  // Creates a Method object.
  File::Method obj;
  // Calls a function within the Method Class.
  obj.PutName("Test Name");
  // Adds the Method obj to the File Class.
  TestFile->AddMethod(obj);
  // Example on how to access the method within the File Class.
  cout << TestFile->List[0].GetName() << endl;
  // Not final, just used to test data storage
  Parse_File(argv[1], TestFile);

  // Prints the stored data.
  int size = TestFile->List[0].GetLength();
  for( int i =0; i<size; i++){
    cout << TestFile->List[0].GetLine(i) << endl;
  }

  return 0;
}
