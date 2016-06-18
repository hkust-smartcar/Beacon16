// st7735r library
// under testing

#include "common.h"
#include "st7735r.h"

void st7735r_Init(uint32_t instance) {
	// GPIO Init
	GPIO_QuickInit(ST7735R_DC_PORT, ST7735R_DC_PIN, kGPIO_Mode_OPP);
	GPIO_QuickInit(ST7735R_RST_PORT, ST7735R_RST_PIN, kGPIO_Mode_OPP);

	// SPI CS PinMux
	PORT_PinMuxConfig(ST7735R_CS_PORT, ST7735R_CS_PIN, kPinAlt2);

	// SPI init
	SPI_QuickInit(instance, kSPI_CPOL1_CPHA1, 8*1000*1000);

	// reset st7735r
	st7735r_Reset();

	// send startup command
	st7735r_Startup();
}

void st7735r_FillColor(uint16_t color) {
	st7735r_WriteCmd(0x2A);		// Column addr set
	st7735r_WriteData(0x00);
	st7735r_WriteData(0x00);	// X START
	st7735r_WriteData(0x00);
	st7735r_WriteData(0x7F);	// X END

	st7735r_WriteCmd(0x2B);		// Row addr set
	st7735r_WriteData(0x00);
	st7735r_WriteData(0x00);	// Y START
	st7735r_WriteData(0x00);
	st7735r_WriteData(0x9F);	// Y END

	st7735r_WriteCmd(0x2C);		// write to RAM
	
	for (uint16_t i = 0; i < MAX_WIDTH*MAX_HEIGHT; i++) {
		st7735r_WriteData(color >> 8);
		st7735r_WriteData(color);
	}
}

void st7735r_PutPixel(uint8_t x, uint8_t y, uint16_t color) {
	st7735r_SetPixelPos(x, y);
	st7735r_WriteData(color >> 8);
	st7735r_WriteData(color);
}

void st7735r_SetPixelPos(uint8_t x, uint8_t y) {
	st7735r_WriteCmd(0x2A);		// Column addr set
	st7735r_WriteData(0x00);
	st7735r_WriteData(x);		// X START
	st7735r_WriteData(0x00);
	st7735r_WriteData(x+1);		// X END

	st7735r_WriteCmd(0x2B);		// Row addr set
	st7735r_WriteData(0x00);
	st7735r_WriteData(y);		// Y START
	st7735r_WriteData(0x00);
	st7735r_WriteData(y+1);		// Y END

	st7735r_WriteCmd(0x2C);		// write to RAM
}

void st7735r_WriteCmd(uint8_t cmd) {
	// set dc to cmd
	GPIO_ResetBit(ST7735R_DC_PORT, ST7735R_DC_PIN);

	// send cmd
	SPI_ReadWriteByte(ST7735R_SPI, HW_CTAR0, (uint16_t)cmd,
		ST7735R_SPI_CS, kSPI_PCS_ReturnInactive);
}

void st7735r_WriteData(uint8_t data) {
	// set dc to data
	GPIO_SetBit(ST7735R_DC_PORT, ST7735R_DC_PIN);

	// send data
	SPI_ReadWriteByte(ST7735R_SPI, HW_CTAR0, (uint16_t)data,
		ST7735R_SPI_CS, kSPI_PCS_ReturnInactive);
}

void st7735r_Reset(void) {
	GPIO_ResetBit(ST7735R_RST_PORT, ST7735R_RST_PIN);
	for (uint16_t i = 0; i < 10000; i++);
	GPIO_SetBit(ST7735R_RST_PORT, ST7735R_RST_PIN);
	for (uint16_t i = 0; i < 10000; i++);
}

