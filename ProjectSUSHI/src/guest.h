#pragma once
#include"multiProce.h"

class cGuest
{
	//画像
	cTexture childTex;
	TextureInfo guestTex;

	cTexture tunaTex;

	//位置情報
	int seat = LEFT;

	bool callbool = false;
	int calltime = 0;

public:
	//コンストラクタ
	cGuest(int seat_num)
		:childTex("res/child.raw", 512, 512, true),
		tunaTex("res/tuna.raw", 1024, 1024, true)
	{
		//席を決める
		seat = seat_num;

		callbool = false;
		calltime = 0;

		//位置情報-125
		guestTex =
		{
			WIDTH / 2 + 100.0f, -HEIGHT / 2 + 175.0f,
			250, 250,
			0, 0, 512, 512
		};
	}

	//描画
	void draw()
	{
		// αブレンディングを有効にする
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		drawTexture(guestTex.pos_x, guestTex.pos_y,
			guestTex.size_x, guestTex.size_y,
			guestTex.cut_pos_x, guestTex.cut_pos_y,
			guestTex.cut_size_x, guestTex.cut_size_y,
			Color(1.0f, 1.0f, 1.0f),
			childTex);

		//吹き出し
		if (callbool)
		{
			drawTexture(guestTex.pos_x, guestTex.pos_y + 200,
				200, 100,
				0, 0, 1024, 600,
				Color(1.0f, 1.0f, 1.0f),
				tunaTex);
		}

		// αブレンディングを無効にする
		glDisable(GL_BLEND);
	}

	//作った処理をまとめ
	void update()
	{
		if (movebool())
		{
			call();
		}
	}

private:

	//座る席の位置を決める
	float sit_pos()
	{
		switch (seat){
			//左の席
		case LEFT:
			return -300.0f;
			break;

			//中央の席
		case CENTER:
			return -125.0f;
			break;

			//右の席
		case RIGHT:
			return 250;
			break;
		}
	}

	//移動処理
	bool movebool()
	{
		if (guestTex.pos_x > sit_pos()){
			guestTex.pos_x -= 5.0f;
			return false;
		}
		else{
			return true;
		}
	}

	void call()
	{
		if (callbool)
		{

		}
		else
		{
			calltime++;
			if (calltime > 60)
			{
				calltime = 0;
				callbool = true;
			}
		}
	}
};
