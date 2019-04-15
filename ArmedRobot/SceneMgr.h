#pragma once

#include "ISceneChanger.h"
#include "BaseScene.h"

#include "DxLib.h"
#include "Menu.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Config.h"
#include "Stage0.h"

class SceneMgr : public ISceneChanger, Task {

private:
	BaseScene* mScene;    //�V�[���Ǘ��ϐ�
	eScene mNextScene;    //���̃V�[���Ǘ��ϐ�

public:
	SceneMgr();
	void Initialize() override;//������
	void Finalize() override;//�I������
	void Update() override;//�X�V
	void Draw() override;//�`��

	// ���� nextScene �ɃV�[����ύX����
	void ChangeScene(eScene NextScene) override;

};