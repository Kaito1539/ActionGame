#include "Stage3.h"

Stage3::Stage3(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void Stage3::Initialize(){
	LoadDivGraph("images/back.bmp", MAPCHIP_KIND, MAPCHIP_KIND / 2, MAPCHIP_KIND / 2, MAPCHIP_SIZE, MAPCHIP_SIZE, mapChipGraph);
	MakeMap();
	player.Initialize(mapData, mapH, mapW, 128, 256, &atkID);
	player.SlashInitialize(&playerSlash);
	playerSlash.Initialize(&atkID);
	for (int i = 0; i < PLAYER_BULLET_MAX; i++){
		player.BeamShootInitialize(&(playerBeamShoot[i]),i);
		playerBeamShoot[i].Initialize(&atkID);
	}
	

	boss.Initialize(mapData, mapH, mapW, 640, 256, &atkID, &player);
	boss.SolidShootInitialize(&(enemySolidShoot));
	enemySolidShoot.Initialize(mapData, mapH, mapW, &atkID);
	boss.SlashInitialize(&enemySlash);
	enemySlash.Initialize(&atkID);

	enemyRect[0] = &boss;
	enemyRect[1] = &enemySolidShoot;
	enemyRect[2] = &enemySlash;

	atkID = 0;
	bgm = LoadSoundMem("musics/stage3BGM.wav");
	ChangeVolumeSoundMem(saveData.volume*256/100-1, bgm);
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);

	mImageHandle = LoadGraph("images/YouWin.bmp");
}

//更新
void Stage3::Update(){
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0 || Keyboard_Get(KEY_INPUT_ESCAPE) == 1){ //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
		StopSoundMem(bgm);
	}
	if (player.GetAlive() != true){ 
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
		StopSoundMem(bgm);
	}
	if (boss.GetAlive() != true){ 
		if (Keyboard_Get(KEY_INPUT_RETURN) == 1){
			saveData.clear[3] = true;
			Save();
			mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
			
		}
		StopSoundMem(bgm);
	}

	player.Update();
	for (int i = 0; i < PLAYER_BULLET_MAX; i++){
		if (playerBeamShoot[i].GetAlive()){
			playerBeamShoot[i].Update();
		}
	}
	

	if (boss.GetAlive()){
		boss.Update();
	}
	if (enemySolidShoot.GetAlive()){
		enemySolidShoot.Update();
	}

	if (playerSlash.GetAlive()){
		for (int i = 0; i < 2; i++){
			if (enemyRect[i]->GetAlive()){
				if (CheckCollisionRectToRect(&playerSlash, enemyRect[i])){
					enemyRect[i]->SetDamage(playerSlash.GetAtk(), playerSlash.GetStun(), playerSlash.GetBlowX(), playerSlash.GetBlowY(), playerSlash.GetID());
				}
			}
		}
	}
	for (int j = 0; j < PLAYER_BULLET_MAX; j++){
		if (playerBeamShoot[j].GetAlive()){
			for (int i = 0; i < 2; i++){
				if (enemyRect[i]->GetAlive()){
					if (CheckCollisionRectToRect(&(playerBeamShoot[j]), enemyRect[i])){
						enemyRect[i]->SetDamage(playerBeamShoot[j].GetAtk(), playerBeamShoot[j].GetStun(), playerBeamShoot[j].GetBlowX(), playerBeamShoot[j].GetBlowY(), playerBeamShoot[j].GetID());
					}
				}
			}
		}
	}
	
	for (int i = 0; i < 3; i++){
		if (enemyRect[i]->GetAlive()){
			if (CheckCollisionRectToRect(&player, enemyRect[i])){
				player.SetDamage(enemyRect[i]->GetAtk(), enemyRect[i]->GetStun(), enemyRect[i]->GetBlowX(), enemyRect[i]->GetBlowY(), enemyRect[i]->GetID());
				enemyRect[i]->SetDamage(player.GetAtk(), player.GetStun(), player.GetBlowX(), player.GetBlowY(), player.GetID());
			}
		}
	}
}

//描画
void Stage3::Draw(){
	
	startScreenX = player.GetX() - SHOW_PLAYER_X;
	startScreenY = player.GetY() - SHOW_PLAYER_Y;
	if (startScreenX < 0){
		startScreenX = 0;
	}
	else if (startScreenX>MAPCHIP_SIZE*mapW - SCREEN_SIZE_X){
		startScreenX = MAPCHIP_SIZE*mapW - SCREEN_SIZE_X;
	}
	if (startScreenY < 0){
		startScreenY = 0;
	}
	else if (startScreenY>MAPCHIP_SIZE*mapH - SCREEN_SIZE_Y){
		startScreenY = MAPCHIP_SIZE*mapH - SCREEN_SIZE_Y;
	}
	for (int i = 0; i < mapH; i++){
		for (int j = 0; j < mapW; j++){
			DrawGraph(MAPCHIP_SIZE*j - startScreenX, MAPCHIP_SIZE*i - startScreenY, mapChipGraph[mapData[i][j]], FALSE);
		}
	}
	//敵機,自機,敵攻撃,自機攻撃の順
	if (boss.GetAlive()){
		boss.Draw(startScreenX, startScreenY);
	}

	player.Draw(startScreenX, startScreenY);

	if (enemySolidShoot.GetAlive()){
		enemySolidShoot.Draw(startScreenX, startScreenY);
	}
	if (enemySlash.GetAlive()){
		enemySlash.Draw(startScreenX, startScreenY);
	}

	playerSlash.Draw(startScreenX, startScreenY);
	for (int i = 0; i < PLAYER_BULLET_MAX; i++){
		if (playerBeamShoot[i].GetAlive()){
			playerBeamShoot[i].Draw(startScreenX, startScreenY);
		}
	}
	if (boss.GetAlive() != true){
		BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	}
	
}

void Stage3::MakeMap(){
	FILE *fp;
	char *fname = "maps/map3.csv";
	fopen_s(&fp, fname, "r");
	if (fp == NULL){
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%sファイルが開けません。n", fname);
		exit(-1);
	}
	mapH = mapW = a = 0;
	while ((fscanf_s(fp, "%[^\n]%*c", map, MAP_WIDTH_MAX)) != EOF){
		for (mapW = 0; mapW < MAP_WIDTH_MAX; mapW++){
			if (map[a] == ','){
				a++;
			}
			if (map[a] == '\0'){
				break;
			}
			mapData[mapH][mapW] = atoi(&map[a]);
			if (mapData[mapH][mapW]>9){//マップチップの種類が100種以内である必要がある。
				a++;
			}
			a++;
		}
		mapH++;
		a = 0;
	}
	fclose(fp);
}

//矩形同士の接触判定
bool Stage3::CheckCollisionRectToRect(Rect * setRectA, Rect * setRectB){
	flg = false;
	if (setRectA->GetX() <= setRectB->GetX() + setRectB->GetWidth() && setRectB->GetX() <= setRectA->GetX() + setRectA->GetWidth()){
		if (setRectA->GetY() <= setRectB->GetY() + setRectB->GetHeight() && setRectB->GetY() <= setRectA->GetY() + setRectA->GetHeight()){
			flg = true;
		}
	}
	return flg;
}
