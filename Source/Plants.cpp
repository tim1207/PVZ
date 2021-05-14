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
	Plants::Plants(int id, int col, int roww) { //0-8 0-4
		ID = id;
		x = 172 + col* 80;
		y = 80 + roww * 98;
		
		
		// if (ID == 4) {
		// 	x -= 15;
		// 	y -= 150;
		// }
		// else if (ID == 5) {
		// 	x -= 20;
		// }
		
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
		switch (ID) {							                
		case 1:	ActionCounter = 30 * 10;  break;
		case 2: ActionCounter = 30 * 1;   break;
		case 6: ActionCounter = 30 * 1;   break;
		case 7: ActionCounter = 30 * 1;   break;
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
	int Plants::GetID() {						      
		return ID;
	}
	void Plants::ResetCounter() {				    
		Counter = 0;
	}
	void Plants::SetLife() {					      
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
	int Plants::GetLife() {						      
		return life;
	}
	bool Plants::isAlive() {					  
		if (GetLife() > 0)	return true;
		return false;
	}
	void Plants::BeingAttacked() {			    	
		life--;
	}
	void Plants::SetFrames()					    
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
		case 0: frames = 18;	break;
		default:	break;
		}
	}
	int Plants::GetRow()						       
	{
		return row;
	} 
	int Plants::GetColumn() {					     
		return column;
	}
	int Plants::GetX()							       
	{
		return x;
	}
	int Plants::GetY() {						        
		return y;
	}
	int Plants::GetWidth()						      
	{
		return anime.Width();
	}
	void Plants::SetX(int a) {				    	
		x = a;
	}
	void Plants::SetY(int a) {				    	
		y = a;
	}
	void Plants::LoadBitmap() {					    
		SetFrames();							            
		if (ID == 0) {
			for (int i = 0; i <= frames; i++) {		
				char FILENAME[100];
				sprintf(FILENAME, "%s.bmp", GetPath().c_str());

				anime.AddBitmap(FILENAME, RGB(0, 0, 0));
			}
		}
		else {
			for (int i = 0; i <= frames; i++) {		
				char FILENAME[100];
				sprintf(FILENAME, "%s%d.bmp", GetPath().c_str(),i);

				anime.AddBitmap(FILENAME, RGB(0, 0, 0));
			}
		}
				
		if (ID == 3) {
			SetID(31);
			SetFrames();
			for (int i = 0; i <= frames; i++) {
				char FILENAME[100];
				sprintf(FILENAME, "%s%d.bmp", GetPath().c_str(),i);
				anime2.AddBitmap(FILENAME, RGB(0, 0, 0));
			}
			SetID(32);
			SetFrames();
			for (int i = 0; i <= frames; i++) {
				char FILENAME[100];
				sprintf(FILENAME, "%s%d.bmp", GetPath().c_str(),i);
				anime3.AddBitmap(FILENAME, RGB(0, 0, 0));
			}
			SetID(3);
		}		
		else if (ID == 4) {
			SetID(41);
			SetFrames();
			for (int i = 0; i <= frames; i++) {
				char FILENAME[100];
				sprintf(FILENAME, "%s%d.bmp", GetPath().c_str(),i);
				anime2.AddBitmap(FILENAME, RGB(0, 0, 0));
			}
			SetID(4);
		}
		else if (ID == 5) {
			for (int i = 0; i <= 12; i++) {
				char FILENAME[100];
				sprintf(FILENAME, "%s%d.bmp", ".\\BMP_RES\\image\\plants\\CherryBomb\\Boom",i);
				Boom.AddBitmap(FILENAME, RGB(0, 0, 0));
			}
		}
		
	}
	void Plants::SetCounterOn(bool a) {				
		CounterOn = a;
		if (a == false) {
			Counter = 1;
		}
	}
	bool Plants::isCounterOn() {				    
		return CounterOn;
	}
	int Plants::CounterLeft() {					    
		return ActionCounter - (Counter%ActionCounter);
	}
	bool Plants::isAction() {					    
		return Action && CounterOn;
	}
	void Plants::StartAction() {				    
		status = 2;
	}
	int Plants::WhichAction() {					    
		return status;
	}
	void Plants::SetTargetX(int a) {			    
		TargetX = a;
		velocity = (TargetX - x) / 10;
	}
	bool Plants::isFinished() {					    
		if (ID == 4 && anime2.IsFinalBitmap() == true) {
			return true;
		}
		else if (ID == 5 && anime2Counter == 5) {
			return true;
		}
		return false;
	}
	void Plants::OnMove() {						      
		if (status == 1) {
			anime.OnMove();
		}
		else if (ID == 4 && status == 2) {
			anime2.OnMove();
		}
		else if (ID == 5 && status == 2) {
			anime2Counter++;
		}
		// if (ID == 4 && anime.IsFinalBitmap() == true) {
		// 	StartAction();
		// }
		if (ID == 4 && anime2.IsFinalBitmap() == true) {
			status=3;
		}
		// if (ID == 4 && TargetX != 1000) {
		// 	if (MovingCounter != 10) {
		// 		x = x + velocity;
		// 		y -= 15;
		// 		MovingCounter++;
		// 	}
		// 	else {
		// 		y += 160;
		// 		StartAction();
		// 		TargetX = 1000;
		// 	}
		// }
		if (ID == 5 && anime.IsFinalBitmap() == true) {
			StartAction();
		}
		if (ID == 5 && Boom.IsFinalBitmap() == true) {
			status=3;
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
	void Plants::OnShow() {						      
		if (ID == 4) {
			if (WhichAction() == 1) {
				anime.SetTopLeft(x, y);
				anime.OnShow();
			}
			else if (WhichAction() == 2) {
				anime2.SetTopLeft(x+velocity, y);
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
			Boom.SetTopLeft(x-40, y-40);
			Boom.OnMove();
			Boom.OnShow();

		}
		else {
			anime.SetTopLeft(x, y);
			anime.OnShow();
		}
	}
	string Plants::GetPath() {						  
		stringstream ss;
		switch (ID) {
		case 0: ss << ".\\BMP_RES\\image\\plants\\void";		  			  	break;
		case 1: ss << ".\\BMP_RES\\image\\plants\\SunFlower\\SunFlower_";	  	break;
		case 2: ss << ".\\BMP_RES\\image\\plants\\PeaShooter\\PeaShooter_";	  	break;

		case 3: ss << ".\\BMP_RES\\image\\plants\\WallNut\\WallNut_";	  	    break;
		case 31:ss << ".\\BMP_RES\\image\\plants\\WallNut\\WallNut_cracked1_";  break;
		case 32:ss << ".\\BMP_RES\\image\\plants\\WallNut\\WallNut_cracked2_";  break;

		case 4: ss << ".\\BMP_RES\\image\\plants\\Squash\\Squash_";			    break;
		case 41:ss << ".\\BMP_RES\\image\\plants\\Squash\\SquashAttack_";	  	break;
		case 5: ss << ".\\BMP_RES\\image\\plants\\CherryBomb\\CherryBomb_";  	break;
		case 6: ss << ".\\BMP_RES\\image\\plants\\SnowPea\\SnowPea_";			    	break;
		case 7: ss << ".\\BMP_RES\\image\\plants\\Repeater\\Repeater_";	    			break;
		default:ss << "";                                           			break;
		}
		return ss.str();
	}
}