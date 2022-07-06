#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_now.h"
#include "esp_crc.h"
#include "espnow_basic_config.h"
#include "uart_function.c"
#include "driver/uart.h"
#include "driver/gpio.h"

//#include "freertos/event_groups.h"

#include "sdkconfig.h"
#define BTN_PIN 3
static int count = 0;
static bool btn_flag = false;

const char *TAG = "ESPNOW_UART_MASTER";
xQueueHandle s_espnow_queue;
uint8_t s_broadcast_mac[ESP_NOW_ETH_ALEN] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
uint16_t s_espnow_seq[ESPNOW_DATA_MAX] = { 0, 0 };

espnow_send_param_t *my_data;
espnow_send_param_t *my_data2;
TaskHandle_t xHandle = NULL;
TaskHandle_t xHandle_return = NULL;


void nvs_init(){
	// Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK( nvs_flash_erase() );
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK( ret );
}

void my_data_populate(my_data_t *data)
{
	ESP_LOGI(TAG, "Populating my_data_t");
	memcpy(data->mac_addr, s_broadcast_mac, ESP_NOW_ETH_ALEN);
	data->button_pushed = 0;
}


static esp_err_t uart_espnow(void *arg)
{
    static const char *RX_TASK_TAG = "RX_TASK";
    esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    uint8_t* uart_data = (uint8_t*) malloc(RX_BUF_SIZE+1);
    static my_data_t data;

    while(1){
    	const int rxBytes = uart_read_bytes(UART, uart_data, RX_BUF_SIZE, 500 / portTICK_RATE_MS);
		if (rxBytes > 0) {
			uart_data[rxBytes] = '\0';
		    ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, uart_data);

		    my_data_populate(&data);


		    if(uart_data[0] == '2' && rxBytes == 1)
		    {
			  gpio_set_level(BLINK_GPIO, 1);
			  vTaskSuspend( xHandle );	//  vTaskResume(TaskHandle_t xTaskToResume)
//			  my_data_t *send_param = (my_data_t *)arg;

			  esp_err_t err = esp_now_send(data.mac_addr, (uint8_t*)&data, sizeof(data));
			  if (err != ESP_OK) {
				  ESP_LOGE(TAG, "Send error");
//				  espnow_deinit(send_param);
//				  vTaskDelete(NULL);
				  return ESP_FAIL;
			  }else{
				  ESP_LOGI(TAG, "Send to Target");

			  }
		    }
		    else if(uart_data[0] == '0' && rxBytes == 1)
		    {
			  gpio_set_level(BLINK_GPIO, 0);
			  vTaskResume(xHandle);
		    }else if(uart_data[0]== '3' && rxBytes == 1){


		    }
		}
    }
    free(uart_data);
    return ESP_OK;
}


void app_main(void)
{

	nvs_init();
	uart_init();
    wifi_init();
    espnow_init();

    gpio_set_direction(BTN_PIN, GPIO_MODE_INPUT);
	gpio_set_pull_mode(BTN_PIN, GPIO_PULLUP_ONLY);
//    broadcast_init(my_data);

    /* Initialize sending parameters. */
    my_data = malloc(sizeof(espnow_send_param_t));
	memset(my_data, 0, sizeof(espnow_send_param_t));
	if (my_data == NULL) {
		ESP_LOGE(TAG, "Malloc send parameter fail");
		vSemaphoreDelete(s_espnow_queue);
		esp_now_deinit();

	}else{
		ESP_LOGI(TAG, "broadcast initialize");
	}

	my_data->unicast = true;						// 1 : 1 comunication
	my_data->broadcast = false;
	my_data->state = 0;
	my_data->magic = esp_random();
	my_data->count = CONFIG_ESPNOW_SEND_COUNT;		// 100
	my_data->delay = CONFIG_ESPNOW_SEND_DELAY;		// 1000 = 1s
	my_data->len = CONFIG_ESPNOW_SEND_LEN;			// 10
	my_data->buffer = malloc(CONFIG_ESPNOW_SEND_LEN);
	if (my_data->buffer == NULL) {
		ESP_LOGE(TAG, "Malloc send buffer fail");
		free(my_data);
		vSemaphoreDelete(s_espnow_queue);
		esp_now_deinit();

	}
	memcpy(my_data->dest_mac, s_broadcast_mac, ESP_NOW_ETH_ALEN);
	espnow_data_prepare(my_data);

	my_data2 = malloc(sizeof(espnow_send_param_t));
	memset(my_data2, 0, sizeof(espnow_send_param_t));
	if (my_data2 == NULL) {
		ESP_LOGE(TAG, "Malloc send parameter fail");
		vSemaphoreDelete(s_espnow_queue);
		esp_now_deinit();

	}else{
		ESP_LOGI(TAG, "broadcast initialize");
	}

	my_data2->unicast = true;						// 1 : 1 comunication
	my_data2->broadcast = false;
	my_data2->state = 0;
	my_data2->magic = esp_random();
	my_data2->count = CONFIG_ESPNOW_SEND_COUNT;		// 100
	my_data2->delay = CONFIG_ESPNOW_SEND_DELAY;		// 1000 = 1s
	my_data2->len = CONFIG_ESPNOW_SEND_LEN;			// 10
	my_data2->buffer = malloc(CONFIG_ESPNOW_SEND_LEN);
	if (my_data2->buffer == NULL) {
		ESP_LOGE(TAG, "Malloc send buffer fail");
		free(my_data2);
		vSemaphoreDelete(s_espnow_queue);
		esp_now_deinit();

	}
	memcpy(my_data2->dest_mac, s_broadcast_mac, ESP_NOW_ETH_ALEN);
	espnow_data_prepare(my_data2);




    ESP_LOGI(TAG, "Setup Done");
	vTaskDelay(1000/ portTICK_PERIOD_MS);

	xTaskCreate(received_queue_task, "espnow_task", 2048, my_data, 4, &xHandle);
//	xTaskCreate((void *)uart_espnow, "uart_rx_task", 1024*2, NULL, configMAX_PRIORITIES, NULL);		// higher priority
	//	xTaskCreate(tx_task, "uart_tx_task", 1024*2, NULL, configMAX_PRIORITIES-1, NULL);

//	esp_now_unregister_recv_cb();
	while(true)
	{
		if(gpio_get_level(BTN_PIN) == 0)
		{

			vTaskDelay(5 / portTICK_RATE_MS);
			printf("Button Pressed %d\r\n", count);
			count++;
			if(count == 100)
				break;
		}
		else
		{
			count = 0;
		}
		vTaskDelay(10 / portTICK_RATE_MS);
	}
	ESP_LOGI(TAG, "STOP COUNT");
	if(btn_flag == 0)
	{
//		esp_now_register_recv_cb(espnow_recv_cb);

//		xTaskCreate(espnow_return_task,"espnow_returen_task", 2048, my_data2, configMAX_PRIORITIES, &xHandle_return);
//		my_data2->dest_mac = ;
		for (int i=0; i<3; i++)
		{
			if (esp_now_send(my_data2->dest_mac, my_data2->buffer, my_data2->len) != ESP_OK) {
				ESP_LOGE(TAG, "Send error");
				espnow_deinit(my_data2);
				vTaskDelete(NULL);
			}
			vTaskDelay(500/ portTICK_RATE_MS);
			btn_flag = 1;
		}

	}
}
