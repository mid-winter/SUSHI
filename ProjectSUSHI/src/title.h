#pragma once
#include "app.h"
#include "multiProce.h"
#include "gamePad.h"

namespace nTitle
{
	//�X�V
	void update(cApp& app, cGamePad& gamepad)
	{
		//�摜
		cTexture title("res/Title.raw",
			1024, 512, true);

		Color fadecolor = Color(0, 0, 0, 1);

		bool endbool = false;

		while (1)
		{
			if (!app.isOpen()) exit(0);
			app.begin();

			// ���u�����f�B���O��L���ɂ���
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//�^�C�g���w�i�摜
			drawTexture(-960 / 2, -540 / 2,
				960, 540,
				0, 0, 765, 512,
				Color(1, 1, 1),
				title);

			gamepad.update();

			if (fadeIn(WIDTH, HEIGHT,
				fadecolor,
				0.02f))
			{
				//�Ȃɂ��{�^�����������Ƃ����̉�ʂɈڍs
				for (int i = 0; i < gamepad.buttons(); ++i)
				{
					if (gamepad.isPressButton(i))
					{
						exit(0);
					}
				}
			}

			// ���u�����f�B���O�𖳌��ɂ���
			glDisable(GL_BLEND);
			app.end();
		}
	}
};
