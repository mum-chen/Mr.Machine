/*
 * File       : led.c
 * This file is part of Mr.Machine
 * COPYRIGHT (C) 2017, Mr.Machine Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-03-23     MiaoBin      the first version
 */
 
#include <board.h>
#include <led.h>

#define led1_rcc                    RCC_AHB1Periph_GPIOE
#define led1_gpio                   GPIOE
#define led1_pin                    (GPIO_Pin_3)

#define led2_rcc                    RCC_AHB1Periph_GPIOE
#define led2_gpio                   GPIOE
#define led2_pin                    (GPIO_Pin_4)

#define led3_rcc                    RCC_AHB1Periph_GPIOG
#define led3_gpio                   GPIOG
#define led3_pin                    (GPIO_Pin_9)

static rt_uint8_t led_stack[ 512 ];
static struct rt_thread led_thread;

void rt_hw_led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(led1_rcc|led2_rcc|led3_rcc, ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_InitStructure.GPIO_Pin   = led1_pin;
	GPIO_Init(led1_gpio, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin   = led2_pin;
	GPIO_Init(led2_gpio, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = led3_pin;
	GPIO_Init(led3_gpio, &GPIO_InitStructure);
}

void rt_hw_led_off(rt_int8_t led)
{
	switch (led)
	{
	case 1:
		GPIO_SetBits(led1_gpio, led1_pin);
		break;
	case 2:
		GPIO_SetBits(led2_gpio, led2_pin);
		break;
	case 3:
		GPIO_SetBits(led3_gpio, led3_pin);
		break;
	default:
		break;
	}
}

void rt_hw_led_on(rt_int8_t led)
{
	switch (led)
	{
	case 1:
		GPIO_ResetBits(led1_gpio, led1_pin);
		break;
	case 2:
		GPIO_ResetBits(led2_gpio, led2_pin);
		break;
	case 3:
		GPIO_ResetBits(led3_gpio, led3_pin);
		break;
	default:
		break;
	}
}

static void led_thread_entry(void* parameter)
{
	rt_hw_led_init();

	while (1)
	{
		rt_hw_led_on(1);  // led1 on
		rt_hw_led_off(2); // led2 off
		rt_hw_led_off(3); // led3 off
		rt_thread_delay(RT_TICK_PER_SECOND); // sleep 1 second and switch to other thread

		rt_hw_led_on(2);
		rt_hw_led_off(1);
		rt_hw_led_off(3);
		rt_thread_delay(RT_TICK_PER_SECOND);
		
		rt_hw_led_on(3);
		rt_hw_led_off(1);
		rt_hw_led_off(2);
		rt_thread_delay(RT_TICK_PER_SECOND);
	}
}

int rt_led_init(void)
{
	rt_err_t result;
	
	/* init led thread */
	result = rt_thread_init(&led_thread,
													"led",
													led_thread_entry,
													RT_NULL,
													(rt_uint8_t*)&led_stack[0],
													sizeof(led_stack),
													20,
													5);
	if (result == RT_EOK)
	{
		rt_thread_startup(&led_thread);
	}
	
	return 0;
}
