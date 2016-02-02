#pragma once
#include "GLFW/glfw3.h"
#include "graphic.h"

//ウィンドウサイズ
enum WindowSize
{
	WIDTH = 960,
	HEIGHT = 540
};

//席をわかりやすく
enum GuestSeat
{
	LEFT = 0,
	CENTER,
	RIGHT
};

//寿司ネタを定義
enum SushiMenu
{
	MAGURO = 0,
	SALMON,
	TAMAGO,
	EBI,
	IKURA,
	IKA,
	ANAGO,
	HOTATE
};


//画像情報
struct  TextureInfo
{
	float pos_x, pos_y;
	float size_x, size_y;
	float cut_pos_x, cut_pos_y;
	float cut_size_x, cut_size_y;
};

//画像描画
//pos_x, pos_y				始点
//width, height				幅・高さ
//texture_x, texture_y		切り取り開始位置
//texture_w, texture_h		切り取り幅
//texture					画像
void drawTexture(const float pos_x, const float pos_y,
	const float width, const float height,
	const float texture_x, const float texture_y,
	const float texture_w, const float texture_h,
	Color& color,
	cTexture& texture)
{
	//四角の情報の配列
	GLfloat boxStatus[] =
	{
		pos_x, pos_y,
		pos_x, pos_y + height,
		pos_x + width, pos_y,
		pos_x + width, pos_y + height,
	};

	//描画に使う頂点の配列をOpenGLに指示する
	glVertexPointer(2, GL_FLOAT, 0, boxStatus);

	const auto& size = texture.size();

	GLfloat uv[] = {
		texture_x / size.x(), (texture_y + texture_h) / size.y(),
		texture_x / size.x(), texture_y / size.y(),
		(texture_x + texture_w) / size.x(), (texture_y + texture_h) / size.y(),
		(texture_x + texture_w) / size.x(), texture_y / size.y(),
	};

	glTexCoordPointer(2, GL_FLOAT, 0, uv);

	glEnable(GL_TEXTURE_2D);
	//画像情報
	glBindTexture(GL_TEXTURE_2D, texture.id_);

	//頂点配列で描画するモードに切り替え
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	color.setToGl();

	//画像を描画
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//描画モードを元に戻す
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//画像情報を解放
	glBindTexture(GL_TEXTURE_2D, 0);
}

////回転ありの画像描画
//void drawTexture(const float pos_x, const float pos_y,
//	const float width, const float height,
//	const float texture_x, const float texture_y,
//	const float texture_w, const float texture_h,
//	Color& color,
//	cTexture& texture,
//	const float angle,
//	const Eigen::Vector2f& scaling,
//	const Eigen::Vector2f& origin
//	)
//{
//	//行列を生成
//	auto matrix = transform
//}

//塗りつぶしありの四角
//pos_x, pos_y		始点
//width, height		幅・高さ
//color				色
void drawFillBox(const float pos_x, const float pos_y,
	const float width, const float height,
	const Color& color)
{
	const float size_x = pos_x + width;
	const float size_y = pos_y + height;

	//四角の情報の配列
	GLfloat boxStatus[] = 
	{
		pos_x, pos_y,
		size_x, pos_y,
		pos_x, size_y,
		size_x, size_y
	};

	glVertexPointer(2, GL_FLOAT, 0, boxStatus);

	//色を設定
	color.setToGl();

	//頂点配列で描画するモードに切り替え
	glEnableClientState(GL_VERTEX_ARRAY);

	//OpenGLに線分の描画を指示
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//描画モードを元に戻す
	glDisableClientState(GL_VERTEX_ARRAY);
}

//フェードイン
bool fadeIn(int window_width, int window_height,
	Color& color,
	float fade_speed)
{

	//ウィンドウサイズと同じ大きさのフェードを描画
	drawFillBox(-window_width / 2, -window_height / 2,
		window_width, window_height,
		color);

	//α値を徐々に下げて透明に
	if (color.alpha() > 0){
		color.alpha() -= fade_speed;
	}
	else{
		return true;
	}
	return false;
}
