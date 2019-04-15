#pragma once

typedef enum {
	eScene_Menu,    //メニュー画面
	eScene_Stage0, //チュートリアル
	eScene_Stage1,    //ゲーム画面
	eScene_Stage2,    //ゲーム画面
	eScene_Stage3,    //ゲーム画面
	eScene_Config,  //設定画面

	eScene_None,    //無し
} eScene;

//シーンを変更するためのインターフェイスクラス
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;//指定シーンに変更する
};