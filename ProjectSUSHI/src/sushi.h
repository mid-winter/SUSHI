#pragma once
#include"multiProce.h"

class cSushi
{

	cTexture MaguroTex;
	cTexture SalmonTex;
	cTexture TamagoTex;
	cTexture EbiTex;
	cTexture IkuraTex;
	cTexture IkaTex;
	cTexture AnagoTex;
	cTexture HotateTex;

	TextureInfo sushiInfo;

	int menu_ = NONE;
	int seat = CENTER;

public:

	cSushi():
		MaguroTex("res/menu/maguro.raw", 512, 256, true),
		SalmonTex("res/menu/salmon.raw", 512, 256, true),
		TamagoTex("res/menu/tamago.raw", 512, 256, true),
		EbiTex("res/menu/ebi.raw", 512, 256, true),
		IkuraTex("res/menu/ikura.raw", 512, 256, true),
		IkaTex("res/menu/ika.raw", 512, 256, true),
		AnagoTex("res/menu/anago.raw", 512, 256, true),
		HotateTex("res/menu/hotate.raw", 512, 256, true)
	{
		sushiInfo =
		{
			0, 0,
			150, 75,
			0, 0, 400, 256
		};
		menu_ = MAGURO;
	}

	void draw()
	{
		// αブレンディングを有効にする
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		switch (menu_)
		{
		case MAGURO:
			drawTexture(sushiInfo.pos_x, sushiInfo.pos_y,
				sushiInfo.size_x, sushiInfo.size_y,
				sushiInfo.cut_pos_x, sushiInfo.cut_pos_y,
				sushiInfo.cut_size_x, sushiInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				MaguroTex);
			break;
		case IKA:
			drawTexture(sushiInfo.pos_x, sushiInfo.pos_y,
				sushiInfo.size_x, sushiInfo.size_y,
				sushiInfo.cut_pos_x, sushiInfo.cut_pos_y,
				sushiInfo.cut_size_x, sushiInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				IkaTex);
			break;
		}

		// αブレンディングを無効にする
		glDisable(GL_BLEND);
	}

	void update(int menu, int player_position)
	{
		setPosition();
		//位置情報を同期
		seat = player_position;
		menu_ = menu;
	}
private:

	void setPosition()
	{
		switch (seat)
		{
		case LEFT:
			sushiInfo.pos_x = -400;
			sushiInfo.pos_y = -HEIGHT / 2 + 150;
			break;
		case CENTER:
			sushiInfo.pos_x = -75;
			sushiInfo.pos_y = -HEIGHT / 2 + 150;
			break;
		case RIGHT:
			sushiInfo.pos_x = 250;
			sushiInfo.pos_y = -HEIGHT / 2 + 150;
			break;
		}
	}
};
