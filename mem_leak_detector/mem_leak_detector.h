#ifndef _MEM_LEAK_DETECTOR_H
#define _MEM_LEAK_DETECTOR_H

#ifdef _DEBUG
	/**/
	#define _CRTDBG_MAP_ALLOC

	#include <stdlib.h>
	#include "crtdbg.h"
	#define DEBUG_NEW   new( _NORMAL_BLOCK, __FILE__, __LINE__)
#else
	#define DEBUG_NEW
#endif

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif  

//�����������main()�����е��κεط����������main��ڴ���
void memoryLeakDetector();

//�ڷ���ڼ����ڴ��ʱ��ϵ��жϵ��ԣ����ڴ�й¶�������кŵ�ʱ���ø÷�������һ������
void setBreakPoint(int alloc_num);


#endif