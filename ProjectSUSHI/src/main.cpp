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
	std::vector<cGamePad>gamepads;

	//�R���g���[���[�̏�����
	initGamePad();

	//nTitle::update(app, gamepads);
	nGame::update(app, gamepads);
}