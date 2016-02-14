#pragma once
#include"multiProce.h"

class cSushi
{
	//�e�N�X�`��
	cTexture MaguroTex;
	cTexture SalmonTex;
	cTexture TamagoTex;
	cTexture EbiTex;
	cTexture IkuraTex;
	cTexture IkaTex;
	cTexture AnagoTex;
	cTexture HotateTex;

	//�`����
	TextureInfo sushiInfo;

	//���i�l�^�I��
	int menu_ = NONE;
	//�v���C���[�Ɠ����ʒu�ɏo�����߂�
	int seat_ = CENTER;
	
	//�l�i
	int price = 0;

public:

	//�R���X�g���N�^�i�������j
	cSushi() :
		MaguroTex("res/menu/maguro.raw", 512, 256, true),
		SalmonTex("res/menu/salmon.raw", 512, 256, true),
		TamagoTex("res/menu/tamago.raw", 512, 256, true),
		EbiTex("res/menu/ebi.raw", 512, 256, true),
		IkuraTex("res/menu/ikura.raw", 512, 256, true),
		IkaTex("res/menu/ika.raw", 512, 256, true),
		AnagoTex("res/menu/anago.raw", 512, 256, true),
		HotateTex("res/menu/hotate.raw", 512, 256, true)
	{
		//�摜�ʒu�Ȃǂ̏��
		sushiInfo =
		{
			0, 0,
			150, 75,
			0, 0, 400, 256
		};
		menu_ = NONE;
		seat_ = CENTER;
	}

	//�`��
	void draw()
	{
		// ���u�����f�B���O��L���ɂ���
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		switch (menu_)
		{
		case NONE:
			break;
		case MAGURO:
			drawTexture(sushiInfo.pos_x, sushiInfo.pos_y,
				sushiInfo.size_x, sushiInfo.size_y,
				sushiInfo.cut_pos_x, sushiInfo.cut_pos_y,
				sushiInfo.cut_size_x, sushiInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				MaguroTex);
			break;
		case SALMON:
			drawTexture(sushiInfo.pos_x, sushiInfo.pos_y,
				sushiInfo.size_x, sushiInfo.size_y,
				sushiInfo.cut_pos_x, sushiInfo.cut_pos_y,
				sushiInfo.cut_size_x, sushiInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				SalmonTex);
			break;
		case TAMAGO:
			drawTexture(sushiInfo.pos_x, sushiInfo.pos_y,
				sushiInfo.size_x, sushiInfo.size_y,
				sushiInfo.cut_pos_x, sushiInfo.cut_pos_y,
				sushiInfo.cut_size_x, sushiInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				TamagoTex);
			break;
		case EBI:
			drawTexture(sushiInfo.pos_x, sushiInfo.pos_y,
				sushiInfo.size_x, sushiInfo.size_y,
				sushiInfo.cut_pos_x, sushiInfo.cut_pos_y,
				sushiInfo.cut_size_x, sushiInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				EbiTex);
			break;
		case IKURA:
			drawTexture(sushiInfo.pos_x, sushiInfo.pos_y,
				sushiInfo.size_x, sushiInfo.size_y,
				sushiInfo.cut_pos_x, sushiInfo.cut_pos_y,
				sushiInfo.cut_size_x, sushiInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				IkuraTex);
			break;
		case IKA:
			drawTexture(sushiInfo.pos_x, sushiInfo.pos_y,
				sushiInfo.size_x, sushiInfo.size_y,
				sushiInfo.cut_pos_x, sushiInfo.cut_pos_y,
				sushiInfo.cut_size_x, sushiInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				IkaTex);
			break;
		case ANAGO:
			drawTexture(sushiInfo.pos_x, sushiInfo.pos_y,
				sushiInfo.size_x, sushiInfo.size_y,
				sushiInfo.cut_pos_x, sushiInfo.cut_pos_y,
				sushiInfo.cut_size_x, sushiInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				AnagoTex);
			break;
		case HOTATE:
			drawTexture(sushiInfo.pos_x, sushiInfo.pos_y,
				sushiInfo.size_x, sushiInfo.size_y,
				sushiInfo.cut_pos_x, sushiInfo.cut_pos_y,
				sushiInfo.cut_size_x, sushiInfo.cut_size_y,
				Color(1.0f, 1.0f, 1.0f),
				HotateTex);
			break;
		}

		// ���u�����f�B���O�𖳌��ɂ���
		glDisable(GL_BLEND);
	}

	//����
	void update(int player_menu, int player_position)
	{
		//�ʒu���𓯊�
		setPosition();
		seat_ = player_position;
		menu_ = player_menu;
	}
private:
	//�ʒu���
	void setPosition()
	{
		switch (seat_)
		{
		case LEFT:
			sushiInfo.pos_x = -400;
			sushiInfo.pos_y = -HEIGHT / 2 + 150;
			break;
		case CENTER:
			sushiInfo.pos_x = -75;
			sushiInfo.pos_y = -HEIGHT / 2 + 150;
			break;
		case RIGHT:
			sushiInfo.pos_x = 250;
			sushiInfo.pos_y = -HEIGHT / 2 + 150;
			break;
		}
	}
};