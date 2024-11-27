#include "dht.h"
#include <stdio.h>
#include <pico/stdlib.h>

#define DHT_MODEL DHT22
#define DATA_PIN 28

int main() {

    stdio_init_all();
    sleep_ms(1000); // Wait for serial connection

    char dht_string[600];

    dht_t dht;
    dht_init(&dht, DHT_MODEL, pio0, DATA_PIN, true /* pull_up */);

    while (1) {
        dht_start_measurement(&dht);
        float humidity;
        float temperature_c;
        dht_result_t result = dht_finish_measurement_blocking(&dht, &humidity, &temperature_c);

        if (result == DHT_RESULT_OK)
        {
            snprintf(dht_string, sizeof(dht_string), "%.1f C (%.1f F), %.1f%% humidity\n",
            temperature_c, celsius_to_fahrenheit(temperature_c), humidity);
            printf("%s\r\n",dht_string);
        } 
        else if (result == DHT_RESULT_TIMEOUT) {
            printf("DHT sensor not responding. Please check your wiring.\n");
        } else {
            printf("Bad checksum.\n");
        }
        sleep_ms(2000); // Wait 2 seconds between measurements
    }

    dht_deinit(&dht);
    return 0;
}
