//#pragma once

#ifndef _TOPACEMODEL_H
#define _TOPACEMODEL_H
#include "Def.h"	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <xmmintrin.h>
typedef enum _TAM_File_States {
	_TAM_File_States_NoRead =0x01,
	_TAM_File_States_ReadOK =0x02,
	_TAM_File_States_NoFile =0x03,
	_TAM_File_States_ReadFail = 0x04
}_TAM_File_States;
typedef enum _TAM_Camera_Type {
    TAM_Camera_Type_Target		= 0x01, 
    TAM_Camera_Type_Free		= 0x02
} _TAM_Camera_Type;
typedef enum _TAM_Light_Type {//****灯光种类：01_omni,02_freeSpot,03_targetSpot,04_freeDirect,05_targetDirect*********
	TAM_Light_Type_Omni = 0x01,
	TAM_Light_Type_Free_Spot = 0x02,
	TAM_Light_Type_Target_Spot = 0x03,
	TAM_Light_Type_Free_Direct = 0x04,
	TAM_Light_Type_Target_Direct = 0x05
} _TAM_Light_Type;
typedef enum _TAM_Bone_Frame_Type{
	_TAM_Bone_Frame_Type_Translate = 0x01,
	_TAM_Bone_Frame_Type_Rotate = 0x02,
	_TAM_Bone_Frame_Type_Scale = 0x03
} _TAM_Bone_Frame_Type;
typedef enum _TAM_Light_Frame_Type{
	_TAM_Light_Frame_Type_Color = 0x01,
	_TAM_Light_Frame_Type_Constant = 0x02,
	_TAM_Light_Frame_Type_CutOff = 0x03
} _TAM_Light_Frame_Type;

struct _TAM_Mesh
{
	unsigned int UserID;
	void * UserPTR;
	unsigned int OBJID;
	unsigned int OBJMATID;

	float BoneWeights[4];

	float BoneIDs[4];

	unsigned char UnUse1[16];

	unsigned int OBJChunkNum;//0x40obj内数据数量
	__m128 * vertices;
	__m128 * Normals;
	float * texcos;

	unsigned int * Faces;
	unsigned int FaceNum;
	float * vecBoneWeights;
	unsigned int * vecBoneIDs;

	unsigned char MeshName[32];
};
struct _TAM_Mesh_Head
{
	unsigned int OBJNum;
	_TAM_Mesh ** OBJAddress;
};
struct _TAM_Mat
{
	unsigned int UserID;
	void * UserPTR;
	unsigned int MatID;
	unsigned char UnUse1[4];

	unsigned char MatName[32];

	unsigned char ambient[4];
	unsigned char diffuse[4];
	unsigned char specular[4];
	unsigned char self_illum[4];

	float specularLv;
	float Glossiness;
	float opacity;
	unsigned char UnUse2[4];

	unsigned char diffuseMap[32];
	unsigned char specularMap[32];
	unsigned char NormalMap[32];
	unsigned char Refract[32];
};
struct _TAM_Bone_Frame//帧
{
	unsigned char UnUse1[8];
	_TAM_Bone_Frame * PreviousFrameAddress;
	unsigned int FrameTime;
	__m128 FrameData;
};
struct _TAM_Bone_Frame_Head//动画
{
	unsigned int TotalFrameNum;//实际帧数
	unsigned int MAXFrameNum;
	_TAM_Bone_Frame ** FramesAddress;//TotalFrameNum和MAXFrameNum一般情况下是不同的，为了在读取速度和储存空间之间折中，桢地址数量等于MAXFrameNum。如果当前桢没有数据，那么当前桢的地址实际上是指向下一个有数据的帧
};
struct _TAM_Bone
{
	unsigned int UserID;
	void * UserPTR;
	unsigned int BoneID;
	unsigned int NextBoneID;//0xc同级boneID ,也就是同一个父节点的下一个bone，如果与BoneID相等或为0则表示同一个父节点没有下一个bone了

	unsigned int ChildBoneID;
	unsigned char UnUse1[12];

	__m128 FirstTranslate;

	__m128 FirstRotate;

	__m128 FirstScale;

	unsigned int FrameChunkNum;
	_TAM_Bone_Frame_Head * FramesHeadAddress[3];//_TAM_Bone_Frame_Type
	//_TAM_Bone_Frame_Head * TranslateFramesHeadAddress;
	//_TAM_Bone_Frame_Head * RotateFramesHeadAddress;
	//_TAM_Bone_Frame_Head * ScaleFramesHeadAddress;

