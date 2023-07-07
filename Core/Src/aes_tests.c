/*
 * aes_tests.c
 *
 * Tests the AES encrypt method to ensure it produces the correct results
 *
 *  Created on: 4 Jul 2023
 *      Author: doggi
 */
#include "main.h"
#include "aes_tests.h"
#include "aes.h"
#include <stdio.h>

static const uint8_t testPlaintext[128][16] = {
{ 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8 },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe },
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
};

static const uint8_t testPlaintextRes[128][16] = {
{ 0x3a, 0xd7, 0x8e, 0x72, 0x6c, 0x1e, 0xc0, 0x2b, 0x7e, 0xbf, 0xe9, 0x2b, 0x23, 0xd9, 0xec, 0x34 },
{ 0xaa, 0xe5, 0x93, 0x9c, 0x8e, 0xfd, 0xf2, 0xf0, 0x4e, 0x60, 0xb9, 0xfe, 0x71, 0x17, 0xb2, 0xc2 },
{ 0xf0, 0x31, 0xd4, 0xd7, 0x4f, 0x5d, 0xcb, 0xf3, 0x9d, 0xaa, 0xf8, 0xca, 0x3a, 0xf6, 0xe5, 0x27 },
{ 0x96, 0xd9, 0xfd, 0x5c, 0xc4, 0xf0, 0x74, 0x41, 0x72, 0x7d, 0xf0, 0xf3, 0x3e, 0x40, 0x1a, 0x36 },
{ 0x30, 0xcc, 0xdb, 0x04, 0x46, 0x46, 0xd7, 0xe1, 0xf3, 0xcc, 0xea, 0x3d, 0xca, 0x08, 0xb8, 0xc0 },
{ 0x16, 0xae, 0x4c, 0xe5, 0x04, 0x2a, 0x67, 0xee, 0x8e, 0x17, 0x7b, 0x7c, 0x58, 0x7e, 0xcc, 0x82 },
{ 0xb6, 0xda, 0x0b, 0xb1, 0x1a, 0x23, 0x85, 0x5d, 0x9c, 0x5c, 0xb1, 0xb4, 0xc6, 0x41, 0x2e, 0x0a },
{ 0xdb, 0x4f, 0x1a, 0xa5, 0x30, 0x96, 0x7d, 0x67, 0x32, 0xce, 0x47, 0x15, 0xeb, 0x0e, 0xe2, 0x4b },
{ 0xa8, 0x17, 0x38, 0x25, 0x26, 0x21, 0xdd, 0x18, 0x0a, 0x34, 0xf3, 0x45, 0x5b, 0x4b, 0xaa, 0x2f },
{ 0x77, 0xe2, 0xb5, 0x08, 0xdb, 0x7f, 0xd8, 0x92, 0x34, 0xca, 0xf7, 0x93, 0x9e, 0xe5, 0x62, 0x1a },
{ 0xb8, 0x49, 0x9c, 0x25, 0x1f, 0x84, 0x42, 0xee, 0x13, 0xf0, 0x93, 0x3b, 0x68, 0x8f, 0xcd, 0x19 },
{ 0x96, 0x51, 0x35, 0xf8, 0xa8, 0x1f, 0x25, 0xc9, 0xd6, 0x30, 0xb1, 0x75, 0x02, 0xf6, 0x8e, 0x53 },
{ 0x8b, 0x87, 0x14, 0x5a, 0x01, 0xad, 0x1c, 0x6c, 0xed, 0xe9, 0x95, 0xea, 0x36, 0x70, 0x45, 0x4f },
{ 0x8e, 0xae, 0x3b, 0x10, 0xa0, 0xc8, 0xca, 0x6d, 0x1d, 0x3b, 0x0f, 0xa6, 0x1e, 0x56, 0xb0, 0xb2 },
{ 0x64, 0xb4, 0xd6, 0x29, 0x81, 0x0f, 0xda, 0x6b, 0xaf, 0xdf, 0x08, 0xf3, 0xb0, 0xd8, 0xd2, 0xc5 },
{ 0xd7, 0xe5, 0xdb, 0xd3, 0x32, 0x45, 0x95, 0xf8, 0xfd, 0xc7, 0xd7, 0xc5, 0x71, 0xda, 0x6c, 0x2a },
{ 0xf3, 0xf7, 0x23, 0x75, 0x26, 0x4e, 0x16, 0x7f, 0xca, 0x9d, 0xe2, 0xc1, 0x52, 0x7d, 0x96, 0x06 },
{ 0x8e, 0xe7, 0x9d, 0xd4, 0xf4, 0x01, 0xff, 0x9b, 0x7e, 0xa9, 0x45, 0xd8, 0x66, 0x66, 0xc1, 0x3b },
{ 0xdd, 0x35, 0xce, 0xa2, 0x79, 0x99, 0x40, 0xb4, 0x0d, 0xb3, 0xf8, 0x19, 0xcb, 0x94, 0xc0, 0x8b },
{ 0x69, 0x41, 0xcb, 0x6b, 0x3e, 0x08, 0xc2, 0xb7, 0xaf, 0xa5, 0x81, 0xeb, 0xdd, 0x60, 0x7b, 0x87 },
{ 0x2c, 0x20, 0xf4, 0x39, 0xf6, 0xbb, 0x09, 0x7b, 0x29, 0xb8, 0xbd, 0x6d, 0x99, 0xaa, 0xd7, 0x99 },
{ 0x62, 0x5d, 0x01, 0xf0, 0x58, 0xe5, 0x65, 0xf7, 0x7a, 0xe8, 0x63, 0x78, 0xbd, 0x2c, 0x49, 0xb3 },
{ 0xc0, 0xb5, 0xfd, 0x98, 0x19, 0x0e, 0xf4, 0x5f, 0xbb, 0x43, 0x01, 0x43, 0x8d, 0x09, 0x59, 0x50 },
{ 0x13, 0x00, 0x1f, 0xf5, 0xd9, 0x98, 0x06, 0xef, 0xd2, 0x5d, 0xa3, 0x4f, 0x56, 0xbe, 0x85, 0x4b },
{ 0x3b, 0x59, 0x4c, 0x60, 0xf5, 0xc8, 0x27, 0x7a, 0x51, 0x13, 0x67, 0x7f, 0x94, 0x20, 0x8d, 0x82 },
{ 0xe9, 0xc0, 0xfc, 0x18, 0x18, 0xe4, 0xaa, 0x46, 0xbd, 0x2e, 0x39, 0xd6, 0x38, 0xf8, 0x9e, 0x05 },
{ 0xf8, 0x02, 0x3e, 0xe9, 0xc3, 0xfd, 0xc4, 0x5a, 0x01, 0x9b, 0x4e, 0x98, 0x5c, 0x7e, 0x1a, 0x54 },
{ 0x35, 0xf4, 0x01, 0x82, 0xab, 0x46, 0x62, 0xf3, 0x02, 0x3b, 0xae, 0xc1, 0xee, 0x79, 0x6b, 0x57 },
{ 0x3a, 0xeb, 0xba, 0xd7, 0x30, 0x36, 0x49, 0xb4, 0x19, 0x4a, 0x69, 0x45, 0xc6, 0xcc, 0x36, 0x94 },
{ 0xa2, 0x12, 0x4b, 0xea, 0x53, 0xec, 0x28, 0x34, 0x27, 0x9b, 0xed, 0x7f, 0x7e, 0xb0, 0xf9, 0x38 },
{ 0xb9, 0xfb, 0x43, 0x99, 0xfa, 0x4f, 0xac, 0xc7, 0x30, 0x9e, 0x14, 0xec, 0x98, 0x36, 0x0b, 0x0a },
{ 0xc2, 0x62, 0x77, 0x43, 0x74, 0x20, 0xc5, 0xd6, 0x34, 0xf7, 0x15, 0xae, 0xa8, 0x1a, 0x91, 0x32 },
{ 0x17, 0x1a, 0x0e, 0x1b, 0x2d, 0xd4, 0x24, 0xf0, 0xe0, 0x89, 0xaf, 0x2c, 0x4c, 0x10, 0xf3, 0x2f },
{ 0x7c, 0xad, 0xbe, 0x40, 0x2d, 0x1b, 0x20, 0x8f, 0xe7, 0x35, 0xed, 0xce, 0x00, 0xae, 0xe7, 0xce },
{ 0x43, 0xb0, 0x2f, 0xf9, 0x29, 0xa1, 0x48, 0x5a, 0xf6, 0xf5, 0xc6, 0xd6, 0x55, 0x8b, 0xaa, 0x0f },
{ 0x09, 0x2f, 0xaa, 0xcc, 0x9b, 0xf4, 0x35, 0x08, 0xbf, 0x8f, 0xa8, 0x61, 0x3c, 0xa7, 0x5d, 0xea },
{ 0xcb, 0x2b, 0xf8, 0x28, 0x0f, 0x3f, 0x97, 0x42, 0xc7, 0xed, 0x51, 0x3f, 0xe8, 0x02, 0x62, 0x9c },
{ 0x21, 0x5a, 0x41, 0xee, 0x44, 0x2f, 0xa9, 0x92, 0xa6, 0xe3, 0x23, 0x98, 0x6d, 0xed, 0x3f, 0x68 },
{ 0xf2, 0x1e, 0x99, 0xcf, 0x4f, 0x0f, 0x77, 0xce, 0xa8, 0x36, 0xe1, 0x1a, 0x2f, 0xe7, 0x5f, 0xb1 },
{ 0x95, 0xe3, 0xa0, 0xca, 0x90, 0x79, 0xe6, 0x46, 0x33, 0x1d, 0xf8, 0xb4, 0xe7, 0x0d, 0x2c, 0xd6 },
{ 0x4a, 0xfe, 0x7f, 0x12, 0x0c, 0xe7, 0x61, 0x3f, 0x74, 0xfc, 0x12, 0xa0, 0x1a, 0x82, 0x80, 0x73 },
{ 0x82, 0x7f, 0x00, 0x0e, 0x75, 0xe2, 0xc8, 0xb9, 0xd4, 0x79, 0xbe, 0xed, 0x91, 0x3f, 0xe6, 0x78 },
{ 0x35, 0x83, 0x0c, 0x8e, 0x7a, 0xae, 0xfe, 0x2d, 0x30, 0x31, 0x0e, 0xf3, 0x81, 0xcb, 0xf6, 0x91 },
{ 0x19, 0x1a, 0xa0, 0xf2, 0xc8, 0x57, 0x01, 0x44, 0xf3, 0x86, 0x57, 0xea, 0x40, 0x85, 0xeb, 0xe5 },
{ 0x85, 0x06, 0x2c, 0x2c, 0x90, 0x9f, 0x15, 0xd9, 0x26, 0x9b, 0x6c, 0x18, 0xce, 0x99, 0xc4, 0xf0 },
{ 0x67, 0x80, 0x34, 0xdc, 0x9e, 0x41, 0xb5, 0xa5, 0x60, 0xed, 0x23, 0x9e, 0xea, 0xb1, 0xbc, 0x78 },
{ 0xc2, 0xf9, 0x3a, 0x4c, 0xe5, 0xab, 0x6d, 0x5d, 0x56, 0xf1, 0xb9, 0x3c, 0xf1, 0x99, 0x11, 0xc1 },
{ 0x1c, 0x31, 0x12, 0xbc, 0xb0, 0xc1, 0xdc, 0xc7, 0x49, 0xd7, 0x99, 0x74, 0x36, 0x91, 0xbf, 0x82 },
{ 0x00, 0xc5, 0x5b, 0xd7, 0x5c, 0x7f, 0x9c, 0x88, 0x19, 0x89, 0xd3, 0xec, 0x19, 0x11, 0xc0, 0xd4 },
{ 0xea, 0x2e, 0x6b, 0x5e, 0xf1, 0x82, 0xb7, 0xdf, 0xf3, 0x62, 0x9a, 0xbd, 0x6a, 0x12, 0x04, 0x5f },
{ 0x22, 0x32, 0x23, 0x27, 0xe0, 0x17, 0x80, 0xb1, 0x73, 0x97, 0xf2, 0x40, 0x87, 0xf8, 0xcc, 0x6f },
{ 0xc9, 0xca, 0xcb, 0x5c, 0xd1, 0x16, 0x92, 0xc3, 0x73, 0xb2, 0x41, 0x17, 0x68, 0x14, 0x9e, 0xe7 },
{ 0xa1, 0x8e, 0x3d, 0xbb, 0xca, 0x57, 0x78, 0x60, 0xda, 0xb6, 0xb8, 0x0d, 0xa3, 0x13, 0x92, 0x56 },
{ 0x79, 0xb6, 0x1c, 0x37, 0xbf, 0x32, 0x8e, 0xcc, 0xa8, 0xd7, 0x43, 0x26, 0x5a, 0x3d, 0x42, 0x5c },
{ 0xd2, 0xd9, 0x9c, 0x6b, 0xcc, 0x1f, 0x06, 0xfd, 0xa8, 0xe2, 0x7e, 0x8a, 0xe3, 0xf1, 0xcc, 0xc7 },
{ 0x1b, 0xfd, 0x4b, 0x91, 0xc7, 0x01, 0xfd, 0x6b, 0x61, 0xb7, 0xf9, 0x97, 0x82, 0x9d, 0x66, 0x3b },
{ 0x11, 0x00, 0x5d, 0x52, 0xf2, 0x5f, 0x16, 0xbd, 0xc9, 0x54, 0x5a, 0x87, 0x6a, 0x63, 0x49, 0x0a },
{ 0x3a, 0x4d, 0x35, 0x4f, 0x02, 0xbb, 0x5a, 0x5e, 0x47, 0xd3, 0x96, 0x66, 0x86, 0x7f, 0x24, 0x6a },
{ 0xd4, 0x51, 0xb8, 0xd6, 0xe1, 0xe1, 0xa0, 0xeb, 0xb1, 0x55, 0xfb, 0xbf, 0x6e, 0x7b, 0x7d, 0xc3 },
{ 0x68, 0x98, 0xd4, 0xf4, 0x2f, 0xa7, 0xba, 0x6a, 0x10, 0xac, 0x05, 0xe8, 0x7b, 0x9f, 0x20, 0x80 },
{ 0xb6, 0x11, 0x29, 0x5e, 0x73, 0x9c, 0xa7, 0xd9, 0xb5, 0x0f, 0x8e, 0x4c, 0x0e, 0x75, 0x4a, 0x3f },
{ 0x7d, 0x33, 0xfc, 0x7d, 0x8a, 0xbe, 0x3c, 0xa1, 0x93, 0x67, 0x59, 0xf8, 0xf5, 0xde, 0xaf, 0x20 },
{ 0x3b, 0x5e, 0x0f, 0x56, 0x6d, 0xc9, 0x6c, 0x29, 0x8f, 0x0c, 0x12, 0x63, 0x75, 0x39, 0xb2, 0x5c },
{ 0xf8, 0x07, 0xc3, 0xe7, 0x98, 0x5f, 0xe0, 0xf5, 0xa5, 0x0e, 0x2c, 0xdb, 0x25, 0xc5, 0x10, 0x9e },
{ 0x41, 0xf9, 0x92, 0xa8, 0x56, 0xfb, 0x27, 0x8b, 0x38, 0x9a, 0x62, 0xf5, 0xd2, 0x74, 0xd7, 0xe9 },
{ 0x10, 0xd3, 0xed, 0x7a, 0x6f, 0xe1, 0x5a, 0xb4, 0xd9, 0x1a, 0xcb, 0xc7, 0xd0, 0x76, 0x7a, 0xb1 },
{ 0x21, 0xfe, 0xec, 0xd4, 0x5b, 0x2e, 0x67, 0x59, 0x73, 0xac, 0x33, 0xbf, 0x0c, 0x54, 0x24, 0xfc },
{ 0x14, 0x80, 0xcb, 0x39, 0x55, 0xba, 0x62, 0xd0, 0x9e, 0xea, 0x66, 0x8f, 0x7c, 0x70, 0x88, 0x17 },
{ 0x66, 0x40, 0x40, 0x33, 0xd6, 0xb7, 0x2b, 0x60, 0x93, 0x54, 0xd5, 0x49, 0x6e, 0x7e, 0xb5, 0x11 },
{ 0x1c, 0x31, 0x7a, 0x22, 0x0a, 0x7d, 0x70, 0x0d, 0xa2, 0xb1, 0xe0, 0x75, 0xb0, 0x02, 0x66, 0xe1 },
{ 0xab, 0x3b, 0x89, 0x54, 0x22, 0x33, 0xf1, 0x27, 0x1b, 0xf8, 0xfd, 0x0c, 0x0f, 0x40, 0x35, 0x45 },
{ 0xd9, 0x3e, 0xae, 0x96, 0x6f, 0xac, 0x46, 0xdc, 0xa9, 0x27, 0xd6, 0xb1, 0x14, 0xfa, 0x3f, 0x9e },
{ 0x1b, 0xde, 0xc5, 0x21, 0x31, 0x65, 0x03, 0xd9, 0xd5, 0xee, 0x65, 0xdf, 0x3e, 0xa9, 0x4d, 0xdf },
{ 0xee, 0xf4, 0x56, 0x43, 0x1d, 0xea, 0x8b, 0x4a, 0xcf, 0x83, 0xbd, 0xae, 0x37, 0x17, 0xf7, 0x5f },
{ 0x06, 0xf2, 0x51, 0x9a, 0x2f, 0xaf, 0xaa, 0x59, 0x6b, 0xfe, 0xf5, 0xcf, 0xa1, 0x5c, 0x21, 0xb9 },
{ 0x25, 0x1a, 0x7e, 0xac, 0x7e, 0x2f, 0xe8, 0x09, 0xe4, 0xaa, 0x8d, 0x0d, 0x70, 0x12, 0x53, 0x1a },
{ 0x3b, 0xff, 0xc1, 0x6e, 0x4c, 0x49, 0xb2, 0x68, 0xa2, 0x0f, 0x8d, 0x96, 0xa6, 0x0b, 0x40, 0x58 },
{ 0xe8, 0x86, 0xf9, 0x28, 0x19, 0x99, 0xc5, 0xbb, 0x3b, 0x3e, 0x88, 0x62, 0xe2, 0xf7, 0xc9, 0x88 },
{ 0x56, 0x3b, 0xf9, 0x0d, 0x61, 0xbe, 0xef, 0x39, 0xf4, 0x8d, 0xd6, 0x25, 0xfc, 0xef, 0x13, 0x61 },
{ 0x4d, 0x37, 0xc8, 0x50, 0x64, 0x45, 0x63, 0xc6, 0x9f, 0xd0, 0xac, 0xd9, 0xa0, 0x49, 0x32, 0x5b },
{ 0xb8, 0x7c, 0x92, 0x1b, 0x91, 0x82, 0x9e, 0xf3, 0xb1, 0x3c, 0xa5, 0x41, 0xee, 0x11, 0x30, 0xa6 },
{ 0x2e, 0x65, 0xeb, 0x6b, 0x6e, 0xa3, 0x83, 0xe1, 0x09, 0xac, 0xcc, 0xe8, 0x32, 0x6b, 0x03, 0x93 },
{ 0x9c, 0xa5, 0x47, 0xf7, 0x43, 0x9e, 0xdc, 0x3e, 0x25, 0x5c, 0x0f, 0x4d, 0x49, 0xaa, 0x89, 0x90 },
{ 0xa5, 0xe6, 0x52, 0x61, 0x4c, 0x93, 0x00, 0xf3, 0x78, 0x16, 0xb1, 0xf9, 0xfd, 0x0c, 0x87, 0xf9 },
{ 0x14, 0x95, 0x4f, 0x0b, 0x46, 0x97, 0x77, 0x6f, 0x44, 0x49, 0x4f, 0xe4, 0x58, 0xd8, 0x14, 0xed },
{ 0x7c, 0x8d, 0x9a, 0xb6, 0xc2, 0x76, 0x17, 0x23, 0xfe, 0x42, 0xf8, 0xbb, 0x50, 0x6c, 0xbc, 0xf7 },
{ 0xdb, 0x7e, 0x19, 0x32, 0x67, 0x9f, 0xdd, 0x99, 0x74, 0x2a, 0xab, 0x04, 0xaa, 0x0d, 0x5a, 0x80 },
{ 0x4c, 0x6a, 0x1c, 0x83, 0xe5, 0x68, 0xcd, 0x10, 0xf2, 0x7c, 0x2d, 0x73, 0xde, 0xd1, 0x9c, 0x28 },
{ 0x90, 0xec, 0xbe, 0x61, 0x77, 0xe6, 0x74, 0xc9, 0x8d, 0xe4, 0x12, 0x41, 0x3f, 0x7a, 0xc9, 0x15 },
{ 0x90, 0x68, 0x4a, 0x2a, 0xc5, 0x5f, 0xe1, 0xec, 0x2b, 0x8e, 0xbd, 0x56, 0x22, 0x52, 0x0b, 0x73 },
{ 0x74, 0x72, 0xf9, 0xa7, 0x98, 0x86, 0x07, 0xca, 0x79, 0x70, 0x77, 0x95, 0x99, 0x10, 0x35, 0xe6 },
{ 0x56, 0xaf, 0xf0, 0x89, 0x87, 0x8b, 0xf3, 0x35, 0x2f, 0x8d, 0xf1, 0x72, 0xa3, 0xae, 0x47, 0xd8 },
{ 0x65, 0xc0, 0x52, 0x6c, 0xbe, 0x40, 0x16, 0x1b, 0x80, 0x19, 0xa2, 0xa3, 0x17, 0x1a, 0xbd, 0x23 },
{ 0x37, 0x7b, 0xe0, 0xbe, 0x33, 0xb4, 0xe3, 0xe3, 0x10, 0xb4, 0xaa, 0xbd, 0xa1, 0x73, 0xf8, 0x4f },
{ 0x94, 0x02, 0xe9, 0xaa, 0x6f, 0x69, 0xde, 0x65, 0x04, 0xda, 0x8d, 0x20, 0xc4, 0xfc, 0xaa, 0x2f },
{ 0x12, 0x3c, 0x1f, 0x4a, 0xf3, 0x13, 0xad, 0x8c, 0x2c, 0xe6, 0x48, 0xb2, 0xe7, 0x1f, 0xb6, 0xe1 },
{ 0x1f, 0xfc, 0x62, 0x6d, 0x30, 0x20, 0x3d, 0xcd, 0xb0, 0x01, 0x9f, 0xb8, 0x0f, 0x72, 0x6c, 0xf4 },
{ 0x76, 0xda, 0x1f, 0xbe, 0x3a, 0x50, 0x72, 0x8c, 0x50, 0xfd, 0x2e, 0x62, 0x1b, 0x5a, 0xd8, 0x85 },
{ 0x08, 0x2e, 0xb8, 0xbe, 0x35, 0xf4, 0x42, 0xfb, 0x52, 0x66, 0x8e, 0x16, 0xa5, 0x91, 0xd1, 0xd6 },
{ 0xe6, 0x56, 0xf9, 0xec, 0xf5, 0xfe, 0x27, 0xec, 0x3e, 0x4a, 0x73, 0xd0, 0x0c, 0x28, 0x2f, 0xb3 },
{ 0x2c, 0xa8, 0x20, 0x9d, 0x63, 0x27, 0x4c, 0xd9, 0xa2, 0x9b, 0xb7, 0x4b, 0xcd, 0x77, 0x68, 0x3a },
{ 0x79, 0xbf, 0x5d, 0xce, 0x14, 0xbb, 0x7d, 0xd7, 0x3a, 0x8e, 0x36, 0x11, 0xde, 0x7c, 0xe0, 0x26 },
{ 0x3c, 0x84, 0x99, 0x39, 0xa5, 0xd2, 0x93, 0x99, 0xf3, 0x44, 0xc4, 0xa0, 0xec, 0xa8, 0xa5, 0x76 },
{ 0xed, 0x3c, 0x0a, 0x94, 0xd5, 0x9b, 0xec, 0xe9, 0x88, 0x35, 0xda, 0x7a, 0xa4, 0xf0, 0x7c, 0xa2 },
{ 0x63, 0x91, 0x9e, 0xd4, 0xce, 0x10, 0x19, 0x64, 0x38, 0xb6, 0xad, 0x09, 0xd9, 0x9c, 0xd7, 0x95 },
{ 0x76, 0x78, 0xf3, 0xa8, 0x33, 0xf1, 0x9f, 0xea, 0x95, 0xf3, 0xc6, 0x02, 0x9e, 0x2b, 0xc6, 0x10 },
{ 0x3a, 0xa4, 0x26, 0x83, 0x10, 0x67, 0xd3, 0x6b, 0x92, 0xbe, 0x7c, 0x5f, 0x81, 0xc1, 0x3c, 0x56 },
{ 0x92, 0x72, 0xe2, 0xd2, 0xcd, 0xd1, 0x10, 0x50, 0x99, 0x8c, 0x84, 0x50, 0x77, 0xa3, 0x0e, 0xa0 },
{ 0x08, 0x8c, 0x4b, 0x53, 0xf5, 0xec, 0x0f, 0xf8, 0x14, 0xc1, 0x9a, 0xda, 0xe7, 0xf6, 0x24, 0x6c },
{ 0x40, 0x10, 0xa5, 0xe4, 0x01, 0xfd, 0xf0, 0xa0, 0x35, 0x4d, 0xdb, 0xcc, 0x0d, 0x01, 0x2b, 0x17 },
{ 0xa8, 0x7a, 0x38, 0x57, 0x36, 0xc0, 0xa6, 0x18, 0x9b, 0xd6, 0x58, 0x9b, 0xd8, 0x44, 0x5a, 0x93 },
{ 0x54, 0x5f, 0x2b, 0x83, 0xd9, 0x61, 0x6d, 0xcc, 0xf6, 0x0f, 0xa9, 0x83, 0x0e, 0x9c, 0xd2, 0x87 },
{ 0x4b, 0x70, 0x6f, 0x7f, 0x92, 0x40, 0x63, 0x52, 0x39, 0x40, 0x37, 0xa6, 0xd4, 0xf4, 0x68, 0x8d },
{ 0xb7, 0x97, 0x2b, 0x39, 0x41, 0xc4, 0x4b, 0x90, 0xaf, 0xa7, 0xb2, 0x64, 0xbf, 0xba, 0x73, 0x87 },
{ 0x6f, 0x45, 0x73, 0x2c, 0xf1, 0x08, 0x81, 0x54, 0x6f, 0x0f, 0xd2, 0x38, 0x96, 0xd2, 0xbb, 0x60 },
{ 0x2e, 0x35, 0x79, 0xca, 0x15, 0xaf, 0x27, 0xf6, 0x4b, 0x3c, 0x95, 0x5a, 0x5b, 0xfc, 0x30, 0xba },
{ 0x34, 0xa2, 0xc5, 0xa9, 0x1a, 0xe2, 0xae, 0xc9, 0x9b, 0x7d, 0x1b, 0x5f, 0xa6, 0x78, 0x04, 0x47 },
{ 0xa4, 0xd6, 0x61, 0x6b, 0xd0, 0x4f, 0x87, 0x33, 0x5b, 0x0e, 0x53, 0x35, 0x12, 0x27, 0xa9, 0xee },
{ 0x7f, 0x69, 0x2b, 0x03, 0x94, 0x58, 0x67, 0xd1, 0x61, 0x79, 0xa8, 0xce, 0xfc, 0x83, 0xea, 0x3f },
{ 0x3b, 0xd1, 0x41, 0xee, 0x84, 0xa0, 0xe6, 0x41, 0x4a, 0x26, 0xe7, 0xa4, 0xf2, 0x81, 0xf8, 0xa2 },
{ 0xd1, 0x78, 0x8f, 0x57, 0x2d, 0x98, 0xb2, 0xb1, 0x6e, 0xc5, 0xd5, 0xf3, 0x92, 0x2b, 0x99, 0xbc },
{ 0x08, 0x33, 0xff, 0x6f, 0x61, 0xd9, 0x8a, 0x57, 0xb2, 0x88, 0xe8, 0xc3, 0x58, 0x6b, 0x85, 0xa6 },
{ 0x85, 0x68, 0x26, 0x17, 0x97, 0xde, 0x17, 0x6b, 0xf0, 0xb4, 0x3b, 0xec, 0xc6, 0x28, 0x5a, 0xfb },
{ 0xf9, 0xb0, 0xfd, 0xa0, 0xc4, 0xa8, 0x98, 0xf5, 0xb9, 0xe6, 0xf6, 0x61, 0xc4, 0xce, 0x4d, 0x07 },
{ 0x8a, 0xde, 0x89, 0x59, 0x13, 0x68, 0x5c, 0x67, 0xc5, 0x26, 0x9f, 0x8a, 0xae, 0x42, 0x98, 0x3e },
{ 0x39, 0xbd, 0xe6, 0x7d, 0x5c, 0x8e, 0xd8, 0xa8, 0xb1, 0xc3, 0x7e, 0xb8, 0xfa, 0x9f, 0x5a, 0xc0 },
{ 0x5c, 0x00, 0x5e, 0x72, 0xc1, 0x41, 0x8c, 0x44, 0xf5, 0x69, 0xf2, 0xea, 0x33, 0xba, 0x54, 0xf3 },
{ 0x3f, 0x5b, 0x8c, 0xc9, 0xea, 0x85, 0x5a, 0x0a, 0xfa, 0x73, 0x47, 0xd2, 0x3e, 0x8d, 0x66, 0x4e },
};

