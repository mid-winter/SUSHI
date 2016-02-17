#pragma once
#include"app.h"
#include"multiProce.h"
#include "gamePad.h"
#include "guest.h"
#include "player.h"
#include "time.h"
#include "score.h"
#include"cout.h"
#include<mutex>

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

	//ポーズ描画
	void pauseDraw(cTexture& japaneseTex, cTexture& numberJapTex)
	{
		// αブレンディングを有効にする
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//少し暗く
		drawFillBox(-WIDTH / 2, -HEIGHT / 2,
			WIDTH, HEIGHT,
			Color(0, 0, 0, 0.7f));

		//文字
		drawTexture(-75 * 2, 50,
			75 * 4, 75,
			0, 100,
			100 * 4, 100,
			Color(1, 1, 1),
			japaneseTex);

		//目標
		drawTexture(-400, -100,
			200, 100,
			0, 100 * 6,
			100 * 2, 100,
			Color(1, 1, 1),
			japaneseTex);


		int score1000 = clear_score / 1000 % 10;
		int score100 = clear_score / 100 % 10;
		int score10 = clear_score / 10 % 10;

		//数字
		//一ケタ目	確実に0
		drawTexture(-400 + 100 * 6, -100,
			100, 100,
			0, 0,
			100, 100,
			Color(1, 1, 1),
			numberJapTex);

		//十ケタ目
		if (clear_score >= 10)
		{
			drawTexture(-400 + 100 * 5, -100,
				100, 100,
				0 + score10 * 100, 0,
				100, 100,
				Color(1, 1, 1),
				numberJapTex);
		}

		//百ケタ目
		if (clear_score >= 100)
		{
			drawTexture(-400 + 100 * 4, -100,
				100, 100,
				0 + score100 * 100, 0,
				100, 100,
				Color(1, 1, 1),
				numberJapTex);
		}

		//千ケタ目
		if (clear_score >= 1000)
		{
			drawTexture(-400 + 100 * 3, -100,
				100, 100,
				0 + score1000 * 100, 0,
				100, 100,
				Color(1, 1, 1),
				numberJapTex);
		}
		//円
		drawTexture(300, -100,
			100, 100,
			0, 100 * 5,
			100, 100,
			Color(1, 1, 1),
			japaneseTex);

		// αブレンディングを無効にする
		glDisable(GL_BLEND);
	}

	//画面更新
	void update(cApp& app, std::vector<cGamePad>& gamepad)
	{
		//背景画像
		cTexture backTex("res/background.raw",
			1024, 1024, true);
		//下駄
		cTexture getaTex("res/geta.raw",
			1024, 1024, true);
		//文字
		cTexture japaneseTex("res/japanese.raw",
			1024, 1024, true);
		//数字
		cTexture numberJapTex("res/number/numberJap.raw",
			1024, 128, true);

		//プレイヤー
		cPlayer player(selectMenu[0],
			selectMenu[1],
			selectMenu[2],
			selectMenu[3]);
		//客
		cGuest guests1(LEFT);
		cGuest guests2(CENTER);
		cGuest guests3(RIGHT);

		//制限時間
		cTime time(limit_time);
		cScore score(clear_score);

		//std::coutを使うためのもの
		DbgStreambuf dbg_stream;
		std::streambuf* stream;

		//ゲームパッドをひとつ使うためのもの
		gamepad.emplace_back(cGamePad(0));

		bool pause = false;

		bool loop = true;
		//メインループ
		while (loop)
		{
			if (!app.isOpen()) exit(0);
			app.begin();

			//ゲームパッドの更新
			updateGamePad(gamepad);
			//cout用のもの
			stream = std::cout.rdbuf(&dbg_stream);

			//--------------------
			//描画関係
			//--------------------

			//背景描画
			backdraw(backTex);
			//奥から順に表示したいもの順で描画
			guests1.draw();
			guests2.draw();
			guests3.draw();

			//客の次に描画
			objectDraw(getaTex);

			//一番最後にプレイヤーを描画
			player.draw();

			//--------------------
			//UI	必ず最後に
			//--------------------

			//時間
			time.draw();
			//スコア
			score.draw();

			//--------------------
			//処理関係
			//--------------------

			if (gamepad[0].isPushButton(12))
			{
				pause = !pause;
			}

			if (!pause)
			{
				guests1.update(player.menu(), player.position());
				guests2.update(player.menu(), player.position());
				guests3.update(player.menu(), player.position());
				player.update(gamepad,
					guests1.menu(), guests2.menu(), guests3.menu());
				time.update();
				score.update(guests1.earnings,
					guests2.earnings,
					guests3.earnings);
			}
			else
			{
				//ポーズ描画
				pauseDraw(japaneseTex, numberJapTex);
			}

			//---------------
			//クリア判定
			//---------------

			//点数が一定以上で
			if (score.clearbool())
			{
				result = WIN;
				loop = false;
			}
			//制限時間いっぱいで
			if (time.endbool())
			{
				result = LOSE;
				loop = false;
			}

			//std::cout用
			std::cout.rdbuf(stream);
			app.end();
		}
		gamepad.clear();
	}
}