void st7735r_Startup(void) {
	st7735r_WriteCmd(0x01);	//Software setting
	// DelayMs(10);
	st7735r_WriteCmd(0x11);	//Sleep out
	// DelayMs(120);
	
	//ST7735R Frame Rate
	st7735r_WriteCmd(0xB1);
	st7735r_WriteData(0x01);
	st7735r_WriteData(0x2C);
	st7735r_WriteData(0x2D);
	st7735r_WriteCmd(0xB2);
	st7735r_WriteData(0x01);
	st7735r_WriteData(0x2C);
	st7735r_WriteData(0x2D);
	st7735r_WriteCmd(0xB3);
	st7735r_WriteData(0x01);
	st7735r_WriteData(0x2C);
	st7735r_WriteData(0x2D);
	st7735r_WriteData(0x01);
	st7735r_WriteData(0x2C);
	st7735r_WriteData(0x2D);
	//------------------------------------End ST7735R Frame Rate-----------------------------------------//
	st7735r_WriteCmd(0xB4);//Column inversion
	st7735r_WriteData(0x07);
	//------------------------------------ST7735R Power Sequence-----------------------------------------//
	st7735r_WriteCmd(0xC0);
	st7735r_WriteData(0xA2);
	st7735r_WriteData(0x02);
	st7735r_WriteData(0x84);
	st7735r_WriteCmd(0xC1);
	st7735r_WriteData(0xC5);
	st7735r_WriteCmd(0xC2);
	st7735r_WriteData(0x0A);
	st7735r_WriteData(0x00);
	st7735r_WriteCmd(0xC3);
	st7735r_WriteData(0x8A);
	st7735r_WriteData(0x2A);
	st7735r_WriteCmd(0xC4);
	st7735r_WriteData(0x8A);
	st7735r_WriteData(0xEE);
	//---------------------------------End ST7735R Power Sequence-------------------------------------//
	st7735r_WriteCmd(0xC5);	//VCOM
	st7735r_WriteData(0x0E);
	st7735r_WriteCmd(0x36);	//MX, MY, RGB mode
	st7735r_WriteData(0xC8);
	//------------------------------------ST7735R Gamma Sequence-----------------------------------------//
	st7735r_WriteCmd(0xe0);
	st7735r_WriteData(0x02);
	st7735r_WriteData(0x1c);
	st7735r_WriteData(0x07);
	st7735r_WriteData(0x12);
	st7735r_WriteData(0x37);
	st7735r_WriteData(0x32);
	st7735r_WriteData(0x29);
	st7735r_WriteData(0x2d);
	st7735r_WriteData(0x29);
	st7735r_WriteData(0x25);
	st7735r_WriteData(0x2b);
	st7735r_WriteData(0x39);
	st7735r_WriteData(0x00);
	st7735r_WriteData(0x01);
	st7735r_WriteData(0x03);
	st7735r_WriteData(0x10);
	st7735r_WriteCmd(0xe1);
	st7735r_WriteData(0x03);
	st7735r_WriteData(0x1d);
	st7735r_WriteData(0x07);
	st7735r_WriteData(0x06);
	st7735r_WriteData(0x2e);
	st7735r_WriteData(0x2c);
	st7735r_WriteData(0x29);
	st7735r_WriteData(0x2d);
	st7735r_WriteData(0x2e);
	st7735r_WriteData(0x2e);
	st7735r_WriteData(0x37);
	st7735r_WriteData(0x3f);
	st7735r_WriteData(0x00);
	st7735r_WriteData(0x00);
	st7735r_WriteData(0x02);
	st7735r_WriteData(0x10);
	st7735r_WriteCmd(0x2A);
	st7735r_WriteData(0x00);
	st7735r_WriteData(0x00);
	st7735r_WriteData(0x00);
	st7735r_WriteData(0x7f);

	st7735r_WriteCmd(0x2B);
	st7735r_WriteData(0x00);
	st7735r_WriteData(0x00);
	st7735r_WriteData(0x00);
	st7735r_WriteData(0x9f);
	//------------------------------------End ST7735R Gamma Sequence-----------------------------------------//

	st7735r_WriteCmd(0x3A);
	st7735r_WriteData(0x05);  
	st7735r_WriteCmd(0x29);	//Display on
}
