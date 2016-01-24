//
//SUSHI
//

#include"app.h"
#include"graphic.h"
#include"gamePad.h"

enum WindowSize
{
	WIDTH = 960,
	HEIGHT = 540
};

int main()
{
	//�A�v���P�[�V��������
	cApp app("SUSHI", WIDTH, HEIGHT);

	//�摜
	cTexture title("res/Title.raw",
		1024, 512, true);

	while (1)
	{
		if (!app.isOpen()) exit(0);
		app.begin();

		// ���u�����f�B���O��L���ɂ���
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//�^�C�g���w�i�摜
		drawTexture(-WIDTH / 2, -HEIGHT / 2,
			WIDTH, HEIGHT,
			0, 0, 765, 512,
			title);

		// ���u�����f�B���O�𖳌��ɂ���
		glDisable(GL_BLEND);
		app.end();
	}
}