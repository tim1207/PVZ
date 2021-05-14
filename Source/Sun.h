﻿#pragma once
namespace game_framework {
	class Sun {
	public:
		Sun();
		Sun(int, int, bool);		    // 太陽的初始化
		void LoadBitmap();		        // 讀取所需圖檔
		void OnMove();			        // 處理太陽的移動
		void MoveAnime();		        // 處理太陽的動畫
		void OnShow();			        // 顯示在畫面中
		void drop();			        // 讓太陽從空中掉下來
		void fly();				        // 讓太陽以拋物線的方式移動
		int GetX();				        // 回傳X座標
		int GetY();				        // 回傳Y座標
		int GetHeight();		        // 回傳圖的高度
		int GetWidth();			        // 回傳圖的寬度
		void PickUp();			        // 讓太陽被撿起
		bool isFinished();		        // 檢查移動是否已結束
	private:
		int x, y;				        // X, Y座標
		int desy;				        // 太陽最終的Y座標
		int vx, vy;				        // X方向的速度和Y方向的速度
		bool picked;			        // 是否已被選取
		int MoveCounter;		        // 移動的計時器
		int stepX, stepY;		        // 移動過程中每一次移動的距離
		bool finished;			        // 移動是否已結束
		bool CallFromSunFlower;	      	// 是否是從向日葵中產生
	};
}