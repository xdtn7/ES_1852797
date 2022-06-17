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
#define TASKT "T_Function"
#define NUM_TASK 3

int marks[NUM_TASK] = {0,0,0};




QueueHandle_t xQueue1;
typedef struct xmessage
{
    int id;
    int indicat;
};

void r_func (void* pvParameters) {
    int indicator = -1;
    int id = 0;
    int dec = 0;

    while(1){
        struct xmessage * ms = (struct xmessage *)malloc(sizeof(struct xmessage));

        ms->indicat = 99;
        id++;
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
        
        ms->id = id;
        ms->indicat = indicator;

        if( xQueue1 != 0 )
        {
            ESP_LOGI(TASKR, "queue. indicator: %d, id: %d in %d \n", ms->indicat, ms->id, xTaskGetTickCount());
            if( xQueueSend( xQueue1,
                                ( void * ) ms,
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
    
    
    struct xmessage * rec=(struct xmessage *)malloc(sizeof(struct xmessage));
    while(1){
        // printf("1. ");
        if( xQueue1 != 0 )
        {
            if( xQueuePeek( xQueue1,
                            ( void * ) rec,
                            ( TickType_t ) 0 )  ) 
            {
                ESP_LOGI(TASK1, "1. Receive: %d, id= %d\n", rec->indicat, rec->id);
                if(rec->indicat==1) {
                    ESP_LOGI(TASK1, "1. Doing task A\n");

                }
                marks[0] = rec->id;

                
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void B_Function (void* pvParameters) {
    
    
    struct xmessage * rec=(struct xmessage *)malloc(sizeof(struct xmessage));
    while(1){

        if( xQueue1 != 0 )
            {
                
                if( xQueuePeek( xQueue1,
                            ( void * ) rec,
                            ( TickType_t ) 0 )  ) 
                {
                    ESP_LOGI(TASK1, "2. Receive: %d, id= %d\n", rec->indicat, rec->id);
                    if(rec->indicat==2) {
                        ESP_LOGI(TASK2, "2. Doing task B\n");

                    }
                    marks[1] = rec->id;
                }
            }
            vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void C_Function (void* pvParameters) {
    
   
    struct xmessage * rec=(struct xmessage *)malloc(sizeof(struct xmessage));
    while(1){
        if( xQueue1 != 0 )
        {
            if( xQueuePeek( xQueue1,
                            ( void * ) rec,
                            ( TickType_t ) 0 )  ) 
            {
                ESP_LOGI(TASK3, "3. Receive: %d, id= %d\n", rec->indicat, rec->id);
                if(rec->indicat==3) {
                    ESP_LOGI(TASK3, "3. Doing task C\n");
                }
                marks[2] = rec->id;
            }
            
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void T_Function (void* pvParameters) {
    
    struct xmessage * rec =(struct xmessage *)malloc(sizeof(struct xmessage));
    while(1){
        if( xQueue1 != 0 )
        {

            bool remain = false;
            if( xQueuePeek( xQueue1,
                            ( void * ) rec,
                            ( TickType_t ) 0 )  ) 
            {
                
                for(int i = 0; i < NUM_TASK; i++) {
                    if(rec->id != marks[i]) remain = true;
                }
                ESP_LOGI(TASKT, "T. consider: id=%d indi=%d, [%d, %d, %d] => delete?: %d\n", rec->id, rec->indicat,marks[0], marks[1], marks[2], !remain);
                
            }
            if(!remain){
                if( xQueueReceive( xQueue1,
                                ( void * ) rec,
                                ( TickType_t ) 0 ) != pdPASS )
                            {
                                printf("ERROR TRASHING\n");
                                
                            }
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    
    xQueue1 = xQueueCreate (5, sizeof( struct xmessage )) ;

    xTaskCreate(&r_func, "R_task", (1024*5), NULL, 1, NULL);

    xTaskCreate(&A_Function, "A_task", 2048, NULL, 0, NULL);

    xTaskCreate(&B_Function, "B_task", 2048, NULL, 0, NULL);
    
    xTaskCreate(&C_Function, "C_task", 2048, NULL, 0, NULL);
    
    xTaskCreate(&T_Function, "Trash_task", (1024*5), NULL, 0, NULL);
}
