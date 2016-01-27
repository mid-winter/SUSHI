#pragma once
#include "graphic.h"
#include "multiProce.h"

class cFade
{
	//�t�F�[�h�F
	Color fadecolor_;

public:
	bool fade_in_start = false;
	bool fade_out_start = false;

	//�R���X�g���N�^
	cFade(Color& color) :
		fadecolor_(color)
	{
	}

	//�`��		�K���`�悷����̂̍Ō�ɓǂݍ���
	void draw(int width, int height,
		Color& color)
	{
		//�t�F�[�h�̓h��Ԃ���`
		drawFillBox(-width / 2, -height / 2,
			width, height,
			color);
	}

	void update();
};
