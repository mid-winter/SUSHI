//
//SUSHI
//

#include"app.h"
#include"gamePad.h"
#include"title.h"
#include"settings.h"
#include"game.h"
#include"result.h"

int main()
{
	//アプリケーション準備
	cApp app("SUSHI", WIDTH, HEIGHT);

	//ゲームパッド
	std::vector<cGamePad>gamepads;

	//コントローラーの初期化
	initGamePad();

	while (true)
	{
		nTitle::update(app, gamepads);
		//nSetting::update(app, gamepads);
		nGame::update(app, gamepads);
		nResult::update(app, gamepads);
	}
}