	unsigned char BoneName[32];
};
struct _TAM_Bone_Head
{
	unsigned int BoneNum;
	_TAM_Bone** BoneAddress;
};
struct _TAM_Light_Frame
{
	_TAM_Light_Frame * PreviousFrameAddress;
	unsigned int FrameTime;
	unsigned int FrameData;
};
struct _TAM_Light_Frame_Head
{
	unsigned int TotalFrameNum;//实际帧数
	unsigned int MAXFrameNum;
	_TAM_Light_Frame ** FramesAddress;
};
struct _TAM_Light
{
	unsigned int UserID;
	void * UserPTR;
	unsigned int LightID;
	unsigned char UnUse1[4];

	unsigned int LightType;
	unsigned char LightColor[4];
	int LightConstant;
	float LightCutOff;

	unsigned int BoneID;
	unsigned int TGTBoneID;
	unsigned char UnUse2[4];
	unsigned char UnUse3[4];

	unsigned char LightName[32];
	_TAM_Light_Frame_Head * FramesHeadAddress[3];//_TAM_Light_Frame_Type
	//_TAM_Light_Frame_Head * LightColorFramesHeadAddress;
	//_TAM_Light_Frame_Head * LightConstantFramesHeadAddress;
	//_TAM_Light_Frame_Head * LightCutOffFramesHeadAddress;

};
struct _TAM_Light_Head
{
	unsigned int LightNum;
	void ** LightAddress;
};
struct _TAM_Camera
{
	unsigned int UserID;
	void * UserPTR;
	unsigned int CameraID;
	unsigned char UnUse1[4];

	unsigned int CameraType;
	float Fov;
	unsigned int SelfBoneID;
	unsigned int TGTBoneID;

	unsigned char CameraName[32];
};
struct _TAM_FileHead
{
	unsigned char HeadName[4];
	unsigned int FileSize;
	unsigned char UnUse1[4];
	unsigned char UnUse2[4];
	unsigned int ChunkNum;//0x10地址表数量
	_TAM_Mesh_Head * MeshHeadAddress;
	_TAM_Mat * MatsAddress;
	_TAM_Bone_Head * BoneHeadAddress;
	_TAM_Light_Head * LightHeadAddress;
	_TAM_Camera * CameraAddress;
};

class CTopAceModel
{
public:
	CTopAceModel(void);
	~CTopAceModel(void);
	bool ReadTAMFile(char * FileName);
	bool ReadTAMFile(wchar_t * FileName);
	_TAM_FileHead TAM_FileHead;
	_TAM_Mesh * TAM_Get_Mesh(unsigned int MeshID);
	_TAM_Bone * TAM_Get_Bone(unsigned int BoneID);
	_TAM_Light * TAM_Get_Light(unsigned int LightID);

	_TAM_Bone_Frame * TAM_Get_Bone_Frame(unsigned int BoneFrameID,unsigned int BoneID,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type);
	_TAM_Bone_Frame * TAM_Get_Bone_Frame(unsigned int BoneFrameID,_TAM_Bone * TAM_Bone,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type);
	_TAM_Bone_Frame * TAM_Get_Bone_PreviousFrame(unsigned int BoneFrameID,unsigned int BoneID,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type);
	_TAM_Bone_Frame * TAM_Get_Bone_PreviousFrame(unsigned int BoneFrameID,_TAM_Bone * TAM_Bone,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type);

	_TAM_Light_Frame * TAM_Get_Light_Frame(unsigned int LightFrameID,unsigned int LightID,_TAM_Light_Frame_Type TAM_Light_Frame_Type);
	_TAM_Light_Frame * TAM_Get_Light_Frame(unsigned int LightFrameID,_TAM_Light * TAM_Light,_TAM_Light_Frame_Type TAM_Light_Frame_Type);
	_TAM_Light_Frame * TAM_Get_Light_PreviousFrame(unsigned int LightFrameID,unsigned int LightID,_TAM_Light_Frame_Type TAM_Light_Frame_Type);
	_TAM_Light_Frame * TAM_Get_Light_PreviousFrame(unsigned int LightFrameID,_TAM_Light * TAM_Light,_TAM_Light_Frame_Type TAM_Light_Frame_Type);

	_TAM_Bone * TAM_Get_NextBone(unsigned int BoneID);
	_TAM_Bone * TAM_Get_NextBone(_TAM_Bone * TAM_Bone);

	_TAM_Bone * TAM_Get_ChildBone(unsigned int BoneID);
	_TAM_Bone * TAM_Get_ChildBone(_TAM_Bone * TAM_Bone);

	_TAM_File_States TAM_File_States;
	unsigned char * TMA_FileData;
};
#endif