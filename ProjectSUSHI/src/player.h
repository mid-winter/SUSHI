#pragma once
#include"multiProce.h"
#include"gamePad.h"
#include"guest.h"
#include"sushi.h"

//プレイヤーのクラス
class cPlayer
{
	//画像
	cTexture hand_lTex;
	cTexture hand_rTex;
	cTexture hand_sushi_lTex;
	cTexture hand_sushi_rTex;
	cTexture keyTex;
	cTexture menuTex;

	//画像情報
	TextureInfo handInfo;

	//寿司クラス
	cSushi sushi;

	//ボタンに対するメニュー
	int menuMARU;
	int menuBATSU;
	int menuSHIKAKU;
	int menuSANKAKU;

	//メニュー
	int menu_ = NONE;
	//位置
	int position_ = CENTER;

	//寿司を生成する体制になっている時間
	int make_time = 0;
	//生成判定
	bool makebool_ = false;

	//このクラスのコピーを禁止する
	cPlayer(const cPlayer&) = delete;
	cPlayer& operator =(const cPlayer&) = delete;

public:
	int menu() const{ return menu_; }
	bool makebool() const { return makebool_; }
	int position() const { return position_; }

	//コンストラクタ
	cPlayer(
		int maru = NONE,
		int batsu = NONE,
		int shikaku = NONE,
		int sankaku = NONE)
		:hand_lTex("res/hand/hand_l.raw", 1024, 1024, true),
		hand_rTex("res/hand/hand_r.raw", 1024, 1024, true),
		hand_sushi_lTex("res/hand/hand_sushi_l.raw", 1024, 1024, true),
		hand_sushi_rTex("res/hand/hand_sushi_r.raw", 1024, 1024, true),
		keyTex("res/key.raw", 512, 512, true),
		menuTex("res/menu/menu.raw",
		1024, 512, true),
		sushi()
	{
		//手の位置情報
		handInfo = {
			0, -350,
			400, 200,
			0, 0,
			1024, 600
		};

		//手の位置
		position_ = CENTER;

		//寿司生成判定
		makebool_ = false;
		menu_ = NONE;

		menuMARU = maru;
		menuBATSU = batsu;
		menuSHIKAKU = shikaku;
		menuSANKAKU = sankaku;
	}

	//描画
	void draw()
	{
		// αブレンディングを有効にする
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (!makebool_)
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
		drawTexture(175, -195, 50, 50,
			150, 0, 200, 200,
			Color(1, 1, 1, 0.4f),
			keyTex);
		drawTexture(175, -275, 50, 50,
			155, 315, 200, 200,
			Color(1, 1, 1, 0.4f),
			keyTex);
		drawTexture(275, -235, 50, 50,
			320, 175, 200, 200,
			Color(1, 1, 1, 0.4f),
			keyTex);
		drawTexture(80, -235, 50, 50,
			0, 175, 200, 200,
			Color(1, 1, 1, 0.4f),
			keyTex);

		//文字
		setCharacter(320, -220, menuMARU, menuTex);
		setCharacter(225, -190, menuSANKAKU, menuTex);
		setCharacter(225, -265, menuBATSU, menuTex);
		setCharacter(125, -220, menuSHIKAKU, menuTex);

		//寿司の画像
		sushi.draw();

		// αブレンディングを無効にする
		glDisable(GL_BLEND);
	}

	//処理更新
	void update(std::vector<cGamePad>& pad,
		int guest_menu1 = NONE,
		int guest_menu2 = NONE,
		int guest_menu3 = NONE
		)
	{
		setPos();
		make();
		sushi.update(menu_, position_);

		//ゲームパッドを使用する
		for (auto& gamepad : pad)
		{
			//左右移動
			if (!makebool_)
			{
				if (gamepad.isPushButton(R1) || gamepad.isPushButton(R2))
				{
					++position_;
					if (position_ > RIGHT) position_ = LEFT;
				}
				if (gamepad.isPushButton(L1) || gamepad.isPushButton(L2))
				{
					--position_;
					if (position_ < LEFT) position_ = RIGHT;
				}
			}

			//寿司をつくる体制
			if (guest_menu1 != NONE ||
				guest_menu2 != NONE ||
				guest_menu3 != NONE)
			{
				if (gamepad.isPushButton(MARU))
				{
					menu_ = menuMARU;
					makebool_ = true;
				}
				if (gamepad.isPushButton(BATSU))
				{
					menu_ = menuBATSU;
					makebool_ = true;
				}
				if (gamepad.isPushButton(SHIKAKU))
				{
					menu_ = menuSHIKAKU;
					makebool_ = true;
				}
				if (gamepad.isPushButton(SANKAKU))
				{
					menu_ = menuSANKAKU;
					makebool_ = true;
				}
			}
		}
	}

private:
	//位置情報の変更先を登録
	void setPos()
	{
		switch (position_)
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

	//文字表示
	//pos_x, pos_y		位置
	//setmenu			対応したメニュー
	//japaneseMenuTex	画像
	void setCharacter(float pos_x, float pos_y, 
		int setmenu,
		cTexture& japaneseMenuText)
	{
		int chara_num = 0;
		float cut_start_x = 0;
		float cut_start_y = 0;
		float cut_end_x = 0;
		float cut_end_y = 0;

		//画像の切り取り位置を変更
		switch (setmenu)
		{
		case MAGURO:
			chara_num = 3;
			cut_start_x = 0;
			cut_start_y = 0;
			cut_end_x = 100 * chara_num;
			cut_end_y = 100;
			break;
		case SALMON:
			chara_num = 4;
			cut_start_x = 0;
			cut_start_y = 100;
			cut_end_x = 100 * chara_num;
			cut_end_y = 100;
			break;
		case TAMAGO:
			chara_num = 3;
			cut_start_x = 0;
			cut_start_y = 200;
			cut_end_x = 100 * chara_num;
			cut_end_y = 100;
			break;
		case EBI:
			chara_num = 2;
			cut_start_x = 0;
			cut_start_y = 300;
			cut_end_x = 100 * chara_num;
			cut_end_y = 100;
			break;
		case IKURA:
			chara_num = 3;
			cut_start_x = 500;
			cut_start_y = 0;
			cut_end_x = 100 * chara_num;
			cut_end_y = 100;
			break;
		case IKA:
			chara_num = 2;
			cut_start_x = 500;
			cut_start_y = 100;
			cut_end_x = 100 * chara_num;
			cut_end_y = 100;
			break;
		case ANAGO:
			chara_num = 3;
			cut_start_x = 500;
			cut_start_y = 200;
			cut_end_x = 100 * chara_num;
			cut_end_y = 100;
			break;
		case HOTATE:
			chara_num = 3;
			cut_start_x = 500;
			cut_start_y = 300;
			cut_end_x = 100 * chara_num;
			cut_end_y = 100;
			break;
		}

		//文字表示
		if (setmenu != NONE)
		{
			drawTexture(pos_x, pos_y,
				35 * chara_num, 35,
				cut_start_x, cut_start_y,
				cut_end_x, cut_end_y,
				Color(0, 0, 0, 0.5f),
				japaneseMenuText);
		}
	}

	//寿司をつくる
	void make()
	{
		if (makebool_)
		{
			make_time++;
			if (make_time > 30)
			{
				make_time = 0;
				//作る前の体制に戻す
				makebool_ = false;
				//プレイヤーの選択しているメニューを戻す
				menu_ = NONE;
			}
		}
	}
};
