#pragma once
#include "app.h"
#include "multiProce.h"
#include "gamePad.h"

namespace nTitle
{
	//�X�V
	void update(cApp& app, std::vector<cGamePad>& gamepad)
	{
		//�摜
		cTexture title("res/Title.raw",
			1024, 512, true);

		Color fadecolor = Color(0, 0, 0, 1);
		gamepad.emplace_back(cGamePad(0));

		bool a = true;

		while (a)
		{
			if (!app.isOpen()) exit(0);
			app.begin();

			updateGamePad(gamepad);
			// ���u�����f�B���O��L���ɂ���
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//�^�C�g���w�i�摜
			drawTexture(-WIDTH / 2, -HEIGHT / 2,
				WIDTH, HEIGHT,
				0, 0, 765, 512,
				Color(1, 1, 1),
				title);

			if (fadeIn(WIDTH, HEIGHT,
				fadecolor,
				0.02f))
			{
				//�Ȃɂ��{�^�����������Ƃ����̉�ʂɈڍs
				for (int i = 0; i < gamepad[0].buttons(); ++i)
				{
					if (gamepad[0].isPressButton(i))
					{
						a = false;
					}
				}
			}

			// ���u�����f�B���O�𖳌��ɂ���
			glDisable(GL_BLEND);
			app.end();
		}
	}
};
