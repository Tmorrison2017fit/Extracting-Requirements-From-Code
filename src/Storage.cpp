#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <cctype>
#include "Storage.h"

using namespace std;

// Node Class Constructor.
Node::Node(){
  Parent = NULL;
};
// LinkedList Class Constructor.
LinkedList::LinkedList(){
  Root = NULL;
};
// Creates and Updates the Linked List Root.
void LinkedList::UpdateRoot(){
  Node* RootNode = new Node();
  RootNode->Name = "main";
  Root = RootNode;

};
// Creates the new nodes and attaches them onto the linked list.
void LinkedList::CreateNode(string NodeName, string ParentName){
  Node* newNode= new Node();
  Node* ParentPointer;
  newNode->Parent=NULL;
  newNode->Name = NodeName;
  ParentPointer = SearchParent(ParentName); // Searches for the Nodes Parent in the Tree.
  ParentPointer->Children.push_back(newNode);
  newNode->Parent = ParentPointer;
};
// Checks to see if the string passed exists within the current Linked List.
// Uses Breadth-First Search.
bool LinkedList::InLinkedList(string NodeName){
  queue<Node*> SearchQueue;
  Node* Temp;
  SearchQueue.push(Root);
  while(!SearchQueue.empty()){
    Temp = SearchQueue.front();
    SearchQueue.pop();
    if(Temp->Name == NodeName){
      return true;
    }
    if(!Temp->Children.empty()){
      for(int i = 0; i< Temp->Children.size(); i++){
        if(Temp->Children[i] != NULL){
          SearchQueue.push(Temp->Children[i]);
        }
      }
    }
  }
  return false;
};

// Searches for the Parent Node pointer, return NULL if nothing found.
// Uses Breadth-First Search.
Node* LinkedList::SearchParent(string ParentName){

  queue<Node*> SearchQueue;
  Node* Temp;
  SearchQueue.push(Root);
  while(!SearchQueue.empty()){
    Temp = SearchQueue.front();
    SearchQueue.pop();
    if(Temp->Name == ParentName){
      return Temp;
    }
    if(!Temp->Children.empty()){
      for(int i = 0; i< Temp->Children.size(); i++){
        if(Temp->Children[i] != NULL){
          SearchQueue.push(Temp->Children[i]);
        }
      }
    }
  }
  return NULL;
};

// Prints out the Linked List.
// Uses Breadth-First Search.
void LinkedList::PrintList(){
  queue<Node*> SearchQueue;
  Node* Temp;
  string PrevParent;
  SearchQueue.push(Root);
  while(!SearchQueue.empty()){
    Temp = SearchQueue.front();

    SearchQueue.pop();
    if(Temp->Name == "main"){
      cout << "Root: main" << endl;
    }
    else if(Temp->Parent != NULL && (PrevParent == Temp->Parent->Name)){
      cout << "   [-]Child: "<<Temp->Name << endl;
    }
    else if(Temp->Parent != NULL && (PrevParent != Temp->Parent->Name)){
      cout << "[+]Parent: "<< Temp->Parent->Name << "\n   [-]Child: "<<Temp->Name << endl;
      PrevParent = Temp->Parent->Name;
    }

    if(!Temp->Children.empty()){
      for(int i = 0; i< Temp->Children.size(); i++){
        SearchQueue.push(Temp->Children[i]);
      }
    }
  }
};
//-------------------------Method Class---------------------------
File::Method::Method(string MName){
  MethodName = MName;
};

int File::Method::GetLength(){
  return Lines.size();
};

string File::Method::GetName(){
  return MethodName;
};

string File::Method::GetLine(int index){
  return Lines[index];
};

void File::Method::AddLine(string Line){
    Lines.push_back(Line);
};

void File::Method::AddLoopRange(int begin, int finish){
  vector<int> newRange(2);
  newRange[0] = begin - 1; // -1 to make up for indexes starting at 0
  newRange[1] = finish;
  Loops.push_back(newRange);
};

vector<int> File::Method::GetLoopRange(int index){
  vector<int> Range(2);
  Range[0] = Loops[index][0];
  Range[1] = Loops[index][1];
  return Range;
};


int File::Method::GetCleanedLength(){
  return Cleaned_Lines.size();
}

string File::Method::GetCleanedLine(int index){
  return Cleaned_Lines[index];
};

void File::Method::AddCleanedLine(string Line){
  Cleaned_Lines.push_back(Line);
};


//------------------------------File Class--------------------------
File::File(string Name_of_File){
  FileName = Name_of_File;
};
void File::AddFileName(string Name){
  FileName = Name;
}
void File::AddMethod(Method NewEntry){
  MethodsInFile.push_back(NewEntry);
};

void File::AddMethodDef(string NewDef){
  MethodDefs.push_back(NewDef);
};

void File::AddLibrary(string NewLib){
  Libraries.push_back(NewLib);
};

void File::AddPreprocessors(string preProc){
  Preprocessors.push_back(preProc);
};

void File::AddComment(string CommentStr){
  Comments.push_back(CommentStr);
};

string File::GetMethodDef(int index){
  if(index < MethodDefs.size() && index >= 0){
    return MethodDefs[index];
  }
  else{
    return "Error: Index out of bounds";
  }

};

string File::GetLibrary(int index){
  if(index < Libraries.size() && index >= 0){
    return Libraries[index];
  }
  else{
    return "Error: Index out of bounds";
  }
};

string File::GetPreprocessors(int index){
  if(index < Preprocessors.size() && index >= 0){
    return Preprocessors[index];
  }
  else{
    return "Error: Index out of bounds";
  }
};

string File::GetComment(int index){
  if(index < Comments.size() && index >= 0){
    return Comments[index];
  }
  else{
    return "Error: Index out of bounds";
  }
};


int File::GetMethodDefLen(){
  return MethodDefs.size();
};

int File::GetLibraryLen(){
  return Libraries.size();
};

int File::GetPreprocessorsLen(){
  return Preprocessors.size();
};

int File::GetCommentLen(){
  return Comments.size();
};
//------------------------------------------------------------------
string StripString(string str){
  int Openindex;
  int start;
  string final = "";
  Openindex = str.find('(');
  start = Openindex-1;
  while (isalnum(str[start])){ //finds start of function name
    start--;
  }
  start++;

  while(start < Openindex){
    final = final + str[start];
    start++;
  }
  return final;
};
bool MultipleMethods(string str){
  int position = str.find('(');

  if(str.find('(', position+1) != -1){
    return true;
  }
  else{
    return false;
  }

};

void MethodTotal(string str, vector<string> & List){
  string name;
  int start;
  int position = str.find('(');

  while(position != -1){
      name = "";

      start = position - 1;
      while (isalnum(str[start])){ //finds start of function name
        start--;
      }
      start++;

      while(start < position){
        name = name + str[start];
        start++;
      }

      List.push_back(name);
      position = str.find('(', position + 1);
  }
}


File* New_File(string File_Name){
  File *NFile = new File(File_Name);
  return NFile;
};
