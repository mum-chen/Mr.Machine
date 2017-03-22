/*
 * File       : led.c
 * This file is part of Mr.Machine
 * COPYRIGHT (C) 2017, Mr.Machine Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-03-23     MiaoBin      the first version
 */

#ifndef __LED_H__
#define __LED_H__

#include <rtthread.h>

void rt_hw_led_init(void);
void rt_hw_led_on(rt_int8_t led);
void rt_hw_led_off(rt_int8_t led);

static void led_thread_entry(void* parameter);
int rt_led_init(void);

#endif
