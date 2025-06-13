#include "TaskDongCo.h"

#define IN1 6
#define IN2 7
#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0

#define t 5000

int i=0;
void chaydongco(void *pvParameters)
{
    while (true)
    {
        if(i==0)
        {
            motor_1_Tien(MAX_SPEED);
            i=1;
        }
        else if(i==1)
        {
            motor_1_Dung();
            i=2;
        }
        else if(i==2)
        {
            motor_1_Lui(MAX_SPEED);
            i=0;
        }


        // motor_1_Tien(100);
        // vTaskDelay(t / portTICK_PERIOD_MS);
        // motor_1_Dung();
        // vTaskDelay(t / portTICK_PERIOD_MS);
        // motor_1_Lui(100);

        vTaskDelay(t / portTICK_PERIOD_MS);
    }
}

void initDongCo()
{
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
    xTaskCreate(chaydongco, "run", 2048, NULL, 1, NULL);
}

void motor_1_Dung() {
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
    publishData("Dong_Co","STOP");
}

void motor_1_Tien(int speed) { //speed: từ 0 - MAX_SPEED
	speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
	digitalWrite(IN1, HIGH);// chân này không có PWM
	digitalWrite(IN2, 255 - speed);
    publishData("Dong_Co","TIEN");
}

void motor_1_Lui(int speed) {
	speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
	digitalWrite(IN1, HIGH);// chân này không có PWM
	digitalWrite(IN2, speed);
    publishData("Dong_Co","LUI");
}