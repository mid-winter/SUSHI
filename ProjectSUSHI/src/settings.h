#pragma once
#include"app.h"
#include"multiProce.h"
#include"gamePad.h"

namespace nSetting
{
	//更新
	void update(cApp& app, std::vector<cGamePad>& gamepad)
	{
		//画像
		cTexture title("res/TitleScene/title.raw",
			1024, 512, true);

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
			drawFillBox(
				-WIDTH / 2, -HEIGHT / 2,
				WIDTH, HEIGHT,
				Color(0, 1, 1));

			if (fadeIn(WIDTH, HEIGHT,
				fadecolor,
				0.02f))
			{
				//なにかボタンを押したとき次の画面に移行
				for (int i = 0; i < gamepad[0].buttons(); ++i)
				{
					if (gamepad[0].isPressButton(i))
					{
						clear_score = 2000;
						limit_time = 120;
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
