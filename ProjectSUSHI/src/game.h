#pragma once
#include"app.h"
#include"multiProce.h"
#include "gamePad.h"

namespace nGame
{
	void update(cApp& app, std::vector<cGamePad>& gamepad)
	{
		//背景画像
		cTexture backTex("res/background.raw",
			1024, 1024,
			true);
		cTexture counterTex("res/counter.raw",
			1024, 1024,
			true);

		gamepad.emplace_back(cGamePad(0));
		while (1)
		{
			if (!app.isOpen()) exit(0);
			app.begin();
			updateGamePad(gamepad);

			// αブレンディングを有効にする
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//背景
			drawTexture(-WIDTH / 2, -HEIGHT / 2,
				WIDTH, HEIGHT,
				0, 0, WIDTH, HEIGHT,
				Color(1, 1, 1),
				backTex);

			//カウンター
			drawTexture(-WIDTH / 2, -HEIGHT / 2,
				WIDTH, HEIGHT,
				0, 0, WIDTH, HEIGHT,
				Color(1, 1, 1),
				counterTex);

			// αブレンディングを無効にする
			glDisable(GL_BLEND);
			app.end();
		}
	}
}
