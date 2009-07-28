#ifndef HGL_FILE_INCLUDE
#define HGL_FILE_INCLUDE

namespace hgl
{
	wchar_t *MergeFilename(const wchar_t *,const wchar_t *);										///<���·�������ļ���
	bool MergeFilename(wchar_t *,int,const wchar_t *,const wchar_t *);								///<���·�������ļ���

	bool FileCopy(const wchar_t *,const wchar_t *);                                                 ///<�ļ�����
	bool FileDelete(const wchar_t *);                                                               ///<�ļ�ɾ��
	bool FileMove(const wchar_t *,const wchar_t *);                                                 ///<�ļ��ƶ�
	bool FileRename(const wchar_t *,const wchar_t *);                                               ///<�ļ�����
	bool FileFind(const wchar_t *);                                                                 ///<�ļ�����
	bool FileComp(const wchar_t *,const wchar_t *);                                                 ///<�ļ��Ƚ�

	bool FileCheckOpen(const wchar_t *);															///<���Դ��ļ�
	bool FileCheckOpen(const wchar_t *,const wchar_t *);											///<���Դ��ļ�

	int LoadFileToMemory(const wchar_t *,void **);                                                  ///<����һ���ļ����ڴ�
	bool SaveMemoryToFile(const wchar_t *,void *,int);                                              ///<����һ���ڴ���ļ�

	void *LoadFileToMemory(const wchar_t *,unsigned int,unsigned int,void *buf=0);					///<����һ���ļ���һ���ֵ��ڴ�
	bool SaveMemoryToFile(const wchar_t *,unsigned int,unsigned int,void *);						///<����һ���ڴ浽һ���ļ�

	bool IsDirectory(const wchar_t *);                                                              ///<�ж���������Ƿ���Ŀ¼

	bool MakePath(const wchar_t *);                                                                 ///<����һ��·��
	bool DeletePath(const wchar_t *);                                                               ///<ɾ��һ��·��
	void DeleteTree(const wchar_t *);																///<ɾ��һ��·��(���������ļ�)
	void GetCurrentPath(wchar_t *);                                                                 ///<ȡ��ǰ·��

	/**
	* �ļ���Ϣ���ݽṹ
	*/
	struct FileInfo								///�ļ���Ϣ
	{
		wchar_t name[1024];						///<�ļ���(������·��)
		wchar_t fullname[1024];					///<��������(����·��)

		union
		{
			unsigned __int64 size;				///<�ļ�����

			struct
			{                                                           
				unsigned __int32 size_low;		///<�ļ����ȵ�32λ      
				unsigned __int32 size_high;		///<�ļ����ȸ�32λ
			};
		};

		union
		{
			unsigned __int32 attrib;			///<�ļ�����

			struct
			{
				bool directory:1;				///<��Ŀ¼
				bool only_read:1;				///<��ֻ��
			};
		};
	};
                   
	/**
	* ö��һ��Ŀ¼�ڵ������ļ�
	* @param folder_name Ŀ¼����
	* @param find_name ����������
	* @param data �Զ���ش�����
	* @param proc_folder ����Ŀ¼
	* @param proc_file �����ļ�
	* @param func �ص�����
	* @return ���ҵ��ļ�����,-1��ʾʧ��
	*/
	int EnumFile(const wchar_t *folder_name,const wchar_t *find_name,void *data,bool proc_folder,bool proc_file,void (__cdecl *func)(void *,hgl::FileInfo &));

	/**
	* ö��һ��Ŀ¼�ڵ������ļ�
	* @param folder_name Ŀ¼����
	* @param find_name ����������
	* @param data �Զ���ش�����
	* @param func �ص�����
	* @return ���ҵ��ļ�����,-1��ʾʧ��
	*/
	int EnumFile(const wchar_t *folder_name,const wchar_t *find_name,void *data,void (__cdecl *func)(void *,hgl::FileInfo &));

	/**
	* ����Ϣ���ݽṹ
	*/
	struct VolumeInfo
	{
		enum DriverType
		{
			dtNone=0,				//δ֪����

			dtRemovable,			//���ƶ��豸
			dtFixed,				//�̶��豸
			dtRemote,				//Զ���豸
			dtCDROM,				//����������
			dtRamDisk,				//�ڴ������豸

			dtVirtualCDROM,			//�������������

			dtEnd					//��������
		};

		wchar_t 			name[1024];			//������

		wchar_t 			path[1024];			//������Ӧ��·����(ע��:�������о����ж�Ӧ·��)

		DriverType 			driver_type;		//����������(ע��:�������еľ�����Ӧ������)

		unsigned __int32 	serial;				//�����к�

		wchar_t				volume_label[256];	//��������	

		wchar_t 			file_system[256];	//�ļ�ϵͳ����

		unsigned __int32 	filename_max_length;//�ļ�����󳤶�

		bool 				unicode;			//�ļ���֧��UNICODE

		unsigned __int64	available_space;	//��Ч����
		unsigned __int64 	total_space;		//�ܿ���
		unsigned __int64 	free_space;			//��������
	};

	/**
	* ö�ٵ�ǰ��������о�
	* @param data �û��Զ���ش���Ϣ
	* @param func �ص�����
	* @return ���ҵ��ľ�������-1��ʾʧ��
	*/
	int EnumVolume(void *data,void (__cdecl *func)(void *,hgl::VolumeInfo &));
}
#endif//HGL_FILE_INCLUDE