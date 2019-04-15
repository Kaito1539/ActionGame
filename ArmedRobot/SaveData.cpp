#include "SaveData.h"

SaveData saveData;

void Save(){
	FILE* fp;
	fopen_s(&fp, SAVE_DATA_FILE_NAME, "wb");
	if (fp == NULL){
		DrawString(300, 300, "save failed", GetColor(255, 255, 255));
		return;
	}
	fwrite(&saveData, sizeof(saveData), 1, fp);
	fclose(fp);//ファイルを閉じる
}

SaveData Load(){
	FILE* fp;
	SaveData tmp;
	fopen_s(&fp, SAVE_DATA_FILE_NAME, "rb");
	if (fp == NULL){

	}
	else{
		fread(&tmp, sizeof(tmp), 1, fp);
		fclose(fp);//ファイルを閉じる
	}

	return tmp;
}