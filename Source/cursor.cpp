#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "cursor.h"
namespace game_framework {
	Cursor::Cursor() {
		which = 0;
	}
	 //讀取所需圖片
	void Cursor::LoadBitmap() {
		Sunflower.LoadBitmap(".\\BMP_RES\\image\\plants\\SunFlower.bmp",RGB(0,0,0));
		peashooter.LoadBitmap(".\\BMP_RES\\image\\plants\\Peashooter.bmp", RGB(0, 0, 0));
		Wallnut.LoadBitmap(".\\BMP_RES\\image\\plants\\WallNut_1.bmp", RGB(0, 0, 0));
		//squash.LoadBitmap(".\\RES\\Plants\\Squash\\Squash_00.bmp", RGB(0, 0, 0));
		//cherrybomb.LoadBitmap(".\\RES\\Plants\\CherryBomb\\CherryBomb_00.bmp", RGB(0, 0, 0));
		//snowpea.LoadBitmap(".\\RES\\Plants\\SnowPea\\SnowPea_00.bmp", RGB(0, 0, 0));
		//repeater.LoadBitmap(".\\RES\\Plants\\Repeater\\Repeater_00.bmp", RGB(0, 0, 0));
		shovel.LoadBitmap(".\\BMP_RES\\image\\interface\\Shovel.bmp", RGB(0, 0, 255));
	}
	void Cursor::OnMove() {
	}
	 //設定游標目前要顯示的圖片
	void Cursor::SetWhich(int a) {
		which = a;
	}
	 //讓圖片跟著游標移動
	void Cursor::SetXY(int xx, int yy) {
		x = xx;
		y = yy;
		if (which == 4 || which == 5) {
			x -= 10;
		}
		if (which == 4) {
			y -= 150;
		}
	}
	 //顯示圖片
	void Cursor::OnShow() {
		if (which != 0) {
			CMovingBitmap*	pointer;
			switch (which) {
			case 1:	pointer = &Sunflower;	break;
			case 2: pointer = &peashooter;	break;
			case 3: pointer = &Wallnut;		break;
			//case 4: pointer = &squash;		break;
			//case 5: pointer = &cherrybomb;	break;
			//case 6: pointer = &snowpea;		break;
			//case 7: pointer = &repeater;	break;
			case 8: pointer = &shovel;		break;
			}
			if (which != 8) {
				pointer->SetTopLeft(x-30, y-30);
				pointer->ShowBitmap();
			}
			else {
				pointer->SetTopLeft(x - 30, y - 15);
				pointer->ShowBitmap();
			}
		}
	}
}