#ifndef HGL_FILESTREAM_INCLUDE
#define HGL_FILESTREAM_INCLUDE

#include<hgl/Stream.H>
namespace hgl
{
	enum FileOpenMode                   			///�ļ�����ģʽö��
	{
		fomCreate		=0x01,         			///<����һ���ļ�,ֻд��ʽ
		fomOpenRead     =0x02,         			///<��һ���ļ�,ֻ����ʽ
		fomOpenWrite    =0x04,         			///<��һ���ļ�,ֻд��ʽ
		fomOpenReadWrite=fomOpenRead|fomOpenWrite, ///<��һ���ļ�,�ɶ���д

		fomRead			=fomOpenRead,
		fomWrite		=fomOpenWrite,
		fomReadWrite	=fomOpenReadWrite
	};

	/**
	* FileStream��һ������ļ�����ʽ�����࣬����Stream������
	*/
	class FileStream:public Stream                                                                  ///�ļ���������
	{
		friend class PartFileStream;
	
		wchar_t *filename;
		void *fp;
		unsigned long result;

	protected:

		int64 GetPosition();
		void SetPosition(int64);

		int64 GetSize();
		void SetSize(int64);

		void InitPrivate();

	public: //����

		FileStream();
		FileStream(void *);
		FileStream(const wchar_t *,FileOpenMode=fomOpenRead);
		~FileStream();

		bool Create(const wchar_t *);
		bool Open(const wchar_t *,FileOpenMode=fomOpenRead);
		void Close();

		int Read(void *,int);
		int Write(const void *,int);

		int64 Seek(int64,SeekOrigin=soBegin);
	};
}
//--------------------------------------------------------------------------------------------------
#endif//HGL_FILESTREAM_INCLUDE