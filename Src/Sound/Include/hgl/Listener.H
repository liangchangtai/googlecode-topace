#ifndef HGL_LISTENER_INCLUDE
#define HGL_LISTENER_INCLUDE

#include<hgl/Vertex3.H>
namespace hgl
{
	/**
	* ��������ڹ��������ߵ�һЩ״̬������ͨ�����趨ͳһ�������������ߵ�λ�á������
	*/
	class AudioListener                                                                             ///�����߹�����
	{
	protected:

		float gain;
		Vertex3f position;
		Vertex3f velocity;
		Vertex3f *orientation;

	public:	//���Է���

		float GetGain(){return gain;}                                                               ///<��ȡ�����������
		const Vertex3f &GetPosition(){return position;}                                             ///<��ȡ��Դ����λ��
		const Vertex3f &GetVelocity(){return velocity;}                                             ///<��ȡ����
		const Vertex3f *GetOrientation(){return orientation;}                                       ///<��ȡ����

		void SetGain(float);                                                                        ///<���������������
		void SetPosition(const Vertex3f &);                                                         ///<������Դ����λ��
		void SetVelocity(const Vertex3f &);                                                         ///<��������
		void SetOrientation(const Vertex3f *);                                                      ///<���õ���

	public: //����

		AudioListener();
		~AudioListener();
	};
}

#endif//HGL_LISTENER_INCLUDE