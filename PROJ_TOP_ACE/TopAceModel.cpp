#include "TopAceModel.h"//文件头

CTopAceModel::CTopAceModel(void)
:TAM_File_States(_TAM_File_States_NoRead)
, TAM_FileData(NULL)
, pTAM_FileHead(NULL)
, SuppotVBO(false)
, MeshVBOIDs(NULL)
, isVRAM(false)
, BoneMatrixs(NULL)
, TAM_Bone_FramesTMP(NULL)
, TAM_Light_FramesTMP(NULL)
, TAM_Bone_Tmp(NULL)
, FilePath(NULL)
{
	
}

CTopAceModel::~CTopAceModel(void)
{
	DeleteVRAM();
	if(TAM_FileData)
		_aligned_free(TAM_FileData);
	TAM_FileData = NULL;
	pTAM_FileHead = NULL;

	DeinitTAMBoneMatrixs();
	DeinitTAMMesh();
	if(FilePath)
		delete[] FilePath;
}

bool CTopAceModel::ReadTAMFile(char * FileName)
{
	if(TAM_File_States==_TAM_File_States_ReadOK)
		return false;
	HANDLE   hFile;     
      
	hFile   =   CreateFileA(FileName,                 
                                  GENERIC_READ,                 
                                  FILE_SHARE_READ,                     
                                  NULL,                                  
                                  OPEN_EXISTING,                        
                                  FILE_ATTRIBUTE_NORMAL,       
                                  NULL); 
	if   (hFile   ==   INVALID_HANDLE_VALUE)  
	{
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_NoFile;
		TAM_FileData = NULL;
		return false;
	}

	_TAM_FileHead TAM_FileHeadTMP;
	DWORD Readedsize=0;
	BOOL ReadStates=ReadFile(hFile,&TAM_FileHeadTMP,sizeof(TAM_FileHeadTMP),&Readedsize,NULL);
	if(!ReadStates)
	{
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_NoFile;
		TAM_FileData = NULL;
		return false;
	}
	if(TAM_FileHeadTMP.FileSize<sizeof(TAM_FileHeadTMP))
	{
		TAM_File_States=_TAM_File_States_ReadFail;
		TAM_FileData = NULL;
		CloseHandle(hFile);
		return false;
	}
	TAM_FileData = (unsigned char * ) _aligned_malloc (TAM_FileHeadTMP.FileSize,16);

	Readedsize = 0;
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	ReadStates=ReadFile(hFile,TAM_FileData,TAM_FileHeadTMP.FileSize,&Readedsize,NULL);
	if(!ReadStates)
	{
		DWORD dwError = GetLastError();
		_aligned_free(TAM_FileData);
		TAM_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}
	if(!InitTAMFile(TAM_FileData))
	{
		_aligned_free(TAM_FileData);
		TAM_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}


	CloseHandle(hFile);
	return true;
}
bool CTopAceModel::ReadTAMFile(wchar_t * FileName)
{
	FilePath=new wchar_t[wcslen(FileName)];
	wcscpy_s(FilePath,wcslen(FileName)*sizeof(wchar_t),FileName);
	HANDLE   hFile;     
      
	hFile   =   CreateFileW(FileName,                       //   open   MYFILE.TXT     
                                  GENERIC_READ,                             //   open   for   reading     
                                  FILE_SHARE_READ,                       //   share   for   reading     
                                  NULL,                                             //   no   security     
                                  OPEN_EXISTING,                           //   existing   file   only     
                                  FILE_ATTRIBUTE_NORMAL,           //   normal   file     
                                  NULL);     
	if   (hFile   ==   INVALID_HANDLE_VALUE)  
	{
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_NoFile;
		return false;
	}

	_TAM_FileHead TAM_FileHeadTMP;
	DWORD Readedsize=0;
	BOOL ReadStates=ReadFile(hFile,&TAM_FileHeadTMP,sizeof(TAM_FileHeadTMP),&Readedsize,NULL);
	if(!ReadStates)
	{
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_NoFile;
		TAM_FileData = NULL;
		return false;
	}
	if(TAM_FileHeadTMP.FileSize<sizeof(TAM_FileHeadTMP))
	{
		TAM_File_States=_TAM_File_States_ReadFail;
		TAM_FileData = NULL;
		CloseHandle(hFile);
		return false;
	}
	TAM_FileData = (unsigned char * ) _aligned_malloc (TAM_FileHeadTMP.FileSize,16);

	Readedsize = 0;
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	ReadStates=ReadFile(hFile,TAM_FileData,TAM_FileHeadTMP.FileSize,&Readedsize,NULL);
	if(!ReadStates)
	{
		DWORD dwError = GetLastError();
		_aligned_free(TAM_FileData);
		TAM_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}
	if(!InitTAMFile(TAM_FileData))
	{
		_aligned_free(TAM_FileData);
		TAM_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}


	CloseHandle(hFile);
	return true;
}
bool CTopAceModel::InitTAMFile(unsigned char * TAM_FileData_IN)
{
	if(!TAM_FileData_IN)
		return false;

	_TAM_FileHead  * TAM_FileHead_IN=(_TAM_FileHead*)TAM_FileData_IN;
	pTAM_FileHead=TAM_FileHead_IN;

	if((unsigned int(TAM_FileHead_IN->MeshHeadAddress)!=0xFFFFFFFF)&&(TAM_FileHead_IN->MeshNum)>0)
	{
		TAM_FileHead_IN->MeshHeadAddress=(_TAM_Mesh ** )&TAM_FileData_IN[(int)TAM_FileHead_IN->MeshHeadAddress];
		for (unsigned int i=0;i<TAM_FileHead_IN->MeshNum;i++)
		{
			TAM_FileHead_IN->MeshHeadAddress[i]=(_TAM_Mesh *)(int(TAM_FileHead_IN->MeshHeadAddress[i])+int(TAM_FileData_IN));
			InitTAMMesh(TAM_FileHead_IN->MeshHeadAddress[i]);
		}
	}

	if((unsigned int(TAM_FileHead_IN->MatsAddress)!=0xFFFFFFFF)&&(TAM_FileHead_IN->MatNum>0))
	{
		TAM_FileHead_IN->MatsAddress=(_TAM_Mat * )&TAM_FileData_IN[(int)TAM_FileHead_IN->MatsAddress];
		for (unsigned int i=0;i<TAM_FileHead_IN->MatNum;i++)
		{
			InitTAMMat(&(TAM_FileHead_IN->MatsAddress[i]));
		}
	}

	if((unsigned int(TAM_FileHead_IN->BoneHeadAddress)!=0xFFFFFFFF)&&(TAM_FileHead_IN->BoneNum>0))
	{
		TAM_FileHead_IN->BoneHeadAddress=(_TAM_Bone ** )&TAM_FileData_IN[(int)TAM_FileHead_IN->BoneHeadAddress];
		for (unsigned int i=0;i<TAM_FileHead_IN->BoneNum;i++)
		{
			TAM_FileHead_IN->BoneHeadAddress[i]=(_TAM_Bone *)(int(TAM_FileHead_IN->BoneHeadAddress[i])+int(TAM_FileData_IN));
			InitTAMBone(TAM_FileHead_IN->BoneHeadAddress[i]);
		}
	}

	if((unsigned int(TAM_FileHead_IN->LightHeadAddress)!=0xFFFFFFFF)&&(TAM_FileHead_IN->LightNum>0))
	{
		TAM_FileHead_IN->LightHeadAddress=(_TAM_Light ** )&TAM_FileData_IN[(int)TAM_FileHead_IN->LightHeadAddress];
		for (unsigned int i=0;i<TAM_FileHead_IN->LightNum;i++)
		{
			TAM_FileHead_IN->LightHeadAddress[i]=(_TAM_Light *)(int(TAM_FileHead_IN->LightHeadAddress[i])+int(TAM_FileData_IN));
			InitTAMLight(TAM_FileHead_IN->LightHeadAddress[i]);
		}
	}

	if((unsigned int(TAM_FileHead_IN->CameraAddress)!=0xFFFFFFFF)&&(TAM_FileHead_IN->CameraNum>0))
	{
		TAM_FileHead_IN->CameraAddress=(_TAM_Camera * )&TAM_FileData_IN[(int)TAM_FileHead_IN->CameraAddress];
		for (unsigned int i=0;i<TAM_FileHead_IN->CameraNum;i++)
		{
			InitTAMCamera(&(TAM_FileHead_IN->CameraAddress[i]));
		}
	}
	
	InitTAMBoneMatrixs();
	TAM_File_States = _TAM_File_States_ReadOK;
	return true;
}
bool CTopAceModel::InitTAMMesh(_TAM_Mesh * TAM_MeshData_IN)
{
	if(!((TAM_MeshData_IN->FaceNum>0)&&(TAM_MeshData_IN->vecNum>0)))
		return false;
	TAM_MeshData_IN->vertices=(__m128 *)&TAM_FileData[(int)TAM_MeshData_IN->vertices];
	TAM_MeshData_IN->Normals=(__m128 *)&TAM_FileData[(int)TAM_MeshData_IN->Normals];
	TAM_MeshData_IN->texcos=(float *)&TAM_FileData[(int)TAM_MeshData_IN->texcos];
	TAM_MeshData_IN->Faces=(unsigned int *)&TAM_FileData[(int)TAM_MeshData_IN->Faces];
	TAM_MeshData_IN->vecBoneWeightsAndBoneIDs=(_TAM_vecBoneWeightsAndBoneIDs *)&TAM_FileData[(int)TAM_MeshData_IN->vecBoneWeightsAndBoneIDs];

	if(TAM_MeshData_IN->IsFiexible)
		TAM_MeshData_IN->UserPTR=_aligned_malloc(sizeof(__m128)*TAM_MeshData_IN->vecNum*2,16);
	else
		TAM_MeshData_IN->UserPTR=NULL;
	return true;
}
void CTopAceModel::DeinitTAMMesh()
{
	_TAM_Mesh * pTAM_Mesh_TMP=NULL;
	if(!pTAM_FileHead)
		return;
	for(unsigned int i=0;i<pTAM_FileHead->MeshNum;i++)
	{
		pTAM_Mesh_TMP=pTAM_FileHead->MeshHeadAddress[i];
		if(pTAM_Mesh_TMP->UserPTR)
			_aligned_free(pTAM_Mesh_TMP->UserPTR);
		pTAM_Mesh_TMP->UserPTR=NULL;
	}
}
bool CTopAceModel::InitTAMMat(_TAM_Mat * TAM_MatData_IN)
{
	if(TAM_MatData_IN->Name_diffuseMap[0]!=0)
	{
		TAM_MatData_IN->Tex_diffuse=new _TAM_Mat_Texture;
		//TAM_MatData_IN->Tex_diffuse->Mat_Texture.loadfile
	}
	return true;
}
bool CTopAceModel::InitTAMBone(_TAM_Bone * TAM_BoneData_IN)
{
	for(unsigned int i=0;i<TAM_BoneData_IN->FrameChunkNum;i++)
	{
		if(unsigned int(TAM_BoneData_IN->FramesHeadAddress[i])==0xFFFFFFFF)
			continue;

		TAM_BoneData_IN->FramesHeadAddress[i]=(_TAM_Bone_Frame_Head *)&TAM_FileData[int(TAM_BoneData_IN->FramesHeadAddress[i])];
		if(TAM_BoneData_IN->FramesHeadAddress[i]->TotalFrameNum>0)
		{
			_TAM_Bone_Frame ** TAM_Bone_Frames=(_TAM_Bone_Frame **) &(TAM_BoneData_IN->FramesHeadAddress[i]->FramesAddress);
			for(unsigned int j=0;j<=TAM_BoneData_IN->FramesHeadAddress[i]->MAXFrameNum;j++)
			{
				TAM_Bone_Frames[j]=(_TAM_Bone_Frame *)&TAM_FileData[int(TAM_Bone_Frames[j])];
			}
			_TAM_Bone_Frame * pTAM_Bone_FrameTMP=TAM_Bone_Frames[TAM_BoneData_IN->FramesHeadAddress[i]->MAXFrameNum];
			while(unsigned int(pTAM_Bone_FrameTMP->PreviousFrameAddress)!=0xFFFFFFFF)
			{
				pTAM_Bone_FrameTMP->PreviousFrameAddress=(_TAM_Bone_Frame *)&TAM_FileData[int(pTAM_Bone_FrameTMP->PreviousFrameAddress)];
				pTAM_Bone_FrameTMP=pTAM_Bone_FrameTMP->PreviousFrameAddress;
			}
			if(unsigned int(pTAM_Bone_FrameTMP->PreviousFrameAddress)==0xFFFFFFFF)
			{
				pTAM_Bone_FrameTMP->PreviousFrameAddress=pTAM_Bone_FrameTMP;
			}
		}
	}
	
	return true;
}
void CTopAceModel::InitTAMBoneMatrixs()
{
	if(BoneMatrixs)
		return;
	if(pTAM_FileHead->BoneNum<=0)
		return;
	BoneMatrixs=(__m128 *) _aligned_malloc(4*(pTAM_FileHead->BoneNum+1)*sizeof(__m128),16);

	Easy_matrix_identity(NodeBoneMatrixTMP);
	Easy_matrix_identity(TAM_IdentityMatrix);
	Easy_matrix_identity(BoneMatrixs,pTAM_FileHead->BoneNum+1);
	for(unsigned int i=0;i<pTAM_FileHead->BoneNum;i++)
	{
		TAM_Bone_Tmp=pTAM_FileHead->BoneHeadAddress[i];
		Easy_matrix_transpose(TAM_Bone_Tmp->LocMat);
	}

}
void CTopAceModel::FrameTAMBoneMatrixs(float Frame)
{
	if(!BoneMatrixs)
		return;
	if(pTAM_FileHead->BoneNum<=0)
		return;
	for(unsigned int i=0;i<pTAM_FileHead->BoneNum;i++)
	{
		TAM_Bone_Tmp=pTAM_FileHead->BoneHeadAddress[i];
		GetBoneMatrix(Frame,TAM_Bone_Tmp->BoneID);
	}
	for(TAM_Bone_Tmp=TAM_Get_Bone_Fast1(pTAM_FileHead->RootBoneID);TAM_Bone_Tmp!=NULL;TAM_Bone_Tmp=TAM_Get_Bone_Fast1(TAM_Bone_Tmp->NextBoneID))
	{
		GetNodeMatrixs(TAM_IdentityMatrix,TAM_IdentityMatrix,TAM_Bone_Tmp);
	}
}
void CTopAceModel::GetNodeMatrixs(__m128 * NodeMatrix,__m128 * NodeFirstMatrix,_TAM_Bone * TAM_Bone)
{
	Easy_matrix_mult(NodeBoneMatrixTMPFirst,TAM_Bone->LocMat,NodeFirstMatrix);
	Easy_matrix_mult(NodeBoneMatrixTMP,NodeMatrix,&BoneMatrixs[TAM_Bone->BoneID*4]);
	Easy_matrix_mult(&BoneMatrixs[TAM_Bone->BoneID*4],NodeBoneMatrixTMP,NodeBoneMatrixTMPFirst);
	__m128 NodeBoneMatrixRec[4];
	__m128 NodeBoneMatrixRecFirst[4];
	Easy_matrix_copy(NodeBoneMatrixRec,NodeBoneMatrixTMP);
	Easy_matrix_copy(NodeBoneMatrixRecFirst,NodeBoneMatrixTMPFirst);
	for(_TAM_Bone * TAM_Bone_Child=TAM_Get_Bone_Fast1(TAM_Bone->ChildBoneID);TAM_Bone_Child!=NULL;TAM_Bone_Child=TAM_Get_Bone_Fast1(TAM_Bone_Child->NextBoneID))
		GetNodeMatrixs(NodeBoneMatrixRec,NodeBoneMatrixRecFirst,TAM_Bone_Child);
}

