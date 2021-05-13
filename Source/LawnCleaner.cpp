#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "LawnCleaner.h"
namespace game_framework {
	LawnCleaner::LawnCleaner() {
		x = 100;
		move = false;
	}
	//重設除草機的位置
	void LawnCleaner::Reset() {
		x = 100;
		move = false;
	}
	//設定除草機的位置
	void LawnCleaner::SetY(int a) {
		y = a * 98 + 80;
	}
	//取得除草機的位置
	int LawnCleaner::GetX() {
		return x;
	}
	//讀取除草機的圖片
	void LawnCleaner::LoadBitmap() {
		bmp_LawnCleaner.LoadBitmap(".\\BMP_RES\\image\\interface\\LawnCleaner.bmp", RGB(0, 0, 0));
	}
	//移動除草機
	void LawnCleaner::OnMove() {
		if (move == true) {
			x += 10;
		}
	}
	//顯示除草機
	void LawnCleaner::OnShow() {
		bmp_LawnCleaner.SetTopLeft(x, y);
		bmp_LawnCleaner.ShowBitmap();
	}
	//讓除草機動起來
	void LawnCleaner::StartMove() {
		move = true;
	}
}