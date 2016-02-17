#pragma once
#include"multiProce.h"
#include"random.h"
#include<time.h>

class cGuest
{
	//�摜
	cTexture childTex;
	TextureInfo guestInfo;

	cTexture fukidashiTex;
	cTexture menuTex;
	TextureInfo menuInfo;

	//�����_��
	cRandom random;

	//�ʒu���
	int position_ = LEFT;

	//�ړ����x
	float move_speed = 10.0f;

	//����
	bool callbool = false;
	int calltime = 0;

	//�������j���[
	int menu_;
	float fontsize;
	int price_ = 0;

	bool oncebool = false;

	//�\��
	int face;
	//�I��
	int set_ = 0;

	//�����|�C���g
	int satisfaction = 0;
	int clearpoint = 0;

	//���̃N���X�̃R�s�[���֎~����
	cGuest(const cGuest&) = delete;
	cGuest& operator =(const cGuest&) = delete;

public:
	int earnings = 0;
	int menu() const{ return menu_; }
	bool clearbool = false;

	//�R���X�g���N�^
	cGuest(int seat_num)
		:childTex("res/child.raw", 1024, 256, true),
		fukidashiTex("res/fukidashi.raw", 1024, 1024, true),
		menuTex("res/menu/menu.raw", 1024, 512, true)
	{
		//�Ȃ����߂�
		position_ = seat_num;

		callbool = false;
		calltime = 0;

		//�����T�C�Y(�c������)
		fontsize = 100;

		oncebool = false;

		//�\��
		face = NORMAL;

		//�N���A���邽�߂̕ϐ�
		satisfaction = 0;

		random.setSeed((unsigned int)time(NULL));
		clearbool = false;

		//�ʒu���
		guestInfo =
		{
			WIDTH / 2 + 100.0f, -HEIGHT / 2 + 175.0f,
			250, 250,
			0, 0, 256, 256
		};
		//�����o���̒��g
		menuInfo =
		{
			0, 0,
			150, 50,
			0, 0,
			400, 100
		};
	}

	//�`��
	void draw()
	{
		// ���u�����f�B���O��L���ɂ���
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//�q�摜
		drawTexture(guestInfo.pos_x, guestInfo.pos_y,
			guestInfo.size_x, guestInfo.size_y,
			guestInfo.cut_pos_x, guestInfo.cut_pos_y,
			guestInfo.cut_size_x, guestInfo.cut_size_y,
			Color(0.0f, 0.0f, 0.0f),
			childTex);
		drawTexture(guestInfo.pos_x + 1, guestInfo.pos_y + 1,
			guestInfo.size_x - 2, guestInfo.size_y -2,
			guestInfo.cut_pos_x, guestInfo.cut_pos_y,
			guestInfo.cut_size_x, guestInfo.cut_size_y,
			Color(1.0f, 1.0f, 1.0f),
			childTex);

		//�����o��
		if (callbool)
		{
			drawTexture(guestInfo.pos_x, guestInfo.pos_y + 200,
				200, 100,
				0, 0, 1024, 600,
				Color(0.0f, 0.0f, 0.0f),
				fukidashiTex);
			drawTexture(guestInfo.pos_x + 2, guestInfo.pos_y + 200 + 2,
				200 - 4, 100 -4,
				0, 0, 1024, 600,
				Color(1.0f, 1.0f, 1.0f),
				fukidashiTex);

			//��������
			drawTexture(menuInfo.pos_x, menuInfo.pos_y + 200,
				menuInfo.size_x, menuInfo.size_y,
				menuInfo.cut_pos_x, menuInfo.cut_pos_y,
				menuInfo.cut_size_x, menuInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				menuTex);
		}

		// ���u�����f�B���O�𖳌��ɂ���
		glDisable(GL_BLEND);
	}

	//�����X�V
	void update(int player_menu, int player_position)
	{
		if (clearpoint < 7)
		{
			clearpoint = rand() % 10;
		}

		//����������Ŗ��t���[���X�V������̂�����
		changeFace();
		setmenu();

		if (movebool()) call();

		//�\���������
		if (player_menu == NONE)
		{
			face = NORMAL;
		}

		//�v���C���[�̈ʒu�Ƌq�̈ʒu�������Ȃ�
		if (position_ == player_position)
		{
			if (player_menu != NONE)
			{
				if (!oncebool)
				{
					judge(player_menu);
				}
				oncebool = true;
			}
			else
			{
				oncebool = false;
			}
		}

		//����������o�Ă���
		if (satisfaction >= clearpoint)
		{
			if (guestInfo.pos_x >= -WIDTH)
			{
				guestInfo.pos_x -= move_speed;
			}
			else
			{
				clearbool = true;
				Init();
			}
		}
	}

	//�\���ύX
	void judge(int menu)
	{
		if (menu_ != NONE)
		{
			if (menu_ != menu)
			{
				face = ANGER;
				satisfaction--;
				if (earnings > 0)
				{
					earnings -= price_;
				}
				else if (earnings <= 0)
				{
					earnings = 0;
				}
				menu_ = NONE;
				callbool = false;
			}
			else if (menu_ == menu)
			{
				face = SMILE;
				satisfaction++;
				earnings += price_;
				menu_ = NONE;
				callbool = false;
			}
		}
		std::cout << "Score" << satisfaction << std::endl;
	}

private:

