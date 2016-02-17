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
		//勝利文字
		cTexture winTex("res/Result/win.raw",
			1024, 512, true);
		//敗北文字
		cTexture loseTex("res/Result/lose.raw",
			1024, 512, true);

		//日本語
		cTexture japaneseTex("res/japanese.raw",
			1024, 1024, true);

		Color fadecolor = Color(0, 0, 0, 1);
		gamepad.emplace_back(cGamePad(0));

		float alpha = 0;
		//タイトルロゴの動き
		float angle = 0.0f;
		float aaa = 0.0f;

		//フェードアウト
		bool fadeoutbool = false;

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
					Color(0.8f, 0.3f, 0.3f),
					backTex);

				//暗くする
				drawFillBox(-WIDTH / 2, -HEIGHT / 2,
					WIDTH, HEIGHT,
					Color(0, 0, 0, 0.5));

				//勝利
				drawTexture(-300, -100,
					600, 300,
					0, 0,
					1024, 512,
					Color(1, 1, 1, alpha),
					winTex);
			}
			else if (result == LOSE)
			{
				drawTexture(-WIDTH / 2, -HEIGHT / 2,
					WIDTH, HEIGHT,
					0, 0, 765, 512,
					Color(0.3f, 0.3f, 0.8f),
					backTex);

				//暗くする
				drawFillBox(-WIDTH / 2, -HEIGHT / 2,
					WIDTH, HEIGHT,
					Color(0, 0, 0, 0.5));

				//敗北
				drawTexture(-300, -100,
					600, 300,
					0, 0,
					1024, 512,
					Color(1, 1, 1, alpha),
					loseTex);
			}

			angle += 0.05f;
			aaa = std::abs(std::sin(angle *0.5f));

			if (fadeoutbool)
			{
				if(fadeOut(WIDTH, HEIGHT,
					fadecolor,
					0.02f))
				{
					for (int i = 0; i < 4; ++i)
					{
						selectMenu[i] = NONE;
					}
					loop = true;
				}
			}

			//フェードインしたかどうか
			if (fadeIn(WIDTH, HEIGHT, fadecolor, 0.02f))
			{
				if (alpha <= 1.0f)
				{
					alpha += 0.02f;
				}
				else
				{
					//なにかボタンを押してください
					drawTexture(-250, -200,
						500, 50,
						0, 100 * 2, 100 * 10, 100,
						Color(1, 1, 1, aaa),
						japaneseTex);

					//なにかボタンを押したとき次の画面に移行
					for (int i = 0; i < gamepad[0].buttons(); ++i)
					{
						if (gamepad[0].isPressButton(i))
						{
							loop = false;
						}
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
