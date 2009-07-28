#ifndef HGL_AUDIO_MANAGE_INCLUDE
#define HGL_AUDIO_MANAGE_INCLUDE

#include<hgl/List.H>
namespace hgl
{
	class AudioSource;
	class AudioBuffer;

	/**
	* �򵥵���Ƶ���Ź�����Ϊһ��Ӧ�õļ򵥲�������
	*/
	class AudioManage
	{
		struct AudioItem
		{
			AudioSource *source;
			AudioBuffer *buffer;

			AudioItem();
			~AudioItem();

			bool Check();
			void Play(const wchar_t *,float);
		};

		ObjectList<AudioItem> Items;

	public:

		/**
		* ���๹�캯��
		* @param count ��������Դ����,Ĭ��Ϊ8
		*/
		AudioManage(int count=8);	
		~AudioManage();

		/**
		* ����һ����Ч
		* @param filename �ļ���
		* @param gain ������Ĭ��Ϊ1
		*/
		bool Play(const wchar_t *filename,float gain=1);
	};
}
#endif//HGL_AUDIO_MANAGE_INCLUDE