#ifndef _COMPRESS_H
#define _COMPRESS_H

#include <stdint.h>

#define MAX_NOTIFICATION_SIZE ((size_t)20)  // 20 byte

typedef struct notification_data {
    uint16_t AB;
    uint16_t CD;
    uint16_t EF;
    uint16_t GH;
    uint16_t IJ;
    uint16_t KL;
    uint16_t MN;
    uint16_t OP;
    uint16_t QR;
    uint16_t ST;
} notification_data_t;

int32_t compress_data(uint16_t* p_dest, const uint8_t src_in_high, const uint8_t src_in_low);
int32_t decompress_data(uint8_t* p_dest_high, uint8_t* p_dest_low, const uint16_t* p_src);

#endif