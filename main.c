#include "config.h"

sbit BUZZ = P1^6;  // 蜂鸣器控制引脚
sbit LED = P1^7;   // LED控制引脚

 //unsigned char str[] = "Happy Birthday";

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
unsigned char code image[] = {  //图片的字模表
0xDB,0x81,0x00,0x00,0x81,0xC3,0xE7,0xFF,0x81,0x81,0x9F,0x81,0x81,0xF9,0x81,0x81,
0xFF,0x81,0x81,0x99,0x99,0x99,0x81,0x81,0xFF,0x81,0x81,0x99,0x99,0x99,0x81,0x81,
0xFF,0x81,0x81,0x9F,0x81,0xFD,0x81,0x81,0xFF,0xDB,0xC9,0xDB,0xDB,0xDB,0xDB,0x81,
0xFF,0x81,0x99,0x99,0x81,0x99,0x99,0x81,0xFF,0xE7,0xC3,0x81,0x81,0xC3,0xE7,0xFF,

};

uint16 code NoteFrequ[] = {
    262, 294, 330, 349, 392, 440, 494,      // 低音1~7
    523, 578, 659, 698, 784, 880, 988,      // 中音1~7
    1046,1175,1318,1397,1568,1760,1976      // 高音1~7
};

uint16 code NoteReload[] = {
   65535-(11059200/12)/( 262*2),    //低音1~7
    65535-(11059200/12)/( 294*2),
    65535-(11059200/12)/( 330*2),
    65535-(11059200/12)/( 349*2),
    65535-(11059200/12)/( 392*2),
    65535-(11059200/12)/( 440*2),
    65535-(11059200/12)/( 494*2),

    65535-(11059200/12)/( 523*2),    //中音1~7
    65535-(11059200/12)/( 578*2),
    65535-(11059200/12)/( 659*2),
    65535-(11059200/12)/( 698*2),
    65535-(11059200/12)/( 784*2),
    65535-(11059200/12)/( 880*2),
    65535-(11059200/12)/( 988*2),

    65535-(11059200/12)/(1046*2),    //高音1~7
    65535-(11059200/12)/(1175*2),
    65535-(11059200/12)/(1318*2),
    65535-(11059200/12)/(1397*2),
    65535-(11059200/12)/(1568*2),
    65535-(11059200/12)/(1760*2),
    65535-(11059200/12)/(1976*2),
};

uint16 T0RH = 0xFC;    // T0高位
uint16 T0RL = 0x67;    // T0低位
bit timeflag = 0;      // 定时器中断完成标志
bit enable = 1;        // 蜂鸣器使能标志

void PlayHappyBirthday();
void InitLcd1602();
void LcdShowStr(unsigned char x, unsigned char y, unsigned char *str);


void main()
{
   
    unsigned char index = 0;  // 移动索引
	unsigned char str[] = "Happy Birthday ";
    EA = 1;            // 开总中断
	ENLED = 0;    //使能U4，选择LED点阵
    ADDR3 = 0;    //因为需要动态改变ADDR0-2的值，所以不需要再初始化了
    TMOD = 0x01;  // 配置T0工作在模式1

    TH0 = T0RH;
    TL0 = T0RL;
    ET0 = 1;           // 使能T0中断
    TR0 = 1;           // 启动T0

    
	

   InitLcd1602();
   LcdShowStr(1, 0, str);
   LcdShowStr(0, 1, "Best wish to you");
   
   
		
			
    while (1)
    {
        
			PlayHappyBirthday();    // 播放“Happy Birthday”歌曲
	
    }

	
}

