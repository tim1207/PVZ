#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "maps.h"
namespace game_framework {
	Maps::Maps() {
		x = 0;
		y = 0;
	}
	//讀取地圖
	void Maps::LoadBitmap() {
		bmp.LoadBitmap("BMP_RES/image/interface/background1unsodded_1.bmp");
	}
	//顯示地圖
	void Maps::OnShow(int x = 0, int y = 0) {
		bmp.SetTopLeft(x, y);
		bmp.ShowBitmap();
	}

	//int Maps::Left() {
		//return x;
	//}
}