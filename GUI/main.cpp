#include <CtrlLib/CtrlLib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <dirent.h>

#if WIN32
	#include <windows.h>
#else
	#include <X11/Xlib.h>
#endif


using namespace Upp;
using namespace std;

/*
TODO LAYOUT
	
	File Saving
*/


struct GUILayout : TopWindow {
	
	
	Vector<String> files;
    String FilePath = "";
    String FileData = "";
	
	//Create a Menu Bar object, called menu, where the top menu is stored
	MenuBar menu;
	
	//Label Box is used to show areas on the Window, I = Input O = Output
	LabelBox I, O;
	
	//Doc Edit allows us to enter in large blocks of text
	DocEdit InputField, OutputField;
	
	ColumnList  Directory;
	FileSel Dir;
	
	int ScreenHeight, ScreenWidth;
	
	int dirLeftBound, dirRightBound;
	int inputLeftBound, inputRightBound;
	int outputLeftBound, outputRightBound;
	
	int padding = 4;
	
	
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
		bar.Add("Open File (CTRL+O)", [=] { OpenFile(); });
		bar.Add("Open Folder (CTRL+SHIFT+O)", [=] {OpenFolder(); });
	}
	
	/*
	Options for the 'Generate' column in the menu bar
	
	Maybe the generate button could perform different types of generation?
	The "Generate" button is in the center of the window, but it could
	be moved up to the menu for more space
	*/
	void SubMenuGen(Bar& bar) {
		bar.Add("Normal Generate (Ctrl+G)", [=] { IOFieldCopy(); });
		bar.Add("Advanced Generate", [=] {DummyFunc(); });
	}
	
	//Options for the 'Save' column in the menu bar
	void SubMenuSave(Bar& bar) {
		bar.Add("Save Output", [=] { OutputFieldSave(); });
	}
	
	//Options in the 'Other' column of the menu bar
	void SubMenuOther(Bar& bar) {
		bar.Add("About", [=] { DummyFunc(); });
		bar.Add("Exit (CTRL+X)", [=] {Exit(); });
	}
	
	//The Main Menu has 4 subcategories at the moment
	void MainMenu(Bar& bar) {
		bar.Sub("File", [=](Bar& bar) { SubMenuFile(bar); });
		
		bar.Sub("Generate", [=](Bar& bar) {SubMenuGen(bar); });
		
		bar.Sub("Save", [=](Bar& bar) {SubMenuSave(bar); });
		bar.Sub("Other", [=](Bar& bar) {SubMenuOther(bar); });
		
		//We could move "Generate" into the top menu if window space becomes an issue
	}
	
	
	void getScreenResolution(int &width, int &height){
	#if WIN32
		width = (int) GetSystemMetrics(SM_CXSCREEN);
		height = (int) GetSystemMetrics(SM_CYSCREEN);
	#else
		_XDisplay* disp = XOpenDisplay(NULL);
		Screen*  scrn = DefaultScreenOfDisplay(disp);
		width  = scrn->width;
		height = scrn->height;
	#endif
	}
	
	GUILayout() {
		Title("ReqEx").Zoomable().Sizeable().Maximize();
		//Grabs the screen size for the current system, used to
		//try and position the elements
		getScreenResolution(ScreenWidth, ScreenHeight);
	
		//The file directory takes up 10% of the screen, the fields take 45% each
		int dirSize = ScreenWidth * 0.10;
		int fieldSize = ScreenWidth * 0.45;
		
		//The directory starts the left of the screen, and goes for its size
		dirLeftBound = padding;
		dirRightBound = dirSize;
		
		//The input field goes from its left border, up until its size
		inputLeftBound = dirRightBound + 2*padding;
		inputRightBound = inputLeftBound + fieldSize;
		
		//The output starts after the right boundary of the input, and goes to the fieldSize
		outputLeftBound = inputRightBound + 3*padding;
	
		
		//Adds the menu bar onto the window
		AddFrame(menu);
		menu.Set([=](Bar& bar) {MainMenu(bar); });
		
		//Sets the dimensions for the other widgets on the window
		// Z Prefix is used for zooming, not sure if it is needed
		*this
			//LeftPos = (Distance from Left Border, Size (goes to right)
			//TopPos = (Distance from Top Border, Size (goes down))
			//VSizePos = (Distance from Top, Distance from Bottom)
			<< Directory.LeftPosZ(dirLeftBound,dirSize-2*padding).VSizePosZ(4,4)
			<< I.SetLabel("INPUT").LeftPosZ(inputLeftBound,64).TopPosZ(20,12)
			<< O.SetLabel("OUTPUT").LeftPosZ(outputLeftBound+2*(padding),64).TopPosZ(20,12)
			
			
			<< InputField.LeftPosZ(inputLeftBound,fieldSize-(2*padding)).VSizePosZ(40,16)
			<< OutputField.SetEditable(false).LeftPosZ(outputLeftBound+(2*padding),fieldSize).VSizePosZ(40,16)
			;
		
	}
	
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
	
	
	void CopyPath(){
		FilePath = "";
		if(files.GetCount())
			for(int i = 0; i < files.GetCount(); i++)
				FilePath = FilePath + files[i];
    }
    
    
    void DragAndDrop(Point p, PasteClip& d){
        if(IsDragAndDropSource())
            return;
        if(AcceptFiles(d)){
            files = GetFiles(d);
            CopyPath();
            OpenPath();
            InputField.Set(FileData);
            //TODO: Update Dir
            Refresh();
        }
    }
    
    bool Key(dword key, int count){
        if(key == K_CTRL_V) {
            files = GetFiles(Ctrl::Clipboard());
            CopyPath();
            OpenPath();
            InputField.Set(FileData);
            Refresh();
            return true;
        }
        
        //Map open file to CTRL+O
        if(key == K_CTRL_O) {
            OpenFile();
            return true;
        }
        
        //Map open Folder to CTRL+SHIFT+O
        if(key == K_CTRL+K_SHIFT+K_O) {
            OpenFolder();
            return true;
        }
        //Hotkey to Generate Ctrl+G
        if(key == K_CTRL_G) {
            IOFieldCopy();
            return true;
        }
        
        //Map Save to CTRL+S
        if(key == K_CTRL_S) {
            OutputFieldSave();
            return true;
        }
            
        
        //Map Exit to CTRL+X
        if(key == K_CTRL_X) {
            Exit();
            return true;
        }
        
        return false;
    }
    
    
    void LeftDrag(Point p, dword keyflags){
        if(files.GetCount()){
            VectorMap<String, ClipData> data;
            AppendFiles(data, files);
            DoDragAndDrop(data, Null, DND_COPY);
        }
    }
    
    
};


GUI_APP_MAIN {
	GUILayout gui;
		
	// X-Distance, Y-Distance
	Size minimum = Size(1000,600);
	gui.SetMinSize(minimum);
	
	gui.Run();


	
}
