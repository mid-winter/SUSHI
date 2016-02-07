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

	int menuMARU;
	int menuBATSU;
	int menuSHIKAKU;
	int menuSANKAKU;

	int menu_;
	int seat = 0;
	int make_time = 0;

	bool makebool_ = false;

	//���̃N���X�̃R�s�[���֎~����
	cPlayer(const cPlayer&) = delete;
	cPlayer& operator =(const cPlayer&) = delete;

public:
	int menu() const{ return menu_; }
	bool makebool() const { return makebool_; }
	int position() const { return seat; }

	//�R���X�g���N�^
	cPlayer(int position,
		int maru = NONE,
		int batsu = NONE,
		int shikaku = NONE,
		int sankaku = NONE)
		:hand_lTex("res/hand/hand_l.raw",
		1024, 1024, true),
		hand_rTex("res/hand/hand_r.raw",
		1024, 1024, true),
		hand_sushi_lTex("res/hand/hand_sushi_l.raw",
		1024, 1024, true),
		hand_sushi_rTex("res/hand/hand_sushi_r.raw",
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
		makebool_ = false;
		menu_ = NONE;

		position = seat;
		menuMARU = maru;
		menuBATSU = batsu;
		menuSHIKAKU = shikaku;
		menuSANKAKU = sankaku;
	}

	//�`��
	void draw()
	{
		// ���u�����f�B���O��L���ɂ���
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (!makebool_)
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
			Color(1, 1, 1, 0.6f),
			keyTex);

		// ���u�����f�B���O�𖳌��ɂ���
		glDisable(GL_BLEND);
	}

	//�����X�V
	void update(std::vector<cGamePad>& pad,
		int position,
		int guest_menu
		)
	{
		setPos();
		make();
		position = seat;

		//�Q�[���p�b�h���g�p����
		for (auto& gamepad : pad)
		{
			//���E�ړ�
			if (gamepad.isPushButton(R1) || gamepad.isPushButton(R2))
			{
				++seat;
				if (seat > RIGHT) seat = LEFT;
			}
			if (gamepad.isPushButton(L1) || gamepad.isPushButton(L2))
			{
				--seat;
				if (seat < LEFT) seat = RIGHT;
			}

			//���i������̐�
			if (guest_menu != NONE)
			{
				if (!makebool_)
				{
					if (gamepad.isPushButton(MARU))
					{
						menu_ = menuMARU;
						makebool_ = true;
					}
					if (gamepad.isPushButton(BATSU))
					{
						menu_ = menuBATSU;
						makebool_ = true;
					}
					if (gamepad.isPushButton(SHIKAKU))
					{
						menu_ = menuSHIKAKU;
						makebool_ = true;
					}
					if (gamepad.isPushButton(SANKAKU))
					{
						menu_ = menuSANKAKU;
						makebool_ = true;
					}
				}
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
		if (makebool_)
		{
			make_time++;
			if (make_time > 60)
			{
				make_time = 0;
				makebool_ = false;
				menu_ = NONE;
			}
		}
	}
};
