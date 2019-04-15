#include "Menu.h"

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
}
const static int STAGE0_Y = 270;
const static int STAGE1_Y = 300;    //�u�X�e�[�W1�v������y�ʒu
const static int STAGE2_Y = 330;    
const static int STAGE3_Y = 360;    
const static int CONFIG_Y = 390;    
const static int SPACE = 30;

typedef enum{
	eMenu_Stage0,
	eMenu_Stage1,        //�Q�[��
	eMenu_Stage2,        //�Q�[��
	eMenu_Stage3,        //�Q�[��
	eMenu_Config,    //�ݒ�

	eMenu_Num,        //�{���ڂ̐�
} eMenu;

static int NowSelect = eMenu_Stage0;    

//������
void Menu::Initialize(){
	mImageHandle = LoadGraph("images/TitleBack.bmp");    //�摜�̃��[�h
}

//�X�V
void Menu::Update(){
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1){//���L�[��������Ă�����
		NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
	}
	if (Keyboard_Get(KEY_INPUT_UP) == 1){//��L�[��������Ă�����
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
	}
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1){//�G���^�[�L�[�������ꂽ��
		switch (NowSelect){//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
		case eMenu_Stage0://�X�e�[�W1�I�𒆂Ȃ�
			mSceneChanger->ChangeScene(eScene_Stage0);
			break;
		case eMenu_Stage1://�X�e�[�W1�I�𒆂Ȃ�
			mSceneChanger->ChangeScene(eScene_Stage1);
			break;
		case eMenu_Stage2://�X�e�[�W1�I�𒆂Ȃ�
			mSceneChanger->ChangeScene(eScene_Stage2);
			break;
		case eMenu_Stage3://�X�e�[�W1�I�𒆂Ȃ�
			mSceneChanger->ChangeScene(eScene_Stage3);
			break;
		case eMenu_Config://�ݒ�I�𒆂Ȃ�
			mSceneChanger->ChangeScene(eScene_Config);//�V�[����ݒ��ʂɕύX
			break;
		}
	}

}

//�`��
void Menu::Draw(){
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�

	DrawString(280, STAGE0_Y, "�`���[�g���A��", GetColor(255, 255, 255));
	for (int i = 1; i <= eMenu_Stage3; i++) {
		DrawFormatString(280, STAGE0_Y+SPACE*i , GetColor(255, 255, 255), "�X�e�[�W%d", i);
	}
	DrawString(280, CONFIG_Y, "�ݒ�", GetColor(255, 255, 255));
	for (int i = 0; i <= eMenu_Stage3; i++) {
		if(saveData.clear[i])DrawFormatString(480, STAGE0_Y + SPACE * i, GetColor(255, 255, 255), "CLEAR");
	}
	int y = 0;
	y = STAGE0_Y + NowSelect * SPACE;
	DrawString(250, y, "��", GetColor(255, 255, 255));
	DrawString(64, 480, "��{�I��Xbox�R���g���[���[�ł̑����z�肵�Ă��܂��B�L�[�{�[�h�ł��v���C�͉\�ł��B", GetColor(255, 255, 255));
	DrawString(96, 510, "Xbox�R���g���[���[�̃A�i���O�p�b�h(�������̓L�[�{�[�h�̏\���L�[)�őI�����A", GetColor(255, 255, 255));
	DrawString(256, 540, "start�{�^��(Enter�L�[)�ŊJ�n���Ă��������B", GetColor(255, 255, 255));
}
