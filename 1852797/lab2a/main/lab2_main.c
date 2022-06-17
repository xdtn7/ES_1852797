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
#include "freertos/queue.h"
#include "esp_chip_info.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"
#include "esp_log.h"

// #include "scheduler.c"
// #include "task.c"

#define TASKR "r_func"
#define TASK1 "A_Function"
#define TASK2 "B_Function"
#define TASK3 "C_Function"
#define IDLE "idle_task"


unsigned int indicator = -1;
QueueHandle_t xQueue1;

void r_func (void* pvParameters) {
    
    int dec = 0;
    while(1){
        // printf("zero. ");
        // printf("loop");
        if(dec==3) dec = 1;
        else dec++; 

        switch (dec)
        {
        case 1:
            /* code */
            indicator = 1;
            break;
        case 2:
            /* code */
            indicator = 2;
            break;
        case 3:
            /* code */
            indicator = 3;
            break;
        case 4:
            /* code */
            indicator = 4;
            break;
        default:
            printf("ERROR FOUND");
            indicator = 0;
            break;
        }
        
        if( xQueue1 != 0 )
        {
            /* Send an unsigned long.  Wait for 10 ticks for space to become
            available if necessary. */
            ESP_LOGI(TASKR, "queue. indicator: %d in %d \n", indicator, xTaskGetTickCount());
            if( xQueueSend( xQueue1,
                                ( void * ) &indicator,
                                ( TickType_t ) 10 ) != pdPASS )
            {
                /* Failed to post the message, even after 10 ticks. */
                printf("ERROR SEND");
                break;
            }
        }
        // printf("\n");
        vTaskDelay(10 / portTICK_PERIOD_MS);

    }
    vTaskDelete(NULL);
}

void A_Function (void* pvParameters) {
    vTaskDelay(50 / portTICK_PERIOD_MS);
    int rec = 0;
    while(1) ESP_LOGI(TASK1, "1. A in %d \n", xTaskGetTickCount());
    vTaskDelete(NULL);
}


void B_Function (void* pvParameters) {
    
    int rec = 0;
    while(1) ESP_LOGI(TASK2, "2. B in %d \n", xTaskGetTickCount());
    vTaskDelete(NULL);
}

void C_Function (void* pvParameters) {
    // vTaskDelay(20 / portTICK_PERIOD_MS);
    int rec = 0;
    while(1)
        ESP_LOGI(TASK3, "3. C in %d \n", xTaskGetTickCount());
    vTaskDelete(NULL);
}

void app_main(void)
{
    
    // xQueue1 = xQueueCreate (5, sizeof( unsigned long )) ;

    // xTaskCreate(&r_func, "R_task", (1024*5), NULL, 5, NULL);

    xTaskCreate(&B_Function, "B_task", 2048, NULL, 1, NULL);
    
    xTaskCreate(&C_Function, "C_task", 2048, NULL, 1, NULL);

    xTaskCreate(&A_Function, "A_task", 2048, NULL, 2, NULL);

    
    
    

    

    printf("Here");
    // printf("Hello world!\n");

    // /* Print chip information */
    // esp_chip_info_t chip_info;
    // esp_chip_info(&chip_info);
    // printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
    //        CONFIG_IDF_TARGET,
    //        chip_info.cores,
    //        (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
    //        (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    // printf("silicon revision %d, ", chip_info.revision);

    // printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
    //        (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    // printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

    // for (int i = 8; i >= 0; i--)
    // {
    //     printf("Restarting in %d seconds...\n", i);
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    // }
    // printf("Restarting now.\n");
    // fflush(stdout);
    // esp_restart();
}
