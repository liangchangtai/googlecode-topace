﻿//#pragma once
#ifndef _LOAD3DS_H
#define _LOAD3DS_H
#include <gl\glew.h>
#include <lib3ds.h>
#include"Textures.h"
#include "EasyMatrix.h"
#define NO_ERROR_3DS 0
#define ERROR_NOT_OPEN_FILE 1
#define ERROR_NO_MESH 2

#define TYPE_3DS_NODE_DM 1//不渲染
#define TYPE_3DS_NODE_CX 2//俯仰
#define TYPE_3DS_NODE_CY 3//左右
#define TYPE_3DS_NODE_CZ 4//侧翻
#define TYPE_3DS_NODE_EN 5//引擎推力
#define TYPE_3DS_NODE_AB 6//减速板
#define TYPE_3DS_NODE_WP 7//起落架
#define TYPE_3DS_NODE_WW 8//起落架盖
#define TYPE_3DS_NODE_SP 9//特殊
#define TYPE_3DS_NODE_GR 10//透明
#define TYPE_3DS_NODE_MH 11//导弹仓门
#define MAX_TYPE_3DS_NODE 12
struct tModelNodes
{
	unsigned int VerticeID;
	unsigned int ColorID;
	unsigned int TexCoordID;
	unsigned int NormalID;
	unsigned int TangentID;
	int VerticeNum;
	float MeshMatrix[4][4];
	float FrameMatrix[4][4];

	int MaterialID;
	bool UseMaterial;
	bool NodeType[MAX_TYPE_3DS_NODE];
	float mat_specular[4];
	float mat_ambient[4];
	float mat_diffuse[4];
	float mat_emission[4];
	float mat_shininess;
};
struct tLightNodes
{
	//bool isSpot;
	__m128 LightWorldPos;
	__m128 LightEyePos;
	__m128 LightColor;
	__m128 Attenuation;//constant,linear,quadratic,multiplier
	__m128 SpotTGTEyePos;
	__m128 SpotTGTWorldPos;
	__m128 SpotEyeDirection;
	__m128 SpotSet;//CutOff,hotspot,falloff,Exponent
	//char LightName[64];

};
class CLoad3DS
{
public:
	CLoad3DS(void);
	~CLoad3DS(void);
	bool Loadfile(char * filename);
	bool LoadToVRAM(void);
	void inline Del_RAM(void);
	void inline Del_VRAM(void);
	bool isRAM;
	bool isVRAM;
	bool VBOSupported;
	Lib3dsFile *Model3ds;
	int TotelVertices;
	int TotelMeshs;
	tModelNodes * VBOIDs;
	void Render();
	void RenderNoColor();
	void RenderNode(Lib3dsNode *Node,bool isTranslucent=false);
	void RenderNodeNoColor(Lib3dsNode *Node);
	bool LoadNode(Lib3dsNode *Node);
	int Error;
	int MeshLoadNum;
	void inline Clear3DSIDs(Lib3dsNode *Node);
	void inline GetNodeType(int NodeID,const char * NodeName);
	float TypeFrame[MAX_TYPE_3DS_NODE];
	bool TypeFrameStats[MAX_TYPE_3DS_NODE];
	Textures * TextureMap;
	int TextureMapNum;
	void inline LoadTexToRam(int TexID,char * FilePath);
	void inline loadTex(char * filename);

	void MultCameraMatrix();
	void inline RenderNodeMesh(tModelNodes ModelNode);
	void inline RenderNodeMeshNoColor(tModelNodes ModelNode);
	void inline MeshNodeEval(Lib3dsNode *Node,float Frame);
	void ModelMatrix(float NodesFrameIn[MAX_TYPE_3DS_NODE],float test_frame=0.0f);
	void NodeMatrix(Lib3dsNode *Node);
	void CameraNodeEval(Lib3dsNode *Node,float Frame=0.0f);
	void CameraTGTNodeEval(Lib3dsNode *Node,float Frame=0.0f);

	__m128 ModelRootMatrix[4];
	void OmniLightNodeEval(Lib3dsNode *Node,float Frame=0.0f);
	void SpotLightNodeEval(Lib3dsNode *Node,float Frame=0.0f);
	void SpotLightTGTNodeEval(Lib3dsNode *Node,float Frame=0.0f);

//	__m128 OmniLightPos[2];
	void SetLightsPos(int lightBase=0);
	tLightNodes * OmniLightNodes;
	tLightNodes * SpotLightNodes;

	__m128 ModelAmbientLightColot;
	int OmniLightNum;
	int SpotLightNum;
	void InitLight(void);
	bool OnlySelfIllum;
};

#endif