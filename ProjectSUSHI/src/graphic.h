#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <Eigen/Core>
#include <Eigen/Geometry>

//�F�̃N���X
class Color
{
	float red_;
	float green_;
	float blue_;
	float alpha_;

public:
	//�R���X�g���N�^
	Color() :red_(0.0f), green_(0.0f), blue_(0.0f),
		alpha_(1.0f){}

	//�l��ݒ�(0.0~1.0)
	Color(const float red, const float green, const float blue,
		const float alpha = 1.0f) :
		red_(red), green_(green), blue_(blue),
		alpha_(alpha){}

	//�F�̕ύX
	float& red(){ return red_; }
	float& green(){ return green_; }
	float& blue(){ return blue_; }
	float& alpha(){ return alpha_; }

	//OpenGL�֕`��F���w�肷��
	void setToGl() const
	{
		glColor4f(red_, green_, blue_, alpha_);
	}
};

//256�ŐF
Color color256(const int red, const int green, const int blue,
	const int alpha = 255)
{
	return Color(red / 255.0f, green / 255.0f, blue / 255.0f,
		alpha / 255.0f);
}

//�t�@�C���̓ǂݍ���
std::vector<char> readData(const std::string& path)
{
	//�t�@�C�����o�C�i�����[�h�ŊJ��
	std::ifstream fstr(path, std::ios::binary);

	//�G���[���o�����̃f�[�^��Ԃ�
	if (!fstr)return std::vector<char>();

	//�t�@�C���T�C�Y�̎擾 0~end�܂łƂ����Ӗ�
	fstr.seekg(0, fstr.end);
	size_t file_size = size_t(fstr.tellg());

	//�ǂݍ��݈ʒu���t�@�C���擪��
	fstr.seekg(0, fstr.beg);

	//���I�z����g���ăt�@�C����ǂݍ��ޏꏊ���m��
	//char��file_size���m�ۂ���Ƃ����Ӗ�
	std::vector<char> read_buffer(file_size);

	//�m�ۂ����ꏊ�փt�@�C���̓��e�����ׂēǂݍ���
	fstr.read(&read_buffer[0], file_size);

	return read_buffer;
}

//�e�N�X�`���̉�����
void setupTexture(const GLuint id,
	const std::vector<char>& raw_image,
	const int width, const int height,
	const bool alpha)
{
	//OpenGL�Ɏw��
	glBindTexture(GL_TEXTURE_2D, id);
	//���l�����邩�Ȃ����ň����ύX
	GLint format = alpha ? GL_RGBA : GL_RGB;

	//width* height�̉摜�f�[�^��OpenGL�֓o�^
	glTexImage2D(GL_TEXTURE_2D,
		0, format, width, height,
		0, format, GL_UNSIGNED_BYTE,
		&raw_image[0]);

	//�摜���g�傳�ꂽ�ꍇ�̏���
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//�摜���k�������ꍇ�̏���
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//�e�N�X�`���̌J��Ԃ��̎w��
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_T, GL_CLAMP);
}

//�摜���N���X
class cTexture
{
	//�摜�̃T�C�Y
	Eigen::Vector2i size_;

	//���̃N���X�̃R�s�[���֎~����
	cTexture(const cTexture&) = delete;
	cTexture& operator =(const cTexture&) = delete;

public:

	GLuint id_;

	//�R���X�g���N�^
	cTexture(const std::string& path,
		const int width, const int height,
		const bool alpha)
		:size_(width, height)
	{
		//�e�N�X�`�����ʎq������
		glGenTextures(1, &id_);

		//�t�@�C���̓ǂݍ���
		std::vector<char> raw_image =
			readData(path);

		//�e�N�X�`���̉�����
		setupTexture(id_, raw_image,
			width, height, alpha);
	}

	//�f�X�g���N�^
	~cTexture()
	{
		//�e�N�X�`�����ʎq���폜
		glDeleteTextures(1, &id_);
	}

	//�T�C�Y���󂯎��
	const Eigen::Vector2i& size() const { return size_; }
};
