
#include <CtrlLib/CtrlLib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <dirent.h>
using namespace Upp;
using namespace std;
/*
TODO LAYOUT
	Fix window resizing issue

	Implement button functions
		Currently Implemented
		-> Exit
		-> Middle/ Normal Generate
		-> Save Output

	Add other panels and features
*/

struct GUILayout : TopWindow {





    Vector<String> files;
    String FilePath = "";
   	String FileData= "";

	//Create a Menu Bar object, called menu, where the top menu is stored
	MenuBar menu;

	//Label Box is used to show areas on the Window, I = Input O = Output
	LabelBox I, O;

	//Doc Edit allows us to enter in large blocks of text
	DocEdit InputField, OutputField;

	ColumnList  Directory;
	//Generate button in the center of the window
	Button GenButton;
	FileSel Dir;

	//Copies text from the input field and pastes to the output field
	//This can then be switched up to run the actual program
	void IOFieldCopy() {

		//We can save the input text as a string, useful to send to
		//analyzing functions
		String inText = InputField.Get();

		//Sets a string into the output field
		OutputField.Set(inText);

	}


	//Function to save whatever is in the output field to a file
	void OutputFieldSave() {

		String outText = OutputField.Get();


		//Look into relative file paths, right now we can use absolutes
		String file = "TestOutput.txt";

		//String file = "/home/zbruggen/Documents/TestOutput.txt";

		//If we can write to the file successfully, we indicate that
		if(SaveFile(file, outText))
			PromptOK("SUCCESS");
		else
			PromptOK("FAIL");

	}

	/*
	This is just a dummy function to hold operations that the
	buttons will perform

	Each button will need it's own function to operate, and then have the
	call replaced for whatever button it's using
	*/
	void DummyFunc() {
		PromptOK("foo");
	}


	//Function to exit the program from the close option in Other
	void Exit() {
		if(PromptOKCancel("Exit ReqEx?"))
			Break();
	}

	/*
	Options for the 'File' column in the menu bar

	Their will probably be different opening options for different types
	(Directory, File, etc.)
	*/
	void SubMenuFile(Bar& bar) {
		bar.Add("Open File", [=] { OpenFile(); });
		bar.Add("Open Folder", [=] {OpenFolder(); });
	}

	/*
	Options for the 'Generate' column in the menu bar

	Maybe the generate button could perform different types of generation?
	The "Generate" button is in the center of the window, but it could
	be moved up to the menu for more space
	*/
	void SubMenuGen(Bar& bar) {
		bar.Add("Normal Generate", [=] { IOFieldCopy(); });
		bar.Add("Advanced Generate", [=] {DummyFunc(); });
	}

	//Options for the 'Save' column in the menu bar
	void SubMenuSave(Bar& bar) {
		bar.Add("Save Output", [=] { OutputFieldSave(); });
	}

	//Options in the 'Other' column of the menu bar
	void SubMenuOther(Bar& bar) {
		bar.Add("About", [=] { DummyFunc(); });
		bar.Add("Exit", [=] {Exit(); });
	}

	//The Main Menu has 4 subcategories at the moment
	void MainMenu(Bar& bar) {
		bar.Sub("File", [=](Bar& bar) { SubMenuFile(bar); });

		bar.Sub("Generate", [=](Bar& bar) {SubMenuGen(bar); });

		bar.Sub("Save", [=](Bar& bar) {SubMenuSave(bar); });
		bar.Sub("Other", [=](Bar& bar) {SubMenuOther(bar); });

		//We could move "Generate" into the top menu if window space becomes an issue
	}

	GUILayout() {
		Title("ReqEx").Zoomable().Sizeable();

		//Adds the menu bar onto the window
		AddFrame(menu);
		menu.Set([=](Bar& bar) {MainMenu(bar); });

		//Sets the dimensions for the other widgets on the window
		*this
			<< Directory.LeftPosZ(4,130).VSizePosZ(4,4)
			<< I.SetLabel("INPUT").LeftPosZ(150,64).TopPosZ(28,24)
			<< O.SetLabel("OUTPUT").RightPosZ(20,64).TopPosZ(28,24)
			<< InputField.LeftPosZ(150,344).VSizePosZ(68,16)
			<< OutputField.RightPosZ(12,272).VSizePosZ(64,12)
			<< GenButton.SetLabel("Generate").HCenterPosZ(80,36).VCenterPosZ(32,8)
			;


		//Middle Generate Button Functionality
		GenButton << [=] {
			IOFieldCopy();
		};

	}
	//-----------------------------------------------------------------------
	void DisplayFilePath(int i){
		if(FilePath.GetCount()){
			DIR *dr;
			struct dirent *en;

			if (dr) {
				Directory.Clear();
				if(i){
					dr = opendir(FilePath); //open all or present directory
				}
				else{
					dr = opendir(FilePath+"\\..");
				}
	    		while ((en = readdir(dr)) != NULL) {
	    	    	Directory.Add(en->d_name,true);
				}
				closedir(dr); //close all directory
	    	}

		}
		Refresh();
	}
	void OpenFile(){ // Opens File
		if(Dir.ExecuteOpen()){
			FilePath = Dir.Get();
			DisplayFilePath(0);
			OpenPath();
        	InputField.Set(FileData);
		}
	}
	void OpenFolder(){
		if(Dir.ExecuteSelectDir()){
			FilePath = Dir.Get();
			//InputField.Set(FilePath);
			DisplayFilePath(1);
		}
	}
	void OpenPath(){
		ifstream infile;
   		infile.open(FilePath);
   	if(infile) {
      ostringstream string;
      string << infile.rdbuf(); // reading data
      FileData = string.str();
   }

   		infile.close();
	}

	void CopyPath()
{
	FilePath = "";
    if(files.GetCount())
        for(int i = 0; i < files.GetCount(); i++)
            FilePath = FilePath + files[i];

}
	void DragAndDrop(Point p, PasteClip& d)
{
    if(IsDragAndDropSource())
        return;
    if(AcceptFiles(d)) {
        files = GetFiles(d);
        CopyPath();
        OpenPath();
        InputField.Set(FileData);
        //TODO: Update Dir
        Refresh();
    }
}

bool Key(dword key, int count)
{
    if(key == K_CTRL_V) {
        files = GetFiles(Ctrl::Clipboard());
        CopyPath();
        OpenPath();
        InputField.Set(FileData);
        Refresh();
        return true;
    }
    return false;
}

void LeftDrag(Point p, dword keyflags)
{
    if(files.GetCount()) {
        VectorMap<String, ClipData> data;
        AppendFiles(data, files);
        DoDragAndDrop(data, Null, DND_COPY);
    }
}
};



GUI_APP_MAIN {
	GUILayout gui;


	// Center X, Center Y, X Distance, Y Distance
	gui.SetRect(0,0,2500,1500);


	gui.Run();


}
