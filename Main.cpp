#include "Application.h"


//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int main(int argc, char** argv)
{
	//FIXME: stack or heap ?
	App app;
	app.init();
	app.loop();
	return 1;
}

