#pragma once
#include<GLFW/glfw3.h>
#include<vector>

enum PS4_BUTTON_NAME
{
	//□×○△
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

	//L3・R3
	L3, R3,
	
	//真ん中押し込み
	TOUCHI_PUSH = 13,

	//十字キー

};

class cGamePad
{
	int id_;

	//ボタンの数
	int button_num_;
	//軸の数
	int axes_num_;

	//ボタンの状況
	std::vector<unsigned char> press_button_;
	std::vector<unsigned char> push_button_;
	std::vector<unsigned char> pull_button_;
	//軸の状況
	std::vector<float> axes_value_;

	// 2軸をボタンとして扱う
	bool  axis_button_;
	//突然動作が始まらないようにする値
	float axis_threshold_;

	//上下左右
	int   axis_x_index_;
	int   axis_y_index_;

	// 軸の Press / Push / Pull の状況
	std::vector<unsigned char> press_axis_button_;
	std::vector<unsigned char> push_axis_button_;
	std::vector<unsigned char> pull_axis_button_;

public:

	//値渡しで呼ばれないコンストラクタ
	explicit cGamePad(const int id)
		:id_(id)
	{
		glfwGetJoystickButtons(id_, &button_num_);
		glfwGetJoystickAxes(id_, &axes_num_);

		//ボタンの数に応じた初期化

		//press
		press_button_.resize(button_num_);
		std::fill(std::begin(press_button_), std::end(press_button_), 0);
		//push
		push_button_.resize(button_num_);
		std::fill(std::begin(push_button_), std::end(push_button_), 0);
		//pull
		pull_button_.resize(button_num_);
		std::fill(std::begin(pull_button_), std::end(pull_button_), 0);

		//軸
		axes_value_.resize(axes_num_);
		std::fill(std::begin(axes_value_), std::end(axes_value_), 0.0f);
	}

	//ボタンの数を返す
	int buttons() const{ return button_num_; }
	//軸の数を返す
	int axes() const{ return axes_num_; }

	//指定のボタンの状態を返す
	bool isPressButton(const int index)const {
		return press_button_[index];
	}
	bool isPushButton(const int index) const {
		return push_button_[index];
	}
	bool isPullButton(const int index) const {
		return pull_button_[index];
	}

	//ゲームパッドが有効かの判定
	bool isActive() const
	{
		return (glfwJoystickPresent(id_) == GL_TRUE)
			? true : false;
	}

	//ゲームパッド内部の更新
	void update()
	{
		//ボタンの押されているかの状況を取得
		int button_num;
		const auto* buttons = glfwGetJoystickButtons(id_, &button_num);

		//ボタンの情報を生成
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

//PCに接続されているゲームパッド情報を取得
std::vector<cGamePad> initGamePad()
{
	std::vector<cGamePad> gamepad;

	//PCに接続されているパッドの検出をしコンテナに格納
	for (int id = GLFW_JOYSTICK_1; id <= GLFW_JOYSTICK_LAST; ++id)
	{
		if (glfwJoystickPresent(id) == GL_TRUE)
		{
			gamepad.emplace_back(id);
		}
	}

	return gamepad;
}

//ゲームパッドの情報をまとめて更新

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