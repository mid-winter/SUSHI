#pragma once
#include "app.h"
#include "multiProce.h"
#include "gamePad.h"

namespace nTitle
{
	//更新
	void update(cApp& app, std::vector<cGamePad>& gamepad)
	{
		//画像
		cTexture title("res/Title.raw",
			1024, 512, true);

		Color fadecolor = Color(0, 0, 0, 1);
		gamepad.emplace_back(cGamePad(0));

		bool a = true;

		while (a)
		{
			if (!app.isOpen()) exit(0);
			app.begin();

			updateGamePad(gamepad);
			// αブレンディングを有効にする
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//タイトル背景画像
			drawTexture(-WIDTH / 2, -HEIGHT / 2,
				WIDTH, HEIGHT,
				0, 0, 765, 512,
				Color(1, 1, 1),
				title);

			if (fadeIn(WIDTH, HEIGHT,
				fadecolor,
				0.02f))
			{
				//なにかボタンを押したとき次の画面に移行
				for (int i = 0; i < gamepad[0].buttons(); ++i)
				{
					if (gamepad[0].isPressButton(i))
					{
						a = false;
					}
				}
			}

			// αブレンディングを無効にする
			glDisable(GL_BLEND);
			app.end();
		}
	}
};
