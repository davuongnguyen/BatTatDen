#include <Arduino.h>

#define pinLED D0
#define pinButton D1

unsigned long time_delay = 0;

unsigned long time_prev = 0;

/**
 * @brief Hàm điều khiển đèn
 *
 * @param state Trạng thái đèn
 */
void control_Led(bool state);

/**
 * @brief Đọc giá trị nút bấm
 *
 * @return byte Trả về trường hợp bấm nút
 */
byte read_button();

/**
 * @brief In ra man hinh LCD
 * 
 */
void monitor();

void setup()
{
    Serial.begin(115200);

    // put your setup code here, to run once:
    pinMode(pinLED, OUTPUT);
    digitalWrite(pinLED, HIGH);

    pinMode(pinButton, INPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (read_button() == 1)
    {
        time_delay += 5000;
        Serial.println(time_delay);
    }

    if (time_delay == 0)
    {
        control_Led(HIGH);
    }
    else
    {
        control_Led(LOW);

        // Giảm time_delay sau mỗi giây
        if ((unsigned long)(millis() - time_prev) > 1000)
        {

            time_delay -= 1000;
            monitor();

            // cập nhật lại biến time_prev
            time_prev = millis();
        }
    }
}

void control_Led(bool state)
{
    digitalWrite(pinLED, state);
}

byte read_button()
{
    if (digitalRead(pinButton) == LOW)
    {
        delay(500);
        Serial.println("Bam nut");

        return 1;
    }
    else
    {
        return 0;
    }
}

void monitor()
{

}