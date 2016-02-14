#pragma once
#include"multiProce.h"

class cTime
{
	//画像
	cTexture numberTex;
	TextureInfo numberInfo;

	//時間変数
	int time_;

public:
	//クリア判定
	bool endbool() 
	{
		if (time_ <= 0)
		{
			return true;
		}
		return false;
	}

	//コンストラクタ
	//cleartime		制限時間
	cTime(int cleartime)
		:numberTex("res/number/number.raw", 512, 128, true)
	{
		//制限時間を読み込む
		time_ = cleartime * 60;

		//数字の情報
		numberInfo =
		{
			-WIDTH / 2, -HEIGHT / 2,
			50 * 0.6, 100 * 0.6,
			0, 0,
			50, 100
		};
	}

	//描画
	void draw()
	{
		//分
		int min = time_ / 60 / 60;
		//秒
		int sec10 = time_ / 60 % 60 / 10;
		int sec1 = time_ / 60 % 60 % 10;

		// αブレンディングを有効にする
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//分
		drawTexture(numberInfo.pos_x, numberInfo.pos_y,
			numberInfo.size_x, numberInfo.size_y,
			numberInfo.cut_pos_x + min * 50, numberInfo.cut_pos_y,
			numberInfo.cut_size_x, numberInfo.cut_size_y,
			Color(1, 1, 1), numberTex);

		//：
		drawFillBox(numberInfo.pos_x + numberInfo.size_x + 2.5f, numberInfo.pos_y + 15,
			10, 10,
			Color(0, 0, 0));
		drawFillBox(numberInfo.pos_x + numberInfo.size_x + 2.5f, numberInfo.pos_y + 40,
			10, 10,
			Color(0, 0, 0));

		//秒の10桁
		drawTexture(numberInfo.pos_x + numberInfo.size_x * 1.5f, numberInfo.pos_y,
			numberInfo.size_x, numberInfo.size_y,
			numberInfo.cut_pos_x + sec10 * 50, numberInfo.cut_pos_y,
			numberInfo.cut_size_x, numberInfo.cut_size_y,
			Color(1, 1, 1), numberTex);

		//秒の1桁
		drawTexture(numberInfo.pos_x + numberInfo.size_x * 2.5f, numberInfo.pos_y,
			numberInfo.size_x, numberInfo.size_y,
			numberInfo.cut_pos_x + sec1 * 50, numberInfo.cut_pos_y,
			numberInfo.cut_size_x, numberInfo.cut_size_y,
			Color(1, 1, 1), numberTex);

		// αブレンディングを無効にする
		glDisable(GL_BLEND);
	}

	//処理
	void update()
	{
		elapsed();
	}

private:

	//時間の経過
	void elapsed()
	{
		//60フレームで一秒の考え
		if (time_ >= 0)
		{
			time_--;
		}
	}
};
