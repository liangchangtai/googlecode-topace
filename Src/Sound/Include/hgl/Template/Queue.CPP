#ifndef HGL_QUEUE_CPP
#define HGL_QUEUE_CPP

#include<hgl/Queue.H>
namespace hgl
{
	/**
	* ���๹�캯��
	* @param m ���m��ֵ��Ϊ0�����ʾʹ�ù̶��Ķ��д�С���̶���С�Ķ��л���һ��ʼ��������ڴ档
	*/
    template<typename T>
	Queue<T>::Queue(int m)
	{
		hglSetPropertyRead(Count,this,Queue<T>::GetCount);
		hglSetProperty(MaxCount,this,Queue<T>::GetMax,Queue<T>::SetMax);

        count=0;

        if(m)
        {
			max_count=m;

			items=(T *)hgl_malloc(max_count*sizeof(T));
        }
		else max_count=0;

		mem_count=max_count;
	}

    template<typename T>
    Queue<T>::~Queue()
    {
		if(count||max_count)hgl_free(items);
    }

    /**
    * �޸Ķ��е����ֵ
    */
    template<typename T>
    void Queue<T>::SetMax(int m)
    {
		if(max_count||(!max_count&&count))
			items=(T *)hgl_realloc(items,m*sizeof(T));
		else
			items=(T *)hgl_malloc(m*sizeof(T));

		max_count=m;
		mem_count=m;

		if(count>=max_count)count=max_count-1;
    }

    /**
    * ��������е���������
    */
    template<typename T>
    void Queue<T>::Clear()
    {
		if(max_count==0)
			if(count)
			{
				hgl_free(items);
				mem_count=0;
			}

		count=0;
    }

	/**
	* ���ʶ����е�һ�����ݣ����������
	* @param t ȡ�������ݱ����
	* @return �Ƿ�ɹ�ȡ������
    */
    template<typename T>
	bool Queue<T>::Peek(T &t)
	{
		if(count)
		{
        	t=items[0];
//			hgl_memcpy(&t,items,sizeof(T));
			return(true);
		}
		else
			return(false);
	}

	/**
	* �Ӷ�����ȡ��һ������
	* @param t ȡ�������ݱ����
	* @return �Ƿ�ɹ�ȡ������
    */
    template<typename T>
	bool Queue<T>::Pop(T &t)
	{
        if(count)
		{
        	t=items[0];
//			hgl_memcpy(&t,items,sizeof(T));

            count--;

			if(max_count==0)
            {
				if(count==0)
				{
					hgl_free(items);

					mem_count=0;
				}
                else
                {
                    hgl_memcpy(items,items+1,count*sizeof(T));
//                    items=(T *)hgl_realloc(items,count*sizeof(T));
                }
			}
			else
			{
                hgl_memcpy(items,items+1,count*sizeof(T));
			}
			
			return(true);
		}
		else
			return(false);
	}

	/**
	* ������з���һ������
	* @param data Ҫ���������ָ��
	* @return true �������ݳɹ�
	* @return false ��������ʧ��
    */
    template<typename T>
	bool Queue<T>::Push(T &data)
	{
		if(max_count)
		{
			if(count>=max_count)return(false);
		}
		else
		{
			if(count)
			{
				if(count+1>mem_count)
				{
					mem_count=count+1;

					items=(T *)hgl_realloc(items,mem_count*sizeof(T));
				}
			}
			else
			{
				items=(T *)hgl_malloc(sizeof(T));

				mem_count=1;
			}
		}

		items[count++]=data;
//		hgl_memcpy(items+count,&data,sizeof(T));
//		count++;

        return(true);
	}

	template<typename T>
	void Queue<T>::operator =(const Queue<T> &ori)
	{
		if(ori.count==0)return;

		Clear();

		max_count=ori.count;
		count=ori.count;

		if(max_count==0)
			mem_count=count;
		else
			mem_count=max_count;

		items=(T *)hgl_malloc(mem_count*sizeof(T));

		hgl_memcpy(items,ori.items,mem_count*sizeof(T));
	}
}

namespace hgl
{
	template<typename T>
	void QueueObject<T>::Clear()
	{
		int n=count;
		while(n--)
			delete items[n];

		Queue<T *>::Clear();
	}
}
#endif//HGL_QUEUE_CPP