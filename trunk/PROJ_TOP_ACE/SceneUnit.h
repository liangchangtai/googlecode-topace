//#pragma once
#ifndef _SCENEUNIT_H
#define _SCENEUNIT_H
#include "unitmath.h"
typedef enum _ACT_Orders{
	StandBy=0,
	FollowTo=1,
	AttackTo=2,
	Avoid=3
}_ACT_Orders;

typedef enum _ACT_Modes{
	CounterAttack=0,
	OnlyTravel=1,
	OnlyAvoid=2
}_ACT_Modes;
class CSceneUnit :
	public CUnitMath
{
public:
	CSceneUnit(void);
	~CSceneUnit(void);
	unsigned int UnitType;
	unsigned int ModelType;
	// Move Speed
	float MoveSPD;
	// Turn Speed
	float TurnSPD;
	// Move Speed Resistance
	float MoveSPD_R;
	// Turn Speed Resistance
	float TurnSPD_R;
	float Life;
	unsigned int Status;
	float TurnSPD_Now;
	void SetTGTPos(__m128 TGTPos);
	void SetTGTPos(float TGTPos[3]);
	// AT Think Time
	float AIThinkTime;
	float LilfTime;
	void Updata(void);
	__m128 TGT_Pos;
	unsigned int TGT_ID;
	_ACT_Orders ACT_Order;
	_ACT_Modes ACT_Modes;

};
#endif