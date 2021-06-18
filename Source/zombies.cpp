﻿#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "zombies.h"
#include <cstring>
#include <sstream>
#include <stdio.h>
namespace game_framework {
	Zombies::Zombies() {
	}
	// 殭屍的初始化
	Zombies::Zombies(int a, int b, int c) :status(1) {
		ID = a;
		x = c;
		y =  35 + (b-1) * 98;
		row = b-1;
		LastMove = 0;
		AttackCounter = 0;
		AttackClock = 30;
		SnowCounter = 0;
		HeadFinished = false;
		DieFinished = false;
		BoomFinished = false;
		Boom = false;
		velocity = 1;
		NormalWalking1.SetDelayCount(7);
		NormalAttacking1.SetDelayCount(3);
		NormalWalking2.SetDelayCount(7);
		NormalAttacking2.SetDelayCount(3);
		NormalWalking3.SetDelayCount(7);
		NormalAttacking3.SetDelayCount(3);		
		AnimeDie.SetDelayCount(4);
		Head.SetDelayCount(4);
		BoomDie.SetDelayCount(4);
		GiveLife();
		LoadBitmap();
	}
	//	設定殭屍的種類
	void Zombies::SetID(int a) {
		ID = a;
	}
	//	回傳殭屍的種類
	int Zombies::GetID() {
		return ID;
	}
	//	設定殭屍的生命
	void Zombies::GiveLife() {
		switch (ID) {
		case 1:life = 50; break;
		case 2:life = 60; break;
		case 3:life = 70; break;
		default:	      break;
		}
	}
	//	回傳目前剩下的生命
	int Zombies::GetLife() {
		return life;
	}
	//	回傳是否已經死亡
	bool Zombies::isAlive() {
		if (GetLife() > 0)	return true;
		return false;
	}
	//	讓殭屍瞬間死亡
	void Zombies::GoToDie() {
		life = 0;
		x=1000;
	}
	void Zombies::SetX(int newx) {
		x = newx;
	}
	//	讓殭屍被炸死
	void Zombies::BoomToDie() {
		Boom = true;
		life = 0;
	}
	// 設定殭屍的狀態
	void Zombies::SetStatus(int now) {
		status = now;
	}
	//	回傳目前的狀態
	int Zombies::GetStatus() {
		return status;
	}
	//	根據殭屍的種類決定圖片的數量
	// void Zombies::SetFrames()
	// {
	// 	switch (ID) {
	// 	case 1: WalkingFrames1 = 17;	AttackingFrames1 = 20; break;
	// 	case 2: WalkingFrames2 = 20; 	AttackingFrames2 = 10; break;
	// 	case 3:	WalkingFrames3 = 14;	AttackingFrames3 = 10; break;
	// 	default:	                                      	   break;
	// 	}
	// }
	//	讀取所需的圖檔
	void Zombies::LoadBitmap() {
		// SetStatus(1);
		// SetFrames();		
		// SetStatus(2);
		for (int i = 0; i <= 17; i++) {
			char FILENAME[100];
			sprintf(FILENAME,".\\BMP_RES\\image\\zombies\\Normal Zombie\\Zombie_%d.bmp",i);
			NormalWalking1.AddBitmap(FILENAME, RGB(0, 0, 0));
		}
		for (int i = 0; i <= 20; i++) {
			char FILENAME[100];
			sprintf(FILENAME,".\\BMP_RES\\image\\zombies\\Normal Zombie\\ZombieAttack_%d.bmp",i);
			NormalAttacking1.AddBitmap(FILENAME, RGB(0, 0, 0));
		}

		for (int i = 0; i <= 20; i++) {
			char FILENAME[100];

			sprintf(FILENAME,".\\BMP_RES\\image\\zombies\\ConeHeadZombie\\Zombie_%d.bmp",i);
			NormalWalking2.AddBitmap(FILENAME, RGB(0, 0, 0));
		}
		for (int i = 0; i <= 10; i++) {
			char FILENAME[100];

			sprintf(FILENAME,".\\BMP_RES\\image\\zombies\\ConeHeadZombie\\ZombieAttack_%d.bmp",i);
			NormalAttacking2.AddBitmap(FILENAME, RGB(0, 0, 0));
		}

		for (int i = 0; i <= 14; i++) {
			char FILENAME[100];
			sprintf(FILENAME,".\\BMP_RES\\image\\zombies\\BucketHeadZombie\\Zombie_%d.bmp",i);
			NormalWalking3.AddBitmap(FILENAME, RGB(0, 0, 0));
		}
		for (int i = 0; i <= 10; i++) {
			char FILENAME[100];
			sprintf(FILENAME,".\\BMP_RES\\image\\zombies\\BucketHeadZombie\\ZombieAttack_%d.bmp",i);
			NormalAttacking3.AddBitmap(FILENAME, RGB(0, 0, 0));
		}
		
		// SetStatus(1);
		for (int i = 0; i <= 9; i++) {
			char FILENAME[100];
			sprintf(FILENAME,"%s%d.bmp",".\\BMP_RES\\image\\zombies\\Normal Zombie\\ZombieDie_",i);
			AnimeDie.AddBitmap(FILENAME, RGB(0, 0, 0));
		}
		
		// 可能沒有頭繼續走
		for (int i = 0; i <= 11; i++) {
			char FILENAME[100];
			sprintf(FILENAME, "%s%d.bmp" ,".\\BMP_RES\\image\\zombies\\Normal Zombie\\Head_",i);
			Head.AddBitmap(FILENAME, RGB(0, 0, 0));
		}
		
		for (int i = 0; i <= 19; i++) {
			char FILENAME[100];
			sprintf(FILENAME, "%s%d.bmp", ".\\BMP_RES\\image\\zombies\\BoomDie\\BoomDie_",i);
			BoomDie.AddBitmap(FILENAME, RGB(0, 0, 255));
		}
			
	}
		//	產生圖檔路徑
	// string Zombies::GetPath() {
	// 	stringstream ss;
	// 	switch (ID) {
	// 	case 1: ss << ".\\BMP_RES\\image\\zombies\\Normal Zombie\\"; break;
	// 	case 2: ss << ".\\BMP_RES\\image\\zombies\\ConeHeadZombie\\"; break;
	// 	case 3: ss << ".\\BMP_RES\\image\\zombies\\BucketHeadZombie\\"; break;
	// 	default:ss << "";  break;
	// 	}
	// 	return ss.str();
	// }
	//	回傳殭屍所在的列數
	int Zombies::GetRow()
	{
		return row;
	}
	//	回傳X座標
	int Zombies::GetX() {
		return x;
	}
	//	檢查殭屍是否要攻擊
	bool Zombies::Attack() {
		if (AttackCounter == AttackClock) {
			AttackCounter = 0;
			return true;
		}
		return false;
	}
	//	讓殭屍加速(密技用)
	void Zombies::Faster() {
		velocity+=5;
	}
	// 讓殭屍向前移動
	void Zombies::MoveX() {
		if (SnowCounter == 0) {
			 x-= velocity;
		}
		else if (SnowCounter != 0) {
			//	如果殭屍處於冷凍狀態則移動速度減半
			SnowCounter--;
			if (LastMove == 0) {
				x -= 1;
				LastMove = 1;
			}
			else if (LastMove == 1) {
				LastMove = 0;
			}
		}
	}
	//	處理殭屍的動作
	void Zombies::OnMove() {
		if (SnowCounter == 1) {
			//AttackClock = 30;
		}
		if (isAlive() == false && Boom == false) {
			AnimeDie.OnMove();
			Head.OnMove();
		}
		else if (isAlive() == false && Boom == true) {
			BoomDie.OnMove();
		}
		else if (GetStatus() == 1) {
			NormalWalking1.OnMove();
			NormalWalking2.OnMove();
			NormalWalking3.OnMove();
			
			MoveX();
		}
		else if (GetStatus() == 2) {
			AttackCounter++;
			NormalAttacking1.OnMove();
			NormalAttacking2.OnMove();
			NormalAttacking3.OnMove();
		}
		
	}
	// 處理殭屍的動畫
	void Zombies::OnShow() {
		
		if (isAlive() == false) {
			if (Boom == false) {
				if (DieFinished == false) {
					AnimeDie.SetTopLeft(x, y);
					AnimeDie.OnShow();
					if (AnimeDie.IsFinalBitmap() == true) {
						DieFinished = true;
					}
				}
				
				if (HeadFinished == false) {
					Head.SetTopLeft(x, y);
					Head.OnShow();
					if (Head.IsFinalBitmap() == true) {
						HeadFinished = true;
					}
				}
				
			}
			else if (Boom == true) {
				if (BoomFinished == false) {
					BoomDie.SetTopLeft(x, y);
					BoomDie.OnShow();
					if (BoomDie.IsFinalBitmap() == true) {
						BoomFinished = true;
					}
				}
			}
		}
		else if (GetStatus() == 1) {
			if(life<=50){
				NormalWalking1.SetTopLeft(x, y);
				NormalWalking1.OnShow();
			}
			if(ID==2 && life>50){
				NormalWalking2.SetTopLeft(x, y);
				NormalWalking2.OnShow();
			}
			if(ID==3 && life>50){
				NormalWalking3.SetTopLeft(x, y);
				NormalWalking3.OnShow();
			}
		}
		else if (GetStatus() == 2) {
			if(life<=50){
				NormalAttacking1.SetTopLeft(x, y);
				NormalAttacking1.OnShow();
			}
			if(ID==2 && life>50){
				NormalAttacking2.SetTopLeft(x, y);
				NormalAttacking2.OnShow();
			}
			if(ID==3 && life>50){
				NormalAttacking3.SetTopLeft(x, y);
				NormalAttacking3.OnShow();
			}
		}
	}
	//	產生圖檔路徑
	
	// string Zombies::GetPathWithStatus() {		
	// 	if (status == 2)	return "Attack_";
	// 	return "_";
	// }
	
	//	設定殭屍進入冷凍狀態
	void Zombies::SetSnowCounter() {
		SnowCounter = 150;
	}
	//	殭屍被擊中
	void Zombies::Hitted(int type)
	{
		life--;
		if (type == 1) {
			SetSnowCounter();
			AttackClock = 60;
			NormalAttacking1.SetDelayCount(5);
			NormalWalking1.SetDelayCount(10);
			NormalAttacking2.SetDelayCount(5);
			NormalWalking2.SetDelayCount(10);
			NormalAttacking3.SetDelayCount(5);
			NormalWalking3.SetDelayCount(10);
		}
	}
	//	檢查死亡的動畫是否已經結束
	bool Zombies::isFinished() {
		if (DieFinished == true && HeadFinished == true || BoomFinished == true) {
			return true;
		}
		return false;
	}
}