#include "compress.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLEAR_8BITS(x) ((x) &= 0x00)
#define CLEAR_16BITS(x) ((x) &= 0x0000)

#define SAVE_IN_HIGH(x, data) (x |= (((data)&0xFF) << 8))
#define SAVE_IN_LOW(x, data) (x |= ((data)&0xFF))

#define GET_HIGH_BYTE(x) (((x)&0xFF00) >> 8)
#define GET_LOW_BYTE(x) ((x)&0x00FF)

int32_t compress_data(uint16_t* p_dest, const uint8_t src_in_high, const uint8_t src_in_low) {
    if (NULL != p_dest) {
        CLEAR_16BITS(*p_dest);
        if (IS_BIG_ENDIAN == 1) {
            SAVE_IN_LOW(*p_dest, src_in_low);
            SAVE_IN_HIGH(*p_dest, src_in_high);
        } else {
            SAVE_IN_LOW(*p_dest, src_in_high);
            SAVE_IN_HIGH(*p_dest, src_in_low);
        }
    }
    return 0;
}

int32_t decompress_data(uint8_t* p_dest_high, uint8_t* p_dest_low, const uint16_t* p_src) {
    if (NULL != p_src && NULL != p_dest_high && NULL != p_dest_low) {
        CLEAR_8BITS(*p_dest_high);
        CLEAR_8BITS(*p_dest_low);
        if (IS_BIG_ENDIAN == 1) {
            *p_dest_high = GET_HIGH_BYTE(*p_src);
            *p_dest_low = GET_LOW_BYTE(*p_src);
        } else {
            *p_dest_high = GET_LOW_BYTE(*p_src);
            *p_dest_low = GET_HIGH_BYTE(*p_src);
        }
    }
    return 0;
}