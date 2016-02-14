#pragma once
#include"multiProce.h"

class cScore
{
	//�摜
	cTexture numberTex;
	cTexture japaneseTex;
	TextureInfo numberInfo;

	//�X�R�A�i����グ�j
	int clear_score_;

public:
	int score = 0;
	bool clearbool() 
	{
		if (score >= clear_score_) return true;
		return false;
	}

	//�R���X�g���N�^
	cScore(int clear_score) :
		numberTex("res/number/numberJap.raw", 1024, 128, true),
		japaneseTex("res/number/japanese.raw", 512, 128, true)
	{
		score = 0;
		clear_score_ = clear_score;

		//�摜���
		numberInfo =
		{
			-WIDTH / 2, HEIGHT / 2 - 60,
			60, 60,
			0, 0,
			100, 100
		};
	}

	//�`��
	void draw()
	{
		int score1000 = score / 1000 % 10;
		int score100 = score / 100 % 10;
		int score10 = score / 10 % 10;

		// ���u�����f�B���O��L���ɂ���
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//�~
		drawTexture(numberInfo.pos_x + numberInfo.size_x * 5, numberInfo.pos_y,
			numberInfo.size_x, numberInfo.size_y,
			100 * 4, 0,
			100, 100,
			Color(1, 1, 1),
			japaneseTex);

		//��P�^��	�m����0
		drawTexture(numberInfo.pos_x + numberInfo.size_x * 4, numberInfo.pos_y,
			numberInfo.size_x, numberInfo.size_y,
			numberInfo.cut_pos_x, numberInfo.cut_pos_y,
			numberInfo.cut_size_x, numberInfo.cut_size_y,
			Color(1, 1, 1),
			numberTex);

		//�\�P�^��
		if (score >=10)
		{
			drawTexture(numberInfo.pos_x + numberInfo.size_x * 3, numberInfo.pos_y,
				numberInfo.size_x, numberInfo.size_y,
				numberInfo.cut_pos_x + score10 *numberInfo.cut_size_x, numberInfo.cut_pos_y,
				numberInfo.cut_size_x, numberInfo.cut_size_y,
				Color(1, 1, 1),
				numberTex);
		}

		//�S�P�^��
		if (score >= 100)
		{
			drawTexture(numberInfo.pos_x + numberInfo.size_x * 2, numberInfo.pos_y,
				numberInfo.size_x, numberInfo.size_y,
				numberInfo.cut_pos_x + score100 *numberInfo.cut_size_x, numberInfo.cut_pos_y,
				numberInfo.cut_size_x, numberInfo.cut_size_y,
				Color(1, 1, 1),
				numberTex);
		}

		//��P�^��
		if (score >= 1000)
		{
			drawTexture(numberInfo.pos_x + numberInfo.size_x, numberInfo.pos_y,
				numberInfo.size_x, numberInfo.size_y,
				numberInfo.cut_pos_x + score1000 *numberInfo.cut_size_x, numberInfo.cut_pos_y,
				numberInfo.cut_size_x, numberInfo.cut_size_y,
				Color(1, 1, 1),
				numberTex);
		}

		// ���u�����f�B���O�𖳌��ɂ���
		glDisable(GL_BLEND);
	}

	void update()
	{
	}

private:
};
