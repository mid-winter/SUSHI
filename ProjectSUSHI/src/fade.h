#pragma once
#include "graphic.h"
#include "multiProce.h"

class cFade
{
	//フェード色
	Color fadecolor_;

public:
	bool fade_in_start = false;
	bool fade_out_start = false;

	//コンストラクタ
	cFade(Color& color) :
		fadecolor_(color)
	{
	}

	//描画		必ず描画するものの最後に読み込む
	void draw(int width, int height,
		Color& color)
	{
		//フェードの塗りつぶし矩形
		drawFillBox(-width / 2, -height / 2,
			width, height,
			color);
	}

	void update();
};
