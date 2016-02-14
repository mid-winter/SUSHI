#pragma once
#include"app.h"
#include"multiProce.h"
#include "gamePad.h"
#include "guest.h"
#include "player.h"
#include "time.h"
#include "score.h"
#include"cout.h"
#include<mutex>

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

		//�v���C���[
		cPlayer player(MAGURO,
			SALMON,
			TAMAGO);
		//�q
		cGuest guests1(LEFT);
		cGuest guests2(CENTER);
		cGuest guests3(RIGHT);

		//��������
		cTime time(limit_time);
		cScore score(clear_score);

		//std::cout���g�����߂̂���
		DbgStreambuf dbg_stream;
		std::streambuf* stream;

		//�Q�[���p�b�h���ЂƂg�����߂̂���
		gamepad.emplace_back(cGamePad(0));

		bool loop = true;
		//���C�����[�v
		while (loop)
		{
			if (!app.isOpen()) exit(0);
			app.begin();

			//�Q�[���p�b�h�̍X�V
			updateGamePad(gamepad);
			//cout�p�̂���
			stream = std::cout.rdbuf(&dbg_stream);

			//--------------------
			//�`��֌W
			//--------------------

			//�w�i�`��
			backdraw(backTex);
			//�����珇�ɕ\�����������̏��ŕ`��
			guests1.draw();
			guests2.draw();
			guests3.draw();

			//�q�̎��ɕ`��
			objectDraw(getaTex);

			//��ԍŌ�Ƀv���C���[��`��
			player.draw();

			//--------------------
			//UI	�K���Ō��
			//--------------------

			//����
			time.draw();
			//�X�R�A
			score.draw();

			//--------------------
			//�����֌W
			//--------------------

			guests1.update(player.menu(), player.position());
			guests2.update(player.menu(), player.position());
			guests3.update(player.menu(), player.position());
			player.update(gamepad,
				guests1.menu(), guests2.menu(), guests3.menu());
			time.update();
			score.update();
			score.score = guests1.earnings + guests2.earnings + guests3.earnings;

			//---------------
			//�N���A����
			//---------------

			//�_�������ȏ��
			if (score.clearbool())
			{
				result = WIN;
				loop = false;
			}
			//�������Ԃ����ς���
			if (time.endbool())
			{
				result = LOSE;
				loop = false;
			}

			//std::cout�p
			std::cout.rdbuf(stream);
			app.end();
		}
		gamepad.clear();
	}
}
