#pragma once
#include"app.h"
#include "multiProce.h"
#include "gamePad.h"

namespace nResult
{
	//更新
	void update(cApp& app, std::vector<cGamePad>& gamepad)
	{
		//背景画像
		cTexture backTex("res/background.raw",
			1024, 1024, true);

		Color fadecolor = Color(0, 0, 0, 1);
		gamepad.emplace_back(cGamePad(0));

		bool loop = true;
		while (loop)
		{
			if (!app.isOpen()) exit(0);
			app.begin();

			updateGamePad(gamepad);
			// αブレンディングを有効にする
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//背景画像

			if (result == WIN)
			{
				drawTexture(-WIDTH / 2, -HEIGHT / 2,
					WIDTH, HEIGHT,
					0, 0, 765, 512,
					Color(1, 0, 0),
					backTex);
			}
			else if (result == LOSE)
			{
				drawTexture(-WIDTH / 2, -HEIGHT / 2,
					WIDTH, HEIGHT,
					0, 0, 765, 512,
					Color(0, 0, 1),
					backTex);
			}

			//暗くする
			drawFillBox(-WIDTH / 2, -HEIGHT / 2,
				WIDTH, HEIGHT,
				Color(0, 0, 0, 0.5));

			//フェードインしたかどうか
			if (fadeIn(WIDTH, HEIGHT, fadecolor, 0.02f))
			{
				//なにかボタンを押したとき次の画面に移行
				for (int i = 0; i < gamepad[0].buttons(); ++i)
				{
					if (gamepad[0].isPressButton(i))
					{
						loop = false;
					}
				}
			}

			// αブレンディングを無効にする
			glDisable(GL_BLEND);
			app.end();
		}
		gamepad.clear();
	}
};
