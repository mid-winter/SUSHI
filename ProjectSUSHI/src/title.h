#pragma once
#include "app.h"
#include "multiProce.h"
#include "gamePad.h"

namespace nTitle
{
	//更新
	void update(cApp& app, cGamePad& gamepad)
	{
		//画像
		cTexture title("res/Title.raw",
			1024, 512, true);

		Color fadecolor = Color(0, 0, 0, 1);

		bool endbool = false;

		while (1)
		{
			if (!app.isOpen()) exit(0);
			app.begin();

			// αブレンディングを有効にする
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//タイトル背景画像
			drawTexture(-960 / 2, -540 / 2,
				960, 540,
				0, 0, 765, 512,
				Color(1, 1, 1),
				title);

			gamepad.update();

			if (fadeIn(WIDTH, HEIGHT,
				fadecolor,
				0.02f))
			{
				//なにかボタンを押したとき次の画面に移行
				for (int i = 0; i < gamepad.buttons(); ++i)
				{
					if (gamepad.isPressButton(i))
					{
						exit(0);
					}
				}
			}

			// αブレンディングを無効にする
			glDisable(GL_BLEND);
			app.end();
		}
	}
};
