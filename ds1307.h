#ifndef __DS1307_H
#define __DS1307_H

#ifdef __cplusplus
extern "C" {
#endif
  
#include <stdint.h>
#include <stddef.h>
typedef struct {
  uint8_t sec;
  uint8_t min;
  uint8_t hour;
  uint8_t day;
  uint8_t date;
  uint8_t month;
  uint8_t year;
}rtc_time;

//rtc_time time;
/**
  * @brief Initialize ds1307 
  * @param None
  * @retval None
  */  
void ds1307init(void);


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
void ds1307_time_set(uint8_t sec_value, uint8_t min_value, uint8_t hour_value, uint8_t day_value, uint8_t month_value, uint8_t year_value, uint8_t date_value);


/** @brief ds1307_time_calibrate callibrate  RTC time
  * @param sec is parameter to set second
  * @param min is parameter to set min
  * @param hour is parameter to set hour
  * @param day is parameter to set day
  * @param month is parameter to set month
  * @param year is parameter to set year
  * @param date is parameter to set date
  * @retval None
**/
void ds1307_time_calibrate(uint8_t sec_value, uint8_t min_value, uint8_t hour_value, uint8_t day_value, uint8_t month_value, uint8_t year_value, uint8_t date_value);


/**
  * @brief ds1307_get_time shows current time value in time_val
  * @param None
  * @retval None
  */
void ds1307_get_time(void);


/** @brief set_sec set second
  * @param sec_value is parameter to set second
  * @retval None
**/
void set_sec(uint8_t sec_value);


/** @brief set_min set minute
  * @param min_value is parameter to set minute
  * @retval None
**/
void set_min(uint8_t min_value);


/** @brief set_hour set hour
  * @param hour_value is parameter to set hour
  * @retval None
**/
void set_hour(uint8_t hour_value);


/** @brief set_day set day
  * @param day_value is parameter to set day
  * @retval None
**/
void set_day(uint8_t day_value);


/** @brief set_date set date 
  * @param date_value is parameter to set date
  * @retval None
**/
void set_date(uint8_t date_value);


/** @brief set_month set month 
  * @param month_value is parameter to set month
  * @retval None
**/
void set_month(uint8_t month_value);


/** @brief set_year set year 
  * @param year_value is parameter to set year
  * @retval None
**/
void set_year(uint8_t year_value);  


#ifdef __cplusplus
}
#endif

#endif 