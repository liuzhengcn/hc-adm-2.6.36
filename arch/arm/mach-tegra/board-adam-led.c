/*
 * kernel/arch/arm/mach-tegra/board-adam-led.c 
 *
 * Copyright (C) 2011 Malata, Corp. All Right Reserved.
 */

#define DEBUG
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/leds.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#include "gpio-names.h"

#include <mach/iomap.h>
#include <mach/io.h>
#include <linux/serial_reg.h>

static struct gpio_led gpio_leds[] = {
	{
		.name = "cpu",
		.default_trigger = "heartbeat",
		.gpio = TEGRA_GPIO_PI3, 
		.active_low = 0,
		.retain_state_suspended = 0, 
	}, 
	{
		.name = "cpu-busy",
		.gpio = TEGRA_GPIO_PI4,
		.active_low = 0,
		.retain_state_suspended = 0, 
		.default_state = LEDS_GPIO_DEFSTATE_OFF, 
	}
};

static struct gpio_led_platform_data gpio_led_platform_data = {
	.num_leds = ARRAY_SIZE(gpio_leds),
	.leds = gpio_leds,
	.gpio_blink_set = NULL, 
};

static struct platform_device gpio_led_platform_device = {
	.name = "leds-gpio",
	.id = -1, 
	.dev = {
		.platform_data = &gpio_led_platform_data, 
	}
};

int __init adam_led_init(void)
{
	int i;
	pr_debug("%s", __func__);
	tegra_gpio_enable(TEGRA_GPIO_PI3);
	gpio_request(TEGRA_GPIO_PI3, "led1");

	for (i = 0; i < 10; i++) {
		gpio_direction_output(TEGRA_GPIO_PI3, i%2);
		msleep(300);
	}
	/*
	for (i = 0; i < ARRAY_SIZE(gpio_leds); i++) {
		tegra_gpio_enable(gpio_leds[i].gpio);
	}
	*/
	return platform_device_register(&gpio_led_platform_device);
}

