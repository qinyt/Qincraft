#include "Application.h"


//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int main(int argc, char** argv)
{
	//FIXME: stack or heap ?
	App* app = new App();
	app->init();
	app->loop();
	return 1;
}

