#include "TaskDHT20.h"
#include "define.h"

DHT20 dht20;

void TaskTemperatureHumidity(void *pvParameters)
{
    while (true)
    {
        getValueDHT20();
        vTaskDelay(delay_time2 / portTICK_PERIOD_MS);
    }
}

void getValueDHT20()
{
    if (dht20.read() == DHT20_OK)
    {
        Serial.println(String(dht20.getTemperature()) + "-" + String(dht20.getHumidity()));
        publishData("feed_1", String(dht20.getTemperature()) + "-" + String(dht20.getHumidity()) );

    }
    else
    {
        Serial.println("Failed to read DHT20 sensor.");
    }
}

void initDHT20()
{
    Wire.begin(MY_SCL, MY_SDA);
    dht20.begin();
    xTaskCreate(TaskTemperatureHumidity, "DHT20", 2048, NULL, 1, NULL);
}
