#pragma once
#include"multiProce.h"
#include"gamePad.h"

class cPlayer
{
	//�摜
	cTexture hand_lTex;
	cTexture hand_rTex;
	cTexture hand_sushi_lTex;
	cTexture hand_sushi_rTex;

	cTexture keyTex;

	//�摜���
	TextureInfo handInfo;

	bool makebool = false;

	int seat = 0;
	int make_time = 0;

public:
	//�R���X�g���N�^
	cPlayer()
		:hand_lTex("res/hand_l.raw",
		1024, 1024, true),
		hand_rTex("res/hand_r.raw",
		1024, 1024, true),
		hand_sushi_lTex("res/hand_sushi_l.raw",
		1024, 1024, true),
		hand_sushi_rTex("res/hand_sushi_r.raw",
		1024, 1024, true),
		keyTex("res/key.raw",
		512, 512, true)
	{
		//��̈ʒu���
		handInfo = {
			0, -350,
			400, 200,
			0, 0,
			1024, 600
		};

		//��̈ʒu
		seat = CENTER;

		//���i��������
		makebool = false;
	}

	//�`��
	void draw()
	{
		// ���u�����f�B���O��L���ɂ���
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (!makebool)
		{
			//����
			drawTexture(handInfo.pos_x - handInfo.size_x, handInfo.pos_y,
				handInfo.size_x, handInfo.size_y,
				handInfo.cut_pos_x, handInfo.cut_pos_y,
				handInfo.cut_size_x, handInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				hand_lTex);
			//�E��
			drawTexture(handInfo.pos_x, handInfo.pos_y,
				handInfo.size_x, handInfo.size_y,
				handInfo.cut_pos_x, handInfo.cut_pos_y,
				handInfo.cut_size_x, handInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				hand_rTex);
		}
		else
		{
			//����
			drawTexture(handInfo.pos_x - handInfo.size_x, handInfo.pos_y,
				handInfo.size_x, handInfo.size_y,
				handInfo.cut_pos_x, handInfo.cut_pos_y,
				handInfo.cut_size_x, handInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				hand_sushi_lTex);
			//�E��
			drawTexture(handInfo.pos_x - handInfo.size_x / 2, handInfo.pos_y,
				handInfo.size_x, handInfo.size_y,
				handInfo.cut_pos_x, handInfo.cut_pos_y,
				handInfo.cut_size_x, handInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				hand_sushi_rTex);
		}

		//�L�[
		drawTexture(200, -300, 200, 200,
			0, 0, 512, 512,
			Color(1, 1, 1, 0.6),
			keyTex);

		// ���u�����f�B���O�𖳌��ɂ���
		glDisable(GL_BLEND);
	}

	void update(std::vector<cGamePad>& pad)
	{
		setPos();
		make();

		//�ړ�����
		for (auto& gamepad : pad)
		{
			//���E�ړ�
			if (gamepad.isPushButton(R1))
			{
				++seat;
				if (seat > RIGHT) seat = LEFT;
			}
			if (gamepad.isPushButton(L1))
			{
				--seat;
				if (seat < LEFT) seat = RIGHT;
			}

			//���i������̐�
			if (gamepad.isPushButton(MARU))
			{
				makebool = true;
			}
		}
	}

private:
	//�ʒu���̕ύX���o�^
	void setPos()
	{
		switch (seat)
		{
		case LEFT:
			handInfo.pos_x = -300;
			break;
		case CENTER:
			handInfo.pos_x = 0;
			break;
		case RIGHT:
			handInfo.pos_x = 250;
			break;
		}
	}

	//���i������
	void make()
	{
		if (makebool)
		{
			make_time++;
			if (make_time > 60)
			{
				make_time = 0;
				makebool = false;
			}
		}
	}
};
