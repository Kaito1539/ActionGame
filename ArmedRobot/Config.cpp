#include "Config.h"


Config::Config(ISceneChanger* changer) : BaseScene(changer) {
}


typedef enum{
	eConfig_Control,
	eConfig_BGM,
	eConfig_Num,        //�{���ڂ̐�
} eConfig;

typedef enum{
	eConfigY_Control=300,
	eConfigY_BGM=330,
} eConfigY;

typedef enum{
	eControl_Keyboard,
	eControl_Joypad,
	eControl_Num,        //�{���ڂ̐�
} eControl;

static int NowSelect = eConfig_Control;

//������
void Config::Initialize(){
	mImageHandle = LoadGraph("images/Scene_Config.png");    //�摜�̃��[�h
}

//�X�V
void Config::Update(){
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0||Keyboard_Get(KEY_INPUT_ESCAPE) == 1){ //Esc�L�[��������Ă�����
		Save();
		mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1){//���L�[��������Ă�����
		NowSelect = (NowSelect + 1) % eConfig_Num;//�I����Ԃ��������
	}
	if (Keyboard_Get(KEY_INPUT_UP) == 1){//��L�[��������Ă�����
		NowSelect = (NowSelect + (eConfig_Num - 1)) % eConfig_Num;//�I����Ԃ���グ��
	}
	
	switch (NowSelect){//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
	case eConfig_Control:
		if (Keyboard_Get(KEY_INPUT_RETURN) == 1 || Keyboard_Get(KEY_INPUT_Z) == 1){//�G���^�[�L�[�������ꂽ��
			ChangeInputSystem();
		}
		break;
	case eConfig_BGM:
		if (Keyboard_Get(KEY_INPUT_LEFT) != 0){
			saveData.volume -= 5;
			if (saveData.volume < 0)saveData.volume = 0;
		}
		if (Keyboard_Get(KEY_INPUT_RIGHT) != 0){
			saveData.volume += 5;
			if (saveData.volume > 100)saveData.volume = 100;
		}
		break;
	}
}

//�`��
void Config::Draw(){
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	DrawString(0, 0, "�ݒ��ʂł��BBack�{�^��(Esc�L�[)�Ŗ߂�܂��B", GetColor(255, 255, 255));
	if (GetInputSystem()){
		DrawString(280, eConfigY_Control,  "���͑��u�ؑ�: �W���C�p�b�h",GetColor(255, 255, 255));
	}
	else{
		DrawString(280, eConfigY_Control, "���͑��u�ؑ�: �L�[�{�[�h", GetColor(255, 255, 255));
	}
	
	DrawFormatString(280, eConfigY_BGM, GetColor(255, 255, 255), "BGM����: %d %",saveData.volume );
	int y = 0;
	switch (NowSelect){//���݂̑I����Ԃɏ]���ď����𕪊�
	case eConfig_Control:
		y = eConfigY_Control;
		break;
	case eConfig_BGM:
		y = eConfigY_BGM;
		break;
	}
	DrawString(250, y, "��", GetColor(255, 255, 255));
}