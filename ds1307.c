#include "ds1307.h"
#include <stm32f1xx_hal.h>
#include <stddef.h>
#include <stdio.h>

#define  RTC_WRITE_ADRESS       (0xD0)
#define  RTC_READ_ADRESS        (0xD1)
#define  SECOND_ADDR            (0x00)
#define  MINUTES_ADDR           (0x01)
#define  HOURS_ADDR             (0x02)
#define  DAY_ADDR               (0x03)
#define  DATE_ADDR              (0x04)
#define  MONTH_ADDR             (0x05)
#define  YEAR_ADDR              (0x06)
#define  ONE_BYTE               (0x01)
#define  EEPROM_CLOCK_ADDR      (0x00)
#define  RTC_SET_OPEN           (0x00)
#define  RTC_SET_CLOSED         (0x01)

static I2C_HandleTypeDef hi2c1;
static int bcd_to_dec(uint8_t variable);
static int read_to_eeprom(uint16_t eeprom_addr);
static int write_to_eeprom(uint8_t send_data, uint16_t eeprom_addr);


rtc_time time_val;
uint8_t receive_variable;
uint8_t memory;


void ds1307_time_set(uint8_t sec_value, uint8_t min_value, uint8_t hour_value, uint8_t day_value, uint8_t month_value, uint8_t year_value, uint8_t date_value)
{
  memory = read_to_eeprom(EEPROM_CLOCK_ADDR);
  if(memory == 0)
  {
    time_val.sec = sec_value;
    set_sec(time_val.sec);     
    
    time_val.min = min_value; 
    set_min(time_val.min);
    
    time_val.hour = hour_value;
    set_hour(time_val.hour);

    time_val.date = date_value;  
    set_date(time_val.date);        
    
    time_val.month = month_value;
    set_month(time_val.month);       
    
    time_val.year =  year_value;
    set_year(time_val.year);      
    
    time_val.day = date_value; 
    set_day(time_val.day);    
    write_to_eeprom(RTC_SET_CLOSED,EEPROM_CLOCK_ADDR);
  }
}


void ds1307_get_time(void)
{
  HAL_I2C_Mem_Read(&hi2c1,RTC_READ_ADRESS,(uint16_t)SECOND_ADDR,ONE_BYTE,&(time_val.sec),ONE_BYTE,1);
  time_val.sec = bcd_to_dec(time_val.sec);
  HAL_I2C_Mem_Read(&hi2c1,RTC_READ_ADRESS,(uint16_t)MINUTES_ADDR,ONE_BYTE,&(time_val.min),ONE_BYTE,1);
  time_val.min = bcd_to_dec(time_val.min);
  HAL_I2C_Mem_Read(&hi2c1,RTC_READ_ADRESS,(uint16_t)HOURS_ADDR,ONE_BYTE,&(time_val.hour),ONE_BYTE,1);
  time_val.hour = bcd_to_dec(time_val.hour);
  HAL_I2C_Mem_Read(&hi2c1,RTC_READ_ADRESS,(uint16_t)DAY_ADDR,ONE_BYTE,&(time_val.day),ONE_BYTE,1);
  time_val.day = bcd_to_dec(time_val.day);
  HAL_I2C_Mem_Read(&hi2c1,RTC_READ_ADRESS,(uint16_t)MONTH_ADDR,ONE_BYTE,&(time_val.month),ONE_BYTE,1);
  time_val.month = bcd_to_dec(time_val.month);
  HAL_I2C_Mem_Read(&hi2c1,RTC_READ_ADRESS,(uint16_t)YEAR_ADDR,ONE_BYTE,&(time_val.year),ONE_BYTE,1);
  time_val.year = bcd_to_dec(time_val.year);
  HAL_I2C_Mem_Read(&hi2c1,RTC_READ_ADRESS,(uint16_t)DATE_ADDR,ONE_BYTE,&(time_val.date),ONE_BYTE,1);
  time_val.date = bcd_to_dec(time_val.date);
}


