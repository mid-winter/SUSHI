#pragma once
#include <GLFW/glfw3.h>
#include<string>
#include<fstream>
#include <vector>
#include<Eigen/Core>
#include<Eigen/Geometry>

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

//OpenGL�̃e�N�X�`���n���h�����O
class cGlTexture
{
	GLuint id_;
public:
	cGlTexture();
	~cGlTexture();

	//���̃N���X�̃R�s�[���֎~����
	cGlTexture(const cGlTexture&) = delete;
	cGlTexture& operator=(const cGlTexture&) = delete;

	//OpenGL�̃R���e�L�X�g�ɍS������
	void bind() const;
	//�S������
	void unbind() const;
};

//�摜���N���X
class cTexture
{
	GLuint id_;
	Eigen::Vector2i size_;

	//���̃N���X�̃R�s�[���֎~����
	cTexture(const cTexture&) = delete;
	cTexture& operator =(const cTexture&) = delete;

public:
	cTexture(const std::string& path,
		const int width, const int height,
		const bool alpha)
		: size_(width, height)
	{
		glGenTextures(1, &id_);

		std::vector<char> raw_image = readData(path);

	}
};

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

////�t�@�C���̉�����
//void setupTexture(const GLuint id,
//	const std::vector<char>& rawImage,
//	const int width, const int height,
//	const bool alpha)
//{
//	glBindTexture()
//
//	//�摜���g�傳�ꂽ�Ƃ��̏���
//	glTexParameteri(GL_TEXTURE_2D,
//		GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//�摜���k�����ꂽ�Ƃ��̏���
//	glTexParameteri(GL_TEXTURE_2D,
//		GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//}
