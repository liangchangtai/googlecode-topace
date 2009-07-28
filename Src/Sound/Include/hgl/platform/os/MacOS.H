#ifndef HGL_OS_MACOS_INCLUDE
#define HGL_OS_MACOS_INCLUDE

#if HGL_CPU == HGL_CPU_PowerPC
	#define HGL_OS_NAME				L"MacOS(PowerPC)"
#elif (HGL_CPU == HGL_CPU_X86_32) || (HGL_CPU == HGL_CPU_X86_64)
	#define HGL_OS_NAME				L"MacOS(Intel)"
#elif HGL_CPU == HGL_CPU_Cell
	#define HGL_OS_NAME				L"MacOS(PlayStation3)"
#elif HGL_CPU == HGL_CPU_MIPS
	#define HGL_OS_NAME				L"MacOS(MIPS)"
	
	#error ��֧������汾��MacOS
#else
	#error δ֪�汾��MacOS
#endif//

#define PIExtName	L".dylib"							//����ļ���չ��
#define PIAPI 											//�����������

#endif//HGL_OS_MACOS_INCLUDE