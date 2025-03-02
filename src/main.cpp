#include <iostream>
#include <string>

#include "Storage.h"
#include "Storage.cpp"

#include "Parse.h"
#include "Parse.cpp"

//#include "Analyze.h"
//#include "Analyze.cpp"



using namespace std;

void printFunction(File *FileObj);

int main(int argc,char* argv[]){

  LinkedList* LogicTree = new LinkedList(); // Creates the Linked List Object.
  File* TestFile = New_File(argv[1]);
  TestFile->AddFileName(argv[1]);
  cout << "Reading File: " << argv[1]<< endl << endl;
  Read_File(argv[1], TestFile, LogicTree);
  Parse_File_Methods(TestFile);
  cout << "Printing Parsed Contents: " << endl << endl;
  printFunction(TestFile);

  cout << "Printing Logic Flow Tree: " << endl << endl;
  LogicTree->PrintList(); // Prints the Linked List that was created in Read_File();


  cout << "Analyzing Text: " << endl << endl;
  //Analyze_Text(TestFile);


// try
//               {
//                   SqlConnectionStringBuilder builder = new SqlConnectionStringBuilder();
//                   builder.DataSource = "reqex.database.windows.net";
//                   builder.UserID = "reqex";
//                   builder.Password = "Yatyas1833!!!";
//                   builder.InitialCatalog = "reqex";
//
//                   using (SqlConnection connection = new SqlConnection(builder.ConnectionString))
//                   {
//                       Console.WriteLine("\nQuery data example:");
//                       Console.WriteLine("=========================================\n");
//
//                       String sql = "SELECT name, collation_name FROM sys.databases";
//
//                       using (SqlCommand command = new SqlCommand(sql, connection))
//                       {
//                           connection.Open();
//                           using (SqlDataReader reader = command.ExecuteReader())
//                           {
//                               while (reader.Read())
//                               {
//                                   Console.WriteLine("{0} {1}", reader.GetString(0), reader.GetString(1));
//                               }
//                           }
//                       }
//                   }
//               }
//               catch (SqlException e)
//               {
//                   Console.WriteLine(e.ToString());
//               }
//               Console.ReadLine();
  return 0;
}

void printFunction(File *FileObj){

  int MethodDefs = FileObj->GetMethodDefLen();
  int preProcLen = FileObj->GetPreprocessorsLen();
  int LibLen = FileObj->GetLibraryLen();
  int MethodLen = FileObj->MethodsInFile.size();
  int CommentLen = FileObj->GetCommentLen();
  cout << "Lists of Included Libraries: " << endl;
  for( int i = 0; i < LibLen ; i++){
    cout << FileObj->GetLibrary(i) << endl;
  }
  cout << endl;
  cout << "Lists of defined Preprocessors: " << endl;
  for( int i = 0; i < preProcLen ; i++){
    cout << FileObj->GetPreprocessors(i) << endl;
  }
  cout << endl;
  cout << "Lists of Method Declarations: " << endl;
  for( int i = 0; i < MethodDefs ; i++){
    cout << FileObj->GetMethodDef(i) << endl;
  }
  cout << endl;
  cout << "Lists of Methods: " << endl;
  for( int i = 0; i < MethodLen ; i++){
    int Lines = FileObj->MethodsInFile[i].GetLength();
    for( int j = 0; j < Lines;j++){
      cout << FileObj->MethodsInFile[i].GetLine(j) << endl;
    }
    cout << endl;
  }

  cout << endl;


  cout << "Lists of Cleaned Methods: " << endl;
  for( int i = 0; i < MethodLen ; i++){
    int Lines = FileObj->MethodsInFile[i].GetCleanedLength();
    for( int j = 0; j < Lines;j++){
      cout << FileObj->MethodsInFile[i].GetCleanedLine(j) << endl;
    }
    cout << endl;
  }

  cout << endl;


  cout << "Lists of Comments: " << endl;
  for( int i = 0; i < CommentLen ; i++){
    cout << FileObj->GetComment(i) << endl;
  }

  cout << endl;

}
