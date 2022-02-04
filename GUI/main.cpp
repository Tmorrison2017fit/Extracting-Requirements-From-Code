#include <CtrlLib/CtrlLib.h>

//This layout include might need to be changed around
//depending on where it is stored at

// TODO: CHANGE ReqExGUI TO WHATEVER YOU NAMED YOUR PROJECT AS 
#define LAYOUTFILE <ReqExGUI/GUILayout.lay>

#include <CtrlCore/lay.h>


using namespace Upp;

/*
TODO LAYOUT
	Fix window resizing issue
	Implement button functions
	Add other panels and features
*/


//An object to hold the entire GUI
struct MainScreenDlg : public WithMainScreen<TopWindow> {
	
	//Create a MenuBar object, called menu, where the top menu is stored
	MenuBar menu;
	
	
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
	
	Their will probably be different opening options for different structs
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
	
	
	//THe Main Menu has 4 subcategories at the moment
	void MainMenu(Bar& bar) {
		bar.Sub("File", [=](Bar& bar) { SubMenuFile(bar); });
		
		bar.Sub("Generate", [=](Bar& bar) {SubMenuGen(bar); });
		
		bar.Sub("Save", [=](Bar& bar) {SubMenuSave(bar); });
		bar.Sub("Other", [=](Bar& bar) {SubMenuOther(bar); });
		
		//We could move "Generate" into the top menu if window space becomes an issue
	}
	
	
	//Add the other items from the template in the Layout file
	MainScreenDlg();
};

//Runs the preset template and the Menu bar as a whole application
MainScreenDlg::MainScreenDlg()
{
	/*
	Give the window a name, add a frame to the window, and make the menu
	a Main Menu bar
	*/
	CtrlLayout(*this, "ReqEx");
	AddFrame(menu);
	menu.Set([=](Bar& bar) {MainMenu(bar); });
	
}
	

//Main controller for the program
GUI_APP_MAIN
{
	//Run the program, and allow it to be resized
	MainScreenDlg().Sizeable().Run();

}