static const uint8_t testKeys[21][16] = {
{ 0x10, 0xa5, 0x88, 0x69, 0xd7, 0x4b, 0xe5, 0xa3, 0x74, 0xcf, 0x86, 0x7c, 0xfb, 0x47, 0x38, 0x59 },
{ 0xca, 0xea, 0x65, 0xcd, 0xbb, 0x75, 0xe9, 0x16, 0x9e, 0xcd, 0x22, 0xeb, 0xe6, 0xe5, 0x46, 0x75 },
{ 0xa2, 0xe2, 0xfa, 0x9b, 0xaf, 0x7d, 0x20, 0x82, 0x2c, 0xa9, 0xf0, 0x54, 0x2f, 0x76, 0x4a, 0x41 },
{ 0xb6, 0x36, 0x4a, 0xc4, 0xe1, 0xde, 0x1e, 0x28, 0x5e, 0xaf, 0x14, 0x4a, 0x24, 0x15, 0xf7, 0xa0 },
{ 0x64, 0xcf, 0x9c, 0x7a, 0xbc, 0x50, 0xb8, 0x88, 0xaf, 0x65, 0xf4, 0x9d, 0x52, 0x19, 0x44, 0xb2 },
{ 0x47, 0xd6, 0x74, 0x2e, 0xef, 0xcc, 0x04, 0x65, 0xdc, 0x96, 0x35, 0x5e, 0x85, 0x1b, 0x64, 0xd9 },
{ 0x3e, 0xb3, 0x97, 0x90, 0x67, 0x8c, 0x56, 0xbe, 0xe3, 0x4b, 0xbc, 0xde, 0xcc, 0xf6, 0xcd, 0xb5 },
{ 0x64, 0x11, 0x0a, 0x92, 0x4f, 0x07, 0x43, 0xd5, 0x00, 0xcc, 0xad, 0xae, 0x72, 0xc1, 0x34, 0x27 },
{ 0x18, 0xd8, 0x12, 0x65, 0x16, 0xf8, 0xa1, 0x2a, 0xb1, 0xa3, 0x6d, 0x9f, 0x04, 0xd6, 0x8e, 0x51 },
{ 0xf5, 0x30, 0x35, 0x79, 0x68, 0x57, 0x84, 0x80, 0xb3, 0x98, 0xa3, 0xc2, 0x51, 0xcd, 0x10, 0x93 },
{ 0xda, 0x84, 0x36, 0x7f, 0x32, 0x5d, 0x42, 0xd6, 0x01, 0xb4, 0x32, 0x69, 0x64, 0x80, 0x2e, 0x8e },
{ 0xe3, 0x7b, 0x1c, 0x6a, 0xa2, 0x84, 0x6f, 0x6f, 0xdb, 0x41, 0x3f, 0x23, 0x8b, 0x08, 0x9f, 0x23 },
{ 0x6c, 0x00, 0x2b, 0x68, 0x24, 0x83, 0xe0, 0xca, 0xbc, 0xc7, 0x31, 0xc2, 0x53, 0xbe, 0x56, 0x74 },
{ 0x14, 0x3a, 0xe8, 0xed, 0x65, 0x55, 0xab, 0xa9, 0x61, 0x10, 0xab, 0x58, 0x89, 0x3a, 0x8a, 0xe1 },
{ 0xb6, 0x94, 0x18, 0xa8, 0x53, 0x32, 0x24, 0x0d, 0xc8, 0x24, 0x92, 0x35, 0x39, 0x56, 0xae, 0x0c },
{ 0x71, 0xb5, 0xc0, 0x8a, 0x19, 0x93, 0xe1, 0x36, 0x2e, 0x4d, 0x0c, 0xe9, 0xb2, 0x2b, 0x78, 0xd5 },
{ 0xe2, 0x34, 0xcd, 0xca, 0x26, 0x06, 0xb8, 0x1f, 0x29, 0x40, 0x8d, 0x5f, 0x6d, 0xa2, 0x12, 0x06 },
{ 0x13, 0x23, 0x7c, 0x49, 0x07, 0x4a, 0x3d, 0xa0, 0x78, 0xdc, 0x1d, 0x82, 0x8b, 0xb7, 0x8c, 0x6f },
{ 0x30, 0x71, 0xa2, 0xa4, 0x8f, 0xe6, 0xcb, 0xd0, 0x4f, 0x1a, 0x12, 0x90, 0x98, 0xe3, 0x08, 0xf8 },
{ 0x90, 0xf4, 0x2e, 0xc0, 0xf6, 0x83, 0x85, 0xf2, 0xff, 0xc5, 0xdf, 0xc0, 0x3a, 0x65, 0x4d, 0xce },
{ 0xfe, 0xbd, 0x9a, 0x24, 0xd8, 0xb6, 0x5c, 0x1c, 0x78, 0x7d, 0x50, 0xa4, 0xed, 0x36, 0x19, 0xa9 },
};