void CTopAceModel::DeinitTAMBoneMatrixs()
{
	if(BoneMatrixs)
	{
		_aligned_free(BoneMatrixs);
		BoneMatrixs=NULL;
	}
}
bool CTopAceModel::InitTAMLight(_TAM_Light * TAM_LightData_IN)
{
	for(unsigned int i=0;i<3;i++)
	{
		if(unsigned int(TAM_LightData_IN->FramesHeadAddress[i])==0xFFFFFFFF)
			continue;
		TAM_LightData_IN->FramesHeadAddress[i]=(_TAM_Light_Frame_Head *)&TAM_FileData[int(TAM_LightData_IN->FramesHeadAddress[i])];
		if(TAM_LightData_IN->FramesHeadAddress[i]->MAXFrameNum>1)
		{
			_TAM_Light_Frame ** TAM_Light_Frames=(_TAM_Light_Frame **)&(TAM_LightData_IN->FramesHeadAddress[i]->FramesAddress);
			for(unsigned int j=0;j<=TAM_LightData_IN->FramesHeadAddress[i]->MAXFrameNum;j++)
				TAM_Light_Frames[j]=(_TAM_Light_Frame *)&TAM_FileData[int(TAM_Light_Frames[j])];
			_TAM_Light_Frame * pTAM_Light_FrameTMP=TAM_Light_Frames[TAM_LightData_IN->FramesHeadAddress[i]->MAXFrameNum];
			while(pTAM_Light_FrameTMP->FrameTime!=0)
			{
				pTAM_Light_FrameTMP->PreviousFrameAddress=(_TAM_Light_Frame *)&TAM_FileData[int(pTAM_Light_FrameTMP->PreviousFrameAddress)];
				pTAM_Light_FrameTMP=pTAM_Light_FrameTMP->PreviousFrameAddress;
			}
			if(pTAM_Light_FrameTMP->FrameTime==0)
			{
				pTAM_Light_FrameTMP->PreviousFrameAddress=pTAM_Light_FrameTMP;
			}
		}
	}
	return true;
}
bool CTopAceModel::InitTAMCamera(_TAM_Camera * TAM_CameraData_IN)
{
	return true;
}
_TAM_Mesh * CTopAceModel::TAM_Get_Mesh(unsigned int MeshID)
{
	if(!MeshID)
		return NULL;
	if(!pTAM_FileHead)
		return NULL;
	if(unsigned int(pTAM_FileHead->MeshHeadAddress)==0xFFFFFFFF)
		return NULL;
	if(pTAM_FileHead->MeshNum<=0)
		return NULL;
	if(pTAM_FileHead->MeshNum<=(MeshID-1))
		return NULL;

	return pTAM_FileHead->MeshHeadAddress[(MeshID-1)];
}

