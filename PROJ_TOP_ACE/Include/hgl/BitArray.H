﻿#ifndef HGL_BITARRAY_INCLUDE
#define HGL_BITARRAY_INCLUDE

#include<hgl/DataType.H>
namespace hgl
{
    class Stream;

    /**
    * 位队列用于处理需要按位保存的数据，它可以按位读取和写入
    */
    class BitArray                                                                                  ///位队列
    {
        bool mapping;

        int byte_size;
        int count,pos;
        uint8 *data;

	private:
	
		int GetCount(){return count;}
		void SetCount(int);

		int GetByteSize(){return byte_size;}

		int GetPos(){return pos;}
		void SetPos(int);

		uint8 *GetData(){return data;}

		void InitPrivate();

	public:

		Property<int>		Count;                                                                  ///<数据长度
		Property<int>		ByteSize;																///<字节长度
		Property<int>		Position;                                                               ///<当前位置
		Property<uint8 *>	Data;                                                                   ///<数据

	public:

		BitArray(int=0);
		BitArray(void *,int,bool=true);
		~BitArray();

		void Create(int);																			///<创建数据区
		void MapData(void *,int);                                                                   ///<映射数据
		void Clear();                                                                               ///<清除所有数据

		void Fill(bool);																			///<填充数据

		bool WriteZero();                                                                           ///<写入一位0
		bool WriteOne();                                                                            ///<写入一位1

		bool WriteTrue(){return WriteOne();}                                                        ///<写入一位真(即1)
		bool WriteFalse(){return WriteZero();}                                                      ///<写入一位假(即0)

		bool WriteBit(bool bit)                                                                     ///<写入一位数据
			{return(bit?WriteOne():WriteZero());}
		bool WriteByte(unsigned __int8 *,int);                                                      ///<按字节写入数据

		bool ReadBit();                                                                             ///<读取一位

		bool FlipBit();                                                                             ///<翻转一位
		bool FlipBit(int o)                                                                         ///<翻转指定位
			{Position=o;return(FlipBit());}

		bool ReadPos(	int o)			{SetPos(o);return(ReadBit());}								///<读取指定位
		void WritePos(	int o,bool bit)	{SetPos(o);bit?WriteOne():WriteZero();}						///<写入一位数据

        bool SaveToStream(Stream *);                                                                ///<保存当前位阵列数据到流
        bool LoadFromStream(Stream *);                                                              ///<从流中读取位阵列数据
        bool SaveToFile(const wchar_t *);                                                           ///<保存当前位阵列数据到文件
        bool LoadFromFile(const wchar_t *);                                                         ///<从文件中读取位阵列数据

    public: //操作符重载

		BitArray & operator =(const BitArray &);													///<=号重载

		BitArray & operator +=(const BitArray &);													///<+
		BitArray & operator -=(const BitArray &);													///<-
		BitArray & operator *=(const BitArray &);													///<*

		bool operator == (const BitArray &) const;
		bool operator != (const BitArray &rhs) const {return !operator==(rhs);}
	};
}//namespace hgl
#endif//HGL_BITARRAY_INCLUDE;
