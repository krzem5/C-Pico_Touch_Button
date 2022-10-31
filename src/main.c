#include <hardware/i2c.h>
#include <mpr121_constants.h>
#include <pico/bootrom.h>
#include <pico/stdlib.h>
#include <stdio.h>



#define SDA_PIN 18
#define SCL_PIN 19
#define IRQ_PIN 20
#define LED_PIN 25

#define INTERPOLATION_FACTOR 0.1f



static inline void set_register(uint8_t register_,uint8_t value){
	uint8_t data[2]={register_,value};
	i2c_write_blocking(i2c1,I2C_ADDRESS,data,2,0);
}



int main(void){
	stdio_init_all();
	stdio_usb_init();
	i2c_init(i2c1,100000);
	gpio_set_function(SDA_PIN,GPIO_FUNC_I2C);
	gpio_set_function(SCL_PIN,GPIO_FUNC_I2C);
	gpio_pull_up(SDA_PIN);
	gpio_pull_up(SCL_PIN);
	gpio_init(IRQ_PIN);
	gpio_set_dir(IRQ_PIN,GPIO_IN);
	gpio_put(IRQ_PIN,1);
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN,GPIO_OUT);
	gpio_put(LED_PIN,1);
	@@ -41,32 +25,19 @@ int main(void){
	sleep_ms(200);
	gpio_put(LED_PIN,0);
	sleep_ms(200);
	set_register(ELE_CFG,0x00);
	set_register(MHD_R,0x01);
	set_register(NHD_R,0x01);
	set_register(NCL_R,0x00);
	set_register(FDL_R,0x00);
	set_register(MHD_F,0x01);
	set_register(NHD_F,0x01);
	set_register(NCL_F,0xff);
	set_register(FDL_F,0x02);
	set_register(ELE0_T,0x09);
	set_register(ELE0_R,0x0a);
	set_register(FIL_CFG,0x04);
	set_register(ELE_CFG,0x01);
	set_register(ATO_CFG0,0x0b);
	set_register(ATO_CFGU,0x45);
	set_register(ATO_CFGL,0x2d);
	set_register(ATO_CFGT,0x3e);
	set_register(ELE_CFG,0x01);
	float value=0.0f;
	while (getchar_timeout_us(1)==PICO_ERROR_TIMEOUT){
		if (!gpio_get(IRQ_PIN)){
			value*=1-INTERPOLATION_FACTOR;
			uint8_t state;
			if (i2c_read_blocking(i2c1,I2C_ADDRESS,&state,1,false)==1){
				value+=(state&1)*INTERPOLATION_FACTOR;
			}
			gpio_put(LED_PIN,value>0.5f);
		}
	}
	reset_usb_boot(0,0);
	return 0;
