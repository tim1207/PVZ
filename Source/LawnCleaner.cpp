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
	//���]���������m
	void LawnCleaner::Reset() {
		x = 100;
		move = false;
	}
	//�]�w���������m
	void LawnCleaner::SetY(int a) {
		y = a * 98 + 80;
	}
	//���o���������m
	int LawnCleaner::GetX() {
		return x;
	}
	//Ū����������Ϥ�
	void LawnCleaner::LoadBitmap() {
		bmp.LoadBitmap(".\\BMP_RES\\image\\interface\\LawnCleaner.bmp", RGB(0, 0, 0));
	}
	//���ʰ����
	void LawnCleaner::OnMove() {
		if (move == true) {
			x += 10;
		}
	}
	//��ܰ����
	void LawnCleaner::OnShow() {
		bmp.SetTopLeft(x, y);
		bmp.ShowBitmap();
	}
	//��������ʰ_��
	void LawnCleaner::StartMove() {
		move = true;
	}
}