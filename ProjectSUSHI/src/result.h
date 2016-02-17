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
		//��������
		cTexture winTex("res/Result/win.raw",
			1024, 512, true);
		//�s�k����
		cTexture loseTex("res/Result/lose.raw",
			1024, 512, true);

		//���{��
		cTexture japaneseTex("res/japanese.raw",
			1024, 1024, true);

		Color fadecolor = Color(0, 0, 0, 1);
		gamepad.emplace_back(cGamePad(0));

		float alpha = 0;
		//�^�C�g�����S�̓���
		float angle = 0.0f;
		float aaa = 0.0f;

		//�t�F�[�h�A�E�g
		bool fadeoutbool = false;

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
					Color(0.8f, 0.3f, 0.3f),
					backTex);

				//�Â�����
				drawFillBox(-WIDTH / 2, -HEIGHT / 2,
					WIDTH, HEIGHT,
					Color(0, 0, 0, 0.5));

				//����
				drawTexture(-300, -100,
					600, 300,
					0, 0,
					1024, 512,
					Color(1, 1, 1, alpha),
					winTex);
			}
			else if (result == LOSE)
			{
				drawTexture(-WIDTH / 2, -HEIGHT / 2,
					WIDTH, HEIGHT,
					0, 0, 765, 512,
					Color(0.3f, 0.3f, 0.8f),
					backTex);

				//�Â�����
				drawFillBox(-WIDTH / 2, -HEIGHT / 2,
					WIDTH, HEIGHT,
					Color(0, 0, 0, 0.5));

				//�s�k
				drawTexture(-300, -100,
					600, 300,
					0, 0,
					1024, 512,
					Color(1, 1, 1, alpha),
					loseTex);
			}

			angle += 0.05f;
			aaa = std::abs(std::sin(angle *0.5f));

			if (fadeoutbool)
			{
				if(fadeOut(WIDTH, HEIGHT,
					fadecolor,
					0.02f))
				{
					for (int i = 0; i < 4; ++i)
					{
						selectMenu[i] = NONE;
					}
					loop = true;
				}
			}

			//�t�F�[�h�C���������ǂ���
			if (fadeIn(WIDTH, HEIGHT, fadecolor, 0.02f))
			{
				if (alpha <= 1.0f)
				{
					alpha += 0.02f;
				}
				else
				{
					//�Ȃɂ��{�^���������Ă�������
					drawTexture(-250, -200,
						500, 50,
						0, 100 * 2, 100 * 10, 100,
						Color(1, 1, 1, aaa),
						japaneseTex);

					//�Ȃɂ��{�^�����������Ƃ����̉�ʂɈڍs
					for (int i = 0; i < gamepad[0].buttons(); ++i)
					{
						if (gamepad[0].isPressButton(i))
						{
							loop = false;
						}
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