_TAM_Bone * CTopAceModel::TAM_Get_Bone(unsigned int BoneID)
{
	if(!BoneID)
		return NULL;
	if(!pTAM_FileHead)
		return NULL;
	if(unsigned int(pTAM_FileHead->BoneHeadAddress)==0xFFFFFFFF)
		return NULL;
	if(pTAM_FileHead->BoneNum<=0)
		return NULL;
	if(pTAM_FileHead->BoneNum<=(BoneID-1))
		return NULL;

	return pTAM_FileHead->BoneHeadAddress[(BoneID-1)];
}
_TAM_Bone * CTopAceModel::TAM_Get_Bone_Fast1(unsigned int BoneID)
{
	if(!BoneID)
		return NULL;
	return pTAM_FileHead->BoneHeadAddress[(BoneID-1)];
}
_TAM_Light * CTopAceModel::TAM_Get_Light(unsigned int LightID)
{
	if(!LightID)
		return NULL;
	if(!pTAM_FileHead)
		return NULL;
	if(unsigned int(pTAM_FileHead->LightHeadAddress)==0xFFFFFFFF)
		return NULL;
	if(pTAM_FileHead->LightNum<=0)
		return NULL;
	if(pTAM_FileHead->LightNum<=(LightID-1))
		return NULL;

	return pTAM_FileHead->LightHeadAddress[(LightID-1)];
}

