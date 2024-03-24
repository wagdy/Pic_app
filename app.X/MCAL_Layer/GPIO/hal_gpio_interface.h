/* 
 * File:   hal_gpio_interface.h
 * Author: elmogy
 *
 * Created on March 7, 2024, 12:43 PM
 */

#ifndef HAL_GPIO_INTERFACE_H
#define	HAL_GPIO_INTERFACE_H
#include "../../types.h"

typedef enum{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}pin_index_t;

typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;

typedef struct{
    u8 port : 3;      /* @ref port_index_t */
    u8 pin : 3;       /* @ref pin_index_t */
    u8 direction : 1; /* @ref direction_t */
    u8 logic : 1;     /* @ref logic_t */
}pin_config_t;


/* Section: Function Declarations */
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config);

Std_ReturnType gpio_port_direction_intialize(port_index_t port, u8 direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port, u8 *direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port, u8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port, u8 *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);



#endif	/* HAL_GPIO_INTERFACE_H */

