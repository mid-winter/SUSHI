#pragma once
#include"app.h"
#include"multiProce.h"

namespace nGame
{
	//”wŒi‰æ‘œ
	cTexture backTex("res/BackGround.raw",
		1024, 1024,
		true);

	void update(cApp& app)
	{
		while (1)
		{
			drawTexture(-WIDTH / 2, -HEIGHT / 2,
				WIDTH, HEIGHT,
				0, 0, 960, 540,
				Color(1, 1, 1),
				backTex);
		}
	}
}