_TAM_Bone_Frame * CTopAceModel::TAM_Get_Bone_Frame(unsigned int BoneFrameID,unsigned int BoneID,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type)
{
	return TAM_Get_Bone_Frame(BoneFrameID,TAM_Get_Bone(BoneID),TAM_Bone_Frame_Type);
}
_TAM_Bone_Frame * CTopAceModel::TAM_Get_Bone_Frame(unsigned int BoneFrameID,_TAM_Bone * TAM_Bone,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type)
{
	if(!pTAM_FileHead)
		return NULL;
	if(unsigned int(pTAM_FileHead->BoneHeadAddress)==0xFFFFFFFF)
		return NULL;
	if(pTAM_FileHead->BoneNum<=0)
		return NULL;
	if(!TAM_Bone)
		return NULL;

	if(!TAM_Bone->FramesHeadAddress[TAM_Bone_Frame_Type])
		return NULL;
	if(unsigned int(TAM_Bone->FramesHeadAddress[TAM_Bone_Frame_Type])==0xFFFFFFFF)
		return NULL;
	TAM_Bone_FramesTMP=(_TAM_Bone_Frame **) &(TAM_Bone->FramesHeadAddress[TAM_Bone_Frame_Type]->FramesAddress);
	if(!TAM_Bone_FramesTMP)
		return NULL;
	return TAM_Bone_FramesTMP[min(TAM_Bone->FramesHeadAddress[TAM_Bone_Frame_Type]->MAXFrameNum,BoneFrameID)];
}

