#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Plants.h"
//#include "zombies.h"
#include <sstream>
namespace game_framework {
	Plants::Plants() {
	}
	Plants::Plants(int id, int col, int roww) {
		ID = id;
		x = 172 + col* 80;
		y = 80 + roww * 98;
		/*
		if (ID == 4) {
			x -= 15;
			y -= 150;
		}
		else if (ID == 5) {
			x -= 20;
		}
		*/
		row = roww;
		column = col;
		SetLife();
		LoadBitmap();
		anime.SetDelayCount(3);
		anime2.SetDelayCount(3);
		anime3.SetDelayCount(3);
		Action = false;
		CounterOn = false;
		TargetX = 1000;
		MovingCounter = 0;
		status = 1;
		switch (ID) {							                // 根據植物的種類決定植物的冷卻時間
		case 1:	ActionCounter = 30 * 10;  break;
		case 2: ActionCounter = 30 * 1;   break;
		//case 6: ActionCounter = 30 * 1;   break;
		//case 7: ActionCounter = 30 * 1;   break;
		default:ActionCounter = -1;		    break;
		}
		Counter = ActionCounter - 1;
		if (ID == 1 || ID == 4) {
			Counter = 0;
		}
		anime2Counter = 0;
	}
	void Plants::SetID(int a) {
		ID = a;
	}
	int Plants::GetID() {						        // 回傳植物的種類
		return ID;
	}
	void Plants::ResetCounter() {				    // 重設植物的冷卻時間
		Counter = 0;
	}
	void Plants::SetLife() {					      // 根據植物的種類設定植物的生命
		switch (ID) {
		case 1:life = 5;  break;
		case 2:life = 5;  break;
		case 3:life = 30; break;
		case 4:life = 5;  break;
		case 5:life = 5;  break;
		case 6:life = 5;  break;
		case 7:life = 5;  break;
		}
	}
	int Plants::GetLife() {						      // 回傳植物目前剩下多少生命
		return life;
	}
	bool Plants::isAlive() {					      // 回傳植物目前是否已經死亡
		if (GetLife() > 0)	return true;
		return false;
	}
	void Plants::BeingAttacked() {			    // 植物被殭屍攻擊
		life--;
	}
	void Plants::SetFrames()					      // 根據植物的種類決定圖檔的數量
	{
		switch (ID) {
		case 1:	frames = 17;	break;
		case 2: frames = 12;	break;
		case 3: frames = 15;	break;
		case 31:frames = 10;	break;
		case 32:frames = 14;	break;
		case 4: frames = 16;	break;
		case 41:frames = 3;		break;
		case 5: frames = 6;		break;
		case 6: frames = 14;	break;
		case 7: frames = 14;	break;
		case 0: frames = 18;		break;
		default:	break;
		}
	}
	int Plants::GetRow()						        // 回傳植物所在的排數
	{
		return row;
	} 
	int Plants::GetColumn() {					      // 回傳植物所在的行數
		return column;
	}
	int Plants::GetX()							        // 回傳植物的X座標
	{
		return x;
	}
	int Plants::GetY() {						        // 回傳植物的Y座標
		return y;
	}
	int Plants::GetWidth()						      // 回傳植物圖片的寬度
	{
		return anime.Width();
	}
	void Plants::SetX(int a) {				    	// 設定X座標
		x = a;
	}
	void Plants::SetY(int a) {				    	// 設定Y座標
		y = a;
	}
	void Plants::LoadBitmap() {					    // 讀取所需圖檔
		SetFrames();							            // 檢查圖檔共有幾張
		for (int i = 0; i <= frames; i++) {		// 依序讀取圖檔
			char FILENAME[100];
			sprintf(FILENAME, "%s.bmp", GetPath().c_str());
			
			anime.AddBitmap(FILENAME, RGB(0, 0, 0));
		}
		/*
		if (ID == 3) {
			SetID(31);
			SetFrames();
			for (int i = 0; i <= frames; i++) {
				char FILENAME[100];
				sprintf(FILENAME, "%s.bmp", GetPath().c_str());
				anime2.AddBitmap(FILENAME, RGB(0, 0, 0));
			}
			SetID(32);
			SetFrames();
			for (int i = 0; i <= frames; i++) {
				char FILENAME[100];
				sprintf(FILENAME, "%s.bmp", GetPath().c_str());
				anime3.AddBitmap(FILENAME, RGB(0, 0, 0));
			}
			SetID(3);
		}
		*/
		/*
		else if (ID == 4) {
			SetID(41);
			SetFrames();
			for (int i = 0; i <= frames; i++) {
				char FILENAME[100];
				sprintf(FILENAME, "%s.bmp", GetPath().c_str());
				anime2.AddBitmap(FILENAME, RGB(0, 0, 0));
			}
			SetID(4);
		}
		else if (ID == 5) {
			Boom.LoadBitmap("./RES/Plants/CherryBomb/ExplosionCloud.bmp", (0, 0, 0));
		}
		*/
	}
	void Plants::SetCounterOn(bool a) {			// 讓植物開始動作
		CounterOn = a;
		if (a == false) {
			Counter = 1;
		}
	}
	bool Plants::isCounterOn() {				    // 回傳目前是否開始動作
		return CounterOn;
	}
	int Plants::CounterLeft() {					    // 回傳還要多久才會開始動作
		return ActionCounter - (Counter%ActionCounter);
	}
	bool Plants::isAction() {					      // 回傳植物是否正在動作
		return Action && CounterOn;
	}
	void Plants::StartAction() {				    // 讓植物開始動作
		status = 2;
	}
	int Plants::WhichAction() {					    // 回傳植物目前的狀態
		return status;
	}
	void Plants::SetTargetX(int a) {			  // 設定攻擊目標的座標(葫蘆用)
		TargetX = a;
		velocity = (TargetX - x) / 10;
	}
	bool Plants::isFinished() {					    // 檢查動畫是否結束
		if (ID == 4 && anime2.IsFinalBitmap() == true) {
			return true;
		}
		else if (ID == 5 && anime2Counter == 5) {
			return true;
		}
		return false;
	}
	void Plants::OnMove() {						      // 控制植物的動作
		if (status == 1) {
			anime.OnMove();
		}
		else if (ID == 4 && status == 2) {
			anime2.OnMove();
		}
		else if (ID == 5 && status == 2) {
			anime2Counter++;
		}
		if (ID == 4 && TargetX != 1000) {
			if (MovingCounter != 10) {
				x = x + velocity;
				y -= 15;
				MovingCounter++;
			}
			else {
				y += 160;
				StartAction();
				TargetX = 1000;
			}
		}
		if (ID == 5 && anime.IsFinalBitmap() == true) {
			StartAction();
		}
		if (CounterOn == true) {
			Counter++;
			if (Counter % ActionCounter == 0) {
				Action = true;
			}
			else {
				if (ID == 4 && Counter > ActionCounter) {
					Action = true;
				}
				if (ID == 7 && Counter % 30 == 5) {
					Action = true;
				}
				else {
					Action = false;
				}
			}
		}
	}
	void Plants::OnShow() {						      // 將植物顯示在螢幕上
		if (ID == 4) {
			if (WhichAction() == 1) {
				anime.SetTopLeft(x, y);
				anime.OnShow();
			}
			else if (WhichAction() == 2) {
				anime2.SetTopLeft(x, y);
				anime2.OnShow();
			}
		}
		else if (ID == 3) {
			if (GetLife() > 20) {
				anime.SetTopLeft(x, y);
				anime.OnShow();
			}
			else if (GetLife() > 10) {
				anime2.OnMove();
				anime2.SetTopLeft(x, y);
				anime2.OnShow();
			}
			else if (GetLife() > 0) {
				anime3.OnMove();
				anime3.SetTopLeft(x, y);
				anime3.OnShow();
			}
		}
		else if (ID == 5 && anime2Counter != 5 && status == 2) {
			Boom.SetTopLeft(x-10*anime2Counter, y-10*anime2Counter);
			Boom.ShowBitmap(anime2Counter*0.3+1);
		}
		else {
			anime.SetTopLeft(x, y);
			anime.OnShow();
		}
	}
	string Plants::GetPath() {						  // 產生植物圖檔的路徑
		stringstream ss;
		switch (ID) {
		case 0: ss << ".\\BMP_RES\\image\\plants\\bitmap9";		  break;
		case 1: ss << ".\\BMP_RES\\image\\plants\\SunFlower";	  break;
		case 2: ss << ".\\BMP_RES\\image\\plants\\PeaShooter";	  break;
		case 3: ss << ".\\BMP_RES\\image\\plants\\WallNut_1";	  break;
		/*
		case 31:ss << ".\\RES\\Plants\\WallNut\\WallNut_cracked1_"; break;
		case 32:ss << ".\\RES\\Plants\\WallNut\\WallNut_cracked2_"; break;
		case 4: ss << ".\\RES\\Plants\\Squash\\Squash_";			      break;
		case 41:ss << ".\\RES\\Plants\\Squash\\SquashAttack_";	  	break;
		case 5: ss << ".\\RES\\Plants\\CherryBomb\\CherryBomb_";  	break;
		case 6: ss << ".\\RES\\Plants\\SnowPea\\SnowPea_";			    break;
		case 7: ss << ".\\RES\\Plants\\Repeater\\Repeater_";	    	break;*/
		default:ss << "";                                           break;
		}
		return ss.str();
	}
}