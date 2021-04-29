#pragma once
namespace game_framework {
	class Zombies
	{
	public:
		Zombies();
		Zombies(int, int, int);				  // 殭屍的初始化
		void LoadBitmap();				    // 讀取所需的圖檔
		void OnMove();					      // 處理殭屍的動作
		void OnShow();					      // 顯示在畫面中
		int GetLife();					      // 回傳目前所剩的生命
		bool isAlive();					      // 檢查是否已死亡
		void GiveLife();				      // 設定殭屍的生命
		string GetPath();				      // 取得圖檔的路徑
		string GetPathWithStatus();		// 取的圖檔的路徑
		void SetStatus(int);			    // 設定殭屍目前的狀態
		int GetStatus();				      // 回傳殭屍目前的狀態
		void SetFrames();				      // 設定殭屍圖檔總量
		void Hitted(int);				      // 殭屍被擊中
		int GetRow();					        // 回傳殭屍所在的列數
		int GetX();						        // 回傳目前的X座標
		void SetID(int);				      // 設定殭屍的種類
		int GetID();					        // 回傳殭屍的種類
		bool Attack();					      // 讓殭屍發動攻擊
		bool isFinished();				    // 檢查死亡動畫是否已經結束
		void GoToDie();					      // 讓殭屍瞬間死亡
		void BoomToDie();				      // 讓殭屍被炸死
		void MoveX();					        // 讓殭屍向前移動
		void SetSnowCounter();			  // 設定冷凍計時器
		void Faster();					      // 讓殭屍加速(密技用)
	private:
		int x, y;						          // 座標
		int AttackCounter;				    // 攻擊的計時器
		int AttackClock;				      // 攻擊的冷卻時間
		int SnowCounter;				      // 冷凍的計時器
		int row;						          // 列數
		unsigned int life;				    // 生命
		int ID;							          // 殭屍的種類
		/*
			0:none
			1:zombie
			2:cone head zombie
			3:bucket head zombie
		*/
		int status;						        // 殭屍的狀態，1是走路，2是攻擊
		int LastMove;					        // 儲存上一步的移動狀態(冷凍狀態用)
		int velocity;					        // 殭屍的移動速度
		int WalkingFrames;				    // 走路的圖檔的數量
		int AttackingFrames;			    // 攻擊的圖檔的數量
		CAnimation AnimeWalking;
		CAnimation AnimeAttacking;
		CAnimation NormalWalking;
		CAnimation NormalAttacking;
		CAnimation AnimeDie;
		CAnimation Head;
		CAnimation BoomDie;
		bool Boom;						        // 是否是被炸死
		bool HeadFinished;				    // 頭掉下來了動畫是否已結束
		bool DieFinished;				      // 死亡的動畫是否已結束
		bool BoomFinished;				    // 爆炸死亡的動畫是否已結束
	};
}