_TAM_Light_Frame * CTopAceModel::TAM_Get_Light_Frame(unsigned int LightFrameID,unsigned int LightID,_TAM_Light_Frame_Type TAM_Light_Frame_Type)
{
	return TAM_Get_Light_Frame(LightFrameID,TAM_Get_Light(LightID),TAM_Light_Frame_Type);
}
_TAM_Light_Frame * CTopAceModel::TAM_Get_Light_Frame(unsigned int LightFrameID,_TAM_Light * TAM_Light,_TAM_Light_Frame_Type TAM_Light_Frame_Type)
{
	if(!pTAM_FileHead)
		return NULL;
	if(unsigned int(pTAM_FileHead->LightHeadAddress)==0xFFFFFFFF)
		return NULL;
	if(pTAM_FileHead->LightNum<=0)
		return NULL;
	if(!TAM_Light)
		return NULL;

	TAM_Light_FramesTMP=(_TAM_Light_Frame **) &(TAM_Light->FramesHeadAddress[TAM_Light_Frame_Type]->FramesAddress);
	return TAM_Light_FramesTMP[min(TAM_Light->FramesHeadAddress[TAM_Light_Frame_Type]->MAXFrameNum,LightFrameID)];
}
_TAM_Bone * CTopAceModel::TAM_Get_NextBone(unsigned int BoneID)
{
	return TAM_Get_NextBone(TAM_Get_Bone(BoneID));
}
_TAM_Bone * CTopAceModel::TAM_Get_NextBone(_TAM_Bone * TAM_Bone)
{
	if(TAM_Bone)
		return TAM_Get_Bone(TAM_Bone->NextBoneID);
	else
		return NULL;
}

