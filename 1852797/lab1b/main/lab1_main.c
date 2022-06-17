/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_spi_flash.h"


#include "tasks.c"


void app_main(void)
{
    
    xTaskCreate(&stuId_Function, "stuid_task", 2048, NULL, 4, NULL);
    xTaskCreate(&btnPrint_Function, "btn_task", 2048, NULL, 5, NULL);

}
