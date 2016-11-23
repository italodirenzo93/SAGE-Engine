#include "MyGame.h"

#if defined(_WIN32) && defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <Windows.h>
#include <crtdbg.h>
#endif // _WIN32 && _DEBUG

int main(int argc, char* argv[])
{
#if defined(_WIN32) && defined(_DEBUG)
	int dbgFlags = ::_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	// bitwise or checks the block integrity on every memory call
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;
	//don't always remove blocks on delete
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;
	//check for memory leaks at process terminatio
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(dbgFlags);
#endif // _WIN32 && _DEBUG
	try {
		std::unique_ptr<cGame> game(new cMyGame);
		game->Run();
	}
	catch (std::exception const& e) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Exception", e.what(), NULL);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}