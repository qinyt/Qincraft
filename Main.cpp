#include "Application.h"

#define HEAP 0
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int main(int argc, char** argv)
{
#if HEAP
	App* app = new App();
	app->init();
	app->loop();
#else
	App app;
	app.init();
	app.loop();
#endif
	return 1;
}

