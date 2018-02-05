#include "sys.h"
#include "DJI_RC.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "led.h"
#include "oled.h"
#include "pwm.h"
#include "Encoder.h"
#include "GPIO_Test.h" 

#define  RC_Value	1024


u16 ch1,ch2,ch3,ch4,s1,s2;//ch1��Roll ch2:Pitch	ch3:����	ch4:Yaw
int32_t speed;
int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);     //��ʼ����ʱ����
	uart_init(115200);	 //��ʼ�����ڲ�����Ϊ115200
	TIM2_Int_Init(1000-1,84-1);//��ʼ��TIM2��ʱ�ж� 1ms�ж�
	Quad_Encoder_Configuration();//��ʼ��������
	RC_Init();           //��ʼ��ң����
	TIM4_PWM_Init(1000);//��ʼ��1000HzPWM��
	LED_Init();					//��ʼ��LED
 	OLED_Init();				//��ʼ��OLED
    OLED_ShowString(16,0,"DJI_RC Test",16);  
	OLED_ShowString(0,16, "ch1:    ",12);  
 	OLED_ShowString(0,28, "ch2:    ",12);  
 	OLED_ShowString(64,16, "ch3:    ",12);  
 	OLED_ShowString(64,28, "ch4:    ",12);  
	OLED_ShowString(0,40, "s1:    ",12);
	OLED_ShowString(0,52, "s2:    ",12);
	OLED_Refresh_Gram();//������ʾ��OLED
    LED_GRE=0;	
	LED_RED=0;
	GPIO_Test_Init();
	PWM_Out(0,0,0,0);
	while(1) 
	{	
		OLED_ShowNum(28,16,Encoder.Num_a,4,12);	//��ʾͨ��ֵ
		OLED_ShowNum(28,28,Encoder.Num_b,4,12);
		OLED_ShowNum(92,16,ch3,4,12);
		OLED_ShowNum(92,28,ch4,4,12);	 
		OLED_ShowNum(28,40,s1,4,12);
		OLED_ShowNum(28,52,s2,4,12);
		OLED_Refresh_Gram();        //������ʾ��OLED 
		delay_ms(50);
		if(s1==1)
			LED_GRE=0;
		else
			LED_GRE=1;
		if(s2==1)
			LED_RED=0;
		else
			LED_RED=1;
		PWM_Out(0,0,0,0);
		//PWM_Out(ch1-1024,ch2-1024,ch3-1024,ch4-1024);
	}
}
