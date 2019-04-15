#include "DxLib.h"
#include "SceneMgr.h"
#include "Keyboard.h"
#include "ConstantNum.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	int Time;

	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	SceneMgr sceneMgr;
	sceneMgr.Initialize();

	if (GetJoypadNum() == 0){
		SetInputSystem(KEYBOARD_INPUT);
	}
	else{
		SetInputSystem(JOYPAD_INPUT);
	}
	saveData=Load();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){//��ʍX�V & ���b�Z�[�W���� & ��ʏ���
		Time = GetNowCount();

		if (GetInputSystem() == KEYBOARD_INPUT){
			Keyboard_Update();    //�L�[�{�[�h�̍X�V
		}
		else{
			Joypad_Update();
		}
		
		sceneMgr.Update();  //�X�V
		sceneMgr.Draw();    //�`��
		
		//���t���b�V�����[�g�𖳎����Ĉ�t���[����17ms(1s=60frame)�ɍ��킹��B�摜���Ԃ��B
		//���ƁA����ɑ΂��锽���������Ȃ�B����Ȃ��Ƃ��Ȃ�����
		while (GetNowCount() - Time < 17){}
	}

	sceneMgr.Finalize();

	DxLib_End(); // DX���C�u�����I������
	return 0;
}