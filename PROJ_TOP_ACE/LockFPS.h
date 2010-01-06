//#pragma once
#ifndef _LOCKFPS_H
#define _LOCKFPS_H
#include <windows.h>

class CLockFPS
{
public:
	CLockFPS(void);
	~CLockFPS(void);
	void Init(int LimitFPS);
	void LockFPS(void);

protected:
	LARGE_INTEGER feq;
	LARGE_INTEGER t1;
	LARGE_INTEGER t2;
	 double oneframetimelimit;
	 double oneframetime;
	void Delay(__int64 Us);
};
#endif