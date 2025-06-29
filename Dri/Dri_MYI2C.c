#include "Dri_MyI2C.h"
#include <stdint.h>

extern uint32_t SystemCoreClock;

static void Delay_us(uint32_t us)
{
	// volatile 是防止编译器优化
	// /4 是因为cpu的指令周期占4个时钟周期
	volatile uint32_t loops = us * (SystemCoreClock / 1000000) / 4;
	while (loops--)
		;
}

void MyI2C_W_SCL(MyI2C_TypeStructure *Myi2c, uint8_t BitValue)
{
	HAL_GPIO_WritePin(Myi2c->SCL_GPIO_Port, Myi2c->SCL_Pin, (GPIO_PinState)BitValue);
	Delay_us(DELAY);
}

void MyI2C_W_SDA(MyI2C_TypeStructure *Myi2c, uint8_t BitValue)
{
	HAL_GPIO_WritePin(Myi2c->SDA_GPIO_Port, Myi2c->SDA_Pin, (GPIO_PinState)BitValue);
	Delay_us(DELAY);
}

uint8_t MyI2C_R_SDA(MyI2C_TypeStructure *Myi2c)
{
	uint8_t BitValue;
	// BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);
	BitValue = HAL_GPIO_ReadPin(Myi2c->SDA_GPIO_Port, Myi2c->SDA_Pin);
	Delay_us(DELAY);
	return BitValue;
}

void MyI2C_Init(MyI2C_TypeStructure *Myi2c)
{
	// HAL库时钟使能方式
	// FIMXE: 要在结构体中配置GPIO时钟使能函数指针
	Myi2c->GPIO_Clock_Enable();

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// SCL引脚配置
	GPIO_InitStruct.Pin = Myi2c->SCL_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; // 开漏输出
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(Myi2c->SCL_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(Myi2c->SCL_GPIO_Port, Myi2c->SCL_Pin, GPIO_PIN_SET);

	// SDA引脚配置
	GPIO_InitStruct.Pin = Myi2c->SDA_Pin;
	HAL_GPIO_Init(Myi2c->SDA_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_WritePin(Myi2c->SDA_GPIO_Port, Myi2c->SDA_Pin, GPIO_PIN_SET);
}

void MyI2C_Start(MyI2C_TypeStructure *Myi2c)
{
	MyI2C_W_SDA(Myi2c, 1);
	MyI2C_W_SCL(Myi2c, 1);
	MyI2C_W_SDA(Myi2c, 0);
	MyI2C_W_SCL(Myi2c, 0);
}

void MyI2C_Stop(MyI2C_TypeStructure *Myi2c)
{
	MyI2C_W_SDA(Myi2c, 0);
	MyI2C_W_SCL(Myi2c, 1);
	MyI2C_W_SDA(Myi2c, 1);
}

void MyI2C_SendByte(MyI2C_TypeStructure *Myi2c, uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		MyI2C_W_SDA(Myi2c, Byte & (0x80 >> i));
		MyI2C_W_SCL(Myi2c, 1);
		MyI2C_W_SCL(Myi2c, 0);
	}
}

uint8_t MyI2C_ReceiveByte(MyI2C_TypeStructure *Myi2c)
{
	uint8_t i, Byte = 0x00;
	MyI2C_W_SDA(Myi2c, 1);
	for (i = 0; i < 8; i++)
	{
		MyI2C_W_SCL(Myi2c, 1);
		if (MyI2C_R_SDA(Myi2c) == 1)
		{
			Byte |= (0x80 >> i);
		}
		MyI2C_W_SCL(Myi2c, 0);
	}
	return Byte;
}

void MyI2C_SendAck(MyI2C_TypeStructure *Myi2c, uint8_t AckBit)
{
	MyI2C_W_SDA(Myi2c, AckBit);
	MyI2C_W_SCL(Myi2c, 1);
	MyI2C_W_SCL(Myi2c, 0);
}

uint8_t MyI2C_ReceiveAck(MyI2C_TypeStructure *Myi2c)
{
	uint8_t AckBit;
	MyI2C_W_SDA(Myi2c, 1);
	MyI2C_W_SCL(Myi2c, 1);
	AckBit = MyI2C_R_SDA(Myi2c);
	MyI2C_W_SCL(Myi2c, 0);
	return AckBit;
}
