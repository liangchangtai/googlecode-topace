#pragma once
#include "unitmath.h"

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
	void TurnTo(__m128 TGTPos);
	void TurnTo(float TGTPos[3]);
	// AT Think Time
	float AIThinkTime;
	float LilfTime;
};
