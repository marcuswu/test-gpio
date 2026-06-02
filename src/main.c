/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/hwinfo.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   100

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

const struct device *port = DEVICE_DT_GET(DT_NODELABEL(gpio0));

#define NUM_BUTTONS 22
static const struct gpio_dt_spec buttons[NUM_BUTTONS] = {
    GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw1), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw2), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw3), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw4), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw5), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw6), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw7), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw8), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw9), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw10), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw11), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw12), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw13), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw14), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw15), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw16), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw17), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw18), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw19), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw20), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(sw21), gpios),
};

void gpio_config(void)
{
	if (!device_is_ready(port)) {
		LOG_ERR("GPIO device is not ready");
		return;
	}
	for (int i = 0; i < NUM_BUTTONS; i++) {
		int err = gpio_pin_configure_dt(&buttons[i], GPIO_INPUT | GPIO_PULL_UP | GPIO_ACTIVE_LOW);
		if (err != 0) {
			LOG_ERR("Failed to configure GPIO pin %d: %d", i, err);
			continue;
		}
	}
}

int main(void)
{
	uint32_t gpio_data = 0;
	gpio_config();
	while (1) {
		gpio_data = 0;
		gpio_port_get(port, &gpio_data);
		LOG_INF("GPIO data: 0x%08X", gpio_data);
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
