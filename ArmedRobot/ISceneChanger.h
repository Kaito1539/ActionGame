#pragma once

typedef enum {
	eScene_Menu,    //���j���[���
	eScene_Stage0, //�`���[�g���A��
	eScene_Stage1,    //�Q�[�����
	eScene_Stage2,    //�Q�[�����
	eScene_Stage3,    //�Q�[�����
	eScene_Config,  //�ݒ���

	eScene_None,    //����
} eScene;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;//�w��V�[���ɕύX����
};