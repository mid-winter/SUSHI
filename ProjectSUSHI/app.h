#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class cApp
{
	GLFWwindow* window_;

	int width_;
	int height_;

	//このクラスのコピーを禁止する
	cApp(const cApp&) = delete;
	cApp& operator =(const cApp&) = delete;

public:
	//コンストラクタ
	cApp::cApp(const std::string& name,
		const int width, const int height)
		:width_(width), height_(height)
	{
		//初期化
		glfwInit();

		//ウィンドウの生成
		window_ = glfwCreateWindow(width, height,
			name.c_str(),
			nullptr, nullptr);

		//自分自身をGLFWのハンドルに登録
		glfwSetWindowUserPointer(window_, this);

		//ウィンドウサイズ変更時の処理
		glfwSetWindowSizeCallback(window_, resize);
		//描画する対象のウィンドウの宣言
		glfwMakeContextCurrent(window_);
		//画面の更新をする間隔の設定
		glfwSwapInterval(1);
	}

	//デストラクタ
	cApp::~cApp()
	{
		//アプリの終了
		glfwTerminate();
	}

	//アプリが開いていたら
	bool cApp::isOpen()
	{
		//閉じなきゃダメ
		return !glfwWindowShouldClose(window_);
	}

	//開始
	void cApp::begin()
	{
		//背景色の設定
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

	//終了
	void cApp::end()
	{
		//バッファと入れ替え
		glfwSwapBuffers(window_);
		//キー入力を調べる
		glfwPollEvents();
	}

private:
	//画面サイズ登録
	void setSize(const int width, const int height)
	{
		width_ = width;
		height_ = height;
	}

	//画面サイズが変更されたときの処理
	static void resize(GLFWwindow* window,
		int width, int height)
	{
		//登録したポインタを取り出す
		cApp* ptr = 
			static_cast<cApp*>(glfwGetWindowUserPointer(window));
		ptr->setSize(width, height);
	}
};