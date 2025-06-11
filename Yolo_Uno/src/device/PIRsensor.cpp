#include "PIRsensor.h"
#define delay_time 3000
#define ledPin 8        // chọn chân 13 báo hiệu LED
#define inputPin 6       // chọn ngõ tín hiệu vào cho PIR
int pirState = LOW;     // Bắt đầu với không có báo động

void TaskPIR(void *pvParameters)
{
    while (true)
    {
        getValuePIR();
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}

void getValuePIR(){
    	if (digitalRead(inputPin) == HIGH)                // nếu giá trị ở mức cao.(1)
	{
		digitalWrite(ledPin, HIGH); // LED On
		delay(150);
 
		if (pirState == LOW)
		{
			Serial.println("Motion detected!");
            publishData("feed_2", "Motion detected!" );
			pirState = HIGH;
		}
	}
	else
	{
		digitalWrite(ledPin, LOW);
		delay(300);
		if (pirState == HIGH)
		{
			Serial.println("Motion ended!");
            publishData("feed_2", "Motion ended!" );
			pirState = LOW;
		}
	}
}

void initPIR(){
    pinMode(ledPin, OUTPUT);
	pinMode(inputPin, INPUT);
	Serial.begin(9600);
    xTaskCreate(TaskPIR, "PIR", 2048, NULL, 1, NULL);
}