_TAM_Bone * CTopAceModel::TAM_Get_ChildBone(unsigned int BoneID)
{
	return TAM_Get_ChildBone(TAM_Get_Bone(BoneID));
}
_TAM_Bone * CTopAceModel::TAM_Get_ChildBone(_TAM_Bone * TAM_Bone)
{
	if(TAM_Bone)
		return TAM_Get_Bone(TAM_Bone->ChildBoneID);
	else
		return NULL;
}
bool CTopAceModel::LoadToVRAM(void)
{
	if(!pTAM_FileHead)
		return false;
	if(unsigned int(pTAM_FileHead->MeshHeadAddress)==0xFFFFFFFF)
		return false;
	if(pTAM_FileHead->MeshNum<=0)
		return false;
	if (glewIsSupported("GL_ARB_vertex_buffer_object"))
		SuppotVBO=true;
	else
		SuppotVBO=false;
	if(!SuppotVBO)
		return false;

	MeshVBOIDs= new tMeshVBOID[pTAM_FileHead->MeshNum+2];
	for (unsigned int i=0;i<pTAM_FileHead->MeshNum+2;i++)
	{
		MeshVBOIDs[i].FaceID=0;
		MeshVBOIDs[i].NormalID=0;
		MeshVBOIDs[i].TexCoordID=0;
		MeshVBOIDs[i].VerticeID=0;
	}
	for (unsigned int i=0;i<pTAM_FileHead->MeshNum;i++)
		LoadMeshToVRAM(pTAM_FileHead->MeshHeadAddress[i]);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );

	isVRAM=true;
	return true;
}
bool CTopAceModel::LoadMeshToVRAM(_TAM_Mesh * TAM_Mesh)
{
	if(TAM_Mesh->IsFiexible)
		return false;
	if(unsigned int(TAM_Mesh->vertices)==0xFFFFFFFF)
		return false;
	if(TAM_Mesh->vecNum<=0)
		return false;
	tMeshVBOID * MeshVBOID = &MeshVBOIDs[TAM_Mesh->OBJID];
	glGenBuffersARB( 1,&MeshVBOID->VerticeID);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, MeshVBOID->VerticeID );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, TAM_Mesh->vecNum*sizeof(__m128), TAM_Mesh->vertices, GL_STATIC_DRAW_ARB );

	if((TAM_Mesh->Normals)&&(unsigned int(TAM_Mesh->Normals)!=0xFFFFFFFF))
	{
		glGenBuffersARB( 1,&MeshVBOID->NormalID);
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, MeshVBOID->NormalID );
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, TAM_Mesh->vecNum*sizeof(__m128), TAM_Mesh->Normals, GL_STATIC_DRAW_ARB );
	}

	if((TAM_Mesh->texcos)&&(unsigned int(TAM_Mesh->texcos)!=0xFFFFFFFF))
	{
		glGenBuffersARB( 1,&MeshVBOID->TexCoordID);
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, MeshVBOID->TexCoordID );
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, TAM_Mesh->vecNum*2*sizeof(float), TAM_Mesh->texcos, GL_STATIC_DRAW_ARB );
	}

	glGenBuffersARB( 1,&MeshVBOID->FaceID);
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, MeshVBOID->FaceID );
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, TAM_Mesh->FaceNum*3*sizeof(unsigned int), TAM_Mesh->Faces, GL_STATIC_DRAW_ARB );
	return true;
}
void CTopAceModel::DeleteVRAM()
{
	if(!pTAM_FileHead)
		return ;
	if(unsigned int(pTAM_FileHead->MeshHeadAddress)==0xFFFFFFFF)
		return ;
	if(pTAM_FileHead->MeshNum<=0)
		return ;
	if(!SuppotVBO)
		return ;
	if(!MeshVBOIDs)
		return ;
	if(!isVRAM)
		return ;
	tMeshVBOID * MeshVBOID = NULL;
	for (unsigned int i=0;i<pTAM_FileHead->MeshNum+2;i++)
	{
		MeshVBOID = &MeshVBOIDs[i];
		if(MeshVBOID->VerticeID)
			glDeleteBuffersARB(1,&MeshVBOID->VerticeID);
		if(MeshVBOID->NormalID)
			glDeleteBuffersARB(1,&MeshVBOID->NormalID);
		if(MeshVBOID->TexCoordID)
			glDeleteBuffersARB(1,&MeshVBOID->TexCoordID);
		if(MeshVBOID->FaceID)
			glDeleteBuffersARB(1,&MeshVBOID->FaceID);
	}
	if(MeshVBOIDs)
		delete[] MeshVBOIDs;
	MeshVBOIDs=NULL;
	isVRAM=false;
}
void CTopAceModel::DeleteMeshVRAM(_TAM_Mesh * TAM_Mesh)
{
	tMeshVBOID * MeshVBOID = &MeshVBOIDs[TAM_Mesh->OBJID];
	if(MeshVBOID->VerticeID)
		glDeleteBuffersARB(1,&MeshVBOID->VerticeID);
	if(MeshVBOID->NormalID)
		glDeleteBuffersARB(1,&MeshVBOID->NormalID);
	if(MeshVBOID->TexCoordID)
		glDeleteBuffersARB(1,&MeshVBOID->TexCoordID);
	if(MeshVBOID->FaceID)
		glDeleteBuffersARB(1,&MeshVBOID->FaceID);

}
void CTopAceModel::Draw(void)
{
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	if(!pTAM_FileHead)
		return ;
	if(unsigned int(pTAM_FileHead->MeshHeadAddress)==0xFFFFFFFF)
		return ;
	_TAM_Mesh * TAM_Mesh_Draw=NULL;
	for(unsigned int i=0;i<pTAM_FileHead->MeshNum;i++)
	{
		TAM_Mesh_Draw=pTAM_FileHead->MeshHeadAddress[i];
		if(TAM_Mesh_Draw)
		{
			
			if(TAM_Mesh_Draw->IsFiexible)
			{
				DrawRAMMeshFiexible(TAM_Mesh_Draw);
			}
			else
			{
				if(TAM_Mesh_Draw->BoneWeightNum>0)
				{
					glGetFloatv(GL_MODELVIEW_MATRIX,(float *)&NodeBoneMatrixTMP[0]);
					if(TAM_Mesh_Draw->FaceNum>0)
					glMultMatrixf((float *)&BoneMatrixs[(TAM_Mesh_Draw->vecBoneWeightsAndBoneIDs[0].vecBoneIDs[0])*4]);
				}
				
				if(SuppotVBO)
					DrawMeshRigid(TAM_Mesh_Draw);
				else
					DrawRAMMeshRigid(TAM_Mesh_Draw);
				if(TAM_Mesh_Draw->BoneWeightNum>0)
					glLoadMatrixf((float *)&NodeBoneMatrixTMP[0]);
			}
		}
	}

	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );
	glEnable(GL_CULL_FACE);
}
void CTopAceModel::DrawRAM(void)
{
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	if(!pTAM_FileHead)
		return ;
	if(unsigned int(pTAM_FileHead->MeshHeadAddress)==0xFFFFFFFF)
		return ;
	_TAM_Mesh * TAM_Mesh_Draw=NULL;
	for(unsigned int i=0;i<pTAM_FileHead->MeshNum;i++)
	{
		TAM_Mesh_Draw=pTAM_FileHead->MeshHeadAddress[i];
		if(TAM_Mesh_Draw)
		{
			if(TAM_Mesh_Draw->IsFiexible)
				DrawRAMMeshFiexible(TAM_Mesh_Draw);
			else
				DrawRAMMeshRigid(TAM_Mesh_Draw);
		}
	}
	glEnable(GL_CULL_FACE);
}
bool CTopAceModel::DrawMeshRigid(_TAM_Mesh * TAM_Mesh)
{
	if(TAM_Mesh->vecNum==0)
		return false;
	tMeshVBOID * MeshVBOID = &MeshVBOIDs[TAM_Mesh->OBJID];
	if((MeshVBOID->FaceID==0)||(MeshVBOID->VerticeID==0))
		return false;
	if(TAM_Mesh->OBJMATID)
	{
		/*_TAM_Mat * TAM_Mat_Tmp=&(pTAM_FileHead->MatsAddress[TAM_Mesh->OBJMATID-1]);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,MatInt8toFloat(&(TAM_Mat_Tmp->specular[0])));
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,MatInt8toFloat(&(TAM_Mat_Tmp->ambient[0])));
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MatInt8toFloat(&(TAM_Mat_Tmp->diffuse[0])));
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,MatInt8toFloat(&(TAM_Mat_Tmp->self_illum[0])));
		MatTmp[0]=pow(2, 10 * TAM_Mat_Tmp->specularLv - 1)*10.0f;
		glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,MatTmp);*/
		/*MatTmp[0]=1.0f/float(TAM_Mat_Tmp->specular[0]);
		MatTmp[1]=1.0f/float(TAM_Mat_Tmp->specular[1]);
		MatTmp[2]=1.0f/float(TAM_Mat_Tmp->specular[2]);
		MatTmp[3]=1.0f/float(TAM_Mat_Tmp->specular[3]);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,MatTmp);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,TAM_Mat_Tmp->ambient);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,ModelNode.mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,ModelNode.mat_emission);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,&ModelNode.mat_shininess);*/
	}

	glBindTexture(GL_TEXTURE_2D, 1);

	glEnableClientState( GL_VERTEX_ARRAY );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, MeshVBOID->VerticeID );
	glVertexPointer( 3, GL_FLOAT, 16, 0 );

	if((TAM_Mesh->Normals)&&(unsigned int(TAM_Mesh->Normals)!=0xFFFFFFFF))
	{
		glEnableClientState( GL_NORMAL_ARRAY );
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, MeshVBOID->NormalID );
		glNormalPointer( GL_FLOAT, 16, 0 );
	}
	if((TAM_Mesh->texcos)&&(unsigned int(TAM_Mesh->texcos)!=0xFFFFFFFF))
	{
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, MeshVBOID->TexCoordID );
		glTexCoordPointer( 2, GL_FLOAT, 0, 0 );
	}

	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, MeshVBOID->FaceID );
	glDrawElements(GL_TRIANGLES,TAM_Mesh->FaceNum*3,GL_UNSIGNED_INT,0);

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	return true;
}
bool CTopAceModel::DrawRAMMeshRigid(_TAM_Mesh * TAM_Mesh)
{
	if(TAM_Mesh->vecNum==0)
		return false;
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBindTexture(GL_TEXTURE_2D, 1);
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 16, (float*)&(TAM_Mesh->vertices[0].m128_f32[0]) );
	if((TAM_Mesh->Normals)&&(unsigned int(TAM_Mesh->Normals)!=0xFFFFFFFF))
	{
		glEnableClientState( GL_NORMAL_ARRAY );
		glNormalPointer( GL_FLOAT, 16, (float*)&(TAM_Mesh->Normals[0].m128_f32[0]) );
	}
	if((TAM_Mesh->texcos)&&(unsigned int(TAM_Mesh->texcos)!=0xFFFFFFFF))
	{
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glTexCoordPointer( 2, GL_FLOAT, 0, TAM_Mesh->texcos );
	}
	glDrawElements(GL_TRIANGLES,TAM_Mesh->FaceNum*3,GL_UNSIGNED_INT,(GLvoid*)&(TAM_Mesh->Faces[0]));
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );

	return true;
}

