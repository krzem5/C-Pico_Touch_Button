#include <mpr121_constants.h>
#include <pico/bootrom.h>
#include <pico/stdlib.h>
#include <stdio.h>



#define DATA_PIN 0
#define LED_PIN 25

#define INTERPOLATION_FACTOR 0.1f



int main(void){
	stdio_init_all();
	stdio_usb_init();
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN,GPIO_OUT);
	gpio_put(LED_PIN,1);
	sleep_ms(200);
	gpio_put(LED_PIN,0);
	sleep_ms(200);
	gpio_put(LED_PIN,1);
	sleep_ms(200);
	gpio_put(LED_PIN,0);
	sleep_ms(200);
	gpio_put(LED_PIN,1);
	sleep_ms(200);
	gpio_put(LED_PIN,0);
	sleep_ms(200);
	gpio_init(DATA_PIN);
	gpio_set_dir(DATA_PIN,GPIO_IN);
	gpio_put(DATA_PIN,0);
	float value=0.0f;
	while (getchar_timeout_us(1)==PICO_ERROR_TIMEOUT){
		value*=1-INTERPOLATION_FACTOR;
		value+=gpio_get(DATA_PIN)*INTERPOLATION_FACTOR;
		gpio_put(LED_PIN,value>0.65f);
		sleep_ms(16);
	}
	reset_usb_boot(0,0);
	return 0;
}
