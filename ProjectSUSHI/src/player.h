#pragma once
#include"multiProce.h"
#include"gamePad.h"
#include"guest.h"
#include"sushi.h"

//�v���C���[�̃N���X
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

	//���i�N���X
	cSushi sushi;

	//�{�^���ɑ΂��郁�j���[
	int menuMARU;
	int menuBATSU;
	int menuSHIKAKU;
	int menuSANKAKU;

	//���j���[
	int menu_ = NONE;
	//�ʒu
	int position_ = CENTER;

	//���i�𐶐�����̐��ɂȂ��Ă��鎞��
	int make_time = 0;
	//��������
	bool makebool_ = false;

	//���̃N���X�̃R�s�[���֎~����
	cPlayer(const cPlayer&) = delete;
	cPlayer& operator =(const cPlayer&) = delete;

public:
	int menu() const{ return menu_; }
	bool makebool() const { return makebool_; }
	int position() const { return position_; }

	//�R���X�g���N�^
	cPlayer(
		int maru = NONE,
		int batsu = NONE,
		int shikaku = NONE,
		int sankaku = NONE)
		:hand_lTex("res/hand/hand_l.raw", 1024, 1024, true),
		hand_rTex("res/hand/hand_r.raw", 1024, 1024, true),
		hand_sushi_lTex("res/hand/hand_sushi_l.raw", 1024, 1024, true),
		hand_sushi_rTex("res/hand/hand_sushi_r.raw", 1024, 1024, true),
		keyTex("res/key.raw", 512, 512, true),
		sushi()
	{
		//��̈ʒu���
		handInfo = {
			0, -350,
			400, 200,
			0, 0,
			1024, 600
		};

		//��̈ʒu
		position_ = CENTER;

		//���i��������
		makebool_ = false;
		menu_ = NONE;

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

		//���i�̉摜
		sushi.draw();

		// ���u�����f�B���O�𖳌��ɂ���
		glDisable(GL_BLEND);
	}

	//�����X�V
	void update(std::vector<cGamePad>& pad,
		int guest_menu1 = NONE,
		int guest_menu2 = NONE,
		int guest_menu3 = NONE
		)
	{
		setPos();
		make();
		sushi.update(menu_, position_);

		//�Q�[���p�b�h���g�p����
		for (auto& gamepad : pad)
		{
			//���E�ړ�
			if (!makebool_)
			{
				if (gamepad.isPushButton(R1) || gamepad.isPushButton(R2))
				{
					++position_;
					if (position_ > RIGHT) position_ = LEFT;
				}
				if (gamepad.isPushButton(L1) || gamepad.isPushButton(L2))
				{
					--position_;
					if (position_ < LEFT) position_ = RIGHT;
				}
			}

			//���i������̐�
			if (guest_menu1 != NONE ||
				guest_menu2 != NONE ||
				guest_menu3 != NONE)
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

private:
	//�ʒu���̕ύX���o�^
	void setPos()
	{
		switch (position_)
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
			if (make_time > 30)
			{
				make_time = 0;
				//���O�̑̐��ɖ߂�
				makebool_ = false;
				//�v���C���[�̑I�����Ă��郁�j���[��߂�
				menu_ = NONE;
			}
		}
	}
};
