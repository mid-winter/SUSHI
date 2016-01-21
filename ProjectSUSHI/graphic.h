#pragma once
#include <GLFW/glfw3.h>
#include<string>
#include<fstream>
#include <vector>
#include<Eigen/Core>
#include<Eigen/Geometry>

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

//OpenGLのテクスチャハンドリング
class cGlTexture
{
	GLuint id_;
public:
	cGlTexture();
	~cGlTexture();

	//このクラスのコピーを禁止する
	cGlTexture(const cGlTexture&) = delete;
	cGlTexture& operator=(const cGlTexture&) = delete;

	//OpenGLのコンテキストに拘束する
	void bind() const;
	//拘束解除
	void unbind() const;
};

//画像情報クラス
class cTexture
{
	GLuint id_;
	Eigen::Vector2i size_;

	//このクラスのコピーを禁止する
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

////ファイルの下準備
//void setupTexture(const GLuint id,
//	const std::vector<char>& rawImage,
//	const int width, const int height,
//	const bool alpha)
//{
//	glBindTexture()
//
//	//画像が拡大されたときの処理
//	glTexParameteri(GL_TEXTURE_2D,
//		GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//画像が縮小されたときの処理
//	glTexParameteri(GL_TEXTURE_2D,
//		GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//}
