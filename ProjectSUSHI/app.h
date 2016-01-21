#pragma once
#include <GLFW/glfw3.h>
#include <string>

class cApp
{
	GLFWwindow* window;

	//���̃N���X�̃R�s�[���֎~����
	cApp(const cApp&) = delete;
	cApp& operator =(const cApp&) = delete;

public:
	//�R���X�g���N�^
	cApp::cApp(const std::string& name,
		const int width, const int height)
	{
		//������
		glfwInit();

		//�E�B���h�E�̐���
		window = glfwCreateWindow(width, height,
			name.c_str(),
			NULL, NULL);
		//�������g��GLFW�̃n���h���ɓo�^
		glfwSetWindowUserPointer(window, this);

		//�`�悷��Ώۂ̃E�B���h�E�̐錾
		glfwMakeContextCurrent(window);
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
		return !glfwWindowShouldClose(window);
	}

	//�J�n
	void cApp::begin()
	{
		//�w�i�F�̐ݒ�
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	//�I��
	void cApp::end()
	{
		//�o�b�t�@�Ɠ���ւ�
		glfwSwapBuffers(window);
		//�L�[���͂𒲂ׂ�
		glfwPollEvents();
	}
};