void PlayHappyBirthday()
{
    uint8 beat;                        //当前节拍索引
    uint8 note;                        //当前音符索引
    uint16 time = 0;                   //当前节拍计时
    uint16 beatTime = 0;               //当前节拍总时间
    uint16 soundTime = 0;              //当前节拍发声时间
    const uint8 code HappyBrithdayNote[] = {   //生日歌音符表：1~7表示低音1~7、8~14表示中音1~7、15~21表示高音1~7、255表示空音符
       9, 8, 9, 8, 9, 10, 12, 10,         //第1、2小节
       9, 8, 9, 8, 9, 10, 9, 8, 6,      //第3、4小节
        9,8,9,8,9,10,12,10,    9,10,9,8,9,9,255,		                   //迈
		 9,8,9,8,9,10,12,10,  	9,10,9,8,6,								   //不
		 10,9,8,9,8,     10,9,8,9,8,    5,10,9,8,9,8, 255,				   //而
		 8,9,10,8,13,12,13,13,  9,14,13,14,								   //从
		 14,13,14,14,10,15,16,15,14,13,  12,13, 12,13, 12,13,13, 12,13, 12,9,9,12,10,10,  //看
		 8,9,10,8,13,12,13,13,  9,14,13,14,
		 14,13,14,14,10,15,16,15,14,13,  12,13, 17,17, 17, 12,13,17,17,17,12,13,13,255,
		 15,16,17, 20,19,19,20,19,19,20,19,16, 16,17, 20,19,19,20,19,19,20,19,19,17,//我曾
		 16,15,13,13,15, 15,16,15,13, 13,15,17,17,16,16, 
		 15,16,17, 20,19,19,20,19,19,20,19,19, 16,17, 20,19,19,20,19,19,20,19,19,17,
		 16,15,13,13, 17,16,16,15,13,13,15,15,255,
		 13,17,16,16,15,13,  13,17,16,16,15,13,13,15,15
    };
    const uint8 code HappyBrithdayBeat[] = {   //节拍表：一拍用4表示、1/4拍=1、2拍=8  1/2=2	  11/4=1 1/2=2 3/4=3 
        3,1,3,1,2,2,2,2,  3,1,3,1,1,1,1,1,4,
	   3,1,3,1,2,2,2,2,  3,1,2,1,1,4,4,
	   3,1,3,1,2,2,2,2,	 3,1,2,2,4,
	   1,1,1,1,4,    1,1,1,1,3,    1,1,1,1,1,3,4,
	   2,2,2,2,2,1,1,3,  1,2,1,4,
	   2,1,1,2,2,1,1,1,1,3,  1,2, 1,2, 1,1,1, 1,2, 1,1,2, 1,1,8,
	   2,2,2,2,2,1,1,3,  1,2,1,4,  
	   2,1,1,2,2,1,1,1,1,3,  1,2, 1,1, 2, 2,2,1,1,1,2,1,8,4,
	   2,2,2, 1,1,2,1,1,2,1,1,2, 2,2, 1,1,2,1,1,2,1,1,2,3,
	   2,1,1,1,2, 1,2,1,1, 2,2,3,1,1,2,
	   2,2,2, 1,1,2,1,1,2,1,1,2, 2,2, 1,1,2,1,1,2,1,1,2,2,
	   2,1,1,1,2,1,2,1,1,1,3,8,4,
	   1,1,3,2,1,1,1,2,1,2,1,1,1,2,8
    };
    for (beat=0; beat<sizeof(HappyBrithdayNote); )  //用节拍索引作为循环变量
    {
        while(!timeflag);    //每次定时器中断完成后，检测处理节拍
        timeflag = 0;
        if(time == 0)        //当前节拍播放完，启动新节拍
        {
            note = HappyBrithdayNote[beat] - 1;
            if(note >= 100)  //检测到空音符时，只启动节拍而不发声
            {
                T0RH = NoteReload[0] >> 8;
                T0RL = NoteReload[0];
                beatTime = (HappyBrithdayBeat[beat] * NoteFrequ[0]) >> 2;
                soundTime = beatTime - (beatTime >> 2);
                enable = 0;  //指示蜂鸣器不发声
                time++;
            }
            else
            {
                T0RH = NoteReload[note] >> 8;
                T0RL = NoteReload[note];
                //计算节拍总时间，右移2位相当于除4，移位代替除法可以加快执行速度
                beatTime = (HappyBrithdayBeat[beat] * NoteFrequ[note]) >> 2;
                //计算发声时间，为总时间的0.75，移位原理同上
                soundTime = beatTime - (beatTime >> 2);
                enable = 1;  //指示蜂鸣器开始发声
                time++;
            }
        }
        else  //当前节拍未播完则处理当前节拍
        {
            if (time >= beatTime)  //当前持续时间到达节拍总时间时归零，
            {                      //并递增节拍索引，以准备启动新节拍
                time = 0;
                beat++;
            }
            else  //当前持续时间未达到总时间时，
            {
                time++;   //累加时间计数
                if (time == soundTime)  //到达发声时间后，指示关闭蜂鸣器，
                {                       //插入0.25*总时间的静音间隔，
                    enable = 0;         //用以区分连续的两个节拍
                }
            }
        }
    }
}


/* T0中断服务函数，用于控制蜂鸣器发声和LCD滚动显示 */
void InterruptTimer0() interrupt 1
{	
	static unsigned char i = 0;  //动态扫描的索引
	//static unsigned char tmr500ms = 0;
    static unsigned char tmr = 0;  //250ms软件定时器
    static unsigned char index = 31;  //图片刷新索引
    TH0 = T0RH;   // 重新加载重载值
    TL0 = T0RL;
    timeflag = 1;
    if (enable)   // 使能时反转蜂鸣器控制电平
        BUZZ = ~BUZZ;
    else          // 未使能时关闭蜂鸣器
        BUZZ = 1;

	switch (i)
    {
        case 0: ADDR2=0; ADDR1=0; ADDR0=0; i++; P0=image[index+0]; break;
        case 1: ADDR2=0; ADDR1=0; ADDR0=1; i++; P0=image[index+1]; break;
        case 2: ADDR2=0; ADDR1=1; ADDR0=0; i++; P0=image[index+2]; break;
        case 3: ADDR2=0; ADDR1=1; ADDR0=1; i++; P0=image[index+3]; break;
        case 4: ADDR2=1; ADDR1=0; ADDR0=0; i++; P0=image[index+4]; break;
        case 5: ADDR2=1; ADDR1=0; ADDR0=1; i++; P0=image[index+5]; break;
        case 6: ADDR2=1; ADDR1=1; ADDR0=0; i++; P0=image[index+6]; break;
        case 7: ADDR2=1; ADDR1=1; ADDR0=1; i=0; P0=image[index+7]; break;
        default: break;
    }
    //以下代码完成每250ms改变一帧图像
    tmr++;
    if (tmr >= 250)  //达到250ms时改变一次图片索引
    {
        tmr = 0;
        index++;
        if (index >= 56)  //图片索引达到64后归零
        {
            index = 0;
        }
    }

	
	}

	
