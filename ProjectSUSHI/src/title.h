#pragma once
#include "app.h"
#include "multiProce.h"
#include "gamePad.h"
#include "random.h"

namespace nTitle
{
	void Choose()
	{
		cRandom random;
		random.setSeed(rand());
		for (int i = 0; i < 4; ++i)
		{
			selectMenu[i] =
				random.fromFirstLast(MAGURO, HOTATE);

			if (selectMenu[0] == selectMenu[1] ||
				selectMenu[0] == selectMenu[2] ||
				selectMenu[0] == selectMenu[3])
			{
				selectMenu[0] =
					random.fromFirstLast(MAGURO, HOTATE);
			}

			if (selectMenu[1] == selectMenu[0] ||
				selectMenu[1] == selectMenu[2] ||
				selectMenu[1] == selectMenu[3])
			{
				selectMenu[1] =
					random.fromFirstLast(MAGURO, HOTATE);
			}

			if (selectMenu[2] == selectMenu[0] ||
				selectMenu[2] == selectMenu[1] ||
				selectMenu[2] == selectMenu[3])
			{
				selectMenu[2] =
					random.fromFirstLast(MAGURO, HOTATE);
			}

			if (selectMenu[3] == selectMenu[0] ||
				selectMenu[3] == selectMenu[1] ||
				selectMenu[3] == selectMenu[2])
			{
				selectMenu[3] =
					random.fromFirstLast(MAGURO, HOTATE);
			}

		}
	}

	//更新
	void update(cApp& app, std::vector<cGamePad>& gamepad)
	{
		//画像
		cTexture titleTex("res/TitleScene/title.raw",
			1024, 512, true);
		cTexture titleLogoTex("res/TitleScene/logo.raw",
			1024, 1024, true);
		cTexture japaneseTex("res/japanese.raw",
			1024, 1024, true);

		Color fadecolor = Color(0, 0, 0, 1);
		gamepad.emplace_back(cGamePad(0));

		//タイトルロゴの動き
		float angle = 0.0f;
		float aaa = 0.0f;

		//文字表示の透過度
		float alpha = 0;

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

			//タイトル背景
			drawTexture(-WIDTH / 2, -HEIGHT / 2,
				WIDTH, HEIGHT,
				0, 0, 765, 512,
				Color(1, 1, 1),
				titleTex);

			//タイトル文字

			drawTexture(-250 - aaa / 2 - 1, -150 - aaa / 2 - 1,
				500 + aaa - 2, 400 + aaa - 2,
				0, 0, 800, 650,
				Color(1, 1, 1),
				titleLogoTex);

			//なにかボタンを押してください
			drawTexture(-250, -200,
				500, 50,
				0, 100 * 2, 100 * 10, 100,
				Color(1, 1, 1, alpha),
				japaneseTex);

			if (!fadeoutbool)
			{
				angle += 0.05;
				aaa = std::abs(std::sin(angle)) * 30;
				alpha = std::abs(std::sin(angle * 0.5f));

				if (fadeIn(WIDTH, HEIGHT,
					fadecolor,
					0.02f))
				{
					//なにかボタンを押したとき次の画面に移行
					for (int i = 0; i < gamepad[0].buttons(); ++i)
					{
						if (gamepad[0].isPressButton(i))
						{
							fadeoutbool = true;
						}
					}
				}
			}
			else
			{
				Choose();

				if (fadeOut(WIDTH, HEIGHT,
					fadecolor,
					0.02f))
				{
					loop = false;
				}
			}

			// αブレンディングを無効にする
			glDisable(GL_BLEND);
			app.end();
		}
		gamepad.clear();
	}
};
