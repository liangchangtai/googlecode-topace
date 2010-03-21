#include "TopAceModel.h"//文件头

CTopAceModel::CTopAceModel(void)
:TAM_File_States(_TAM_File_States_NoRead)
, TMA_FileData(NULL)
{
}

CTopAceModel::~CTopAceModel(void)
{
	if(TMA_FileData)
		_aligned_free(TMA_FileData);
	TMA_FileData = NULL;
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
		TMA_FileData = NULL;
		return false;
	}

	_TAM_FileHead TAM_FileHead;
	DWORD Readedsize=0;
	BOOL ReadStates=ReadFile(hFile,&TAM_FileHead,sizeof(TAM_FileHead),&Readedsize,NULL);
	if(!ReadStates)
	{
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_NoFile;
		TMA_FileData = NULL;
		return false;
	}
	if(TAM_FileHead.FileSize<sizeof(TAM_FileHead))
	{
		TAM_File_States=_TAM_File_States_ReadFail;
		TMA_FileData = NULL;
		CloseHandle(hFile);
		return false;
	}
	TMA_FileData = (unsigned char * ) _aligned_malloc (TAM_FileHead.FileSize,16);

	Readedsize = 0;
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	ReadStates=ReadFile(hFile,TMA_FileData,TAM_FileHead.FileSize,&Readedsize,NULL);
	if(!ReadStates)
	{
		DWORD dwError = GetLastError();
		_aligned_free(TMA_FileData);
		TMA_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}
	if(!ReadTAMFile_After(TMA_FileData))
	{
		_aligned_free(TMA_FileData);
		TMA_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}


	CloseHandle(hFile);
	return true;
}
bool CTopAceModel::ReadTAMFile(wchar_t * FileName)
{
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

	_TAM_FileHead TAM_FileHead;
	DWORD Readedsize=0;
	BOOL ReadStates=ReadFile(hFile,&TAM_FileHead,sizeof(TAM_FileHead),&Readedsize,NULL);
	if(!ReadStates)
	{
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_NoFile;
		TMA_FileData = NULL;
		return false;
	}
	if(TAM_FileHead.FileSize<sizeof(TAM_FileHead))
	{
		TAM_File_States=_TAM_File_States_ReadFail;
		TMA_FileData = NULL;
		CloseHandle(hFile);
		return false;
	}
	TMA_FileData = (unsigned char * ) _aligned_malloc (TAM_FileHead.FileSize,16);

	Readedsize = 0;
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	ReadStates=ReadFile(hFile,TMA_FileData,TAM_FileHead.FileSize,&Readedsize,NULL);
	if(!ReadStates)
	{
		DWORD dwError = GetLastError();
		_aligned_free(TMA_FileData);
		TMA_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}
	if(!ReadTAMFile_After(TMA_FileData))
	{
		_aligned_free(TMA_FileData);
		TMA_FileData = NULL;
		CloseHandle(hFile);
		TAM_File_States=_TAM_File_States_ReadFail;
		return false;
	}


	CloseHandle(hFile);
	return true;
}
bool CTopAceModel::ReadTAMFile_After(unsigned char * TAM_FileData_IN)
{
	if(!TAM_FileData_IN)
		return false;
	_TAM_FileHead  * TAM_FileHead_IN=(_TAM_FileHead*)TAM_FileData_IN;
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

	TAM_FileHead_IN->LightHeadAddress=(_TAM_Light_Head * )&TAM_FileData_IN[(int)TAM_FileHead_IN->LightHeadAddress];
	TAM_FileHead_IN->CameraAddress=(_TAM_Camera * )&TAM_FileData_IN[(int)TAM_FileHead_IN->CameraAddress];
/*
	//_TAM_Mesh ** OBJAddressTMP=NULL;
	//OBJAddressTMP=(_TAM_Mesh **)(TAM_FileHead_IN->MeshHeadAddress);
	for (int i=0;i<TAM_FileHead_IN->MeshNum;i++)
	{
		//TAM_FileHead_IN->MeshHeadAddress[i]=(_TAM_Mesh *)&TAM_FileData_IN[int(TAM_FileHead_IN->MeshHeadAddress[i])];
		TAM_FileHead_IN->MeshHeadAddress[i]=(_TAM_Mesh *)(int(TAM_FileHead_IN->MeshHeadAddress[i])+int(TAM_FileData_IN));
		int sererwer=12132;
	}
	_TAM_Mesh * TTT_TAM_Mesh=TAM_FileHead_IN->MeshHeadAddress[0];
	*/
	return true;
}
bool CTopAceModel::InitTAMMesh(_TAM_Mesh * TAM_MeshData_IN)
{
	if(!((TAM_MeshData_IN->FaceNum>0)&&(TAM_MeshData_IN->vecNum>0)))
		return false;
	TAM_MeshData_IN->vertices=(__m128 *)&TMA_FileData[(int)TAM_MeshData_IN->vertices];
	TAM_MeshData_IN->Normals=(__m128 *)&TMA_FileData[(int)TAM_MeshData_IN->Normals];
	TAM_MeshData_IN->texcos=(float *)&TMA_FileData[(int)TAM_MeshData_IN->texcos];
	TAM_MeshData_IN->Faces=(unsigned int *)&TMA_FileData[(int)TAM_MeshData_IN->Faces];

	//__m128 tmptest=TAM_MeshData_IN->vertices[0];
	return true;
}

