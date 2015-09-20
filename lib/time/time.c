#include "time.h"
#include <stdint.h>

static inline void outb(unsigned short port, unsigned char value) {
	asm volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) );
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

int update_in_progress_flag() {
      outb(CMOS_ADDRESS, 0x0A);
      return (inb(CMOS_DATA) & 0x80);
}

unsigned char read_RTC_register(int reg) {
	outb (CMOS_ADDRESS, (NMI_DISABLE_BIT << 7) | reg);
	return inb(CMOS_DATA);
}

time_t time(void) {
	time_t current_time;

	while (update_in_progress_flag());

	current_time.seconds = read_RTC_register(RTC_SECONDS);
	current_time.minutes = read_RTC_register(RTC_MINUTES);
	current_time.hours = read_RTC_register(RTC_HOURS);
	current_time.week_day = read_RTC_register(RTC_WEEK_DAY);
	current_time.day_of_month = read_RTC_register(RTC_DAY_OF_MONTH);
	current_time.month = read_RTC_register(RTC_MONTH);
	current_time.year = read_RTC_register(RTC_YEAR);
	current_time.century = read_RTC_register(RTC_CENTUARY);

	unsigned char registerB;

	registerB = read_RTC_register(0x0B);

	if (!(registerB & 0x04)) {
		current_time.seconds = (current_time.seconds & 0x0F) + ((current_time.seconds / 16) * 10);
		current_time.minutes = (current_time.minutes & 0x0F) + ((current_time.minutes / 16) * 10);
		//current_time.hours = ((current_time.hours & 0x0F) + (((current_time.hours & 0x70) / 16) * 10) ) | (current_time.hours & 0x80);
		current_time.hours = (current_time.hours & 0x0F) + ((current_time.hours / 16) * 10);
		current_time.week_day = (current_time.week_day & 0x0F) + ((current_time.week_day / 16) * 10);
		current_time.month = (current_time.month & 0x0F) + ((current_time.month / 16) * 10);
		current_time.year = (current_time.year & 0x0F) + ((current_time.year / 16) * 10);
		current_time.century = (current_time.century & 0x0F) + ((current_time.century / 16) * 10);
	}

	if (!(registerB & 0x02) && (current_time.hours & 0x80)) {
		current_time.hours = ((current_time.hours & 0x7F) + 12) % 24;
	}

	return current_time;
}