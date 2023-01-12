/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <Arduino.h>
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

void shutdown()
{
    for (int i = 10; i >= 0; i--) {
    	Serial.printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    Serial.printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}

void setup()
{
    Serial.printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    Serial.printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    Serial.printf("silicon revision %d, ", chip_info.revision);

    Serial.printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    Serial.printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());
}

volatile uint32_t loops=0;

void loop()
{
	loops++;
}


extern "C" void app_main()
{
	setup();

	while(1)
	{

		loop();
	}
}