void ds1307_time_calibrate(uint8_t sec_value, uint8_t min_value, uint8_t hour_value, uint8_t day_value, uint8_t month_value, uint8_t year_value, uint8_t date_value)
{
  write_to_eeprom(RTC_SET_OPEN,EEPROM_CLOCK_ADDR);
  ds1307_time_set(sec_value, min_value, hour_value, day_value, month_value, year_value, date_value);
}


void set_sec(uint8_t sec_value)
{
  time_val.sec = sec_value;
  HAL_I2C_Mem_Write(&hi2c1,(uint16_t)RTC_READ_ADRESS,(uint16_t)SECOND_ADDR,(uint16_t)ONE_BYTE,&time_val.sec,(uint16_t)ONE_BYTE,HAL_MAX_DELAY);
}


void set_min(uint8_t min_value)
{
  time_val.sec = min_value;
  HAL_I2C_Mem_Write(&hi2c1,(uint16_t)RTC_WRITE_ADRESS,(uint16_t)MINUTES_ADDR,(uint16_t)ONE_BYTE,&time_val.min,(uint16_t)ONE_BYTE,HAL_MAX_DELAY);
}


void set_hour(uint8_t hour_value)
{
  time_val.hour = hour_value;
  HAL_I2C_Mem_Write(&hi2c1,(uint16_t)RTC_WRITE_ADRESS,(uint16_t)HOURS_ADDR,(uint16_t)ONE_BYTE,&time_val.hour,(uint16_t)ONE_BYTE,HAL_MAX_DELAY);
}


void set_day(uint8_t day_value)
{
  time_val.date = day_value;
  HAL_I2C_Mem_Write(&hi2c1,(uint16_t)RTC_WRITE_ADRESS,(uint16_t)DAY_ADDR,(uint16_t)ONE_BYTE,&time_val.day,(uint16_t)ONE_BYTE,HAL_MAX_DELAY);
}


void set_month(uint8_t month_value)
{
  time_val.month = month_value;
  HAL_I2C_Mem_Write(&hi2c1,(uint16_t)RTC_WRITE_ADRESS,(uint16_t)MONTH_ADDR,(uint16_t)ONE_BYTE,&time_val.date,(uint16_t)ONE_BYTE,HAL_MAX_DELAY); 
}


void set_year(uint8_t year_value)
{
  time_val.year = year_value;
  HAL_I2C_Mem_Write(&hi2c1,(uint16_t)RTC_WRITE_ADRESS,(uint16_t)YEAR_ADDR,(uint16_t)ONE_BYTE,&time_val.year,(uint16_t)ONE_BYTE,HAL_MAX_DELAY);
}


void set_date(uint8_t date_value)
{
  time_val.date = date_value;
  HAL_I2C_Mem_Write(&hi2c1,(uint16_t)RTC_WRITE_ADRESS,(uint16_t)DATE_ADDR,(uint16_t)ONE_BYTE,&time_val.date,(uint16_t)ONE_BYTE,HAL_MAX_DELAY); 
}


void ds1307init(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  HAL_I2C_Init(&hi2c1);
}


/**
  * @brief Read value to EEPROM
  * @param eeprom_addr where the data will be read
  * @retval receive_variable;
  */
static int read_to_eeprom(uint16_t eeprom_addr)
{
  HAL_I2C_Mem_Read(&hi2c1,0xA1,eeprom_addr,2,&receive_variable,2,HAL_MAX_DELAY);
  return receive_variable;
}


/**
  * @brief Write value to EEPROM
  * @param data variable is sent to eeprom
  * @param eeprom_addr where the data will be sent
  * @retval send_data;
  */
static int write_to_eeprom(uint8_t send_data, uint16_t eeprom_addr)
{
  HAL_I2C_Mem_Write(&hi2c1,0xA0,eeprom_addr,2,&send_data,2,HAL_MAX_DELAY);
  return send_data;
}


/**
  * @brief Converts BCD value to DECIMAL
  * @param variable is convert to decimal
  * @retval dec_value;
  */
static int bcd_to_dec(uint8_t variable)
{
    int dec_value = 0;
    dec_value += (variable & 0x0F); 
    dec_value += ((variable >> 4) & 0x0F) * 10; 
    return dec_value;
}
