#include "SceneMgr.h"

SceneMgr::SceneMgr() :
mNextScene(eScene_None) //���̃V�[���Ǘ��ϐ�
{
	mScene = (BaseScene*) new Menu(this);
}

//������
void SceneMgr::Initialize(){
	mScene->Initialize();
}

//�I������
void SceneMgr::Finalize(){
	mScene->Finalize();
}

//�X�V
void SceneMgr::Update(){
	if (mNextScene != eScene_None){    //���̃V�[�����Z�b�g����Ă�����
		mScene->Finalize();//���݂̃V�[���̏I�����������s
		delete mScene;
		switch (mNextScene){       //�V�[���ɂ���ď����𕪊�
		case eScene_Menu:        //���̉�ʂ����j���[�Ȃ�
			mScene = (BaseScene*) new Menu(this);   //���j���[��ʂ̃C���X�^���X�𐶐�����
			break;//�ȉ���
		case eScene_Stage0:
			mScene = (BaseScene*) new Stage0(this);
			break;
		case eScene_Stage1:
			mScene = (BaseScene*) new Stage1(this);
			break;
		case eScene_Stage2:
			mScene = (BaseScene*) new Stage2(this);
			break;
		case eScene_Stage3:
			mScene = (BaseScene*) new Stage3(this);
			break;
		case eScene_Config:
			mScene = (BaseScene*) new Config(this);
			break;
		}
		mNextScene = eScene_None;    //���̃V�[�������N���A
		mScene->Initialize();    //�V�[����������
	}

	mScene->Update(); //�V�[���̍X�V
}

//�`��
void SceneMgr::Draw(){
	mScene->Draw(); //�V�[���̕`��
}

// ���� nextScene �ɃV�[����ύX����
void SceneMgr::ChangeScene(eScene NextScene){
	mNextScene = NextScene;    //���̃V�[�����Z�b�g����
}
