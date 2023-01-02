#include <stc15f2k60s2.h>
#include <intrins.h>
#include "delay.h"
#include "timer.h"
#include "Buzzer.h"
#include "Key.h"
#define uchar unsigned char
#define uint unsigned int
#define SPEED	500
#define di1 159
#define di2 142
#define di3 126
#define di4 119
#define di5 106
#define di6 95
#define di7 84
 
#define zh1 80
#define zh2 71
#define zh3 63
#define zh4 60
#define zh5 53
#define zh6 47
#define zh7 42
 
#define gao1 40
#define gao2 35
#define gao3 32
#define gao4 30
#define gao5 27
#define gao6 24
#define gao7 21
#define P	0
#define S1	1
#define S1_	2
#define S2	3
#define S2_	4
#define S3	5
#define S4	6
#define S4_	7
#define S5	8
#define S5_	9
#define S6	10
#define S6_	11
#define S7	12
#define M1	13
#define M1_	14
#define M2	15
#define M2_	16
#define M3	17
#define M4	18
#define M4_	19
#define M5	20
#define M5_	21
#define M6	22
#define M6_	23
#define M7	24
#define H1	25
#define H1_	26
#define H2	27
#define H2_	28
#define H3	29
#define H4	30
#define H4_	31
#define H5	32
#define H5_	33
#define H6	34
#define H6_	35
#define H7	36
sbit P37=P3^7;
uchar i,ans;
uint k,KeyNum;
uchar flag;
uchar cntt;
uchar FreqSelect,MusicSelect;
uchar dis[]={
	0xc0,0xf9,0xa4,0xb0,
	0x99,0x92,0x82,0xf8,
	0x80,0x90,0x88,0x83,
	0xc6,0xa1,0x86,0x8e
};
 
uint FreqTable[]={
	0,
	63628,63731,63835,63928,64021,64103,64185,64260,64331,64400,64463,64528,
	64580,64633,64684,64732,64777,64820,64860,64898,64934,64968,65000,65030,
	65058,65085,65110,65134,65157,65178,65198,65217,65235,65252,65268,65283,
};
 
uchar tab[]={
	di1,di2,di3,di4,di5,di6,di7,
	zh1,zh2,zh3,zh4,zh5,zh6,zh7,
	gao1,gao2};
 
