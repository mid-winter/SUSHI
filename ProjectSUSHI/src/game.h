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

	//画面更新
	void update(cApp& app, std::vector<cGamePad>& gamepad)
	{
		//背景画像
		cTexture backTex("res/background.raw",
			1024, 1024, true);
		//下駄
		cTexture getaTex("res/geta.raw",
			1024, 1024, true);

		//プレイヤー
		cPlayer player(MAGURO,
			SALMON,
			TAMAGO);
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

			guests1.update(player.menu(), player.position());
			guests2.update(player.menu(), player.position());
			guests3.update(player.menu(), player.position());
			player.update(gamepad,
				guests1.menu(), guests2.menu(), guests3.menu());
			time.update();
			score.update();
			score.score = guests1.earnings + guests2.earnings + guests3.earnings;

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
