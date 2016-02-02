#pragma once
#include"multiProce.h"
#include"gamePad.h"

class cPlayer
{
	//画像
	cTexture hand_lTex;
	cTexture hand_rTex;
	cTexture hand_sushi_lTex;
	cTexture hand_sushi_rTex;

	cTexture keyTex;

	//画像情報
	TextureInfo handInfo;

	bool makebool = false;

	int seat = 0;
	int make_time = 0;

public:
	//コンストラクタ
	cPlayer()
		:hand_lTex("res/hand_l.raw",
		1024, 1024, true),
		hand_rTex("res/hand_r.raw",
		1024, 1024, true),
		hand_sushi_lTex("res/hand_sushi_l.raw",
		1024, 1024, true),
		hand_sushi_rTex("res/hand_sushi_r.raw",
		1024, 1024, true),
		keyTex("res/key.raw",
		512, 512, true)
	{
		//手の位置情報
		handInfo = {
			0, -350,
			400, 200,
			0, 0,
			1024, 600
		};

		//手の位置
		seat = CENTER;

		//寿司生成判定
		makebool = false;
	}

	//描画
	void draw()
	{
		// αブレンディングを有効にする
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (!makebool)
		{
			//左手
			drawTexture(handInfo.pos_x - handInfo.size_x, handInfo.pos_y,
				handInfo.size_x, handInfo.size_y,
				handInfo.cut_pos_x, handInfo.cut_pos_y,
				handInfo.cut_size_x, handInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				hand_lTex);
			//右手
			drawTexture(handInfo.pos_x, handInfo.pos_y,
				handInfo.size_x, handInfo.size_y,
				handInfo.cut_pos_x, handInfo.cut_pos_y,
				handInfo.cut_size_x, handInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				hand_rTex);
		}
		else
		{
			//左手
			drawTexture(handInfo.pos_x - handInfo.size_x, handInfo.pos_y,
				handInfo.size_x, handInfo.size_y,
				handInfo.cut_pos_x, handInfo.cut_pos_y,
				handInfo.cut_size_x, handInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				hand_sushi_lTex);
			//右手
			drawTexture(handInfo.pos_x - handInfo.size_x / 2, handInfo.pos_y,
				handInfo.size_x, handInfo.size_y,
				handInfo.cut_pos_x, handInfo.cut_pos_y,
				handInfo.cut_size_x, handInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				hand_sushi_rTex);
		}

		//キー
		drawTexture(200, -300, 200, 200,
			0, 0, 512, 512,
			Color(1, 1, 1, 0.6),
			keyTex);

		// αブレンディングを無効にする
		glDisable(GL_BLEND);
	}

	void update(std::vector<cGamePad>& pad)
	{
		setPos();
		make();

		//移動処理
		for (auto& gamepad : pad)
		{
			//左右移動
			if (gamepad.isPushButton(R1))
			{
				++seat;
				if (seat > RIGHT) seat = LEFT;
			}
			if (gamepad.isPushButton(L1))
			{
				--seat;
				if (seat < LEFT) seat = RIGHT;
			}

			//寿司をつくる体制
			if (gamepad.isPushButton(MARU))
			{
				makebool = true;
			}
		}
	}

private:
	//位置情報の変更先を登録
	void setPos()
	{
		switch (seat)
		{
		case LEFT:
			handInfo.pos_x = -300;
			break;
		case CENTER:
			handInfo.pos_x = 0;
			break;
		case RIGHT:
			handInfo.pos_x = 250;
			break;
		}
	}

	//寿司をつくる
	void make()
	{
		if (makebool)
		{
			make_time++;
			if (make_time > 60)
			{
				make_time = 0;
				makebool = false;
			}
		}
	}
};
