#ifndef HGL_ONLYLIST_CPP
#define HGL_ONLYLIST_CPP

#include<hgl/OnlyList.H>
#include<hgl/Stream.H>
#include<malloc.h>
namespace hgl
{
	template<typename T>
	OnlyList<T>::OnlyList()
	{
		OnComp=NULL;

		count=0;

		hglSetPropertyRead(Data,this,OnlyList<T>::GetData);
		hglSetPropertyRead(Count,this,OnlyList<T>::GetCount);
	}

	template<typename T>
	OnlyList<T>::~OnlyList()
	{
		Clear();
	}

	template<typename T>
	T OnlyList<T>::GetItem(int index)
	{
		return((index>=0&&index<count)?items[index]:NULL);
	}

	template<typename T>
	void OnlyList<T>::SetItem(int index,const T &data)
	{
		if(index>=0&&index<count)
//			items[index]=data;
			hgl_memcpy(items+index,&data,sizeof(T));
	}

	/**
	* ����һ�����ݵ��б��У�����������ظ��ģ�������
	* @param data Ҫ���ӵ�����
	* @return ���Ӻ���������б��е�����ֵ
	*/
	template<typename T>
	int OnlyList<T>::Add(const T &data)
	{
		if(count==0)
		{
			items=(T *)hgl_malloc(sizeof(T));

			max_count=1;
		}
		else
		{
			int n=count;

			if(OnComp!=NULL)
			{
				while(n--)
					if(CallEvent(OnComp,(items[n],data))==0)return(n);
			}
			else
			{
				while(n--)
					//if(items[n]==data)return(n);
					if(hgl_memcmp(items+n,&data,sizeof(T))==0)return(n);
			}

			if(count+1>max_count)
			{
				max_count=count+1;

				items=(T *)hgl_realloc(items,max_count*sizeof(T));
			}
		}

//		items[count]=data;
		hgl_memcpy(items+count,&data,sizeof(T));
		return(count++);
	}

	/**
	* ɾ��һ������
	* @param index ���ݵ�����
	*/       
	template<typename T>
	void OnlyList<T>::DeleteByIndex(int index)
	{
		if(index<0||index>=count)return;

		count--;

		if(count<=0)
		{
			max_count=0;
			hgl_free(items);
			return;
		}

		if(index<count)
			hgl_memcpy(items+index,items+index+1,(count-index)*sizeof(T));
	}

	/**
	* ɾ��һ������
	* @param data Ҫɾ��������
	*/
	template<typename T>
	void OnlyList<T>::DeleteByData(const T &data)
	{
		DeleteByIndex(Find(data));
	}

	/**
	* ����д������
	* @param array ����
	* @param array_count ���ݸ���
	*/
	template<typename T>
	void OnlyList<T>::Write(const T *array,int array_count)
	{
		if(count==0)
		{
			items=(T *)hgl_malloc(array_count*sizeof(T));

			max_count=array_count;
		}
		else if(count+array_count>max_count)
		{
			max_count=count+array_count;

			items=(T *)hgl_malloc(max_count*sizeof(T));
		}

		hgl_memcpy(items+count,array,array_count*sizeof(T));

		count+=array_count;
	}

    /**
	* ����д������
	* @param array ����
	* @param array_count ���ݸ���
	*/
	template<typename T>
	void OnlyList<T>::Write(Stream *str,int array_count)
	{
		if(count==0)
		{
			items=(T *)hgl_malloc(array_count*sizeof(T));

			max_count=array_count;
		}
		else if(count+array_count>max_count)
		{
			max_count=count+array_count;

			items=(T *)hgl_malloc(max_count*sizeof(T));
		}

		str->Read(items+count,array_count*sizeof(T));

		count+=array_count;
	}

	/**
	* ��������б�
	*/
	template<typename T>
	void OnlyList<T>::Clear()
	{
		if(count)
		{
			hgl_free(items);
			count=0;
		}
	}

	/**
	* ���б��в���ָ���������������ֵ
	* @param data Ҫ���ҵ�������
	* @return ���б��е�����ֵ��-1��ʾû���ҵ�
	*/
	template<typename T>
	int OnlyList<T>::Find(const T &data)
	{
		int n=count;

		if(OnComp!=NULL)
		{
			while(n--)
				if(CallEvent(OnComp,(items[n],data))==0)return(n);
		}
		else
		{
			while(n--)
				//if(items[n]==data)return(n);
				if(hgl_memcmp(items+n,&data,sizeof(T))==0)return(n);
		}

		return(-1);
	}
}
#endif//HGL_ONLYLIST_CPP