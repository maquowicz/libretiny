/* Copyright (c) Kuba Szczodrzyński 2023-05-24. */

#pragma once

#include <ArduinoPrivate.h>
#include <Serial.h>

struct SerialData {
	RingBuffer *buf;
	hal_uart_adapter_t *uart;
	SerialRingBuffer buf;
} SerialData;

#define DATA   ((SerialData *)data)
#define pDATA  ((SerialData *)param)
#define BUF	   (DATA->buf)
#define pdBUF  (pDATA->buf)
#define UART   (DATA->uart)
#define pdUART (pDATA->uart)
