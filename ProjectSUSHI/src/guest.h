#pragma once
#include"multiProce.h"

class cGuest
{
	//画像
	cTexture childTex;
	TextureInfo guestInfo;

	cTexture fukidashiTex;
	cTexture menuTex;
	TextureInfo menuInfo;
	
	//位置情報
	int seat = LEFT;

	bool callbool = false;
	int calltime = 0;

	int menu_;
	float fontsize;

	//表情
	int face;

	//このクラスのコピーを禁止する
	cGuest(const cGuest&) = delete;
	cGuest& operator =(const cGuest&) = delete;

public:

	//コンストラクタ
	cGuest(int seat_num, int menu)
		:childTex("res/child.raw", 1024, 256, true),
		fukidashiTex("res/fukidashi.raw", 1024, 1024, true),
		menuTex("res/menu.raw", 1024, 512, true)
	{
		//席を決める
		seat = seat_num;

		callbool = false;
		calltime = 0;
		//何を選ぶか引数から読む
		menu_ = menu;
		//文字サイズ(縦横同じ)
		fontsize = 100;

		//表情
		face = NORMAL;

		//位置情報
		guestInfo =
		{
			WIDTH / 2 + 100.0f, -HEIGHT / 2 + 175.0f,
			250, 250,
			0, 0, 256, 256
		};
		//吹き出しの中身
		menuInfo =
		{
			0, 0,
			150, 50,
			0, 0,
			400, 100
		};
	}

	//描画
	void draw()
	{
		// αブレンディングを有効にする
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		drawTexture(guestInfo.pos_x, guestInfo.pos_y,
			guestInfo.size_x, guestInfo.size_y,
			guestInfo.cut_pos_x, guestInfo.cut_pos_y,
			guestInfo.cut_size_x, guestInfo.cut_size_y,
			Color(1.0f, 1.0f, 1.0f),
			childTex);

		//吹き出し
		if (callbool)
		{
			drawTexture(guestInfo.pos_x, guestInfo.pos_y + 200,
				200, 100,
				0, 0, 1024, 600,
				Color(1.0f, 1.0f, 1.0f),
				fukidashiTex);
			//文字部分
			drawTexture(menuInfo.pos_x, menuInfo.pos_y + 200,
				menuInfo.size_x, menuInfo.size_y,
				menuInfo.cut_pos_x, menuInfo.cut_pos_y,
				menuInfo.cut_size_x, menuInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				menuTex);
		}

		// αブレンディングを無効にする
		glDisable(GL_BLEND);
	}

	//作った処理をまとめ
	void update()
	{
		setmenu();
		changeFace();
		if (movebool())
		{
			call();
		}
	}

	//表情を変更
	void judge(int menu)
	{
		if (menu_ == menu)
		{
			face = SMILE;
		}
		else{
			face = ANGER;
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
		if (guestInfo.pos_x > sit_pos()){
			guestInfo.pos_x -= 5.0f;
			return false;
		}
		else{
			return true;
		}
	}

	//メニューを宣言
	void call()
	{
		if (!callbool)
		{
			//一定時間で宣言
			calltime++;
			if (calltime > 60)
			{
				calltime = 0;
				callbool = true;
			}
		}
	}

	//表情を変更
	void changeFace()
	{
		switch (face)
		{
		case NORMAL:
			guestInfo.cut_pos_x = 0;
			break;
		case SMILE:
			guestInfo.cut_pos_x = 256;
			break;
		case ANGER:
			guestInfo.cut_pos_x = 512;
			break;
		}
	}

	//要求に合わせて文字を変更
	void setmenu()
	{
		//位置は同じ
		menuInfo.pos_x = guestInfo.pos_x + 25;
		menuInfo.pos_y = guestInfo.pos_y + 30;

		switch (menu_)
		{
		case MAGURO:

			menuInfo.size_x = 150.0f;
			menuInfo.size_y = 50.0f;

			menuInfo.cut_pos_x = 0;
			menuInfo.cut_pos_y = fontsize * 0;
			menuInfo.cut_size_x = fontsize * 3;
			menuInfo.cut_size_y = fontsize;

			break;
		case SALMON:

			menuInfo.size_x = 160.0f;
			menuInfo.size_y = 40.0f;

			menuInfo.cut_pos_x = 0.0f;
			menuInfo.cut_pos_y = fontsize * 1;
			menuInfo.cut_size_x = fontsize * 3;
			menuInfo.cut_size_y = fontsize;

			break;
		case TAMAGO:

			menuInfo.size_x = 150.0f;
			menuInfo.size_y = 50.0f;

			menuInfo.cut_pos_x = 0.0f;
			menuInfo.cut_pos_y = fontsize * 2;
			menuInfo.cut_size_x = fontsize * 3;
			menuInfo.cut_size_y = fontsize;

			break;
		case EBI:

			menuInfo.size_x = 140.0f;
			menuInfo.size_y = 70.0f;

			menuInfo.cut_pos_x = 0.0f;
			menuInfo.cut_pos_y = fontsize * 3;
			menuInfo.cut_size_x = fontsize * 2;
			menuInfo.cut_size_y = fontsize;

			break;
		case IKURA:

			menuInfo.size_x = 150.0f;
			menuInfo.size_y = 50.0f;

			menuInfo.cut_pos_x = 500.0f;
			menuInfo.cut_pos_y = fontsize * 0;
			menuInfo.cut_size_x = fontsize * 3;
			menuInfo.cut_size_y = fontsize;

			break;
		case IKA:

			menuInfo.size_x = 140.0f;
			menuInfo.size_y = 70.0f;

			menuInfo.cut_pos_x = 500.0f;
			menuInfo.cut_pos_y = fontsize * 1;
			menuInfo.cut_size_x = fontsize * 2;
			menuInfo.cut_size_y = fontsize;

			break;
		case ANAGO:

			menuInfo.size_x = 150.0f;
			menuInfo.size_y = 50.0f;

			menuInfo.cut_pos_x = 500.0f;
			menuInfo.cut_pos_y = fontsize * 2;
			menuInfo.cut_size_x = fontsize * 3;
			menuInfo.cut_size_y = fontsize;

			break;
		case HOTATE:

			menuInfo.size_x = 150.0f;
			menuInfo.size_y = 50.0f;

			menuInfo.cut_pos_x = 500.0f;
			menuInfo.cut_pos_y = fontsize * 3;
			menuInfo.cut_size_x = fontsize * 3;
			menuInfo.cut_size_y = fontsize;

			break;
		}
	}
};
