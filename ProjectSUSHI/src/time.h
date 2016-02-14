#pragma once
#include"multiProce.h"

class cTime
{
	//�摜
	cTexture numberTex;
	TextureInfo numberInfo;

	//���ԕϐ�
	int time_;

public:
	//�N���A����
	bool endbool() 
	{
		if (time_ <= 0)
		{
			return true;
		}
		return false;
	}

	//�R���X�g���N�^
	//cleartime		��������
	cTime(int cleartime)
		:numberTex("res/number/number.raw", 512, 128, true)
	{
		//�������Ԃ�ǂݍ���
		time_ = cleartime * 60;

		//�����̏��
		numberInfo =
		{
			-WIDTH / 2, -HEIGHT / 2,
			50 * 0.6, 100 * 0.6,
			0, 0,
			50, 100
		};
	}

	//�`��
	void draw()
	{
		//��
		int min = time_ / 60 / 60;
		//�b
		int sec10 = time_ / 60 % 60 / 10;
		int sec1 = time_ / 60 % 60 % 10;

		// ���u�����f�B���O��L���ɂ���
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//��
		drawTexture(numberInfo.pos_x, numberInfo.pos_y,
			numberInfo.size_x, numberInfo.size_y,
			numberInfo.cut_pos_x + min * 50, numberInfo.cut_pos_y,
			numberInfo.cut_size_x, numberInfo.cut_size_y,
			Color(1, 1, 1), numberTex);

		//�F
		drawFillBox(numberInfo.pos_x + numberInfo.size_x + 2.5f, numberInfo.pos_y + 15,
			10, 10,
			Color(0, 0, 0));
		drawFillBox(numberInfo.pos_x + numberInfo.size_x + 2.5f, numberInfo.pos_y + 40,
			10, 10,
			Color(0, 0, 0));

		//�b��10��
		drawTexture(numberInfo.pos_x + numberInfo.size_x * 1.5f, numberInfo.pos_y,
			numberInfo.size_x, numberInfo.size_y,
			numberInfo.cut_pos_x + sec10 * 50, numberInfo.cut_pos_y,
			numberInfo.cut_size_x, numberInfo.cut_size_y,
			Color(1, 1, 1), numberTex);

		//�b��1��
		drawTexture(numberInfo.pos_x + numberInfo.size_x * 2.5f, numberInfo.pos_y,
			numberInfo.size_x, numberInfo.size_y,
			numberInfo.cut_pos_x + sec1 * 50, numberInfo.cut_pos_y,
			numberInfo.cut_size_x, numberInfo.cut_size_y,
			Color(1, 1, 1), numberTex);

		// ���u�����f�B���O�𖳌��ɂ���
		glDisable(GL_BLEND);
	}

	//����
	void update()
	{
		elapsed();
	}

private:

	//���Ԃ̌o��
	void elapsed()
	{
		//60�t���[���ň�b�̍l��
		if (time_ >= 0)
		{
			time_--;
		}
	}
};
