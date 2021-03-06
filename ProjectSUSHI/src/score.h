#pragma once
#include"multiProce.h"

class cScore
{
	//画像
	cTexture numberTex;
	cTexture japaneseTex;
	TextureInfo numberInfo;

	//スコア（売り上げ）
	int clear_score_;

public:
	int score = 0;
	bool clearbool()
	{
		if (score >= clear_score_) return true;
		return false;
	}

	//コンストラクタ
	cScore(int clear_score) :
		numberTex("res/number/numberJap.raw", 1024, 128, true),
		japaneseTex("res/japanese.raw", 1024, 1024, true)
	{
		score = 0;
		clear_score_ = clear_score;

		//画像情報
		numberInfo =
		{
			-WIDTH / 2, HEIGHT / 2 - 60,
			60, 60,
			0, 0,
			100, 100
		};
	}

	//描画
	void draw()
	{
		int score1000 = score / 1000 % 10;
		int score100 = score / 100 % 10;
		int score10 = score / 10 % 10;

		// αブレンディングを有効にする
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//売り上げ
		drawTexture(-WIDTH / 2, HEIGHT / 2 - numberInfo.size_y / 1.5,
			numberInfo.size_x * 2, numberInfo.size_y / 2,
			0, 100 * 4,
			100 * 4, 100,
			Color(0, 0, 0),
			japaneseTex);

		//円
		drawTexture(numberInfo.pos_x + numberInfo.size_x * 7, numberInfo.pos_y,
			numberInfo.size_x, numberInfo.size_y,
			0, 100 * 5,
			100, 100,
			Color(0, 0, 0),
			japaneseTex);

		//一ケタ目	確実に0
		drawTexture(numberInfo.pos_x + numberInfo.size_x * 6, numberInfo.pos_y,
			numberInfo.size_x, numberInfo.size_y,
			numberInfo.cut_pos_x, numberInfo.cut_pos_y,
			numberInfo.cut_size_x, numberInfo.cut_size_y,
			Color(0, 0, 0),
			numberTex);

		//十ケタ目
		if (score >= 10)
		{
			drawTexture(numberInfo.pos_x + numberInfo.size_x * 5, numberInfo.pos_y,
				numberInfo.size_x, numberInfo.size_y,
				numberInfo.cut_pos_x + score10 *numberInfo.cut_size_x, numberInfo.cut_pos_y,
				numberInfo.cut_size_x, numberInfo.cut_size_y,
				Color(0, 0, 0),
				numberTex);
		}

		//百ケタ目
		if (score >= 100)
		{
			drawTexture(numberInfo.pos_x + numberInfo.size_x * 4, numberInfo.pos_y,
				numberInfo.size_x, numberInfo.size_y,
				numberInfo.cut_pos_x + score100 *numberInfo.cut_size_x, numberInfo.cut_pos_y,
				numberInfo.cut_size_x, numberInfo.cut_size_y,
				Color(0, 0, 0),
				numberTex);
		}

		//千ケタ目
		if (score >= 1000)
		{
			drawTexture(numberInfo.pos_x + numberInfo.size_x * 3, numberInfo.pos_y,
				numberInfo.size_x, numberInfo.size_y,
				numberInfo.cut_pos_x + score1000 *numberInfo.cut_size_x, numberInfo.cut_pos_y,
				numberInfo.cut_size_x, numberInfo.cut_size_y,
				Color(0, 0, 0),
				numberTex);
		}

		// αブレンディングを無効にする
		glDisable(GL_BLEND);
	}

	void update(int guest_score1 = 0,
		int guest_score2 = 0,
		int guest_score3 = 0)
	{
		score =
			guest_score1 + guest_score2 + guest_score3;
	}

private:
};
