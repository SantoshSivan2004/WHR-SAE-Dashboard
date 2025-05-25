# WHR-SAE-Dashboard

ESP32 paired with NHD-C12864A1Z-FSW-FBW-HTT display.

UI shows the current gear the car is in, and can be made to show various temperatures.

Only the UI has been implemented, this code does not talk with the sensors.

When you run the code, it will loop through gears 0-6 and show dynamic temperature bar increasing and decreasing.

https://github.com/olikraus/u8g2
- This library was used for UI.
