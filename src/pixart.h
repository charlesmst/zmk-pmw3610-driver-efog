#pragma once

/**
 * @file pixart.h
 *
 * @brief Common header file for all optical motion sensor by PIXART
 */

#include <zephyr/device.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>

#ifdef __cplusplus
extern "C" {
#endif

/* device data structure */
struct pixart_data {
    const struct device          *dev;
    bool                         sw_smart_flag;

    struct gpio_callback         irq_gpio_cb;
    struct k_work                trigger_work;

    struct k_work_delayable      init_work;
    int                          async_init_step;
    int                          init_retry_count;
    int                          init_retry_attempts;

    bool                         ready;
    int                          err;

    bool                         data_ready;
    uint8_t                      data_index;
    int64_t                      dx, dy;

    uint8_t                      active_perf;

#if defined(CONFIG_PMW3610_RATE_CYCLE_GPIO)
    struct gpio_callback         rate_cycle_gpio_cb;
    struct k_work_delayable      rate_cycle_work;
    uint8_t                      rate_cycle_idx;
#endif

#if IS_ENABLED(CONFIG_PMW3610_IGNORE_AFTER_REST) || IS_ENABLED(CONFIG_PMW3610_ANTI_WARP)
    uint64_t                     last_data;
#endif
};

struct pixart_config {
    uint8_t id;
	struct spi_dt_spec spi;
    struct gpio_dt_spec irq_gpio;
    struct gpio_dt_spec rst_gpio;
    uint16_t cpi;
    uint8_t evt_type;
    uint8_t x_input_code;
    uint8_t y_input_code;
    bool xy_swap;
    bool x_invert;
    bool y_invert;
    bool force_awake;
    bool force_high_performance;
    bool enable_pm_support;
    uint8_t init_retry_count;
    uint16_t init_retry_interval;

#if defined(CONFIG_PMW3610_OUTPUT_RATE_NOTIFY)
    int32_t usb_rate_ms;
    int32_t ble_rate_ms;
#endif

#if defined(CONFIG_PMW3610_RATE_CYCLE_GPIO)
    struct gpio_dt_spec rate_cycle_gpio;
    const int32_t *rate_cycle_rates_ms;
    size_t rate_cycle_rates_count;
#endif
};

#ifdef __cplusplus
}
#endif
