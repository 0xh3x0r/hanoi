#include<stdio.h>

#include <iostream>
#include <vector>
using namespace std;
__int64 StartConfig;
__int64 CurrGoals;
__int64 FinalConfig;
__int64 FinalConfig2;
__int64 CurrConfig;
__int64 N;
__int64 K;
__int64  Last;
__int64 Hamleler = 0;
void basla();
#define MAX_DISKS 8
#define MAX_PEGS 5

#define GetPegConfig(PegNumConfig,Config) \
{ \
	PegNumConfig = Config>>(PegNumConfig * N); \
	PegNumConfig = PegNumConfig &   ( 2<<(N-1))-1; \
} \


#define SetGoal(Disk,Peg) \
{ \
	if(Peg != 0) \
	CurrGoals = Disk << (N*Peg) | CurrGoals; \
	else \
    CurrGoals = Disk | CurrGoals; \
} \


void SetGl(__int64 Disk,__int64 Peg)
{
	Disk = Disk <<   (N*Peg);
	CurrGoals =  Disk | CurrGoals; 
}
void DeleteGoal(__int64 Disk,__int64 Goal)
{
	Disk = Disk << (N*Goal);
	CurrGoals ^= Disk;

}
void DeleteFinalConfig(__int64 Disk,__int64 Goal)
{
	Disk = Disk << (N*Goal);
	FinalConfig ^= Disk;

}
__int64 dConfig(__int64 PegNumConfig,__int64 Config)
{
	PegNumConfig = Config>>(PegNumConfig * N);
	PegNumConfig = PegNumConfig &   ( 2<<(N-1))-1;
	return PegNumConfig;
}
__int64 GetLowBit(__int64 b)
    {
        if (b == 0)
            return 0;
        __int64 bit = 0;
        while ((b & 1) == 0)
        {
            b >>= 1;
            bit++;
        }
        return bit;
    }

__int64 GetHighBit(__int64 b)
{
	    if(b == 0)
			return -1;
		__int64 bit = 0;
       while(b > 1)
	   {b >>=1;bit++; }
		
        return bit;

}
void Make_Move(__int64 Disk,__int64 SourcePeg,__int64 TargetPeg)
{
	Hamleler++;
   cout<<SourcePeg+1<<" "<<TargetPeg+1<<"\r\n";
   DeleteGoal(Disk,TargetPeg);
	if(SourcePeg > 0)
		CurrConfig =  (Disk << (N*SourcePeg)) ^ CurrConfig;
	else
	CurrConfig = Disk ^ CurrConfig;

   if(TargetPeg > 0)
  	CurrConfig = (Disk << (N*TargetPeg)) | CurrConfig;
   else
	CurrConfig = Disk | CurrConfig;



}
inline __int64 GetPeg(__int64 Disk)
{
	__int64 Peg =0;
	for(__int64 i = K-1;i > -1;i--)
	{
		Peg = i;
		GetPegConfig(Peg,CurrConfig);
		if( (Peg & Disk)==Disk)
			return i;
	}

	return -1;


}

__int64 GetHighDisk(__int64 Peg,__int64 Config)
{
	GetPegConfig(Peg,Config);
	for(__int64 i =Last;i>=1;i = i>>1)
	{
	  if( (Peg & i) == i )
		  return i;
	}
	return -1;

}
inline __int64 GetNextLowDisk(__int64 Disk,__int64 Peg,__int64 Config)
{
	GetPegConfig(Peg,Config);
	if(Peg == 0)
		return -1;
	else
	{
		while(Disk > 0)
		{
		 Disk >>= 1;
		 if( (Peg&Disk) == Disk )
			 return Disk;


		}


	}

	return -1;

}

__int64 GetMaxAviablePegFor(__int64 Disk,__int64 Config,__int64 SourcePeg)
{


  __int64 diskb = GetLowBit(Disk);
  __int64 Max = ( 1<<( N) )-1;
  __int64 High = -1;
  __int64 LowestPeg = -1;
  __int64 LastPegHighDisk = Last;
  __int64 LFinalConfig = Last+1;
  for(__int64 i = K-1; i > -1;i--)
  {
	__int64 Peg = i;
	__int64 PegHighDisk = GetHighDisk(Peg,CurrConfig);
	__int64 PegFinalConfig = i;
	GetPegConfig(PegFinalConfig,FinalConfig);
	GetPegConfig(Peg,Config)
	__int64 pegb = GetLowBit(Peg);
	
    if( ((pegb < diskb)  && (i != SourcePeg)) && ((Peg ^ Max) >= High))
	{
		
		if((Peg ^ Max) == High && PegHighDisk > LastPegHighDisk && LFinalConfig > PegFinalConfig)
		break;
		
        LowestPeg = i;
		LastPegHighDisk = PegHighDisk;
		LFinalConfig = PegFinalConfig;
		High = Peg ^ Max;

	}
  }
  return LowestPeg;
}

