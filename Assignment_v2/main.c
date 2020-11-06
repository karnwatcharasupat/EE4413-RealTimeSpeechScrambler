/*
 * FIR Implementation in C Project
 */

#include <usbstk5515.h>
#include <usbstk5515_i2c.h>
#include <AIC_func.h>
#include <stdio.h>
#include <dsplib.h>
#include <sar.h>
#include "mode.h"
#include "hadamard.h"

#define TCR0		*((ioport volatile Uint16 *) 0x1810) 
#define TIMCNT1_0	*((ioport volatile Uint16 *) 0x1814) 
#define TIME_START	0x8001
#define TIME_STOP	0x8000

#define FSIZE (16)

Uint16 mode = MODE_SCRAMBLE, old_mode;
double scale = 8.0;
Int16 x;
Int16 h[FSIZE*FSIZE] = {0};
Int16 out[FSIZE] = {0};
Int16 buffer[FSIZE*(FSIZE+2)] = {0};
Int16 dummy = 0;


/**
 * @brief  Set the processing mode based on the SAR input
 */
Uint16 set_mode() {
    switch (Get_Sar_Key()) {
        case SW1:
        	if (mode == MODE_BYPASS){
            	return MODE_SCRAMBLE;
        	} else {
            	return MODE_BYPASS;
            }
        case SW2:
        	if (mode != MODE_SCRAMBLE){
            	return MODE_SCRAMBLE;
        	} else {
        		return MODE_DESCRAMBLE;
        	}
        default: 
        	return mode;
    }    
}

void main(void) {
	Uint16 i, j, k, o;
	
    USBSTK5515_init();  // Initializing the Processor
    AIC_init();         // Initializing the Audio Codec

    hadamard(FSIZE, h);  // Generate hadamard matrix
    
    // map to Q15
	for(i = 0; i < FSIZE; i++){
		for(j = 0; j < FSIZE; j++){
			if (h[i*FSIZE+j] == 1){
				h[i*FSIZE+j] = 0x7FFF;
			} else {
				h[i*FSIZE+j] = 0x8000;
			}
		}
    }
    
    for(j = 0; j < FSIZE*(FSIZE+2); j++){
    	buffer[j] = 0;
    }
   
    j = 0; k = 0;
    TCR0 = TIME_STOP; TCR0 = TIME_START;
    while (1) {
    	old_mode = mode;
        mode = set_mode();
        
        if (mode != old_mode && mode != MODE_BYPASS){
        	AIC_read2(&dummy, &dummy);
        	j = 0; k = 0;
        	for(j = 0; j < FSIZE*(FSIZE+2); j++){
		    	buffer[j] = 0;
		    }
        }
                
        start_time = TIMCNT1_0;
		AIC_read2(&x, &dummy);
        switch(mode){
	        case MODE_BYPASS:
				AIC_write2(x, x);
				break;
			case MODE_SCRAMBLE:
			case MODE_DESCRAMBLE:				
				x = (Int16)(x/scale);
				
								
				for (i = 0; i < FSIZE; i++){
					o = fir(&x, h + i*FSIZE, &dummy, buffer + i*(FSIZE+2), 1, FSIZE);
					if (k){
						out[i] = dummy;					
					}		
					if (o){
						printf("Overflow!\n");
					}		
				}
								
				AIC_write2(out[j], out[j]);
				j++; j %= FSIZE;
				k = (j == 0);
				break;
        }        	
        end_time = TIMCNT1_0;
		delta_time = start_time-end_time;
    }
}

