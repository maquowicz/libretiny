/* Copyright (c) Kuba Szczodrzyński 2023-05-24. */

#pragma once

#include <ArduinoPrivate.h>

typedef struct {
	SerialRingBuffer buf;
} SerialData;

#define DATA ((SerialData *)data)
#define BUF	 (DATA->buf)
#define pBUF ((SerialRingBuffer *)param)
struct SerialData {
	RingBuffer *buf;
};