uchar code MusicA[]={
	//1
	P,	4,
	P,	4,
	P,	4,
	M6,	2,
	M7,	2,
	
	H1,	4+2,
	M7,	2,
	H1,	4,
	H3,	4,
	
	M7,	4+4+4,
	M3,	2,
	M3,	2,
	
	//2
	M6,	4+2,
	M5,	2,
	M6, 4,
	H1,	4,
	
	M5,	4+4+4,
	M3,	4,
	
	M4,	4+2,
	M3,	2,
	M4,	4,
	H1,	4,
	
	//3
	M3,	4+4,
	P,	2,
	H1,	2,
	H1,	2,
	H1,	2,
	
	M7,	4+2,
	M4_,2,
	M4_,4,
	M7,	4,
	
	M7,	8,
	P,	4,
	M6,	2,
	M7,	2,
	0xFF
};
uchar code MusicB[]={
	
	//4
	H1,	4+2,
	M7,	2,
	H1,	4,
	H3,	4,
	
	M7,	4+4+4,
	M3,	2,
	M3,	2,
	
	M6,	4+2,
	M5,	2,
	M6, 4,
	H1,	4,
	
	//5
	M5,	4+4+4,
	M2,	2,
	M3,	2,
	
	M4,	4,
	H1,	2,
	M7,	2+2,
	H1,	2+4,
	
	H2,	2,
	H2,	2,
	H3,	2,
	H1,	2+4+4,
	
	//6
	H1,	2,
	M7,	2,
	M6,	2,
	M6,	2,
	M7,	4,
	M5_,4,
	
	
	M6,	4+4+4,
	H1,	2,
	H2,	2,
	
	H3,	4+2,
	H2,	2,
	H3,	4,
	H5,	4,
	0xFF
};
uchar code MusicC[]={
	//7
	H2,	4+4+4,
	M5,	2,
	M5,	2,
	
	H1,	4+2,
	M7,	2,
	H1,	4,
	H3,	4,
	
	H3,	4+4+4+4,
	
	//8
	M6,	2,
	M7,	2,
	H1,	4,
	M7,	4,
	H2,	2,
	H2,	2,
	
	H1,	4+2,
	M5,	2+4+4,
	
	H4,	4,
	H3,	4,
	H3,	4,
	H1,	4,
	
	//9
	H3,	4+4+4,
	H3,	4,
	
	H6,	4+4,
	H5,	4,
	H5,	4,
	
	H3,	2,
	H2,	2,
	H1,	4+4,
	P,	2,
	H1,	2,
	
	//10
	H2,	4,
	H1,	2,
	H2,	2,
	H2,	4,
	H5,	4,
	
	H3,	4+4+4,
	H3,	4,
	
	H6,	4+4,
	H5,	4+4,
	
	//11
	H3,	2,
	H2,	2,
	H1,	4+4,
	P,	2,
	H1,	2,
	
	H2,	4,
	H1,	2,
	H2,	2+4,
	M7,	4,
	
	M6,	4+4+4,
	P,	4,
	
	0xFF
};
void display(uchar k){
	P0=dis[k];
}
//音符函数
void fun(){
	KeyNum=key_scan();
	display(KeyNum);
	if(cntt!=KeyNum){
		cntt=KeyNum;
		flag=1;
	}
	if(flag){
		for(k=0;k<249;k++){
			P37=~P37;
			delay12us(tab[KeyNum]);
		}
		flag=0;
		P37=0;
	}
	delay(70);
}
void fun2(){
	MusicSelect=0;
	Buzzer_Time(100);
	while(1){
		if(MusicA[MusicSelect]!=0xFF)		//如果不是停止标志位
		{
			FreqSelect=MusicA[MusicSelect];	//选择音符对应的频率
			MusicSelect++;
			delay(SPEED/4*MusicA[MusicSelect]);	//选择音符对应的时值
			MusicSelect++;
			TR0=0;
			delay(5);						//音符间短暂停顿
			TR0=1;
		}
		else								//如果是停止标志位
		{
			TR0=0;
			while(1);
		}
	}
}
void fun3(){
	MusicSelect=0;
	Buzzer_Time(100);
	while(1){
		if(MusicB[MusicSelect]!=0xFF)		//如果不是停止标志位
		{
			FreqSelect=MusicB[MusicSelect];	//选择音符对应的频率
			MusicSelect++;
			delay(SPEED/4*MusicB[MusicSelect]);	//选择音符对应的时值
			MusicSelect++;
			TR0=0;
			delay(5);						//音符间短暂停顿
			TR0=1;
		}
		else								//如果是停止标志位
		{
			TR0=0;
			while(1);
		}
	}
}
void fun4(){
	MusicSelect=0;
	Buzzer_Time(100);
	while(1){
		if(MusicC[MusicSelect]!=0xFF)		//如果不是停止标志位
		{
			FreqSelect=MusicC[MusicSelect];	//选择音符对应的频率
			MusicSelect++;
			delay(SPEED/4*MusicC[MusicSelect]);	//选择音符对应的时值
			MusicSelect++;
			TR0=0;
			delay(5);						//音符间短暂停顿
			TR0=1;
		}
		else								//如果是停止标志位
		{
			TR0=0;
			while(1);
		}
	}
}
void timer_routine() interrupt 1{
	if(FreqTable[FreqSelect]){                  //如果不是休止符
		TH0 = FreqTable[FreqSelect]/256;		//设置定时初值
		TL0 = FreqTable[FreqSelect]%256;		//设置定时初值
		P37=!P37;                         		//翻转蜂鸣器IO口
	}
}