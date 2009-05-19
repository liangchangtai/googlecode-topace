#ifndef HGL_MUTEX_INCLUDE
#define HGL_MUTEX_INCLUDE

namespace hgl
{
	/**
	* �ų����������ж������ڱ�һ������η���ʱ�����ܱ���һ����η���
	*/
	class Mutex                                                                                     ///�ų������
	{
		void *ptr;

	public:

		Mutex();                                                                                    ///<���๹�캯��
		virtual ~Mutex();                                                                           ///<������������

		virtual void Acquire();                                                                     ///<ȡ�õĿ���Ȩ(����������ų�״̬����ȴ�)
		virtual bool TryAcquire();                                                                  ///<����ȡ�ÿ���Ȩ
		virtual bool WaitAcquire(unsigned int=0);                                                   ///<�ȴ���ȡ�ÿ���Ȩ
		virtual void Release();                                                                     ///<��������Ȩ
	};
}
#endif//HGL_MUTEX_INCLUDE