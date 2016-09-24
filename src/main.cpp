#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"

//========================================================================
int main( ){
//	ofGLESWindowSettings settings;
	ofGLFWWindowSettings settings;
//	ofGLWindowSettings settings;

	settings.width = 1680;
	settings.height = 1050;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);

	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<GuiApp> guiApp(new GuiApp);
	mainApp->gui = guiApp;

	ofRunApp(guiWindow, guiApp);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();
}
