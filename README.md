# DS1307-RTC-MODUL
DS1307 RTC MODUL DRIVER

After properly initializing the 'ds1307_tim_date_set' function, you can use the RTC module.
If the time is set and you need to make adjustments again, you should write 'write_to_eeprom(0x00, 0x00);' and then call the 'ds1307_tim_date_set' function.

This library calls pcd8544 LCD library, If you don't have you can configure that.
