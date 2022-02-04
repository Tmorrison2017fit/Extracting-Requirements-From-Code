#include <CtrlLib/CtrlLib.h>

using namespace Upp;

/*
TODO LAYOUT
	Fix window resizing issue
	Implement button functions
	Add other panels and features
*/




struct GUILayout : TopWindow {
	
	
	//Create a Menu Bar object, called menu, where the top menu is stored
	MenuBar menu;
	
	//Label Box is used to show areas on the Window, I = Input O = Output
	LabelBox I, O;
	
	//Doc Edit allows us to enter in large blocks of text
	DocEdit InputField, OutputField;
	
	//Generate Button to place in center of window 
	Button GenButton;
	
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
		bar.Add("Open File", [=] { DummyFunc(); });
		bar.Add("Open Folder", [=] {DummyFunc(); });
	}
		
	/*
	Options for the 'Generate' column in the menu bar
	
	Maybe the generate button could perform different types of generation?
	The "Generate" button is in the center of the window, but it could
	be moved up to the menu for more space
	*/
	void SubMenuGen(Bar& bar) {
		bar.Add("Normal Generate", [=] { DummyFunc(); });
		bar.Add("Advanced Generate", [=] {DummyFunc(); });
	}
	
	//Options for the 'Save' column in the menu bar
	void SubMenuSave(Bar& bar) {
		bar.Add("Save Output", [=] { DummyFunc(); });
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
			<< I.SetLabel("INPUT").LeftPosZ(12,64).TopPosZ(28,24)
			<< O.SetLabel("OUTPUT").RightPosZ(20,64).TopPosZ(28,24)
			<< InputField.LeftPosZ(8,344).VSizePosZ(68,16)
			<< OutputField.RightPosZ(12,272).VSizePosZ(64,12)
			<< GenButton.SetLabel("Generate").HCenterPosZ(80,36).VCenterPosZ(32.8)
			;
		
	}	
};



GUI_APP_MAIN {
	GUILayout gui;
	
	
	// Center X, Center Y, X Distance, Y Distance
	gui.SetRect(0,0,1000,500);
	
	
	gui.Run();


}