__int64 GetLowAviablePegFor(__int64 Disk,__int64 Config,__int64 SourcePeg)
{


  __int64 diskb = GetLowBit(Disk);
  __int64 Max = ( 1<<( N) )-1;
  __int64 HighestPeg = -1;
  __int64 High = ( 1<<( N) )-1;
  for(__int64 i = K-1; i > -1;i--)
  {
	__int64 Peg = i;
	GetPegConfig(Peg,Config)
	__int64 pegb = GetLowBit(Peg);
    if( ((pegb < diskb)  && (i != SourcePeg)) && ((Peg ^ Max) < High))
	{
		High = Peg ^ Max;
        HighestPeg = i;
	}
  }
  return HighestPeg;
}

inline __int64 GetGoal(__int64 Disk,__int64 Config)
{

	for(__int64 i = K-1; i > -1 ;i--)
	{
	__int64 Peg = i;
	GetPegConfig(Peg,Config);
	if( (Peg & Disk) == Disk )
		return i;

	}
	return -1;
}



inline __int64 GetNextHighDisk(__int64 Disk,__int64 Peg,__int64 Config)
{

	GetPegConfig(Peg,Config);
	if(Disk == Last)
		return -1;
	else
	{
		while(Disk > 0)
		{
		 Disk <<= 1;
		 if( (Peg&Disk) == Disk )
			 return Disk;


		}


	}

	return -1;



}
bool Get_NK()
{


 cin>>N;
 cin>>K;
 if(N <= MAX_DISKS)
	 if(K <= MAX_PEGS)
		 return 1;
	 else
		 return 0;
}
bool Get_Start()
{
	__int64 Peg = 0;
	for(__int64 i = Last; i >=1;i>>=1)
	{
		cin>>Peg;
		Peg--;
		if(Peg <= K)
		StartConfig |=  (i<<(Peg*N));
		else
			return false;
	

	}
	return true;
}
bool Get_Final()
{
	__int64 Peg = 0;
	for(__int64 i = Last; i >=1;i>>=1)
	{
		cin>>Peg;
		Peg--;
		if(Peg <= K)
		FinalConfig |=  (i<<(Peg*N));
		else
			return false;
	

	}
	return true;

}
inline bool CheckPegFor(__int64 Disk,__int64 Peg,__int64 Config)
{
	GetPegConfig(Peg,Config);
	if(Peg == 0)
		return true; 

	if(GetHighBit(Disk) > GetHighBit(Peg))
		return true;
	else
		return false;


}

__int64 GetLowDisk(__int64 Peg,__int64 Config)
{
	GetPegConfig(Peg,Config);
	for(__int64 i =1;i<=Last;i = i<<1)
	{
	  if( (Peg & i) == i )
		  return i;
	}
	return -1;
}

int main() {
	
	
    Get_NK();
	StartConfig =  (2ULL<< (N * K));
	FinalConfig =  (2ULL<< (N * K));
	CurrGoals = (2ULL<< (N * K));
	Last = ( 1<<( N-1) );
	Get_Start();
	Get_Final();
	CurrConfig = StartConfig;
	FinalConfig2 = FinalConfig;
	
	basla();
	system("Pause");

}
inline __int64 GetBlockHigh(__int64 Peg,__int64 Disk)
{
	  __int64 subDisk = Disk;
	  __int64 Block = 0;
	  while(subDisk != -1)
	  {

		  subDisk = GetNextHighDisk(subDisk,Peg,CurrConfig);
		  Block++;

	  }
	  Block--;
	 


	  return Block;
}
inline __int64 GetBlockLow(__int64 Peg,__int64 Disk)
{
	 __int64 subDisk = Disk;
	 __int64 Block = 0;
	  while(subDisk != -1)
	  {
		   
		 subDisk = GetNextLowDisk(subDisk,Peg,CurrConfig);
		 if( GetPeg(subDisk) != GetGoal(subDisk,FinalConfig))
		 Block++;

	  }
	  return Block;
}


