#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class cApp
{
	GLFWwindow* window_;

	int width_;
	int height_;

	//���̃N���X�̃R�s�[���֎~����
	cApp(const cApp&) = delete;
	cApp& operator =(const cApp&) = delete;

public:
	//�R���X�g���N�^
	cApp::cApp(const std::string& name,
		const int width, const int height)
		:width_(width), height_(height)
	{
		//������
		glfwInit();

		//�E�B���h�E�̐���
		window_ = glfwCreateWindow(width, height,
			name.c_str(),
			nullptr, nullptr);

		//�������g��GLFW�̃n���h���ɓo�^
		glfwSetWindowUserPointer(window_, this);

		//�E�B���h�E�T�C�Y�ύX���̏���
		glfwSetWindowSizeCallback(window_, resize);
		//�`�悷��Ώۂ̃E�B���h�E�̐錾
		glfwMakeContextCurrent(window_);
		//��ʂ̍X�V������Ԋu�̐ݒ�
		glfwSwapInterval(1);
	}

	//�f�X�g���N�^
	cApp::~cApp()
	{
		//�A�v���̏I��
		glfwTerminate();
	}

	//�A�v�����J���Ă�����
	bool cApp::isOpen()
	{
		//���Ȃ���_��
		return !glfwWindowShouldClose(window_);
	}

	//�J�n
	void cApp::begin()
	{
		//�w�i�F�̐ݒ�
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(-width_ / 2, width_ / 2,
			-height_ / 2, height_ / 2,
			-1.0f, 1.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	//�I��
	void cApp::end()
	{
		//�o�b�t�@�Ɠ���ւ�
		glfwSwapBuffers(window_);
		//�L�[���͂𒲂ׂ�
		glfwPollEvents();
	}

private:
	//��ʃT�C�Y�o�^
	void setSize(const int width, const int height)
	{
		width_ = width;
		height_ = height;
	}

	//��ʃT�C�Y���ύX���ꂽ�Ƃ��̏���
	static void resize(GLFWwindow* window,
		int width, int height)
	{
		//�o�^�����|�C���^�����o��
		cApp* ptr = 
			static_cast<cApp*>(glfwGetWindowUserPointer(window));
		ptr->setSize(width, height);
	}
};