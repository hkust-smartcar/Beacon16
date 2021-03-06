/** board.h **
 * general information of mainboard
 */
#ifndef _USER_BOARD_H_
#define _USER_BOARD_H_

#define MAIN_DEBUG 0

// see stackoverflow.com/questions/1489932
#define PASTER2(x, y) x ## y
#define EVALUATOR2(x, y) PASTER2(x, y)
#define PASTER3(x, y, z) x ## y ## z
#define EVALUATOR3(x, y, z) PASTER3(x, y, z)

// LED
#define LED_PORT_NAME D
#define LED_PORT EVALUATOR2(HW_GPIO, LED_PORT_NAME)
#define LED1_PIN 4
#define LED2_PIN 5
#define LED3_PIN 8
#define LED4_PIN 9
#define LED1 EVALUATOR3(P, LED_PORT_NAME, out(LED1_PIN))
#define LED2 EVALUATOR3(P, LED_PORT_NAME, out(LED2_PIN))
#define LED3 EVALUATOR3(P, LED_PORT_NAME, out(LED3_PIN))
#define LED4 EVALUATOR3(P, LED_PORT_NAME, out(LED4_PIN))

// Button
#define BUTTON_PORT_NAME A
#define BUTTON_PORT EVALUATOR2(HW_GPIO, BUTTON_PORT_NAME)
#define BUTTON1_PIN 4
#define BUTTON2_PIN 5
#define BUTTON3_PIN 6
#define BUTTON4_PIN 7

// UART
#define UART_INSTANCE UART0_RX_PD06_TX_PD07

// Encoder & Motor
#define ENC_L HW_FTM2
#define ENC_R HW_FTM1
#define ENC_L_INSTANCE FTM2_QD_PHA_PA10_PHB_PA11
#define ENC_R_INSTANCE FTM1_QD_PHA_PA08_PHB_PA09
#define MOTOR_FTM_MODULE HW_FTM3
#define MOTOR_L 0
#define MOTOR_R 1
#define MOTOR_L_F HW_FTM_CH3
#define MOTOR_L_B HW_FTM_CH2
#define MOTOR_R_F HW_FTM_CH0
#define MOTOR_R_B HW_FTM_CH1
#define MOTOR_L_F_INSTANCE FTM3_CH3_PD03
#define MOTOR_L_B_INSTANCE FTM3_CH2_PD02
#define MOTOR_R_F_INSTANCE FTM3_CH0_PD00
#define MOTOR_R_B_INSTANCE FTM3_CH1_PD01

// mpu6050
#define AX 0x00
#define AY 0x01
#define AZ 0x02
#define GX 0x10
#define GY 0x11
#define GZ 0x12
#define MPU6050_I2C_INSTANCE I2C0_SCL_PB00_SDA_PB01
#define MPU6050_I2C_ID 0

#define MPU6050_I2CX (I2C0)
#define MPU6050_SCLPORT (HW_GPIOB)
#define MPU6050_SCLPIN (0)
#define MPU6050_SDAPORT (HW_GPIOB)
#define MPU6050_SDAPIN (1)

// control
#define STABLE_ANGLE	0
#define TG				1
#define ANGLE_P			2
#define ANGLE_D			3
#define SPEED_I			4
#define SPEED_P			5
#define STR_REG_I		6
#define STR_REG_P		7
#define CONST_CNT		8

// ov7725
// image size
// 0: 60X80
// 1: 120X160
// 2: 180X240
// 3: 240X320
#define OV7725_IMG_SIZE 0

#if (OV7725_IMG_SIZE == 0)
	#define OV7725_W 80
	#define OV7725_H 60
#elif (OV7725_IMG_SIZE == 1)
	#define OV7725_W 160
	#define OV7725_H 120
#elif (OV7725_IMG_SIZE == 2)
	#define OV7725_W 240
	#define OV7725_H 180
#elif (OV7725_IMG_SIZE == 3)
	#define OV7725_W 320
	#define OV7725_H 240
#else
	#error "Invalid image size!"
#endif // OV7725_IMG_SIZE


// signal description
#define OV7725_CTRL_PORT_NAME C
#define OV7725_CTRL_PORT EVALUATOR2(HW_GPIO,OV7725_CTRL_PORT_NAME)
#define OV7725_PCLK_PIN 0
#define OV7725_VSYNC_PIN 1
#define OV7725_DATA_PORT_NAME B
#define OV7725_DATA_PORT EVALUATOR2(HW_GPIO,OV7725_DATA_PORT_NAME)
#define OV7725_DATA_PT EVALUATOR2(PT,OV7725_DATA_PORT_NAME)
#define OV7725_DATA_PIN_OFFSET 16
#define OV7725_DMAREQ_SRC EVALUATOR3(PORT, OV7725_CTRL_PORT_NAME, _DMAREQ)
#define OV7725_VSYNC_IRQ EVALUATOR3(PORT, OV7725_CTRL_PORT_NAME, _IRQn)
#define OV7725_I2C_INSTANCE I2C1_SCL_PC10_SDA_PC11
#define OV7725_I2C_ID 1

// st7735r signal description
#define ST7735R_DC_PORT HW_GPIOC
#define ST7735R_DC_PIN 2
#define ST7735R_CS_PORT HW_GPIOC
#define ST7735R_CS_PIN 4
#define ST7735R_SPI HW_SPI0
#define ST7735R_SPI_CS HW_SPI_CS0
#define ST7735R_RST_PORT HW_GPIOC
#define ST7735R_RST_PIN 3
#define ST7735R_SPI_INSTANCE SPI0_SCK_PC05_SOUT_PC06_SIN_PC07

// flash
#define FLASH_SIZE 0x80000
#define FLASH_DATA_ADDR 0x00070000

// US-100
#define US100_UART_NUM 4
#define US100_UART EVALUATOR2(HW_UART, US100_UART_NUM)
#define US100_RX_ISR EVALUATOR3(UART, US100_UART_NUM, _RX_ISR)
#define US100_UART_INSTANCE UART4_RX_PC14_TX_PC15

//  bluetooth
#define BT_UART_NUM 0
#define BT_UART EVALUATOR2(HW_UART, BT_UART_NUM)
#define BT_RX_ISR EVALUATOR3(UART, BT_UART_NUM, _RX_ISR)
#define BT_UART_INSTANCE UART0_RX_PD06_TX_PD07

#endif // _USER_BOARD_H_
