#pragma once
#include "DxLib.h"

const char SAVE_DATA_FILE_NAME[14] = { 's', 'a', 'v', 'e', '/', 's', 'a', 'v', 'e', '.', 'd', 'a', 't', '\0' };
static const int FILE_NAME_LENGTH = 32;
static const int MAP_LIST_LENGTH = 32;

static const int STAGE_MAX = 4;

struct SaveData{
	int volume;
	bool clear[STAGE_MAX];
};

void Save();
SaveData Load();

extern SaveData saveData;