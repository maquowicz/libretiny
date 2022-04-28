#include "lt_logger.h"

#include <Arduino.h>

#if LT_LOGGER_TASK
#include <FreeRTOS.h>
#include <task.h>
#endif

#define COLOR_FMT			 "\e[0;30m"
#define COLOR_BLACK			 0x00
#define COLOR_RED			 0x01
#define COLOR_GREEN			 0x02
#define COLOR_YELLOW		 0x03
#define COLOR_BLUE			 0x04
#define COLOR_MAGENTA		 0x05
#define COLOR_CYAN			 0x06
#define COLOR_WHITE			 0x07
#define COLOR_BRIGHT_BLACK	 0x10
#define COLOR_BRIGHT_RED	 0x11
#define COLOR_BRIGHT_GREEN	 0x12
#define COLOR_BRIGHT_YELLOW	 0x13
#define COLOR_BRIGHT_BLUE	 0x14
#define COLOR_BRIGHT_MAGENTA 0x15
#define COLOR_BRIGHT_CYAN	 0x16
#define COLOR_BRIGHT_WHITE	 0x17

const char levels[] = {'V', 'D', 'I', 'W', 'E', 'F'};

#if LT_LOGGER_COLOR
const uint8_t colors[] = {
	COLOR_BRIGHT_CYAN,
	COLOR_BRIGHT_BLUE,
	COLOR_BRIGHT_GREEN,
	COLOR_BRIGHT_YELLOW,
	COLOR_BRIGHT_RED,
	COLOR_BRIGHT_MAGENTA,
};
#endif

unsigned long millis(void);

#if LT_LOGGER_FILE
void lt_log(const uint8_t level, const char *filename, const unsigned short line, const char *format, ...) {
#else
void lt_log(const uint8_t level, const char *format, ...) {
#endif

#if LT_LOGGER_TIMESTAMP
	float seconds = millis() / 1000.0f;
#if LT_PRINTF_BROKEN
	char zero[4] = "\x00\x30\x30";
	if (seconds == 0.0f)
		zero[0] = '0';
#endif
#endif

#if LT_LOGGER_TASK
	char task_colon	  = ':';
	TaskHandle_t task = xTaskGetCurrentTaskHandle();
	char *task_name	  = pcTaskGetTaskName(task);
	if (!task) {
		task_name  = "";
		task_colon = '-';
	}
#endif

#if LT_LOGGER_COLOR
	char c_bright = '0' + (colors[level] >> 4);
	char c_value  = '0' + (colors[level] & 0x7);
#endif

	printf(
#if LT_LOGGER_COLOR
		"\e[%c;3%cm"
#endif
		"%c "
#if LT_LOGGER_TIMESTAMP
#if LT_PRINTF_BROKEN
		"[%11.3f%s] "
#else
		"[%11.3f] "
#endif
#endif
#if LT_LOGGER_COLOR
		"\e[0m"
#endif
#if LT_LOGGER_FILE
		"%s:%hu: "
#endif
#if LT_LOGGER_TASK
		"%s%c "
#endif
		,
		levels[level]
#if LT_LOGGER_COLOR
		,
		c_bright, // whether text is bright
		c_value	  // text color
#endif
#if LT_LOGGER_TIMESTAMP
		,
		seconds // float
#if LT_PRINTF_BROKEN
		,
		zero // append missing zeroes if printf "%11.3f" prints "0."
#endif
#endif
#if LT_LOGGER_FILE
		,
		filename,
		line
#endif
#if LT_LOGGER_TASK
		,
		task_name,
		task_colon // printing outside of tasks
#endif
	);

	va_list va_args;
	va_start(va_args, format);
	vprintf(format, va_args);
	va_end(va_args);
	printf("\r\n");
}
