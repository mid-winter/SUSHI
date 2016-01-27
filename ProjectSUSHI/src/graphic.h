#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <Eigen/Core>
#include <Eigen/Geometry>

//色のクラス
class Color
{
	float red_;
	float green_;
	float blue_;
	float alpha_;

public:
	//コンストラクタ
	Color() :red_(0.0f), green_(0.0f), blue_(0.0f),
		alpha_(1.0f){}

	//値を設定(0.0~1.0)
	Color(const float red, const float green, const float blue,
		const float alpha = 1.0f) :
		red_(red), green_(green), blue_(blue),
		alpha_(alpha){}

	//色の変更
	float& red(){ return red_; }
	float& green(){ return green_; }
	float& blue(){ return blue_; }
	float& alpha(){ return alpha_; }

	//OpenGLへ描画色を指定する
	void setToGl() const
	{
		glColor4f(red_, green_, blue_, alpha_);
	}
};

//256で色
Color color256(const int red, const int green, const int blue,
	const int alpha = 255)
{
	return Color(red / 255.0f, green / 255.0f, blue / 255.0f,
		alpha / 255.0f);
}

//ファイルの読み込み
std::vector<char> readData(const std::string& path)
{
	//ファイルをバイナリモードで開く
	std::ifstream fstr(path, std::ios::binary);

	//エラーが出たら空のデータを返す
	if (!fstr)return std::vector<char>();

	//ファイルサイズの取得 0~endまでという意味
	fstr.seekg(0, fstr.end);
	size_t file_size = size_t(fstr.tellg());

	//読み込み位置をファイル先頭へ
	fstr.seekg(0, fstr.beg);

	//動的配列を使ってファイルを読み込む場所を確保
	//charをfile_size個分確保するという意味
	std::vector<char> read_buffer(file_size);

	//確保した場所へファイルの内容をすべて読み込む
	fstr.read(&read_buffer[0], file_size);

	return read_buffer;
}

//テクスチャの下準備
void setupTexture(const GLuint id,
	const std::vector<char>& raw_image,
	const int width, const int height,
	const bool alpha)
{
	//OpenGLに指示
	glBindTexture(GL_TEXTURE_2D, id);
	//α値があるかないかで引数変更
	GLint format = alpha ? GL_RGBA : GL_RGB;

	//width* heightの画像データをOpenGLへ登録
	glTexImage2D(GL_TEXTURE_2D,
		0, format, width, height,
		0, format, GL_UNSIGNED_BYTE,
		&raw_image[0]);

	//画像が拡大された場合の処理
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//画像が縮小した場合の処理
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//テクスチャの繰り返しの指定
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_T, GL_CLAMP);
}

//画像情報クラス
class cTexture
{
	//画像のサイズ
	Eigen::Vector2i size_;

	//このクラスのコピーを禁止する
	cTexture(const cTexture&) = delete;
	cTexture& operator =(const cTexture&) = delete;

public:

	GLuint id_;

	//コンストラクタ
	cTexture(const std::string& path,
		const int width, const int height,
		const bool alpha)
		:size_(width, height)
	{
		//テクスチャ識別子を一つ作る
		glGenTextures(1, &id_);

		//ファイルの読み込み
		std::vector<char> raw_image =
			readData(path);

		//テクスチャの下準備
		setupTexture(id_, raw_image,
			width, height, alpha);
	}

	//デストラクタ
	~cTexture()
	{
		//テクスチャ識別子を削除
		glDeleteTextures(1, &id_);
	}

	//サイズを受け取る
	const Eigen::Vector2i& size() const { return size_; }
};
