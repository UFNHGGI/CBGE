#include <Engine.h>

int main(int argc, char** argv)
{
	CGame::Init(800, 600, "CBGE");
	if(argc == 2)
		CGame::Load(argv[1]);
	CGame::Run();
	return 1;
}
