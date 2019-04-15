#pragma once

#define INPUT_ACCEPT_TIME 24

//スクリーンサイズ 800 600が規格だとは思うんだが
const int SCREEN_SIZE_X=832;
const int SCREEN_SIZE_Y = 640;


const int MAP_WIDTH_MAX = 500;//マップの横数最大

const int MAP_HEIGHT_MAX = 100;//マップの縦数最大

const int IMAGE_CHANGE_FRAME=6;


const int CHECK_X_MAX = 8;//x方向のチェックポイントの数上限

const int CHECK_Y_MAX = 8;//y方向のチェックポイントの数上限

const int MAPCHIP_SIZE = 64; //1マップチップのサイズ
const int MAPCHIP_KIND = 4; //マップチップの総数　100以内
const int MAPCHIP_PASSABLE = 0; //通行可能マップチップの番号の最大値
#define MAPCHIP_X_NUM SCREEN_SIZE_X /MAPCHIP_SIZE//表示するマップチップのx方向の総数
#define MAPCHIP_Y_NUM SCREEN_SIZE_Y /MAPCHIP_SIZE//表示するマップチップのy方向の総数

const int KEYBOARD_INPUT =0;
const int JOYPAD_INPUT = 1;

typedef enum{
	eState_Stand,
	eState_Run,
	eState_Dash,
	eState_Crouch,
	eState_Jump_Stanby,
	eState_Jump,
	eState_Flight,
	eState_WallKick,
	eState_Bend,
	eState_Stun,

	eState_Avoidance,

	eState_Slash_Stanby,
	eState_Front_Slash1,
	eState_Front_Slash2,
	eState_Front_Slash3,
	eState_Upper_Slash,
	eState_Sweep_Slash,

	eState_Rush_Slash,

	eState_Air_Front_Slash,
	eState_Air_Down_Slash,

	eState_Shoot_Stanby,
	eState_Shoot,
} eState;


