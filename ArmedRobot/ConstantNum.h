#pragma once

#define INPUT_ACCEPT_TIME 24

//�X�N���[���T�C�Y 800 600���K�i���Ƃ͎v���񂾂�
const int SCREEN_SIZE_X=832;
const int SCREEN_SIZE_Y = 640;


const int MAP_WIDTH_MAX = 500;//�}�b�v�̉����ő�

const int MAP_HEIGHT_MAX = 100;//�}�b�v�̏c���ő�

const int IMAGE_CHANGE_FRAME=6;


const int CHECK_X_MAX = 8;//x�����̃`�F�b�N�|�C���g�̐����

const int CHECK_Y_MAX = 8;//y�����̃`�F�b�N�|�C���g�̐����

const int MAPCHIP_SIZE = 64; //1�}�b�v�`�b�v�̃T�C�Y
const int MAPCHIP_KIND = 4; //�}�b�v�`�b�v�̑����@100�ȓ�
const int MAPCHIP_PASSABLE = 0; //�ʍs�\�}�b�v�`�b�v�̔ԍ��̍ő�l
#define MAPCHIP_X_NUM SCREEN_SIZE_X /MAPCHIP_SIZE//�\������}�b�v�`�b�v��x�����̑���
#define MAPCHIP_Y_NUM SCREEN_SIZE_Y /MAPCHIP_SIZE//�\������}�b�v�`�b�v��y�����̑���

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


