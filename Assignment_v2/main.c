/*
 * EE4413 Assignment II
 * Real-time Speech Scrambler
 * 
 * @author 	Karn Watcharasupat
 * @version November 2020
 * @note 	Academic Year 2020/21 Semester 1
 */

#include <AIC_func.h>
#include <dsplib.h>
#include <sar.h>
#include <stdio.h>
#include <usbstk5515.h>
#include <usbstk5515_i2c.h>

#include "hadamard.h"
#include "mode.h"

// for profiling
#define TCR0 *((ioport volatile Uint16 *)0x1810)
#define TIMCNT1_0 *((ioport volatile Uint16 *)0x1814)
#define TIME_START 0x8001
#define TIME_STOP 0x8000

//Addresses of the MMIO for the GPIO out registers: 1,2
#define LED_OUT1 *((ioport volatile Uint16 *)0x1C0A)
#define LED_OUT2 *((ioport volatile Uint16 *)0x1C0B)
//Addresses of the MMIO for the GPIO direction registers: 1,2
#define LED_DIR1 *((ioport volatile Uint16 *)0x1C06)
#define LED_DIR2 *((ioport volatile Uint16 *)0x1C07)

// hadamard transform order
#define FSIZE (16)

// initialize parameters
Uint16 mode = MODE_SCRAMBLE, old_mode;
double scale = 8.0;

// initialize buffers/temp variables
Int16 x;
Int16 h[FSIZE * FSIZE] = {0};
Int16 out[FSIZE] = {0};
Int16 buffer[FSIZE * (FSIZE + 2)] = {0};
Int16 dummy = 0;

int bitGpio14 = 14, bitGpio15 = 15, bitGpio16 = 0, bitGpio17 = 1;

/**
 * @brief  Toggle LED
 * @param  index: 0 for Green, 1 for Red, 2 for Yellow, 3 for Blue, Otherwise nothing is done
 */
void toggle_LED(int index) {
    if (index == 3)  //Blue
        LED_OUT1 = LED_OUT1 ^ (Uint16)(1 << (bitGpio14));
    else if (index == 2)  //Yellow(ish)
        LED_OUT1 = LED_OUT1 ^ (Uint16)(1 << (bitGpio15));
    else if (index == 1)  //Red
        LED_OUT2 = LED_OUT2 ^ (Uint16)(1 << (bitGpio16));
    else if (index == 0)  //Green
        LED_OUT2 = LED_OUT2 ^ (Uint16)(1 << (bitGpio17));
}

/**
 * @brief  Initialize the LED registers
 */
void My_LED_init() {
    Uint16 temp = 0x00;
    Uint16 temp2 = 0x01;
    temp |= (1 << 14);
    temp |= (Uint16)(1 << 15);
    LED_DIR1 |= temp;  // set Yellow, Blue (14,15) as OUTPUT
    temp2 |= (1 << 1);
    LED_DIR2 |= temp2;  // set Red, Green (0,1) as OUTPUT

    LED_OUT1 |= temp;   //Set LEDs 0, 1 to off
    LED_OUT2 |= temp2;  //Set LEDs 2, 3 to off
}

/**
 * @brief  Set the processing mode based on the SAR input
 */
Uint16 set_mode() {
    switch (Get_Sar_Key()) {
        case SW1:
            // toggle between BYPASS and SCRAMBLE
            toggle_LED(0);
            toggle_LED(1);
            if (mode == MODE_BYPASS) {
                return MODE_SCRAMBLE;
            } else {
                return MODE_BYPASS;
            }
        case SW2:
            // mostly used to skip samples to adjust alignment
            // since SCRAMBLE and DESCRAMBLE actually do the same thing
            // if the mode is currently BYPASS, change to SCRAMBLE
            if (mode != MODE_SCRAMBLE) {
                toggle_LED(0);
                toggle_LED(1);
                return MODE_SCRAMBLE;
            } else {
                return MODE_DESCRAMBLE;
            }
        default:
            return mode;
    }
}

void main(void) {
    Uint16 i, j = 0, k = 0, o;  // initialize counters/auxiliary variables
    Uint16 start_time, end_time, delta_time;

    USBSTK5515_init();  // Initializing the Processor
    AIC_init();         // Initializing the Audio Codec
    My_LED_init();      // Initialize LED

    hadamard(FSIZE, h);  // Generate hadamard matrix
    // map the hadamard matrix to Q15 format
    for (i = 0; i < FSIZE * FSIZE; i++) {
        if (h[i * FSIZE + j] == 1) {
            h[i * FSIZE + j] = 0x7FFF;
        } else {
            h[i * FSIZE + j] = 0x8000;
        }
    }

    // initialize timer
    TCR0 = TIME_STOP;
    TCR0 = TIME_START;

    // main processing loop
    while (1) {
        old_mode = mode;
        mode = set_mode();  // check for mode change from SAR

        // skip sample and reset counters if SW2 is triggered to adjust alignment
        if (mode != old_mode && mode != MODE_BYPASS) {
            toggle_LED(2);  // visual indicator
            AIC_read2(&dummy, &dummy);
            for (j = 0; j < FSIZE * (FSIZE + 2); j++) {
                buffer[j] = 0;
            }
			
            j = 0;
            k = 0;
        }

        start_time = TIMCNT1_0;  // start profiling

        AIC_read2(&x, &dummy);  // read sample

        switch (mode) {
            case MODE_BYPASS:
                AIC_write2(x, x);
                break;
            case MODE_SCRAMBLE:
            case MODE_DESCRAMBLE:
                x = (Int16)(x / scale);  // perform scaling to prevent overflow, use float arithmetic then cast back to int

                for (i = 0; i < FSIZE; i++) {
                    o = fir(&x, h + i * FSIZE, &dummy, buffer + i * (FSIZE + 2), 1, FSIZE);

                    if (k) {  // only write to output every FSIZE samples
                        out[i] = dummy;
                    }

                    if (o) {  // check for overflow
                        printf("Overflow!\n");
                        toggle_LED(3);  // visual indicator, blue LED will blink
                    }
                }

                AIC_write2(out[j], out[j]);  // write to output buffer

                j++;
                j %= FSIZE;

                k = (j == 0);  // toggle k based on j
                break;
        }
        end_time = TIMCNT1_0;
        delta_time = start_time - end_time;
    }
}
