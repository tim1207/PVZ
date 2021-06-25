#pragma once
namespace game_framework {
	class Zombies
	{
	public:
		Zombies();
		Zombies(int, int, int);				  
		void LoadBitmap();				    
		void OnMove();					      
		void OnShow();					      
		int GetLife();					      
		bool isAlive();					      
		void GiveLife();				      
		string GetPath();				      
		string GetPathWithStatus();		
		void SetStatus(int);			    
		int GetStatus();				      
		void SetFrames();				      
		void Hitted(int);				      
		int GetRow();					       
		int GetX();						       
		void SetID(int);				      
		void SetX(int);
		int GetID();					      
		bool Attack();					      
		bool isFinished();				    
		void GoToDie();					     
		void BoomToDie();				      
		void MoveX();					      
		void SetSnowCounter();			  
		void Faster();					   
	private:
		int x, y;						   
		int AttackCounter;				   
		int AttackClock;				   
		int SnowCounter;				   
		int row;						   
		unsigned int life;				   
		int ID;							   
		/*
			0:none
			1:zombie
			2:cone head zombie
			3:bucket head zombie
		*/
		int status;						   
		int LastMove;					   
		int velocity;					   
		int WalkingFrames1=17;				    
		int AttackingFrames1=20;
		int WalkingFrames2=20;				    
		int AttackingFrames2=10;
		int WalkingFrames3=14;				    
		int AttackingFrames3=10;	


		CAnimation NormalWalking1;// for id 1
		CAnimation NormalAttacking1;
		CAnimation NormalWalking2;// for id 2
		CAnimation NormalAttacking2;
		CAnimation NormalWalking3;// for id 3
		CAnimation NormalAttacking3;


		CAnimation AnimeDie;
		CAnimation Head;
		CAnimation BoomDie;
		bool Boom;						   
		bool HeadFinished;				   
		bool DieFinished;				   
		bool BoomFinished;				   
	};
}