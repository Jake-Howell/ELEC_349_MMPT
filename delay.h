//#define ms_count 168000	//SystemCoreClock/1000         
//#define us_count  168	//SystemCoreClock/1000000    
void SysTick_Init(void);
void delay_nus(unsigned int n); //delay of  n microseconds
int delay_nms(unsigned int n);
void SysTick_Handler(void);