inline __int64 GetCleanerPeg(__int64 Disk,__int64 Block,__int64 TargetPeg)
{
     __int64 Pegbits = (1<<K) -1;
	 Block = 1<<Block;
	 TargetPeg = 1<<TargetPeg;
	 Pegbits ^= Block;
	 Pegbits ^= TargetPeg;
	 __int64 Peg = 0;
	 __int64 LastBlock = Last+1;
	 __int64 LastPeg = 0;
	 __int64 LastHighDisk = 0;
	 while(Pegbits != 0)
	 {
	  Peg = GetHighBit(Pegbits);
	  __int64 DiskBlock = 0 ; 
	  DiskBlock += GetBlockLow(Peg,Disk);
	  DiskBlock +=GetBlockHigh(Peg,Disk);
	  __int64 HighDisk = GetHighDisk(Peg,CurrConfig);
	  if(DiskBlock < LastBlock | HighDisk < LastHighDisk)
	  {
		  LastBlock = DiskBlock;
		  LastPeg = Peg;
		  LastHighDisk = HighDisk;
	  }
	  Pegbits ^= (1 << Peg);
	 }
	 return LastPeg;
}

inline int GetCleanDisk(__int64 Disk,__int64 Peg,__int64 Config)
{
	if(Disk == 0)
	return GetLowDisk(Peg,Config);
	GetPegConfig(Peg,Config);
	if(Peg == 0)
		return -1;

	if(Disk == Last)
		return -1;
	else
	{
		while(Disk > 0)
		{
		 Disk <<= 1;
		 if( (Peg&Disk) == Disk )
			 return Disk;

		 
		}


	}

	return -1;



}

inline __int64 Move(__int64 LowDisk,__int64 Target,int Subdisk)
{
	
	SetGl(LowDisk,Target);
	__int64 SourcePeg = GetPeg(LowDisk);
	__int64 Disk = LowDisk;
	while(Disk < GetHighDisk(SourcePeg,CurrConfig))
	{
	Disk = GetNextHighDisk(Disk,GetPeg(Disk),CurrConfig);
	SetGl(Disk,GetMaxAviablePegFor(Disk,CurrGoals,GetPeg(Disk)));
	
	}
     while( GetGoal(LowDisk,CurrGoals) != -1 )
	{
		if ((GetNextHighDisk(Disk,GetPeg(Disk),CurrConfig) == -1) && CheckPegFor(Disk,GetGoal(Disk,CurrGoals),CurrConfig) )
		{
		 Make_Move(Disk,GetPeg(Disk),GetGoal(Disk,CurrGoals));
		 Disk = GetNextLowDisk(Disk,GetPeg(LowDisk),CurrConfig);
		 continue;
		}
		else if(!(GetNextHighDisk(Disk,GetPeg(Disk),CurrConfig) == -1))
		{
			 Move(Disk,GetGoal(Disk,CurrGoals),Subdisk);
			 Disk = GetNextLowDisk(Disk,GetPeg(LowDisk),CurrConfig);
			 continue;
		}
		else if(!CheckPegFor(Disk,GetGoal(Disk,CurrGoals),CurrConfig))
		 {
	
			  
        __int64 CleanDisk = GetCleanDisk(Subdisk,Target,CurrConfig);
	    __int64 CleanPeg = GetCleanerPeg(CleanDisk,SourcePeg,Target);
	    Move(CleanDisk,CleanPeg,GetNextLowDisk(CleanDisk,CleanPeg,CurrConfig));
		
			 continue;
		 }
	
	
	}

	return 1;
}


__int64 BestMove()
{
	__int64 Peg = 0;
	__int64 LastDisk = Last+1;
	__int64 LastBlock = N;
	for(;Peg<K;Peg++)
	{
	  
	  __int64 Disk =  GetLowDisk(Peg,FinalConfig);
	  if(GetPeg(Disk) != Peg)
	  if(Disk != -1)
	  {
	  __int64 PegConfig = Peg;
	  GetPegConfig(PegConfig,CurrConfig);
	   __int64 Block = GetBlockHigh(GetPeg(Disk),Disk);
	   Block += GetBlockLow(Peg,Disk);
	   Block += GetBlockHigh(Peg,Disk);
		  if(Block <= LastBlock)
		  {
			  if(Block == LastBlock && Disk < LastDisk)
				  continue;
			  LastDisk = Disk;
			  LastBlock = Block;
		  }

	     

	  }

	}
	return LastDisk;
}


void basla()

{
	__int64 BestDisk = BestMove();
	while(BestDisk != Last+1)
	{

		Move(BestDisk,GetGoal(BestDisk,FinalConfig),GetNextLowDisk(BestDisk,GetGoal(BestDisk,FinalConfig2),FinalConfig2));
		DeleteFinalConfig(BestDisk,GetGoal(BestDisk,FinalConfig));
		BestDisk = BestMove();
	}
}