bool CTopAceModel::InitTAMMat(_TAM_Mat * TAM_MatData_IN)
{
	return true;
}
bool CTopAceModel::InitTAMBone(_TAM_Bone * TAM_BoneData_IN)
{
	for(unsigned int i=0;i<TAM_BoneData_IN->FrameChunkNum;i++)
	{
		if(unsigned int(TAM_BoneData_IN->FramesHeadAddress[i])==0xFFFFFFFF)
			continue;

		TAM_BoneData_IN->FramesHeadAddress[i]=(_TAM_Bone_Frame_Head *)&TMA_FileData[int(TAM_BoneData_IN->FramesHeadAddress[i])];
		if(TAM_BoneData_IN->FramesHeadAddress[i]->MAXFrameNum>1)
		{
			_TAM_Bone_Frame ** TAM_Bone_Frames=(_TAM_Bone_Frame **) &(TAM_BoneData_IN->FramesHeadAddress[i]->FramesAddress);
			for(unsigned int j=0;j<=TAM_BoneData_IN->FramesHeadAddress[i]->MAXFrameNum;j++)
				TAM_Bone_Frames[j]=(_TAM_Bone_Frame *)&TMA_FileData[int(TAM_Bone_Frames[j])];
			_TAM_Bone_Frame * pTAM_Bone_FrameTMP=TAM_Bone_Frames[TAM_BoneData_IN->FramesHeadAddress[i]->MAXFrameNum];
			while(pTAM_Bone_FrameTMP->FrameTime!=0)
			{
				pTAM_Bone_FrameTMP->PreviousFrameAddress=(_TAM_Bone_Frame *)&TMA_FileData[int(pTAM_Bone_FrameTMP->PreviousFrameAddress)];
				pTAM_Bone_FrameTMP=pTAM_Bone_FrameTMP->PreviousFrameAddress;
			}
			if(pTAM_Bone_FrameTMP->FrameTime==0)
			{
				pTAM_Bone_FrameTMP->PreviousFrameAddress=pTAM_Bone_FrameTMP;
			}
		}
	}
	return true;
}

_TAM_Mesh * CTopAceModel::TAM_Get_Mesh(unsigned int MeshID)
{
	return NULL;
}

_TAM_Bone * CTopAceModel::TAM_Get_Bone(unsigned int BoneID)
{
	return NULL;
}

_TAM_Light * CTopAceModel::TAM_Get_Light(unsigned int LightID)
{
	return NULL;
}

_TAM_Bone_Frame * CTopAceModel::TAM_Get_Bone_Frame(unsigned int BoneFrameID,unsigned int BoneID,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type)
{
	return NULL;
}
_TAM_Bone_Frame * CTopAceModel::TAM_Get_Bone_Frame(unsigned int BoneFrameID,_TAM_Bone * TAM_Bone,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type)
{
	return NULL;
}
_TAM_Bone_Frame * CTopAceModel::TAM_Get_Bone_PreviousFrame(unsigned int BoneFrameID,unsigned int BoneID,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type)
{
	return NULL;
}
_TAM_Bone_Frame * CTopAceModel::TAM_Get_Bone_PreviousFrame(unsigned int BoneFrameID,_TAM_Bone * TAM_Bone,_TAM_Bone_Frame_Type TAM_Bone_Frame_Type)
{
	return NULL;
}

_TAM_Light_Frame * CTopAceModel::TAM_Get_Light_Frame(unsigned int LightFrameID,unsigned int LightID,_TAM_Light_Frame_Type TAM_Light_Frame_Type)
{
	return NULL;
}
_TAM_Light_Frame * CTopAceModel::TAM_Get_Light_Frame(unsigned int LightFrameID,_TAM_Light * TAM_Light,_TAM_Light_Frame_Type TAM_Light_Frame_Type)
{
	return NULL;
}
_TAM_Light_Frame * CTopAceModel::TAM_Get_Light_PreviousFrame(unsigned int LightFrameID,unsigned int LightID,_TAM_Light_Frame_Type TAM_Light_Frame_Type)
{
	return NULL;
}
_TAM_Light_Frame * CTopAceModel::TAM_Get_Light_PreviousFrame(unsigned int LightFrameID,_TAM_Light * TAM_Light,_TAM_Light_Frame_Type TAM_Light_Frame_Type)
{
	return NULL;
}

_TAM_Bone * CTopAceModel::TAM_Get_NextBone(unsigned int BoneID)
{
	return NULL;
}
_TAM_Bone * CTopAceModel::TAM_Get_NextBone(_TAM_Bone * TAM_Bone)
{
	return NULL;
}

_TAM_Bone * CTopAceModel::TAM_Get_ChildBone(unsigned int BoneID)
{
	return NULL;
}
_TAM_Bone * CTopAceModel::TAM_Get_ChildBone(_TAM_Bone * TAM_Bone)
{
	return NULL;
}