bool CTopAceModel::DrawRAMMeshFiexible(_TAM_Mesh * TAM_Mesh)
{
	glPointSize(2.0f);
	if(TAM_Mesh->vecNum==0)
		return false;
	int j=0;
	pDrawRAMMeshFiexibleDSTTMP=(__m128 *)TAM_Mesh->UserPTR;
	bool testbone=false;
	for(unsigned int i=0;i<TAM_Mesh->vecNum;i++)
	{
		DrawRAMMeshFiexibleTMPvec=TAM_Mesh->vertices[i];
		DrawRAMMeshFiexibleTMPnol=TAM_Mesh->Normals[i];

		TAM_vecBoneWeightsAndBoneIDsTMP=TAM_Mesh->vecBoneWeightsAndBoneIDs[i];
		
		pDrawRAMMeshFiexibleDSTTMP[i]=IdentityMatrix3;
		pDrawRAMMeshFiexibleDSTTMP[i+TAM_Mesh->vecNum]=_mm_set_ps1(0.0f);

		for(j=0;j<min(TAM_Mesh->BoneWeightNum,4);j++)
		{
			if(TAM_vecBoneWeightsAndBoneIDsTMP.vecBoneWeights[j]<=0.0f)
				continue;
			Easy_matrix_mult_vector3X3(
				&DrawRAMMeshFiexibleTMPvec2,
				&BoneMatrixs[TAM_vecBoneWeightsAndBoneIDsTMP.vecBoneIDs[j]*4],
				DrawRAMMeshFiexibleTMPvec
				);
			Easy_matrix_mult_Normal3X3(
				&DrawRAMMeshFiexibleTMPnol2,
				&BoneMatrixs[TAM_vecBoneWeightsAndBoneIDsTMP.vecBoneIDs[j]*4],
				DrawRAMMeshFiexibleTMPnol
				);
			if(TAM_vecBoneWeightsAndBoneIDsTMP.vecBoneWeights[j]<1.0f)
			{
				Easy_vector_scalar_mul(
					&DrawRAMMeshFiexibleTMPvec2,
					DrawRAMMeshFiexibleTMPvec2,
					TAM_vecBoneWeightsAndBoneIDsTMP.vecBoneWeights[j]
					);
				Easy_vector_scalar_mul(
					&DrawRAMMeshFiexibleTMPnol2,
					DrawRAMMeshFiexibleTMPnol2,
					TAM_vecBoneWeightsAndBoneIDsTMP.vecBoneWeights[j]
					);
			}
			Easy_vector_add(
				&pDrawRAMMeshFiexibleDSTTMP[i],
				pDrawRAMMeshFiexibleDSTTMP[i],
				DrawRAMMeshFiexibleTMPvec2
				);
			Easy_vector_add(
				&pDrawRAMMeshFiexibleDSTTMP[i+TAM_Mesh->vecNum],
				pDrawRAMMeshFiexibleDSTTMP[i+TAM_Mesh->vecNum],
				DrawRAMMeshFiexibleTMPnol2
				);
		}
		
		pDrawRAMMeshFiexibleDSTTMP[i].m128_f32[3]=1.0f;
		pDrawRAMMeshFiexibleDSTTMP[i+TAM_Mesh->vecNum].m128_f32[3]=0.0f;
		Easy_vector_normalize(&pDrawRAMMeshFiexibleDSTTMP[i+TAM_Mesh->vecNum],pDrawRAMMeshFiexibleDSTTMP[i+TAM_Mesh->vecNum]);
		


	}
	glColor3f(1.0f,1.0f,1.0f);
	glBindTexture(GL_TEXTURE_2D, 1);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 16, (float*)&(pDrawRAMMeshFiexibleDSTTMP[0].m128_f32[0]) );
	if((TAM_Mesh->Normals)&&(unsigned int(TAM_Mesh->Normals)!=0xFFFFFFFF))
	{
		glEnableClientState( GL_NORMAL_ARRAY );
		glNormalPointer( GL_FLOAT, 16, (float*)&(pDrawRAMMeshFiexibleDSTTMP[TAM_Mesh->vecNum].m128_f32[0]) );
	}
	if((TAM_Mesh->texcos)&&(unsigned int(TAM_Mesh->texcos)!=0xFFFFFFFF))
	{
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glTexCoordPointer( 2, GL_FLOAT, 0, TAM_Mesh->texcos );
	}
	glDrawElements(GL_TRIANGLES,TAM_Mesh->FaceNum*3,GL_UNSIGNED_INT,(GLvoid*)&(TAM_Mesh->Faces[0]));
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	return true;
}

