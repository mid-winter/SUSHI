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
	cGamePad pad(0);

	//コントローラーの初期化
	initGamePad();

	nTitle::update(app, pad);
	nGame::update(app);
}