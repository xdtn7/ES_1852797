

#include "driver/gpio.h"

#define BTN_GPIO 0
#define HOLDING_STATE_TRIGGER 100

enum BTN_STATE {WAIT = 1, PRESS = 0, HOLD = 2};

void stuId_Function (void* pvParameters) {
    
    while(1){
        printf("Student ID: 1852797\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void btnPrint_Function (void* pvParameters) {
    
    //GPIO_DECLARING
    esp_rom_gpio_pad_select_gpio(BTN_GPIO);
    gpio_set_direction(BTN_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BTN_GPIO, GPIO_PULLUP_ONLY);

    //VARIABLE DECLARING
    enum BTN_STATE btn_state = WAIT;
    enum BTN_STATE prev_state = WAIT;
    enum BTN_STATE curr_state = WAIT;
    int cnt = 0;

    //STATE MACHINE
    while(1){
        
        prev_state = curr_state;
        curr_state = gpio_get_level(BTN_GPIO);

        switch (btn_state)
        {
        case WAIT:
            if(curr_state == PRESS) btn_state = PRESS;
            break;
        
        case PRESS:

            //DEBOUNCING
            if(prev_state != curr_state) printf("ESP32\n");
            //STATE CHANGING
            else {
                if (curr_state == PRESS) cnt++;
                else btn_state = WAIT;
                if (cnt == HOLDING_STATE_TRIGGER) btn_state = HOLD;
            }
            break;
        
        case HOLD:
            if(prev_state == curr_state) printf("ESP32\n");
            else {
                cnt = 0;
                btn_state = WAIT;
            }
        
            break;
        default:
            break;
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    

    vTaskDelete(NULL);
}