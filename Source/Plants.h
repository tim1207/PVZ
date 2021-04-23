#pragma once
namespace game_framework {
	class Plants {
	public:
		Plants();
		Plants(int,int,int);		  // 植物的初始化
		void SetID(int);			    // 設定植物的種類
		void SetLife();				    // 設定生命
		int GetLife();				    // 回傳目前剩餘的生命
		bool isAlive();				    // 檢查是否死亡
		void LoadBitmap();			  // 讀取所需圖檔
		void OnMove();			  	  // 控制動作
		void OnShow();			  	  // 顯示在螢幕上
		string GetPath();		  	  // 取得圖檔的路徑
		void SetFrames();		  	  // 根據植物的種類設定圖檔的數量
		int GetRow();				      // 回傳所在的列數
		int GetColumn();			    // 回傳所在的行數
		int GetX();					      // 回傳X座標
		int GetY();					      // 回傳Y座標
		int GetWidth();				    // 回傳圖檔的寬度
		void SetX(int);				    // 設定X座標
		void SetY(int);				    // 設定Y座標
		void BeingAttacked();		  // 讓植物被攻擊
		int GetID();				      // 回傳植物的種類
		void ResetCounter();		  // 重設冷卻時間
		void SetCounterOn(bool);	// 讓植物開始動作
		bool isCounterOn();			  // 檢查是否已啟動動作計時器
		bool isAction();			    // 檢查是否正在動作
		int CounterLeft();			  // 回傳還要多久才會動作
		void StartAction();			  // 開始動作
		int WhichAction();			  // 回傳目前的狀態
		void SetTargetX(int);		  // 設定目標所在的X座標(葫蘆用)
		bool isFinished();			  // 檢查動畫是否已經結束
	private:
		int x, y;					        // X,Y座標
		int Counter;				      // 冷卻時間的計時器
		int ActionCounter;			  // 儲存冷卻時間長度
		int MovingCounter;			  // 儲存移動的冷卻時間長度(葫蘆用)
		int anime2Counter;			  // 爆炸時間計時器(櫻桃用)
		int velocity;				      // 移動的速度(葫蘆用)
		bool CounterOn;			     	// 計時器的啟動與否
		bool Action;				      // 動作狀態
		int status;					      // 攻擊狀態
		int TargetX;				      // 目標的X座標(葫蘆用)
		int row, column;			    // 行列座標
		int life;					        // 生命
		int ID;						        // 植物種類

		/*
			0 : empty
			1 : SunFlower
			2 : PeaShooter
			3 : WallNut
			31: WallNut_cracked1
			32: WallNut_cracked2
			4 : Squash
			41: SquashAttack
			5 : CherryBomb
			6 : SnowPea
			7 : Repeater
		*/
		int frames;					      // 圖檔數量
		CAnimation anime;
		CAnimation anime2;
		CAnimation anime3;
		CMovingBitmap Boom;
	};
}