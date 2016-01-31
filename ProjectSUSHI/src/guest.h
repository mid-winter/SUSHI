#pragma once
#include"multiProce.h"

class cGuest
{
	//�摜
	cTexture childTex;
	TextureInfo guestTex;

	cTexture tunaTex;

	//�ʒu���
	int seat = LEFT;

	bool callbool = false;
	int calltime = 0;

public:
	//�R���X�g���N�^
	cGuest(int seat_num)
		:childTex("res/child.raw", 512, 512, true),
		tunaTex("res/tuna.raw", 1024, 1024, true)
	{
		//�Ȃ����߂�
		seat = seat_num;

		callbool = false;
		calltime = 0;

		//�ʒu���-125
		guestTex =
		{
			WIDTH / 2 + 100.0f, -HEIGHT / 2 + 175.0f,
			250, 250,
			0, 0, 512, 512
		};
	}

	//�`��
	void draw()
	{
		// ���u�����f�B���O��L���ɂ���
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		drawTexture(guestTex.pos_x, guestTex.pos_y,
			guestTex.size_x, guestTex.size_y,
			guestTex.cut_pos_x, guestTex.cut_pos_y,
			guestTex.cut_size_x, guestTex.cut_size_y,
			Color(1.0f, 1.0f, 1.0f),
			childTex);

		//�����o��
		if (callbool)
		{
			drawTexture(guestTex.pos_x, guestTex.pos_y + 200,
				200, 100,
				0, 0, 1024, 600,
				Color(1.0f, 1.0f, 1.0f),
				tunaTex);
		}

		// ���u�����f�B���O�𖳌��ɂ���
		glDisable(GL_BLEND);
	}

	//������������܂Ƃ�
	void update()
	{
		if (movebool())
		{
			call();
		}
	}

private:

	//����Ȃ̈ʒu�����߂�
	float sit_pos()
	{
		switch (seat){
			//���̐�
		case LEFT:
			return -300.0f;
			break;

			//�����̐�
		case CENTER:
			return -125.0f;
			break;

			//�E�̐�
		case RIGHT:
			return 250;
			break;
		}
	}

	//�ړ�����
	bool movebool()
	{
		if (guestTex.pos_x > sit_pos()){
			guestTex.pos_x -= 5.0f;
			return false;
		}
		else{
			return true;
		}
	}

	void call()
	{
		if (callbool)
		{

		}
		else
		{
			calltime++;
			if (calltime > 60)
			{
				calltime = 0;
				callbool = true;
			}
		}
	}
};
