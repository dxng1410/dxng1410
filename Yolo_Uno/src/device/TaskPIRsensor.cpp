#include "TaskPIRsensor.h"
#include "define.h"


int pirState = LOW;     // Bắt đầu với không có báo động

void TaskPIR(void *pvParameters)
{
    while (true)
    {
        getValuePIR();
        vTaskDelay(delay_time1 / portTICK_PERIOD_MS);
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
    xTaskCreate(TaskPIR, "PIR", 2048, NULL, 1, NULL);
}