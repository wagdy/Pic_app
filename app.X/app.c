/*
 * File:   app.c
 * Author: elmogy
 *
 * Created on March 5, 2024, 4:38 PM
 */


#include "app.h"
#include "MCAL_Layer/mcal_std_types.h"
#include "MCAL_Layer/GPIO/hal_gpio.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "ECU_Layer/LED/ecu_led.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "ECU_Layer/Chr_LCD/ecu_chr_lcd.h"
#include "ECU_Layer/ecu_layer_init.h"

void application_intialize(void);

chr_lcd_4bit_t lcd_1 = {
    
.lcd_rs.port        = PORTE_INDEX      , 
.lcd_rs.pin         = GPIO_PIN2      ,
.lcd_rs.direction   = GPIO_DIRECTION_OUTPUT      ,   
.lcd_rs.logic       = GPIO_LOW  , 
.lcd_en.port        = PORTE_INDEX      , 
.lcd_en.pin         = GPIO_PIN1      ,
.lcd_en.direction   = GPIO_DIRECTION_OUTPUT      ,   
.lcd_en.logic       = GPIO_LOW  ,

.lcd_data[0].port   = PORTD_INDEX,
.lcd_data[0].pin    =GPIO_PIN0 ,
.lcd_data[0].direction    =GPIO_DIRECTION_OUTPUT ,
.lcd_data[0].logic    =GPIO_LOW ,

.lcd_data[1].port   = PORTD_INDEX,
.lcd_data[1].pin    =GPIO_PIN1 ,
.lcd_data[1].direction    =GPIO_DIRECTION_OUTPUT ,
.lcd_data[1].logic    =GPIO_LOW ,

.lcd_data[2].port   = PORTD_INDEX,
.lcd_data[2].pin    =GPIO_PIN2 ,
.lcd_data[2].direction    =GPIO_DIRECTION_OUTPUT ,
.lcd_data[2].logic    =GPIO_LOW ,

.lcd_data[3].port   = PORTD_INDEX,
.lcd_data[3].pin    =GPIO_PIN3 ,
.lcd_data[3].direction    =GPIO_DIRECTION_OUTPUT ,
.lcd_data[3].logic    =GPIO_LOW ,


};

chr_lcd_8bit_t lcd_2 = {
.lcd_rs.port        = PORTC_INDEX      , 
.lcd_rs.pin         = GPIO_PIN6      ,
.lcd_rs.direction   = GPIO_DIRECTION_OUTPUT      ,   
.lcd_rs.logic       = GPIO_LOW  , 

.lcd_en.port        = PORTC_INDEX      , 
.lcd_en.pin         = GPIO_PIN7      ,
.lcd_en.direction   = GPIO_DIRECTION_OUTPUT      ,   
.lcd_en.logic       = GPIO_LOW  ,

.lcd_data[0].port   = PORTD_INDEX,
.lcd_data[0].pin    =GPIO_PIN0 ,
.lcd_data[0].direction    =GPIO_DIRECTION_OUTPUT ,
.lcd_data[0].logic    =GPIO_LOW ,

.lcd_data[1].port   = PORTD_INDEX,
.lcd_data[1].pin    =GPIO_PIN1 ,
.lcd_data[1].direction    =GPIO_DIRECTION_OUTPUT ,
.lcd_data[1].logic    =GPIO_LOW ,

.lcd_data[2].port   = PORTD_INDEX,
.lcd_data[2].pin    =GPIO_PIN2 ,
.lcd_data[2].direction    =GPIO_DIRECTION_OUTPUT ,
.lcd_data[2].logic    =GPIO_LOW ,

.lcd_data[3].port   = PORTD_INDEX,
.lcd_data[3].pin    =GPIO_PIN3 ,
.lcd_data[3].direction    =GPIO_DIRECTION_OUTPUT ,
.lcd_data[3].logic    =GPIO_LOW ,

.lcd_data[4].port   = PORTD_INDEX,
.lcd_data[4].pin    =GPIO_PIN4 ,
.lcd_data[4].direction    =GPIO_DIRECTION_OUTPUT ,
.lcd_data[4].logic    =GPIO_LOW ,

.lcd_data[5].port   = PORTD_INDEX,
.lcd_data[5].pin    =GPIO_PIN5 ,
.lcd_data[5].direction    =GPIO_DIRECTION_OUTPUT ,
.lcd_data[5].logic    =GPIO_LOW ,

.lcd_data[6].port   = PORTD_INDEX,
.lcd_data[6].pin    =GPIO_PIN6 ,
.lcd_data[6].direction    =GPIO_DIRECTION_OUTPUT ,
.lcd_data[6].logic    =GPIO_LOW ,

.lcd_data[7].port   = PORTD_INDEX,
.lcd_data[7].pin    =GPIO_PIN7 ,
.lcd_data[7].direction    =GPIO_DIRECTION_OUTPUT ,
.lcd_data[7].logic    =GPIO_LOW ,

};
led_t led1 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN5, .led_status = GPIO_HIGH};
led_t led2 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN2, .led_status = GPIO_HIGH};
led_t led3 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN3, .led_status = GPIO_LOW};
led_t led4 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN4, .led_status = GPIO_LOW};

