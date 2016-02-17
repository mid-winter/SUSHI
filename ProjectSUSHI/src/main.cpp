//
//SUSHI
//

#include"app.h"
#include"gamePad.h"
#include"title.h"
#include"settings.h"
#include"game.h"
#include"result.h"

int main()
{
	//�A�v���P�[�V��������
	cApp app("SUSHI", WIDTH, HEIGHT);

	//�Q�[���p�b�h
	std::vector<cGamePad>gamepads;

	//�R���g���[���[�̏�����
	initGamePad();

	while (true)
	{
		nTitle::update(app, gamepads);
		//nSetting::update(app, gamepads);
		nGame::update(app, gamepads);
		nResult::update(app, gamepads);
	}
}