	//�\��ύX
	void changeFace()
	{
		switch (face)
		{
		case NORMAL:
			guestInfo.cut_pos_x = 0;
			break;
		case SMILE:
			guestInfo.cut_pos_x = 256;
			break;
		case ANGER:
			guestInfo.cut_pos_x = 512;
			break;
		}
	}

	//����Ȃ̈ʒu�����߂�
	float sit_pos()
	{
		switch (position_){
			//���̐�
		case LEFT:
			return -450.0f;
			break;

			//�����̐�
		case CENTER:
			return -125.0f;
			break;

			//�E�̐�
		case RIGHT:
			return 200;
			break;
		}
	}

	//�ړ�����
	bool movebool()
	{
		if (guestInfo.pos_x > sit_pos())
		{
			guestInfo.pos_x -= 5.0f;
			return false;
		}
		else
		{
			return true;
		}
	}

	//���j���[��錾
	void call()
	{
		if (!clearbool)
		{
			if (!callbool)
			{
				//��莞�ԂŐ錾
				calltime++;
				if (calltime >= 120 )
				{
					set_ = rand() % 4;
					menu_ = selectMenu[set_];
					calltime = 0;
					callbool = true;
				}
			}
		}
	}

	//�v���ɍ��킹�ĕ�����ύX
	void setmenu()
	{
		//�ʒu�͓���
		menuInfo.pos_x = guestInfo.pos_x + 25;
		menuInfo.pos_y = guestInfo.pos_y + 30;

		switch (menu_)
		{
		case MAGURO:

			menuInfo.size_x = 150.0f;
			menuInfo.size_y = 50.0f;

			menuInfo.cut_pos_x = 0;
			menuInfo.cut_pos_y = fontsize * 0;
			menuInfo.cut_size_x = fontsize * 3;
			menuInfo.cut_size_y = fontsize;

			price_ = 100;
			break;
		case SALMON:

			menuInfo.size_x = 160.0f;
			menuInfo.size_y = 40.0f;

			menuInfo.cut_pos_x = 0.0f;
			menuInfo.cut_pos_y = fontsize * 1;
			menuInfo.cut_size_x = fontsize * 4;
			menuInfo.cut_size_y = fontsize;

			price_ = 110;
			break;
		case TAMAGO:

			menuInfo.size_x = 150.0f;
			menuInfo.size_y = 50.0f;

			menuInfo.cut_pos_x = 0.0f;
			menuInfo.cut_pos_y = fontsize * 2;
			menuInfo.cut_size_x = fontsize * 3;
			menuInfo.cut_size_y = fontsize;

			price_ = 100;
			break;
		case EBI:

			menuInfo.size_x = 140.0f;
			menuInfo.size_y = 70.0f;

			menuInfo.cut_pos_x = 0.0f;
			menuInfo.cut_pos_y = fontsize * 3;
			menuInfo.cut_size_x = fontsize * 2;
			menuInfo.cut_size_y = fontsize;

			price_ = 100;
			break;
		case IKURA:

			menuInfo.size_x = 150.0f;
			menuInfo.size_y = 50.0f;

			menuInfo.cut_pos_x = 500.0f;
			menuInfo.cut_pos_y = fontsize * 0;
			menuInfo.cut_size_x = fontsize * 3;
			menuInfo.cut_size_y = fontsize;

			price_ = 120;
			break;
		case IKA:

			menuInfo.size_x = 140.0f;
			menuInfo.size_y = 70.0f;

			menuInfo.cut_pos_x = 500.0f;
			menuInfo.cut_pos_y = fontsize * 1;
			menuInfo.cut_size_x = fontsize * 2;
			menuInfo.cut_size_y = fontsize;

			price_ = 110;
			break;
		case ANAGO:

			menuInfo.size_x = 150.0f;
			menuInfo.size_y = 50.0f;

			menuInfo.cut_pos_x = 500.0f;
			menuInfo.cut_pos_y = fontsize * 2;
			menuInfo.cut_size_x = fontsize * 3;
			menuInfo.cut_size_y = fontsize;

			price_ = 120;
			break;
		case HOTATE:

			menuInfo.size_x = 150.0f;
			menuInfo.size_y = 50.0f;

			menuInfo.cut_pos_x = 500.0f;
			menuInfo.cut_pos_y = fontsize * 3;
			menuInfo.cut_size_x = fontsize * 3;
			menuInfo.cut_size_y = fontsize;

			price_ = 140;
			break;
		}
	}

	void Init()
	{
		callbool = false;
		calltime = 0;

		//�����T�C�Y(�c������)
		fontsize = 100;

		oncebool = false;

		//�\��
		face = NORMAL;

		//�N���A���邽�߂̕ϐ�
		satisfaction = 0;

		random.setSeed((unsigned int)time(NULL));
		clearbool = false;

		//�ʒu���
		guestInfo =
		{
			WIDTH / 2 + 100.0f, -HEIGHT / 2 + 175.0f,
			250, 250,
			0, 0, 256, 256
		};
		//�����o���̒��g
		menuInfo =
		{
			0, 0,
			150, 50,
			0, 0,
			400, 100
		};
	}
};