static const uint8_t testKeysCipher[21][16] = {
{ 0x6d, 0x25, 0x1e, 0x69, 0x44, 0xb0, 0x51, 0xe0, 0x4e, 0xaa, 0x6f, 0xb4, 0xdb, 0xf7, 0x84, 0x65 },
{ 0x6e, 0x29, 0x20, 0x11, 0x90, 0x15, 0x2d, 0xf4, 0xee, 0x05, 0x81, 0x39, 0xde, 0xf6, 0x10, 0xbb },
{ 0xc3, 0xb4, 0x4b, 0x95, 0xd9, 0xd2, 0xf2, 0x56, 0x70, 0xee, 0xe9, 0xa0, 0xde, 0x09, 0x9f, 0xa3 },
{ 0x5d, 0x9b, 0x05, 0x57, 0x8f, 0xc9, 0x44, 0xb3, 0xcf, 0x1c, 0xcf, 0x0e, 0x74, 0x6c, 0xd5, 0x81 },
{ 0xf7, 0xef, 0xc8, 0x9d, 0x5d, 0xba, 0x57, 0x81, 0x04, 0x01, 0x6c, 0xe5, 0xad, 0x65, 0x9c, 0x05 },
{ 0x03, 0x06, 0x19, 0x4f, 0x66, 0x6d, 0x18, 0x36, 0x24, 0xaa, 0x23, 0x0a, 0x8b, 0x26, 0x4a, 0xe7 },
{ 0x85, 0x80, 0x75, 0xd5, 0x36, 0xd7, 0x9c, 0xce, 0xe5, 0x71, 0xf7, 0xd7, 0x20, 0x4b, 0x1f, 0x67 },
{ 0x35, 0x87, 0x0c, 0x6a, 0x57, 0xe9, 0xe9, 0x23, 0x14, 0xbc, 0xb8, 0x08, 0x7c, 0xde, 0x72, 0xce },
{ 0x6c, 0x68, 0xe9, 0xbe, 0x5e, 0xc4, 0x1e, 0x22, 0xc8, 0x25, 0xb7, 0xc7, 0xaf, 0xfb, 0x43, 0x63 },
{ 0xf5, 0xdf, 0x39, 0x99, 0x0f, 0xc6, 0x88, 0xf1, 0xb0, 0x72, 0x24, 0xcc, 0x03, 0xe8, 0x6c, 0xea },
{ 0xbb, 0xa0, 0x71, 0xbc, 0xb4, 0x70, 0xf8, 0xf6, 0x58, 0x6e, 0x5d, 0x3a, 0xdd, 0x18, 0xbc, 0x66 },
{ 0x43, 0xc9, 0xf7, 0xe6, 0x2f, 0x5d, 0x28, 0x8b, 0xb2, 0x7a, 0xa4, 0x0e, 0xf8, 0xfe, 0x1e, 0xa8 },
{ 0x35, 0x80, 0xd1, 0x9c, 0xff, 0x44, 0xf1, 0x01, 0x4a, 0x7c, 0x96, 0x6a, 0x69, 0x05, 0x9d, 0xe5 },
{ 0x80, 0x6d, 0xa8, 0x64, 0xdd, 0x29, 0xd4, 0x8d, 0xea, 0xfb, 0xe7, 0x64, 0xf8, 0x20, 0x2a, 0xef },
{ 0xa3, 0x03, 0xd9, 0x40, 0xde, 0xd8, 0xf0, 0xba, 0xff, 0x6f, 0x75, 0x41, 0x4c, 0xac, 0x52, 0x43 },
{ 0xc2, 0xda, 0xbd, 0x11, 0x7f, 0x8a, 0x3e, 0xca, 0xbf, 0xbb, 0x11, 0xd1, 0x21, 0x94, 0xd9, 0xd0 },
{ 0xff, 0xf6, 0x0a, 0x47, 0x40, 0x08, 0x6b, 0x3b, 0x9c, 0x56, 0x19, 0x5b, 0x98, 0xd9, 0x1a, 0x7b },
{ 0x81, 0x46, 0xa0, 0x8e, 0x23, 0x57, 0xf0, 0xca, 0xa3, 0x0c, 0xa8, 0xc9, 0x4d, 0x1a, 0x05, 0x44 },
{ 0x4b, 0x98, 0xe0, 0x6d, 0x35, 0x6d, 0xeb, 0x07, 0xeb, 0xb8, 0x24, 0xe5, 0x71, 0x3f, 0x7b, 0xe3 },
{ 0x7a, 0x20, 0xa5, 0x3d, 0x46, 0x0f, 0xc9, 0xce, 0x04, 0x23, 0xa7, 0xa0, 0x76, 0x4c, 0x6c, 0xf2 },
{ 0xf4, 0xa7, 0x0d, 0x8a, 0xf8, 0x77, 0xf9, 0xb0, 0x2b, 0x4c, 0x40, 0xdf, 0x57, 0xd4, 0x5b, 0x17 },
};



