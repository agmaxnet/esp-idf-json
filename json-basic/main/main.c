/* The example of ESP-IDF
 *
 * This sample code is in the public domain.
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "cJSON.h"

static const char *TAG = "JSON";

void app_main()
{
	ESP_LOGI(TAG, "Serialize.....");
	cJSON *root;
	root = cJSON_CreateObject();
	esp_chip_info_t chip_info;
	esp_chip_info(&chip_info);
	cJSON_AddStringToObject(root, "version", IDF_VER);
	cJSON_AddNumberToObject(root, "cores", chip_info.cores);
	cJSON_AddTrueToObject(root, "flag_true");
	cJSON_AddFalseToObject(root, "flag_false");
	const char *my_json_string = cJSON_Print(root);
	ESP_LOGI(TAG, "my_json_string\n%s",my_json_string);
	cJSON_Delete(root);

	ESP_LOGI(TAG, "Deserialize.....");
	cJSON *root2 = cJSON_Parse(my_json_string);
	char *version = cJSON_GetObjectItem(root2,"version")->valuestring;
	int cores = cJSON_GetObjectItem(root2,"cores")->valueint;
	bool flag_true = cJSON_GetObjectItem(root2,"flag_true")->valueint;
	bool flag_false = cJSON_GetObjectItem(root2,"flag_false")->valueint;
	ESP_LOGI(TAG, "version=%s",version);
	ESP_LOGI(TAG, "cores=%d",cores);
	ESP_LOGI(TAG, "flag_true=%d",flag_true);
	ESP_LOGI(TAG, "flag_false=%d",flag_false);
	cJSON_Delete(root2);
}
