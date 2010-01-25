//#pragma once
#ifndef _LOAD3DS_H
#define _LOAD3DS_H
#include <gl\glew.h>
#include <lib3ds.h>
#include"Textures.h"
#define NO_ERROR_3DS 0
#define ERROR_NOT_OPEN_FILE 1
#define ERROR_NO_MESH 2
#define MAX_TYPE_3DS_NODE 64
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
struct tModelNodes
{
	unsigned int VerticeID;
	unsigned int ColorID;
	unsigned int TexCoordID;
	unsigned int NormalID;
	unsigned int TangentID;
	int VerticeNum;
	float MeshMatrix[4][4];

	int MaterialID;
	bool UseMaterial;
	bool NodeType[MAX_TYPE_3DS_NODE];
	float mat_specular[4];
	float mat_ambient[4];
	float mat_diffuse[4];
	float mat_shininess;
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
	void Render(float current_frame=0.0f);
	void RenderNode(Lib3dsNode *Node,bool isTranslucent=false);
	bool LoadNode(Lib3dsNode *Node);
	int Error;
	int MeshLoadNum;
	void inline Clear3DSIDs(Lib3dsNode *Node);
	void inline GetNodeType(int NodeID,const char * NodeName);
	float TypeFrame[MAX_TYPE_3DS_NODE];
	Textures * TextureMap;
	int TextureMapNum;
	void inline LoadTexToRam(int TexID,char * FilePath);
	void inline loadTex(char * filename);

	void inline CameraMatrix(float Frame);
	void inline RenderNodeMesh(tModelNodes ModelNode);
};

#endif