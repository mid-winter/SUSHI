#pragma once
#include"app.h"
#include "multiProce.h"
#include "gamePad.h"

namespace nResult
{
	//�X�V
	void update(cApp& app, std::vector<cGamePad>& gamepad)
	{
		//�w�i�摜
		cTexture backTex("res/background.raw",
			1024, 1024, true);

		Color fadecolor = Color(0, 0, 0, 1);
		gamepad.emplace_back(cGamePad(0));

		bool loop = true;
		while (loop)
		{
			if (!app.isOpen()) exit(0);
			app.begin();

			updateGamePad(gamepad);
			// ���u�����f�B���O��L���ɂ���
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//�w�i�摜

			if (result == WIN)
			{
				drawTexture(-WIDTH / 2, -HEIGHT / 2,
					WIDTH, HEIGHT,
					0, 0, 765, 512,
					Color(1, 0, 0),
					backTex);
			}
			else if (result == LOSE)
			{
				drawTexture(-WIDTH / 2, -HEIGHT / 2,
					WIDTH, HEIGHT,
					0, 0, 765, 512,
					Color(0, 0, 1),
					backTex);
			}

			//�Â�����
			drawFillBox(-WIDTH / 2, -HEIGHT / 2,
				WIDTH, HEIGHT,
				Color(0, 0, 0, 0.5));

			//�t�F�[�h�C���������ǂ���
			if (fadeIn(WIDTH, HEIGHT, fadecolor, 0.02f))
			{
				//�Ȃɂ��{�^�����������Ƃ����̉�ʂɈڍs
				for (int i = 0; i < gamepad[0].buttons(); ++i)
				{
					if (gamepad[0].isPressButton(i))
					{
						loop = false;
					}
				}
			}

			// ���u�����f�B���O�𖳌��ɂ���
			glDisable(GL_BLEND);
			app.end();
		}
		gamepad.clear();
	}
};
