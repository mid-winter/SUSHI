#pragma once
#include"app.h"
#include"multiProce.h"
#include "gamePad.h"
#include "guest.h"
#include "player.h"
#include "sushi.h"

namespace nGame
{
	//�w�i�`��
	void backdraw(cTexture& back)
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

		// ���u�����f�B���O�𖳌��ɂ���
		glDisable(GL_BLEND);
	}

	//�u���i�����O�ɒu�����́j
	void objectDraw(cTexture& geta){
		// ���u�����f�B���O��L���ɂ���
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	//��ʍX�V
	void update(cApp& app, std::vector<cGamePad>& gamepad)
	{
		//�w�i�摜
		cTexture backTex("res/background.raw",
			1024, 1024, true);
		//����
		cTexture getaTex("res/geta.raw",
			1024, 1024, true);

		//�q
		cGuest guest(CENTER, NONE);
		//�v���C���[
		cPlayer player(CENTER, MAGURO, SALMON, TAMAGO);
		//���i
		cSushi sushi(CENTER);

		gamepad.emplace_back(cGamePad(0));
		while (1)
		{
			if (!app.isOpen()) exit(0);
			app.begin();
			updateGamePad(gamepad);

			backdraw(backTex);
			guest.draw();

			objectDraw(getaTex);
			player.draw();

			sushi.draw();

			guest.update(player.menu());
			player.update(gamepad, CENTER, guest.menu());

			//��낤�Ƃ����画��
			if (player.makebool())
			{
				sushi.update(player.menu(), player.position());
				guest.judge(player.menu());
			}

			app.end();
		}
	}
}
