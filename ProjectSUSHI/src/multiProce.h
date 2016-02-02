#pragma once
#include "GLFW/glfw3.h"
#include "graphic.h"

//�E�B���h�E�T�C�Y
enum WindowSize
{
	WIDTH = 960,
	HEIGHT = 540
};

//�Ȃ��킩��₷��
enum GuestSeat
{
	LEFT = 0,
	CENTER,
	RIGHT
};

//���i�l�^���`
enum SushiMenu
{
	MAGURO = 0,
	SALMON,
	TAMAGO,
	EBI,
	IKURA,
	IKA,
	ANAGO,
	HOTATE
};


//�摜���
struct  TextureInfo
{
	float pos_x, pos_y;
	float size_x, size_y;
	float cut_pos_x, cut_pos_y;
	float cut_size_x, cut_size_y;
};

//�摜�`��
//pos_x, pos_y				�n�_
//width, height				���E����
//texture_x, texture_y		�؂���J�n�ʒu
//texture_w, texture_h		�؂��蕝
//texture					�摜
void drawTexture(const float pos_x, const float pos_y,
	const float width, const float height,
	const float texture_x, const float texture_y,
	const float texture_w, const float texture_h,
	Color& color,
	cTexture& texture)
{
	//�l�p�̏��̔z��
	GLfloat boxStatus[] =
	{
		pos_x, pos_y,
		pos_x, pos_y + height,
		pos_x + width, pos_y,
		pos_x + width, pos_y + height,
	};

	//�`��Ɏg�����_�̔z���OpenGL�Ɏw������
	glVertexPointer(2, GL_FLOAT, 0, boxStatus);

	const auto& size = texture.size();

	GLfloat uv[] = {
		texture_x / size.x(), (texture_y + texture_h) / size.y(),
		texture_x / size.x(), texture_y / size.y(),
		(texture_x + texture_w) / size.x(), (texture_y + texture_h) / size.y(),
		(texture_x + texture_w) / size.x(), texture_y / size.y(),
	};

	glTexCoordPointer(2, GL_FLOAT, 0, uv);

	glEnable(GL_TEXTURE_2D);
	//�摜���
	glBindTexture(GL_TEXTURE_2D, texture.id_);

	//���_�z��ŕ`�悷�郂�[�h�ɐ؂�ւ�
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	color.setToGl();

	//�摜��`��
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//�`�惂�[�h�����ɖ߂�
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//�摜�������
	glBindTexture(GL_TEXTURE_2D, 0);
}

////��]����̉摜�`��
//void drawTexture(const float pos_x, const float pos_y,
//	const float width, const float height,
//	const float texture_x, const float texture_y,
//	const float texture_w, const float texture_h,
//	Color& color,
//	cTexture& texture,
//	const float angle,
//	const Eigen::Vector2f& scaling,
//	const Eigen::Vector2f& origin
//	)
//{
//	//�s��𐶐�
//	auto matrix = transform
//}

//�h��Ԃ�����̎l�p
//pos_x, pos_y		�n�_
//width, height		���E����
//color				�F
void drawFillBox(const float pos_x, const float pos_y,
	const float width, const float height,
	const Color& color)
{
	const float size_x = pos_x + width;
	const float size_y = pos_y + height;

	//�l�p�̏��̔z��
	GLfloat boxStatus[] = 
	{
		pos_x, pos_y,
		size_x, pos_y,
		pos_x, size_y,
		size_x, size_y
	};

	glVertexPointer(2, GL_FLOAT, 0, boxStatus);

	//�F��ݒ�
	color.setToGl();

	//���_�z��ŕ`�悷�郂�[�h�ɐ؂�ւ�
	glEnableClientState(GL_VERTEX_ARRAY);

	//OpenGL�ɐ����̕`����w��
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//�`�惂�[�h�����ɖ߂�
	glDisableClientState(GL_VERTEX_ARRAY);
}

//�t�F�[�h�C��
bool fadeIn(int window_width, int window_height,
	Color& color,
	float fade_speed)
{

	//�E�B���h�E�T�C�Y�Ɠ����傫���̃t�F�[�h��`��
	drawFillBox(-window_width / 2, -window_height / 2,
		window_width, window_height,
		color);

	//���l�����X�ɉ����ē�����
	if (color.alpha() > 0){
		color.alpha() -= fade_speed;
	}
	else{
		return true;
	}
	return false;
}
