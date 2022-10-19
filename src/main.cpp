#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define pinLED D0
#define pinButton D1

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_MOSI D2
#define OLED_CLK D6
#define OLED_DC D7
#define OLED_CS D5
#define OLED_RESET D4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

int time_delay = 0;
byte seconds = 0;
byte minutes = 0;

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

/**
 * @brief Chuyen doi thoi gian sang phut va giay
 */
void cover_times();

void setup()
{
    Serial.begin(115200);

    // put your setup code here, to run once:
    pinMode(pinLED, OUTPUT);
    digitalWrite(pinLED, HIGH);

    pinMode(pinButton, INPUT);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(2000); // Pause for 2 seconds

    // Clear the buffer
    display.clearDisplay();
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (read_button() == 1)
    {
        time_delay += 300;
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

            time_delay -= 1;
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
    cover_times();
    display.clearDisplay();

    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 0);
    display.print(minutes, 10);
    display.print(" : ");
    display.print(seconds, 10);
    display.display(); // Show initial text
    delay(100);
}

void cover_times()
{
    minutes = time_delay / 60;
    seconds = time_delay % 60;
}