void TestEncryptConstantKey(uint8_t key[16])
{
	uint8_t keys[44][4] = {0};
	GenerateKeys(key, keys);

	uint8_t* result = 0;
	uint8_t valid = 1;

	for (int i = 0; i < 128; i++){
		result = Encrypt(testPlaintext[i], keys);
		for (int j = 0; j < 16; j++){
			if (result[j] != testPlaintextRes[i][j]){
				valid = 0;
				break;
			}
		}
		if (valid == 1){
			printf("Test %d passed\r\n", i + 1);
			printf("Plain Text: ");
			for (int x = 0; x < 16; x++){
				printf("%02x", testPlaintext[i][x]);
			}
			printf("\r\n");

			printf("Cipher Text: ");
			for (int y = 0; y < 16; y++){
				printf("%02x", result[y]);
			}
			printf("\r\n");
		}
		else{
			printf("Test %d failed\r\n", i + 1);
			printf("Expected: ");
			for (int x = 0; x < 16; x++){
				printf("%02x", testPlaintextRes[i][x]);
			}
			printf("\r\n");

			printf("Received: ");
			for (int y = 0; y < 16; y++){
				printf("%02x", result[y]);
			}
			printf("\r\n");
		}

	}
}

/**
 * Tests if the decryption works as expected with a constant key
 */
