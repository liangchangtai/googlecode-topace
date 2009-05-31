#ifndef HGL_SMARTPOINTER_INCLUDE
#define HGL_SMARTPOINTER_INCLUDE

namespace hgl
{
	/**
	* SmartPointer ����Ϊ���ɵ�ָ�룬ʹ�������Ժܷ���Ķ�����Զ��ͷŵ���������<br>
	* ����ɲ���SmartPointerʾ����<br>
	* �硰SmartPointer<T> data=new T;����ͨ������ʹ�á�SmartPointer<T> data(new T)��
	*/
	template <class T> class SmartPointer                                                           ///����ָ����
	{
		SmartPointer<T> &operator =(SmartPointer<T> &)
		{
			return(*this);
		}

		SmartPointer(SmartPointer<T> &){}

	protected:

		T *ThisPointer;

	public:

		SmartPointer(T *ptr=0):ThisPointer(ptr){}

		virtual ~SmartPointer()
		{
        	if(ThisPointer)
				delete ThisPointer;
		}

		T &operator *() const
		{
			return *ThisPointer;
		}

		T *operator =(T *ptr)
		{
			if(ThisPointer)
				delete ThisPointer;

			ThisPointer=ptr;
			return(ptr);
		}

		operator T *()const{return ThisPointer;}

		T *operator ->() const
		{
			return(ThisPointer);
		}

		bool operator == (T *ptr) const
		{
        	return ThisPointer == ptr;
		}

		bool operator != (T *ptr) const
		{
        	return !(operator ==(ptr));
		}
	};

	template <class T> class SmartArray                                                           ///����ָ����
	{
		SmartArray<T> &operator =(SmartArray<T> &)
		{
			return(*this);
		}

		SmartArray(SmartArray<T> &){}

	protected:

		T *ThisPointer;

	public:

		SmartArray(T *ptr=0):ThisPointer(ptr){}

		virtual ~SmartArray()
		{
        	if(ThisPointer)
				delete[] ThisPointer;
		}

		T &operator *() const
		{
			return *ThisPointer;
		}

		T *operator =(T *ptr)
		{
			if(ThisPointer)
				delete[] ThisPointer;

			ThisPointer=ptr;
			return(ptr);
		}

		operator T *()const{return ThisPointer;}

//		operator const T [](int n)const{return ThisPointer[n];}

		T *operator ->() const
		{
			return(ThisPointer);
		}

		bool operator == (T *ptr) const
		{
        	return ThisPointer == ptr;
		}

		bool operator != (T *ptr) const
		{
        	return !(operator ==(ptr));
		}
	};

	typedef SmartArray<char> SmartAnsiString;
	typedef SmartArray<wchar_t> SmartWideString;
	typedef SmartArray<wchar_t> SmartUnicodeString;
}

#endif//HGL_SMARTPOINTER_INCLUDE