#include "Touch.h"
#include "global.h"
#include "io_pins.h"

/* touch driver : chsc6x */
void touch_init(void)
{
    pinMode(DISP_TP, INPUT_PULLUP);
    //Wire.begin(SDA2, SCL2); // Turn on the IIC bus for touch driver
    /*Initialize the touch driver for lvgl*/

}


bool chsc6x_is_pressed(void)
{
    if(digitalRead(DISP_TP) != LOW) {
        delay(1);
        if(digitalRead(DISP_TP) != LOW)
        return false;
    }
    USBSerial.println("Touch erkannt");
    return true;
}

void chsc6x_convert_xy(void)
{
    uint8_t x_tmp = x, y_tmp = y, _end = 0;
    for(int i=1; i<=screen_rotation; i++){
        x_tmp = x;
        y_tmp = y;
        _end = (i % 2) ? SCREEN_WIDTH : SCREEN_HEIGHT;
        x = y_tmp;
        y = _end - x_tmp;
    }
}

void chsc6x_get_xy(void)
{
    uint8_t temp[CHSC6X_READ_POINT_LEN] = {0};
    uint8_t read_len = Wire.requestFrom(CHSC6X_I2C_ID, CHSC6X_READ_POINT_LEN);
    if(read_len == CHSC6X_READ_POINT_LEN){
        Wire.readBytes(temp, read_len);
        if (temp[0] == 0x01) {
        x = temp[2];
        y = temp[4];
        chsc6x_convert_xy();
        x = temp[2];
        y = temp[4];
        USBSerial.print("X:");USBSerial.print(x);
        USBSerial.print("Y:");USBSerial.println(y);
        }
    }
}