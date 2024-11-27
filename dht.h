#ifndef _DHT_H_
#define _DHT_H_

#include <stdint.h>
#include <stdbool.h>
#include <hardware/pio.h>
#include "time.h"
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * DHT sensor model.
 */
typedef enum dht_model_t {
    DHT11,
    DHT12,
    DHT21,
    DHT22,
} dht_model_t;

/**
 * DHT sensor.
 */
typedef struct dht_t {
    PIO pio;
    uint8_t model;
    uint8_t pio_program_offset;
    uint8_t sm;
    uint8_t dma_chan;
    uint8_t data_pin;
    uint8_t data[5];
    uint32_t start_time;
} dht_t;

// --- //
// dht //
// --- //

#define dht_wrap_target 0
#define dht_wrap 16

#define dht_start_signal_clocks_per_loop 1
#define dht_pulse_measurement_clocks_per_loop 2

static const uint16_t dht_program_instructions[] = {
    //     .wrap_target
    0x0080, //  0: jmp    y--, 0
    0xe080, //  1: set    pindirs, 0
    0x00c2, //  2: jmp    pin, 2
    0x00c5, //  3: jmp    pin, 5
    0x0003, //  4: jmp    3
    0x00c5, //  5: jmp    pin, 5
    0x00c8, //  6: jmp    pin, 8
    0x0006, //  7: jmp    6
    0xa047, //  8: mov    y, osr
    0x00cb, //  9: jmp    pin, 11
    0x000f, // 10: jmp    15
    0x0089, // 11: jmp    y--, 9
    0xe021, // 12: set    x, 1
    0x4021, // 13: in     x, 1
    0x0005, // 14: jmp    5
    0x4061, // 15: in     null, 1
    0x0006, // 16: jmp    6
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program dht_program = {
    .instructions = dht_program_instructions,
    .length = 17,
    .origin = -1,
};

static inline pio_sm_config dht_program_get_default_config(uint offset)
{
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + dht_wrap_target, offset + dht_wrap);
    return c;
}
#endif

/**
 * Measurement result.
 */
typedef enum dht_result_t {
    DHT_RESULT_OK, /**< No error.*/
    DHT_RESULT_TIMEOUT, /**< DHT sensor not responding. */
    DHT_RESULT_BAD_CHECKSUM, /**< Sensor data doesn't match checksum. */
} dht_result_t;

float celsius_to_fahrenheit(float temperature);
static uint get_start_pulse_duration_us(dht_model_t model);
static uint get_pio_sm_clocks(uint us);

void dht_init(dht_t *dht, dht_model_t model, PIO pio, uint8_t data_pin, bool pull_up);
void dht_deinit(dht_t *dht);
void dht_start_measurement(dht_t *dht);
dht_result_t dht_finish_measurement_blocking(dht_t *dht, float *humidity, float *temperature_c);

// 추가된 함수들 선언
static bool pio_sm_is_enabled(PIO pio, uint sm);
static void configure_dma_channel(uint chan, PIO pio, uint sm, uint8_t *write_addr);
static void dht_program_init(PIO pio, uint sm, uint offset, dht_model_t model, uint data_pin);

static float decode_humidity(dht_model_t model, uint8_t b0, uint8_t b1);
static float decode_temperature(dht_model_t model, uint8_t b0, uint8_t b1);
// Removed declaration of time_us_32 to avoid redefinition conflict with the SDK implementation
#ifdef __cplusplus
}
#endif

#endif // _DHT_H_
