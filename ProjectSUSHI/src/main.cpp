//
//SUSHI
//

#include"app.h"
#include"gamePad.h"
#include"title.h"
#include"game.h"

int main()
{
	//�A�v���P�[�V��������
	cApp app("SUSHI", WIDTH, HEIGHT);

	//�Q�[���p�b�h
	cGamePad pad(0);

	//�R���g���[���[�̏�����
	initGamePad();

	nTitle::update(app, pad);
	nGame::update(app);
}