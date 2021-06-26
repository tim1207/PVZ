#pragma once
namespace game_framework {
	class Plants {
	public:
		Plants();
		Plants(int,int,int);
		void resetTo0(int col, int roww);
		void SetID(int);			  
		void SetLife();				  
		int GetLife();				  
		bool isAlive();				  
		void LoadBitmap();			  
		void OnMove();			  	  
		void OnShow();			  	  
		string GetPath();		  	  
		void SetFrames();		  	  
		int GetRow();				  
		int GetColumn();			  
		int GetX();				      
		int GetY();				      
		int GetWidth();		  		  
		void SetX(int);				  
		void SetY(int);				  
		void BeingAttacked();		  
		int GetID();				  
		void ResetCounter();		  
		void SetCounterOn(bool);	  
		bool isCounterOn();			  
		bool isAction();			  
		int CounterLeft();			  
		void StartAction();			  
		int WhichAction();			  
		void SetTargetX(int);		  
		bool isFinished();			  
	private:
		int x, y;					  
		int Counter;			      
		int ActionCounter;			  
		int MovingCounter;			  
		int anime2Counter;			  
		int velocity;			      
		bool CounterOn;				  
		bool Action;				  
		int status;	  		 		  
		int TargetX;				  
		int row, column;			  
		int life;					  
		int ID;						  

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
		int frames;	
		
		CAnimation anime;
		CAnimation anime2;
		CAnimation anime3;
		CAnimation Boom;
	};
}