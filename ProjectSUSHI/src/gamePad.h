#pragma once
#include<GLFW/glfw3.h>
#include<vector>

enum PS4_BUTTON_NAME
{
	//���~����
	SHIKAKU = 0,
	BATSU,
	MARU,
	SANKAKU,

	//L1~R2
	L1, R1,
	L2, R2,

	//SHARE & OPTIONS
	SHARE,
	OPTIONS,

	//L3�ER3
	L3, R3,
	
	//�^�񒆉�������
	TOUCHI_PUSH = 13,

	//�\���L�[

};

class cGamePad
{
	int id_;

	//�{�^���̐�
	int button_num_;
	//���̐�
	int axes_num_;

	//�{�^���̏�
	std::vector<unsigned char> press_button_;
	std::vector<unsigned char> push_button_;
	std::vector<unsigned char> pull_button_;
	//���̏�
	std::vector<float> axes_value_;

	// 2�����{�^���Ƃ��Ĉ���
	bool  axis_button_;
	//�ˑR���삪�n�܂�Ȃ��悤�ɂ���l
	float axis_threshold_;

	//�㉺���E
	int   axis_x_index_;
	int   axis_y_index_;

	// ���� Press / Push / Pull �̏�
	std::vector<unsigned char> press_axis_button_;
	std::vector<unsigned char> push_axis_button_;
	std::vector<unsigned char> pull_axis_button_;

public:

	//�l�n���ŌĂ΂�Ȃ��R���X�g���N�^
	explicit cGamePad(const int id)
		:id_(id)
	{
		glfwGetJoystickButtons(id_, &button_num_);
		glfwGetJoystickAxes(id_, &axes_num_);

		//�{�^���̐��ɉ�����������

		//press
		press_button_.resize(button_num_);
		std::fill(std::begin(press_button_), std::end(press_button_), 0);
		//push
		push_button_.resize(button_num_);
		std::fill(std::begin(push_button_), std::end(push_button_), 0);
		//pull
		pull_button_.resize(button_num_);
		std::fill(std::begin(pull_button_), std::end(pull_button_), 0);

		//��
		axes_value_.resize(axes_num_);
		std::fill(std::begin(axes_value_), std::end(axes_value_), 0.0f);
	}

	//�{�^���̐���Ԃ�
	int buttons() const{ return button_num_; }
	//���̐���Ԃ�
	int axes() const{ return axes_num_; }

	//�w��̃{�^���̏�Ԃ�Ԃ�
	bool isPressButton(const int index)const {
		return press_button_[index];
	}
	bool isPushButton(const int index) const {
		return push_button_[index];
	}
	bool isPullButton(const int index) const {
		return pull_button_[index];
	}

	//�Q�[���p�b�h���L�����̔���
	bool isActive() const
	{
		return (glfwJoystickPresent(id_) == GL_TRUE)
			? true : false;
	}

	//�Q�[���p�b�h�����̍X�V
	void update()
	{
		//�{�^���̉�����Ă��邩�̏󋵂��擾
		int button_num;
		const auto* buttons = glfwGetJoystickButtons(id_, &button_num);

		//�{�^���̏��𐶐�
		if (button_num > 0)
		{
			for (int i = 0; i < button_num; ++i)
			{
				push_button_[i] = !press_button_[i] && buttons[i];
				pull_button_[i] = press_button_[i] && !buttons[i];

				press_button_[i] = buttons[i];
			}
		}
	}
};

//PC�ɐڑ�����Ă���Q�[���p�b�h�����擾
std::vector<cGamePad> initGamePad()
{
	std::vector<cGamePad> gamepad;

	//PC�ɐڑ�����Ă���p�b�h�̌��o�����R���e�i�Ɋi�[
	for (int id = GLFW_JOYSTICK_1; id <= GLFW_JOYSTICK_LAST; ++id)
	{
		if (glfwJoystickPresent(id) == GL_TRUE)
		{
			gamepad.emplace_back(id);
		}
	}

	return gamepad;
}

//�Q�[���p�b�h�̏����܂Ƃ߂čX�V

void updateGamePad(std::vector<cGamePad>& gamepad)
{
	for (auto& pad : gamepad)
	{
		if (pad.isActive())
		{
			pad.update();
		}
	}
}