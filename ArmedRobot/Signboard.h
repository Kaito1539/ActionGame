#pragma once

#include "ConstantNum.h"

#include "DxLib.h"
#include "Rect.h"
#include "Player.h"


const int CONTENTSAREA_HEIGHT = 128;
const int SIGNBOARD_LENGTH_MAX = 1024;
const int CONTENTS_ROW_NUM = 4;

class Signboard : public Rect {
private:
	typedef enum {
		eWidth_Normal = 64,
	} eWidth;

	typedef enum {
		eHeight_Normal = 64,
	} eHeight;

	//char contents[SIGNBOARD_LENGTH_MAX];
	char *contents[CONTENTS_ROW_NUM];
	bool showContents;
	int contentsImage;
public:
	void Initialize(int setMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX], int setMapH, int setMapW, int setX, int setY, int* setID);
	void SetContents(char **set);
	//void Finalize();     
	void Update();
	void Draw(int setStartScreenX, int setStartScreenY);
	void Show();
	bool GetShowContents();
	void DrawContents(int setStartScreenX, int setStartScreenY);
};

static char *SIGN_CONTENTS[12][CONTENTS_ROW_NUM] = { 
	{ "アナログパッド(十字キー)を左右に入力すると左右に移動する。","","",""}
, { "Aボタン(Cキー)でジャンプする。長く押すことでより高く飛ぶことができる。","","",""}
,{ "アナログパッド(十字キー)を下に入力するとしゃがむ。","しゃがんだ状態ならば狭い通路も通ることができる。","",""}

,{ "アナログパッド(十字キー)を左右どちらかに素早く二度入力するとダッシュできる。","狭い通路でも素早く抜けることが可能だ。","しゃがんだ状態からダッシュすることはできない。","ダッシュ中にジャンプすることでジャンプ距離を大きく延ばすことができる。"}
,{ "空中で壁に接触した状態でジャンプボタンを押すと壁を蹴ってより高く跳べる。","二枚の壁があれば壁蹴りを繰り返すことでいくらでも上ることができる。","",""}
,{ "Bボタン(Xキー)で銃での攻撃を行える。弾丸は自然回復するが、撃ち尽くすとしばらく撃てない。","弾は壁を貫通する。アナログパッドもしくは十字キーを上に入力すると銃を上に撃てる。","",""}
,{ "Xボタン(Zキー)で剣での攻撃を行える。アナログパッドもしくは十字キーを同時に入力すると攻撃方法が変化する。","攻撃後再度Zキーで剣での追加攻撃を行える。","追加攻撃もアナログパッドもしくは十字キーを同時に入力すると攻撃方法が変化する。","連続で攻撃すると相手の防御を崩し、大ダメージを与えられるようになる。"}
,{ "Yボタン(Vキー)で回避行動をとれる。","ダメージを受けた時など自由に動けないときにも移動できる。","ジャンプから使えば到達距離を延ばすこともできる。",""}
,{ "","","",""}
,{ "","","",""}
,{ "","","",""}

};

/*
1:アナログパッドもしくは十字キーを左右に入力すると左右に移動する。gt/n¥nko
2:Cキーでジャンプする。長く押すことでより高く飛ぶことができる。
3:アナログパッドもしくは十字キーを下に入力するとしゃがむ。しゃがんだ状態ならば狭い通路も通ることができる。
4:アナログパッドもしくは十字キーを左右どちらかに素早く二度入力するとダッシュできる。狭い通路でも素早く抜けることが可能だ。
しゃがんだ状態からダッシュすることはできないので注意すること。
5:壁に接触した状態でジャンプボタンを押すと壁を蹴ってより高く跳べる。二枚の壁があれば壁蹴りを繰り返すことでいくらでも上ることができる。
6:
7:Vキーで回避行動をとれる。攻撃中でもとっさに動くことができるほか、ジャンプから使えば到達距離を延ばすこともできる。
8:Zキーで剣での攻撃を行える。アナログパッドもしくは十字キーを同時に入力すると攻撃方法が変化する。
9:攻撃後再度Zキーで剣での追加攻撃を行える。追加攻撃もアナログパッドもしくは十字キーを同時に入力すると攻撃方法が変化する。
10:Xキーで銃での攻撃を行える。弾丸は自然回復するが、撃ち尽くすとしばらく撃てないので注意。アナログパッドもしくは十字キーを上に入力すると銃を上に撃てる。

*/