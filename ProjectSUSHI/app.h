#pragma once
#include <GLFW/glfw3.h>
#include <string>

class cApp
{
	GLFWwindow* window;

	//このクラスのコピーを禁止する
	cApp(const cApp&) = delete;
	cApp& operator =(const cApp&) = delete;

public:
	//コンストラクタ
	cApp::cApp(const std::string& name,
		const int width, const int height)
	{
		//初期化
		glfwInit();

		//ウィンドウの生成
		window = glfwCreateWindow(width, height,
			name.c_str(),
			NULL, NULL);
		//自分自身をGLFWのハンドルに登録
		glfwSetWindowUserPointer(window, this);

		//描画する対象のウィンドウの宣言
		glfwMakeContextCurrent(window);
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
		return !glfwWindowShouldClose(window);
	}

	//開始
	void cApp::begin()
	{
		//背景色の設定
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	//終了
	void cApp::end()
	{
		//バッファと入れ替え
		glfwSwapBuffers(window);
		//キー入力を調べる
		glfwPollEvents();
	}
};