void CTopAceModel::GetBoneMatrix(float Frame,unsigned int BoneID)
{
	if(!BoneMatrixs)
		return;

	GetBoneMatrix_BonePos=IdentityMatrix3;
	GetlinearBoneFrameData(TAM_Get_Bone_Frame(unsigned int(Frame)+1,BoneID,_TAM_Bone_Frame_Type_Translate),&GetBoneMatrix_BonePos,Frame);
	if(GetSlerpBoneFrameData(TAM_Get_Bone_Frame(unsigned int(Frame)+1,BoneID,_TAM_Bone_Frame_Type_Rotate),&GetBoneMatrix_BoneRot,Frame))
	{
		
		Easy_quat_normalize(&GetBoneMatrix_BoneRot,GetBoneMatrix_BoneRot);
		Easy_quat_to_matrix(&BoneMatrixs[BoneID*4],GetBoneMatrix_BoneRot);
		Easy_matrix_translate_External(&BoneMatrixs[BoneID*4],GetBoneMatrix_BonePos);
	}
	else
	{
		Easy_matrix_identity(&BoneMatrixs[BoneID*4]);
		Easy_matrix_translate_External(&BoneMatrixs[BoneID*4],GetBoneMatrix_BonePos);
	}
	if(GetlinearBoneFrameData(TAM_Get_Bone_Frame(unsigned int(Frame)+1,BoneID,_TAM_Bone_Frame_Type_Scale),&GetBoneMatrix_BoneSca,Frame))
		Easy_matrix_scale(&BoneMatrixs[BoneID*4],GetBoneMatrix_BoneSca);	

}
void QuatSlerp(const __m128 from, const __m128 to, float frac, __m128 * out)
{
	float           cosom, absCosom, sinom, sinSqr, omega, scale0, scale1;
	cosom = from.m128_f32[0] * to.m128_f32[0] + from.m128_f32[1] * to.m128_f32[1] + from.m128_f32[2] * to.m128_f32[2] + from.m128_f32[3] * to.m128_f32[3];
	absCosom = fabs(cosom);

	if((1.0f - absCosom) > 1e-6f)
	{
		sinSqr = 1.0f - absCosom * absCosom;
		sinom = 1.0f / sqrt(sinSqr);
		omega = atan2(sinSqr * sinom, absCosom);

		scale0 = sin((1.0f - frac) * omega) * sinom;
		scale1 = sin(frac * omega) * sinom;
	}
	else
	{
		scale0 = 1.0f - frac;
		scale1 = frac;
	}

	scale1 = (cosom >= 0.0f) ? scale1 : -scale1;

	out->m128_f32[0] = scale0 * from.m128_f32[0] + scale1 * to.m128_f32[0];
	out->m128_f32[1] = scale0 * from.m128_f32[1] + scale1 * to.m128_f32[1];
	out->m128_f32[2] = scale0 * from.m128_f32[2] + scale1 * to.m128_f32[2];
	out->m128_f32[3] = scale0 * from.m128_f32[3] + scale1 * to.m128_f32[3];
}
bool CTopAceModel::GetlinearBoneFrameData(_TAM_Bone_Frame * TAM_Bone_FrameFront,__m128 * linearFrameData,float Frame)
{
	if(!TAM_Bone_FrameFront)
		return false;
	if ((int(TAM_Bone_FrameFront)==int(TAM_Bone_FrameFront->PreviousFrameAddress))||(unsigned int(Frame)>=TAM_Bone_FrameFront->FrameTime))
	{
		Easy_vector_copy(linearFrameData,TAM_Bone_FrameFront->FrameData);
	}
	else
	{

		Easy_quat_Mix(
			linearFrameData,
			TAM_Bone_FrameFront->FrameData,
			TAM_Bone_FrameFront->PreviousFrameAddress->FrameData,
			( Frame - float ( TAM_Bone_FrameFront->PreviousFrameAddress->FrameTime ) ) / float( TAM_Bone_FrameFront->FrameTime - TAM_Bone_FrameFront->PreviousFrameAddress->FrameTime )
			);

	}
	return true;

}

bool CTopAceModel::GetSlerpBoneFrameData(_TAM_Bone_Frame * TAM_Bone_FrameFront,__m128 * SlerpFrameData,float Frame)
{
	if(!TAM_Bone_FrameFront)
		return false;
	if ((int(TAM_Bone_FrameFront)==int(TAM_Bone_FrameFront->PreviousFrameAddress))||(unsigned int(Frame)>=TAM_Bone_FrameFront->FrameTime))
	{
		Easy_vector_copy(SlerpFrameData,TAM_Bone_FrameFront->FrameData);
	}
	else
	{
		QuatSlerp(
			TAM_Bone_FrameFront->PreviousFrameAddress->FrameData,
			TAM_Bone_FrameFront->FrameData,
			( Frame - float ( TAM_Bone_FrameFront->PreviousFrameAddress->FrameTime ) ) / float( TAM_Bone_FrameFront->FrameTime - TAM_Bone_FrameFront->PreviousFrameAddress->FrameTime ),
			SlerpFrameData
			);
	}
	return true;

}
