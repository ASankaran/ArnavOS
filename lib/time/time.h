#define NMI_DISABLE_BIT 0x80
#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71
#define RTC_SECONDS 0x00
#define RTC_MINUTES 0x02
#define RTC_HOURS 0x04
#define RTC_WEEK_DAY 0x06
#define RTC_DAY_OF_MONTH 0x07
#define RTC_MONTH 0x08
#define RTC_YEAR 0x09
#define RTC_CENTUARY 0x32

typedef struct {
	unsigned char seconds;
	unsigned char minutes;
	unsigned char hours;
	unsigned char week_day;
	unsigned char day_of_month;
	unsigned char month;
	unsigned char year;
	unsigned char century;
} time_t;

time_t time(void);