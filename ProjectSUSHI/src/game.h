#pragma once
#include"app.h"
#include"multiProce.h"
#include "gamePad.h"
#include "guest.h"
#include "player.h"
#include "sushi.h"

namespace nGame
{
	//背景描画
	void backdraw(cTexture& back)
	{
		// αブレンディングを有効にする
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//背景
		drawTexture(-WIDTH / 2, -HEIGHT / 2,
			WIDTH, HEIGHT,
			0, 0, WIDTH, HEIGHT,
			Color(1.0f, 1.0f, 1.0f),
			back);

		// αブレンディングを無効にする
		glDisable(GL_BLEND);
	}

	//置物（少し前に置くもの）
	void objectDraw(cTexture& geta){
		// αブレンディングを有効にする
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//カウンター
		drawFillBox(-WIDTH / 2, -HEIGHT / 2 + 100,
			WIDTH, 75,
			Color(0.8f, 0.5f, 0.0f));
		drawFillBox(-WIDTH / 2, -HEIGHT / 2,
			WIDTH, 100,
			Color(0.7f, 0.7f, 0.7f));

		//下駄
		drawTexture(-450, -HEIGHT / 2 + 100,
			250, 125,
			0, 0, 1024, 1024,
			Color(1.0f, 1.0f, 1.0f),
			geta);
		drawTexture(-125, -HEIGHT / 2 + 100,
			250, 125,
			0, 0, 1024, 1024,
			Color(1.0f, 1.0f, 1.0f),
			geta);
		drawTexture(200, -HEIGHT / 2 + 100,
			250, 125,
			0, 0, 1024, 1024,
			Color(1.0f, 1.0f, 1.0f),
			geta);

		// αブレンディングを無効にする
		glDisable(GL_BLEND);
	}

	void update(cApp& app, std::vector<cGamePad>& gamepad)
	{
		//背景画像
		cTexture backTex("res/background.raw",
			1024, 1024, true);
		//下駄
		cTexture getaTex("res/geta.raw",
			1024, 1024, true);

		//客
		cGuest guest(CENTER, IKA);
		//プレイヤー
		cPlayer player(CENTER, MAGURO);
		//寿司
		cSushi sushi;

		gamepad.emplace_back(cGamePad(0));
		while (1)
		{
			if (!app.isOpen()) exit(0);
			app.begin();
			updateGamePad(gamepad);

			backdraw(backTex);
			guest.draw();

			objectDraw(getaTex);
			player.draw();
			sushi.draw();

			guest.update();
			player.update(gamepad, CENTER);
			sushi.update(player.menu(),player.position());

			//作ろうとしたら判定
			if (player.makebool())
			{
				guest.judge(player.menu());
			}

			app.end();
		}
	}
}
