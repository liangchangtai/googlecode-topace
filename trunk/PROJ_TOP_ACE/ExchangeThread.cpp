﻿#include "ExchangeThread.h"
CExchangeThread ThreadDataExchange;
_ReadingThread_States ReadingThread_States=_ReadingThread_States_NoThread;
int ReadingThreadWait_Updata=0; 
int ReadingThreadWait_Draw=0; 
void ThreadUpdataToExchange(CExchangeThread * ThreadDataUpdata)
{
	ReadingThreadWait_Updata=0;
	while(ReadingThread_States==_ReadingThread_States_ThreadExchangeToDraw)
		ReadingThreadWait_Updata++;
	ReadingThread_States=_ReadingThread_States_ThreadUpdataToExchange;

	if(ThreadDataUpdata->ListCount>ThreadDataExchange.ListCount)
	{
		ThreadDataExchange.AddListToCount(ThreadDataUpdata->ListCount);
	}
	memcpy_s(
		ThreadDataExchange.DataList,
		sizeof(_UnitData)*ThreadDataExchange.ListCount,
		ThreadDataUpdata->DataList,
		sizeof(_UnitData)*ThreadDataUpdata->DataCount);
	ThreadDataExchange.DataCount=ThreadDataUpdata->DataCount;
	memcpy_s(
		&(ThreadDataExchange.Global_Data),
		sizeof(_Global_Data),
		&(ThreadDataUpdata->Global_Data),
		sizeof(_Global_Data));
	
	ReadingThread_States=_ReadingThread_States_NoThread;
}
void ThreadExchangeToDraw(CExchangeThread * ThreadDataDraw)
{
	ReadingThreadWait_Draw=0;
	while(ReadingThread_States==_ReadingThread_States_ThreadUpdataToExchange)
		ReadingThreadWait_Draw++;
	ReadingThread_States=_ReadingThread_States_ThreadExchangeToDraw;
	
	if(ThreadDataExchange.ListCount>ThreadDataDraw->ListCount)
	{
		ThreadDataDraw->AddListToCount(ThreadDataExchange.ListCount);
	}
	memcpy_s(
		ThreadDataDraw->DataList,
		sizeof(_UnitData)*ThreadDataDraw->ListCount,
		ThreadDataExchange.DataList,
		sizeof(_UnitData)*ThreadDataExchange.DataCount);
	ThreadDataDraw->DataCount=ThreadDataExchange.DataCount;
	memcpy_s(
		&(ThreadDataDraw->Global_Data),
		sizeof(_Global_Data),
		&(ThreadDataExchange.Global_Data),
		sizeof(_Global_Data));

	ReadingThread_States=_ReadingThread_States_NoThread;
}
CExchangeThread::CExchangeThread(void)
: ListCount(DEFDATANUM)
, DataCount(1)
{
	Global_Data.Scene.CamID=0;
	Global_Data.Scene.PlayerID=0;
	DataList = (_UnitData *)_aligned_malloc(sizeof(_UnitData)*ListCount,16);
	DataList[0].UnitData_States=_UnitData_States_Use;
}

CExchangeThread::~CExchangeThread(void)
{
	_aligned_free(DataList);
}

bool CExchangeThread::AddListCount(int AddCount)
{
	if(AddCount<=0)
		return false;
	if(!DataList)
		return false;
	_UnitData * ListTMP=(_UnitData *)_aligned_malloc(sizeof(_UnitData)*(ListCount+AddCount),16);
	if(!ListTMP)
		return false;
	memcpy_s(ListTMP,sizeof(_UnitData)*(ListCount+AddCount),DataList,sizeof(_UnitData)*ListCount);
	_aligned_free(DataList);
	DataList=ListTMP;
	ListCount=ListCount+AddCount;
	return true;
}
bool CExchangeThread::AddListToCount(int Count)
{
	return AddListCount(Count-ListCount);
}
bool CExchangeThread::AddOneData(_UnitData * UnitData,int * DataNum)
{
	if((!UnitData)||(!DataList))
		return false;
	for(int ListNumTMP=0;ListNumTMP<ListCount;ListNumTMP++)
	{
		if(DataList[ListNumTMP].UnitData_States==_UnitData_States_NoUse)
		{
			DataList[ListNumTMP].UnitData_States=_UnitData_States_Use;
			memcpy_s(&(DataList[ListNumTMP]),sizeof(_UnitData),UnitData,sizeof(_UnitData));
			if(DataNum)
				DataNum[0]=ListNumTMP;
			return true;
		}
	}
	if(DataCount>=ListCount)
	{
		if(!AddListCount())
			return false;
	}
	memcpy_s(&(DataList[DataCount]),sizeof(_UnitData),UnitData,sizeof(_UnitData));
	if(DataNum)
		DataNum[0]=DataCount;
	DataCount++;
	return true;
}

bool CExchangeThread::UpdataOneData(_UnitData * UnitData,int DataNum)
{
	if((!UnitData)||(!DataList))
		return false;
	memcpy_s(&(DataList[DataNum]),sizeof(_UnitData),UnitData,sizeof(_UnitData));
	return true;
}

int CExchangeThread::GetOneUseAbleIndex(void)
{
	if(!DataList)
		return 0;
	for(int ListNumTMP=0;ListNumTMP<ListCount;ListNumTMP++)
	{
		if(DataList[ListNumTMP].UnitData_States==_UnitData_States_NoUse)
		{
			DataList[ListNumTMP].UnitData_States=_UnitData_States_Use;
			return ListNumTMP;
		}
	}
	if(DataCount>=ListCount)
	{
		if(!AddListCount())
			return 0;
	}
	DataCount++;
	return DataCount-1;
}