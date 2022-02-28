//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//CONFIG HEADER FOR STM32F4XX DISCOVERY DAC MODULE
//BY STUART MACVEIGH		24/03/2014
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

#define STM32F4xx_DAC_CR_DMAUDRIE2			0
#define STM32F4xx_DAC_CR_DMAEN2					0
#define STM32F4xx_DAC_CR_MAMP2					0
#define STM32F4xx_DAC_CR_WAVE2					0
#define STM32F4xx_DAC_CR_TSEL2					0
#define STM32F4xx_DAC_CR_TEN2						0
#define STM32F4xx_DAC_CR_BOFF2					0
#define STM32F4xx_DAC_CR_DMAUDRIE1			0
#define STM32F4xx_DAC_CR_DMAEN1					0
#define STM32F4xx_DAC_CR_MAMP1					0
#define STM32F4xx_DAC_CR_WAVE1					0
#define STM32F4xx_DAC_CR_TSEL1					0
#define STM32F4xx_DAC_CR_TEN1						0
#define STM32F4xx_DAC_CR_BOFF1					0


#define STM32F4xx_DAC_SWTRIGR_SWTRIG2		0
#define STM32F4xx_DAC_SWTRIGR_SWTRIG1		0


//====================================================================================
//====================================================================================
//====================================================================================
//DO NOT CHANGE ANY SETTINGS BEYOND THIS POINT!!
//====================================================================================
//====================================================================================
//REGISTER CONSTRUCTION FOR DAC

#define STM32F4xx_DAC_CR								((STM32F4xx_DAC_CR_DMAUDRIE2<<29)|(STM32F4xx_DAC_CR_DMAEN2<<28)|(STM32F4xx_DAC_CR_MAMP2<<24)|(STM32F4xx_DAC_CR_WAVE2<<22)|(STM32F4xx_DAC_CR_TSEL2<<19)|(STM32F4xx_DAC_CR_TEN2<<18)|(STM32F4xx_DAC_CR_BOFF2<<17)|(STM32F4xx_DAC_CR_DMAUDRIE1<<13)|(STM32F4xx_DAC_CR_DMAEN1<<12)|(STM32F4xx_DAC_CR_MAMP1<<8)|(STM32F4xx_DAC_CR_WAVE1<<6)|(STM32F4xx_DAC_CR_TSEL1<<3)|(STM32F4xx_DAC_CR_TEN1<<2)|(STM32F4xx_DAC_CR_BOFF1<<1))
#define STM32F4xx_DAC_SWTRIGR						((STM32F4xx_DAC_SWTRIGR_SWTRIG2<<1)|(STM32F4xx_DAC_SWTRIGR_SWTRIG1<<0))


//====================================================================================
//====================================================================================
//CALL FUNCTIONS TO CONFIG AND ENABLE WITH SELECTED SETTINGS
//====================================================================================

#define config_DAC()										{RCC->APB1ENR|=0x20000000; DAC->CR=STM32F4xx_DAC_CR; DAC->SWTRIGR=STM32F4xx_DAC_SWTRIGR; DAC->CR|=0x10001;}

#define output_dac1(val)							DAC->DHR12R1=(unsigned short int)(val)
#define output_dac2(val)							DAC->DHR12R2=(unsigned short int)(val)


//EOF
