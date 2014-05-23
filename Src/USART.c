#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "delay.h"
#include "USART.h"

//��������� ��� ������������� GPIOA � USART1
GPIO_InitTypeDef    USART_GPIO_InitStruct;
USART_InitTypeDef    USART_InitStruct;

void USART1_Init(void); //���������� ������� ������������� ���������
void Usart1_Send_symbol(uint8_t); //���������� ������� �������� �������
void Usart1_Send_String(char* str); //���������� ������� �������� ������

//������� ������������� ���������
void USART1_Init(void)
{
  //�������� ������������ GPIOA, USART1 � �������������� ������� AFIO
  RCC_APB2PeriphClockCmd((RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO), ENABLE);

  //������������� ������ PA9 - USART1_Tx
  USART_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9; //��������� ������ PA9
  USART_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; //�������� �����
  USART_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; //����� �������������� �������, ����� Push-Pull
  GPIO_Init(GPIOA, &USART_GPIO_InitStruct); //�������� ��������� ��������� � ��������� GPIO�

  //������������� ������ PA10 - USART1_Rx
  USART_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10; //��������� ������ PA10
  USART_GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING; //Input floating
  GPIO_Init(GPIOA, &USART_GPIO_InitStruct); //�������� ��������� ��������� � ��������� GPIO�

  //������������� USART1
  USART_InitStruct.USART_BaudRate = 9600; //�������� ������ 9600 ���
  USART_InitStruct.USART_WordLength = USART_WordLength_8b; //����� ����� 8 ���
  USART_InitStruct.USART_StopBits = USART_StopBits_1; //1 ����-���
  USART_InitStruct.USART_Parity = USART_Parity_No ; //��� �������� ��������
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��� ����������� ��������
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //������� ���������� � �������� USART1
  USART_Init(USART1, &USART_InitStruct); //�������� ��������� ��������� � ��������� USART1

  USART_Cmd(USART1, ENABLE); //�������� USART1
}

//������� �������� �������
void Usart1_Send_symbol(uint8_t data)
{
  while(!(USART1->SR & USART_SR_TC)); //��������� ��������� ����� TC - ���������� ���������� ��������
  USART1->DR = data; //���������� �������� � ������� ������ - �������� ������
}

//������� �������� ������ ����� USART
void Usart1_Send_String(char* str)
{
  uint8_t i=0;
  while(str[i])
  {
    Usart1_Send_symbol(str[i]);
      Delay(400);
    i++;
  }
  Usart1_Send_symbol('\n');
      Delay(400);
  Usart1_Send_symbol('\r');
    Delay(400);
}

