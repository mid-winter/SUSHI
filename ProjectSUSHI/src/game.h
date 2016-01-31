#pragma once
#include"app.h"
#include"multiProce.h"
#include "gamePad.h"
#include "guest.h"
#include "player.h"

namespace nGame
{
	//�w�i�`��
	void backdraw(cTexture& back, cTexture& geta)
	{
		// ���u�����f�B���O��L���ɂ���
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//�w�i
		drawTexture(-WIDTH / 2, -HEIGHT / 2,
			WIDTH, HEIGHT,
			0, 0, WIDTH, HEIGHT,
			Color(1.0f, 1.0f, 1.0f),
			back);

		//�J�E���^�[
		drawFillBox(-WIDTH / 2, -HEIGHT / 2 + 100,
			WIDTH, 75,
			Color(0.8f, 0.5f, 0.0f));
		drawFillBox(-WIDTH / 2, -HEIGHT / 2,
			WIDTH, 100,
			Color(0.7f, 0.7f, 0.7f));

		//����
		drawTexture(-450, -HEIGHT / 2 + 100,
			250, 125,
			0, 0, 1024, 1024,
			Color(1.0f, 1.0f, 1.0f),
			geta);
		drawTexture(-125, -HEIGHT / 2 + 100,
			250, 125,
			0, 0, 1024, 1024,
			Color(1.0f, 1.0f, 1.0f),
			geta);
		drawTexture(200, -HEIGHT / 2 + 100,
			250, 125,
			0, 0, 1024, 1024,
			Color(1.0f, 1.0f, 1.0f),
			geta);

		// ���u�����f�B���O�𖳌��ɂ���
		glDisable(GL_BLEND);
	}

	void update(cApp& app, std::vector<cGamePad>& gamepad)
	{
		//�w�i�摜
		cTexture backTex("res/background.raw",
			1024, 1024, true);
		//����
		cTexture getaTex("res/geta.raw",
			1024, 1024, true);

		//�q
		cGuest gest(CENTER);
		//�v���C���[
		cPlayer player;

		gamepad.emplace_back(cGamePad(0));
		while (1)
		{
			if (!app.isOpen()) exit(0);
			app.begin();
			updateGamePad(gamepad);

			backdraw(backTex, getaTex);

			gest.draw();
			player.draw();
			
			gest.update();
			player.update(gamepad);

			app.end();
		}
	}
}
