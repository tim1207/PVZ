#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Sun.h"
#include <ctime>
#include <cstdlib>
bool LoadSunAlready = false;	              // 太陽圖檔是否已經讀取
namespace game_framework {
	CAnimation	anime;
	Sun::Sun() {
	}
	Sun::Sun(int a, int b, bool c) {             // a是X座標, b是Y座標 ,c代表怎麼被產生的
		x = a;
		y = (c ? b : -100);
		desy = b;
		picked = false;
		MoveCounter = 0;
		finished = false;
		CallFromSunFlower = c;
		if (c) {					                      //	如果是從向日葵產生的則以拋物線的方式出現
			srand((unsigned)time(NULL));
			vy = -8;
			vx = (rand() % 5) - 2;
		}
		if (LoadSunAlready == false) {	        //	如果已經讀取過圖檔則不用讀取
			LoadBitmap();
			LoadSunAlready = true;
		}
	}
	void Sun::LoadBitmap() {			            // 讀取圖檔
		for (int i = 0; i <= 21; i++) {
			char FILENAME[100];
			sprintf(FILENAME, "BMP_RES/image/interface/Sun.bmp");
			anime.AddBitmap(FILENAME, RGB(255, 255, 255));
		}
		anime.SetDelayCount(2);
	}
	int Sun::GetX() {					                // 回傳X座標
		return x;
	}
	int Sun::GetY() {					                // 回傳Y座標
		return y;
	}
	int Sun::GetHeight() {				            // 回傳圖的高度
		return anime.Height();
	}
	int Sun::GetWidth() {				              // 回傳圖的寬度
		return anime.Width();
	}

	void Sun::PickUp() {				              // 設定太陽被撿起後的移動
		picked = true;
		stepX = (x - 25) / 20;
		stepY = (y - 25) / 20;

	}
	bool Sun::isFinished() {			            // 檢查移動是否結束
		return finished;
	}
	void Sun::drop() {					              // 讓太陽從空中落下
		if (y <= desy) {
			y += 2;
		}
	}
	void Sun::fly() {					                // 讓太陽以拋物線飛出來
		if (y <= desy) {
			y += vy;
			vy++;
			x += vx;
		}
	}
	void Sun::MoveAnime() {				            // 處理太陽的動畫
		anime.OnMove();
	}
	void Sun::OnMove() {				              // 處理太陽的移動
		if (picked == false && CallFromSunFlower == false) {
			drop();
		}
		else if (picked == false && CallFromSunFlower == true) {
			fly();
		}
		else if (picked == true) {
			x -= stepX;
			y -= stepY;
			MoveCounter++;
		}
		if (MoveCounter == 20) {
			finished = true;
		}
	}
	void Sun::OnShow() {				              //	讓太陽顯示在畫面中
		anime.SetTopLeft(x, y);
		anime.OnShow();
	}
}