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
		drawTexture(200, -300, 200, 200,
			0, 0, 512, 512,
			Color(1, 1, 1, 0.6f),
			keyTex);

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
