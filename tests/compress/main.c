#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "compress.h"

int main(int argc, char* argv[]) {
    // Make sure size under limit.
    size_t size_of_data = sizeof(notification_data_t);
    assert(size_of_data <= MAX_NOTIFICATION_SIZE);

    notification_data_t notify_data = {0};
    // No compress.
    uint16_t AB = 998;
    notify_data.AB = 998;
    assert(notify_data.AB == AB);

    // Compress unsigned integer.
    uint8_t C = 100;
    uint8_t D = 76;
    compress_data(&(notify_data.CD), C, D);

    uint8_t uzipC = 0;
    uint8_t uzipD = 0;
    decompress_data(&uzipC, &uzipD, &(notify_data.CD));
    assert(uzipC == C);
    assert(uzipD == D);

    // Compress signed interger case (-,+).
    int8_t E = -30;
    int8_t F = 50;
    compress_data(&(notify_data.EF), (uint8_t)E, (uint8_t)F);
    uint8_t uzipE = 0;
    uint8_t uzipF = 0;
    decompress_data(&uzipE, &uzipF, &(notify_data.EF));
    assert((int8_t)uzipE == E);
    assert((int8_t)uzipF == F);

    // Compress signed integer case (-, -).
    int8_t G = -99;
    int8_t H = -101;
    compress_data(&(notify_data.GH), (uint8_t)G, (uint8_t)H);
    uint8_t uzipG = 0;
    uint8_t uzipH = 0;
    decompress_data(&uzipG, &uzipH, &(notify_data.GH));
    assert((int8_t)uzipG == G);
    assert((int8_t)uzipH == H);

    // Compress signed integer case (+, -).
    int8_t I = 52;
    int8_t J = -1;
    compress_data(&(notify_data.IJ), (uint8_t)I, (uint8_t)J);
    uint8_t uzipI = 0;
    uint8_t uzipJ = 0;
    decompress_data(&uzipI, &uzipJ, &(notify_data.IJ));
    assert((int8_t)uzipI == I);
    assert((int8_t)uzipJ == J);
}