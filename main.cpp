#include "Arduino.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"   // For reading ADC values
#include "tusb.h"           // For TinyUSB HID functions

#define test 26

// Setup function
void setup() 
{
    pinMode(test, INPUT);
    tusb_init();
}

// Loop function
void loop() 
{   
    int poti = analogRead(test);
    poti = poti / 4;
    poti = poti -128;
    Serial.println(poti);
    delay(1000);

    //report array
    uint8_t report[6];
    

    if (poti<0)
    {
      report[0]= (HID_KEY_A);
    }
    else
    {
      report [0] = (HID_KEY_B);
    }

    tud_hid_n_keyboard_report(0, 0, 0, report);
    delay(100);                            // Short delay
    tud_hid_keyboard_report(0, 0, NULL);   // Send key release

    if (tud_hid_ready())
    {
      Serial.println("HID DETECTED");
    }

    if (tud_cdc_connected())
    {
      Serial.println("CDC DETECTED");
    }

}

extern "C" 
{
    // Invoked when USB HID gets a report request from host
    uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
    {
        // No report to send by default
        return 0;
    }

    // Invoked when USB HID receives a report from host
    void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
    {
        // Handle received report (not needed in this example)
    }
}