void TestDecryptConstantKey()
{
	uint8_t key[16] = {0};
	uint8_t keys[44][4];
	GenerateKeys(key, keys);

	uint8_t* result = 0;
	uint8_t valid = 1;

	for (int i = 0; i < 128; i++){
		result = Decrypt(testPlaintextRes[i], keys);
		for (int j = 0; j < 16; j++){
			if (result[j] != testPlaintext[i][j]){
				valid = 0;
				break;
			}
		}
		if (valid == 1){
			printf("Test %d passed\r\n", i + 1);
			printf("Cipher Text: ");
			for (int x = 0; x < 16; x++){
				printf("%02x", testPlaintextRes[i][x]);
			}
			printf("\r\n");

			printf("Plain Text: ");
			for (int y = 0; y < 16; y++){
				printf("%02x", result[y]);
			}
			printf("\r\n");
		}
		else{
			printf("Test %d failed\r\n", i + 1);
			printf("Expected: ");
			for (int x = 0; x < 16; x++){
				printf("%02x", testPlaintext[i][x]);
			}
			printf("\r\n");

			printf("Received: ");
			for (int y = 0; y < 16; y++){
				printf("%02x", result[y]);
			}
			printf("\r\n");
			valid = 1;
		}
	}

}

void TestEncryptVariableKey()
{
	uint8_t keys[44][4] = {0};
	uint8_t* result = 0;
	uint8_t plaintext[16] = {0};
	uint8_t valid = 1;

	for (uint8_t i = 0; i < 21; ++i){
		// generate the keys
		GenerateKeys(testKeys[i], keys);

		// encrypt the data
		result = Encrypt(plaintext, keys);

		// check the results
		for (uint8_t j = 0; j < 16; ++j){
			if (result[j] != testKeysCipher[i][j]){
				valid = 0;
			}
		}

		if (valid == 1){
			printf("Test %d passed\r\n", i + 1);
			printf("Expected: ");
			PrintText(testKeysCipher[i]);
			printf("Received: ");
			PrintText(result);
		}
		else{
			printf("Test %d failed\r\n", i + 1);
			printf("Expected: ");
			PrintText(testKeysCipher[i]);
			printf("Received: ");
			PrintText(result);
		}
		valid = 1;
	}
}

