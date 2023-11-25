#pragma once
#ifndef __DS1307_H
#define __DS1307_H

#ifdef __cplusplus
extern "C" {
#endif
  
#include "main.h"  

  
/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */  
void I2C1_Init(void);

/** @brief ds1307_tim_date_set adjust  RTC time
  * @param sec is parameter to set second
  * @param min is parameter to set min
  * @param hour is parameter to set hour
  * @param day is parameter to set day
  * @param month is parameter to set month
  * @param year is parameter to set year
  * @param date is parameter to set date
  * @retval None
**/
void ds1307_tim_date_set(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t month, uint8_t year, uint8_t date);

/**
  * @brief Print PCD8544 screen time
  * @param None
  * @retval None
  */
void get_time(void);

/**
  * @brief Write value to EEPROM
  * @param data variable is sent to eeprom
  * @param eeprom_addr where the data will be sent
  * @retval send_data;
  */
int write_to_eeprom(uint8_t send_data, uint16_t eeprom_addr);

/**
  * @brief Read value to EEPROM
  * @param eeprom_addr where the data will be read
  * @retval receive_variable;
  */
int read_to_eeprom(uint16_t eeprom_addr);

#ifdef __cplusplus
}
#endif

#endif 