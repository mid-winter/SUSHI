#pragma once
#include"app.h"
#include"multiProce.h"
#include "gamePad.h"

namespace nGame
{
	void update(cApp& app, std::vector<cGamePad>& gamepad)
	{
		//�w�i�摜
		cTexture backTex("res/background.raw",
			1024, 1024,
			true);
		cTexture counterTex("res/counter.raw",
			1024, 1024,
			true);

		gamepad.emplace_back(cGamePad(0));
		while (1)
		{
			if (!app.isOpen()) exit(0);
			app.begin();
			updateGamePad(gamepad);

			// ���u�����f�B���O��L���ɂ���
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//�w�i
			drawTexture(-WIDTH / 2, -HEIGHT / 2,
				WIDTH, HEIGHT,
				0, 0, WIDTH, HEIGHT,
				Color(1, 1, 1),
				backTex);

			//�J�E���^�[
			drawTexture(-WIDTH / 2, -HEIGHT / 2,
				WIDTH, HEIGHT,
				0, 0, WIDTH, HEIGHT,
				Color(1, 1, 1),
				counterTex);

			// ���u�����f�B���O�𖳌��ɂ���
			glDisable(GL_BLEND);
			app.end();
		}
	}
}
