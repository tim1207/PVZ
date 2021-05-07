#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "LawnMower.h"
namespace game_framework {
	LawnMower::LawnMower() {
		x = 100;
		move = false;
	}
	//���]���������m
	void LawnMower::Reset() {
		x = 100;
		move = false;
	}
	//�]�w���������m
	void LawnMower::SetY(int a) {
		y = a * 98 + 80;
	}
	//���o���������m
	int LawnMower::GetX() {
		return x;
	}
	//Ū����������Ϥ�
	void LawnMower::LoadBitmap() {
		bmp.LoadBitmap(".\\BMP_RES\\image\\interface\\LawnCleaner.bmp", RGB(0, 0, 0));
	}
	//���ʰ����
	void LawnMower::OnMove() {
		if (move == true) {
			x += 10;
		}
	}
	//��ܰ����
	void LawnMower::OnShow() {
		bmp.SetTopLeft(x, y);
		bmp.ShowBitmap();
	}
	//��������ʰ_��
	void LawnMower::StartMove() {
		move = true;
	}
}