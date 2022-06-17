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
#include "freertos/timers.h"

// #include "scheduler.c"
// #include "task.c"

#define TASKR "r_func"
#define TASK1 "A_Function"
#define TASK2 "B_Function"
#define TASK3 "C_Function"
#define ATIMER "ATimerCallback"


int ahihi = 10;
int ihaha = 5;
TimerHandle_t tmHdl1;
TimerHandle_t tmHdl2;

void ATimerCallback(TimerHandle_t xTimer){
    // ESP_LOGI(ATIMER, "Id: %d", (int) pvTimerGetTimerID(xTimer));
    int id = (int) pvTimerGetTimerID(xTimer);
    // if(id == 0) printf("ahihi\n");
    // else if (id == 1) printf("ihaha\n");
    switch (id)
    {
    case 0:
        
	
	if(!ahihi) {
		vTimerSetReloadMode(tmHdl1, pdFALSE);
		//if(vTimerSetReloadMode(tmHdl1, pdFALSE) != pdPASS){

    		//}	
	}
	else printf("ahihi\n");	
	ahihi--;
        break;
    case 1:
        
	
	if(!ihaha) {
		vTimerSetReloadMode(tmHdl2, pdFALSE);
		//if(vTimerSetReloadMode(tmHdl2, pdFALSE) != pdPASS){

    		//}	
	}
	else printf("ihaha\n");
	ihaha--;
        break;
    default:
        break;
    }
    // printf("Id: %d", (int) pvTimerGetTimerID(xTimer));
}

void app_main(void)
{
    
    tmHdl1 = xTimerCreate(
                            "Atimer",
                            pdMS_TO_TICKS(2000),
                            pdTRUE,
                            (void*) 0,
                            ATimerCallback
                        );

    tmHdl2 = xTimerCreate(
                            "Btimer",
                            pdMS_TO_TICKS(3000),
                            pdTRUE,
                            (void*) 1,
                            ATimerCallback
                        );

    if(xTimerStart(tmHdl1, 0) != pdPASS){

    }
    if(xTimerStart(tmHdl2, 0) != pdPASS){

    }


}
