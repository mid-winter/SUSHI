//
//SUSHI
//

#include"app.h"

enum WindowSize
{
	WIDTH = 960,
	HEIGHT = 560
};

int main()
{
	//アプリケーション準備
	cApp app("SUSHI", WIDTH, HEIGHT);

	while (1)
	{
		if (!app.isOpen()) exit(0);
		app.begin();

		app.end();
	}
}