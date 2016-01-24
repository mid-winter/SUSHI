//
//SUSHI
//

#include"app.h"
#include"graphic.h"
#include"gamePad.h"

enum WindowSize
{
	WIDTH = 960,
	HEIGHT = 540
};

int main()
{
	//アプリケーション準備
	cApp app("SUSHI", WIDTH, HEIGHT);

	//画像
	cTexture title("res/Title.raw",
		1024, 512, true);

	while (1)
	{
		if (!app.isOpen()) exit(0);
		app.begin();

		// αブレンディングを有効にする
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//タイトル背景画像
		drawTexture(-WIDTH / 2, -HEIGHT / 2,
			WIDTH, HEIGHT,
			0, 0, 765, 512,
			title);

		// αブレンディングを無効にする
		glDisable(GL_BLEND);
		app.end();
	}
}