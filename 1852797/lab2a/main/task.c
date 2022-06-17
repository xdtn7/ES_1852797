#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"

#define BTN_GPIO 0
#define HOLDING_STATE_TRIGGER 60

// enum BTN_STATE {WAIT = 1, PRESS = 0, HOLD = 2};

void r_func (void* pvParameters) {
    int dec = 0;
    while(1){
        if(dec==4) dec = 1;
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
            if( xQueueSendToBack( xQueue1,
                                ( void * ) &indicator,
                                ( TickType_t ) 10 ) != pdPASS )
            {
                /* Failed to post the message, even after 10 ticks. */
                printf("ERROR SEND");
                break;
            }
        }
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void A_Function (void* pvParameters) {
    int rec = 0;
    if( xQueue1 != 0 )
    {
        /* Send an unsigned long.  Wait for 10 ticks for space to become
        available if necessary. */
        if( xQueueReceive( xQueue1,
                            ( void * ) &rec,
                            ( TickType_t ) 10 ) != pdPASS )
        {
            if(rec==1) printf("A");
            
        }
        else {
            printf("ERROR SEND");
            break;
        }
    }
    
    // int a = 0;
    
    // while(1){
    //     printf("A: %d\n", a++);
    //     // vTaskDelay(1 / portTICK_PERIOD_MS);
    //     if(a == 5) break;
    // }
    vTaskDelete(NULL);
}

void B_Function (void* pvParameters) {
    int rec = 0;
    if( xQueue1 != 0 )
    {
        /* Send an unsigned long.  Wait for 10 ticks for space to become
        available if necessary. */
        if( xQueueReceive( xQueue1,
                            ( void * ) &rec,
                            ( TickType_t ) 10 ) != pdPASS )
        {
            if(rec==2) printf("B");
            
        }
        else {
            printf("ERROR SEND");
            break;
        }
    }
    // vTaskDelay(1 / portTICK_PERIOD_MS);
    // int b = 0;
    // while(1){
    //     printf("B: %d\n", b++);
    //     // vTaskDelay(1 / portTICK_PERIOD_MS);
    //     if(b == 5) break;
    // }
    vTaskDelete(NULL);
}

void C_Function (void* pvParameters) {
    int rec = 0;
    if( xQueue1 != 0 )
    {
        /* Send an unsigned long.  Wait for 10 ticks for space to become
        available if necessary. */
        if( xQueueReceive( xQueue1,
                            ( void * ) &rec,
                            ( TickType_t ) 10 ) != pdPASS )
        {
            if(rec==3) printf("C");
            
        }
        else {
            printf("ERROR SEND");
            break;
        }
    }
    // int c = 0;
    // while(1){
    //     printf("C: %d\n", c++);
    //     // vTaskDelay(1 / portTICK_PERIOD_MS);
    //     if(c == 5) break;
    // }
    vTaskDelete(NULL);
}