void RB4_HIGH_Int_APP_ISR(void){
    led_turn_on(&led1);
    __delay_ms(1000);
        led_turn_off(&led2);

}

void RB4_LOW_Int_APP_ISR(void){
    led_turn_on(&led2);
    __delay_ms(1000);
        led_turn_off(&led1);

}

void RB5_HIGH_Int_APP_ISR(void){
    led_turn_off(&led1);
}

void RB5_LOW_Int_APP_ISR(void){
    led_turn_off(&led2);
}

void RB6_HIGH_Int_APP_ISR(void){
    led_turn_on(&led3);
}

void RB6_LOW_Int_APP_ISR(void){
    led_turn_on(&led4);
}

void RB7_HIGH_Int_APP_ISR(void){
    led_turn_off(&led3);
}

void RB7_LOW_Int_APP_ISR(void){
    led_turn_off(&led4);
}



interrupt_RBx_t rb4_int_obj = {
  .EXT_InterruptHandler_HIGH =  RB4_HIGH_Int_APP_ISR,
  .EXT_InterruptHandler_LOW =  RB4_LOW_Int_APP_ISR,
  .priority = INTERRUPT_HIGH_PRIORITY,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = GPIO_PIN4,
  .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t rb5_int_obj = {
  .EXT_InterruptHandler_HIGH =  RB5_HIGH_Int_APP_ISR,
  .EXT_InterruptHandler_LOW =  RB5_LOW_Int_APP_ISR,
  .priority = INTERRUPT_HIGH_PRIORITY,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = GPIO_PIN5,
  .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t rb6_int_obj = {
  .EXT_InterruptHandler_HIGH =  RB6_HIGH_Int_APP_ISR,
  .EXT_InterruptHandler_LOW =  RB6_LOW_Int_APP_ISR,
  .priority = INTERRUPT_HIGH_PRIORITY,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = GPIO_PIN6,
  .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t rb7_int_obj = {
  .EXT_InterruptHandler_HIGH =  RB7_HIGH_Int_APP_ISR,
  .EXT_InterruptHandler_LOW =  RB7_LOW_Int_APP_ISR,
  .priority = INTERRUPT_HIGH_PRIORITY,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = GPIO_PIN7,
  .mcu_pin.direction = GPIO_DIRECTION_INPUT
};


int main() { 
    Std_ReturnType ret = E_NOT_OK;
//
//    application_intialize();
//    ret = lcd_4bit_intialize(&lcd_1);
  //  ret = lcd_4bit_intialize(&lcd_1);
//
//    while (1) { 
//        ret =lcd_4bit_send_char_data(&lcd_1,'A');
//        //  ret =lcd_8bit_send_char_data_pos(&lcd_2,4,4,'A');
//
//     
////    }

      
//    ret = led_initialize(&led1);
//    ret = led_initialize(&led2);
//    ret = led_initialize(&led3);
//    ret = led_initialize(&led4);
////    
//    ret = Interrupt_INTx_Init(&rb4_int_obj);
////    ret = Interrupt_RBx_Init(&rb5_int_obj);
////    ret = Interrupt_RBx_Init(&rb6_int_obj);
////    ret = Interrupt_RBx_Init(&rb7_int_obj);
////    
    
//    ret = Data_EEPROM_WriteByte(0x3FF,6);
    
//    e2prom_w(0x3FF,6);
    
//    while(1){
//    }
    return (EXIT_SUCCESS);
}


void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    
  //  ret = lcd_8bit_intialize(&lcd_2);
}

