//
//SUSHI
//

#include"app.h"
#include"gamePad.h"
#include"title.h"
#include"game.h"

int main()
{
	//アプリケーション準備
	cApp app("SUSHI", WIDTH, HEIGHT);

	//ゲームパッド
	std::vector<cGamePad>gamepads;

	//コントローラーの初期化
	initGamePad();

	//nTitle::update(app, gamepads);
	nGame::update(app, gamepads);
}