void TestDecryptVariableKey()
{
	uint8_t keys[44][4] = {0};
	uint8_t* result = 0;
	uint8_t plaintext[16] = {0};
	uint8_t valid = 1;
	uint8_t expected[16] = {0};

	for (uint8_t i = 0; i < 21; ++i){
		// generate the keys
		GenerateKeys(testKeys[i], keys);

		// encrypt the data
		result = Decrypt(testKeysCipher[i], keys);

		// check the results
		for (uint8_t j = 0; j < 16; ++j){
			if (result[j] != expected[j]){
				valid = 0;
			}
		}

		if (valid == 1){
			printf("Test %d passed\r\n", i + 1);
			printf("Expected: ");
			PrintText(expected);
			printf("Received: ");
			PrintText(result);
		}
		else{
			printf("Test %d failed\r\n", i + 1);
			printf("Expected: ");
			PrintText(expected);
			printf("Received: ");
			PrintText(result);
		}
		valid = 1;
	}
}

void SpeedTest1MB()
{
	// will run with constant key for 65536 times to simulate one MB of data
	uint8_t key[16] = {0};
	uint8_t keys[44][4] = {0};
	uint8_t plaintext[16] = {0};
	GenerateKeys(key, keys);


	int time = HAL_GetTick();
	for (int i = 0; i < 65536; ++i){
		Encrypt(plaintext, keys);
	}
	time = HAL_GetTick() - time;
	printf("Time: %dms\r\n", time);
}

