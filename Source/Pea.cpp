#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Plants.h"
#include "zombies.h"
#include "Pea.h"
bool LoadPeaAlready = false; //檢查是否已經讀取過圖檔
namespace game_framework {
	CMovingBitmap	anime;
	CMovingBitmap	snow;
	CMovingBitmap	hit;
	Pea::Pea() {
	}
	Pea::Pea(int xx,int rows,int id){
		finished = false;
		x = xx;
		y = 125 + 75 * rows;
		row = rows;
		type = id;
		finished = false;
		HitZombie = false;
		if (LoadPeaAlready == false) {
			LoadBitmap();
			LoadPeaAlready = true;
		}
	}
	void Pea::LoadBitmap() {
		anime.LoadBitmap(".\\BMP_RES\\image\\plants\\PeaBullet.bmp",RGB(0,0,0));
		//snow.LoadBitmap(".\\RES\\Plants\\PeaBullet\\SnowPeaBullet.bmp", RGB(0, 0, 0));
		hit.LoadBitmap(".\\BMP_RES\\image\\plants\\PeaBulletHit.bmp",RGB(0,0,0));
	}
	void Pea::OnMove() {
		x+=4;
	}
	void Pea::OnShow() {
		if (HitZombie == true) {
			hit.SetTopLeft(x, y);
			hit.ShowBitmap();
			finished = true;
		}
		else {
			if (type == 0) {
				anime.SetTopLeft(x, y);
				anime.ShowBitmap();
			}
			else if (type == 1) {
				snow.SetTopLeft(x, y);
				snow.ShowBitmap();
			}
		}
	}
	int Pea::GetRow() {
		return row;
	}
	int Pea::GetX() {
		return x;
	}
	void Pea::SetHitZombie(bool a) {
		HitZombie = a;
	}
	bool Pea::isHitZombie() {
		return HitZombie;
	}
	bool Pea::isFinished() {
		return finished;
	}
	int Pea::MyType() {
		return type;
	}
}