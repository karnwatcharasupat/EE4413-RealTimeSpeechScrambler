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

//#define VERBOSE 1

#define FSIZE (16)

Uint16 mode = MODE_SCRAMBLE;
double scale = 8.0;
Int16 x;
Int16 h[FSIZE*FSIZE] = {0};
Int16 out[FSIZE] = {0};
Int16 buffer[FSIZE*(FSIZE+2)] = {0};
Int16 dummy = 0;

/*Int16 firc(Uint16 i, Int16 *arr, Int16 *coef, Uint16 TAPS)
{
	Int32 sum;
	Uint16 j;
	Uint32 index;
	sum=0;

	//The actual filter work
	for(j=0; j<TAPS; j++)
	{
		if(i>=j)
 			index = i - j;
		else 
 			index = TAPS + i - j;
		sum += arr[index] * coef[j];
	}
//	sum = sum + 0x00004000;			// So we round rather than truncate.
	
//		printf("\n\n");
	return (Int16) (sum);  	// Conversion from 32 Q30 to 16 Q15.

}*/


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
        	if (mode == MODE_BYPASS){
            	return MODE_SCRAMBLE;
        	} else {
        		AIC_read2(&dummy, &dummy);
        		printf("Skipping a sample\n");
        		return mode;
        	}
        default: 
        	return mode;
    }    
}

void main(void) {
	Uint16 i, j, o;
    USBSTK5515_init();  // Initializing the Processor
    AIC_init();         // Initializing the Audio Codec

    hadamard(FSIZE, h);  // Generate hadamard matrix
    
	for(i = 0; i < FSIZE; i++){
		for(j = 0; j < FSIZE; j++){
//    		printf("%2d, ", *(h + i*FSIZE+j));
			if (h[i*FSIZE+j] == 1){
				h[i*FSIZE+j] = 0x7FFF;
			} else {
				h[i*FSIZE+j] = 0x8000;
			}
		}
//		printf("\n");
    }
    
    for(j = 0; j < FSIZE*(FSIZE+2); j++){
    	buffer[j] = 0;
    }
   
    j = 0;
    while (1) {
        mode = set_mode();
        
		AIC_read2(&x, &dummy);
        switch(mode){
	        case MODE_BYPASS:
				AIC_write2(x, x);
				break;
			case MODE_SCRAMBLE:
//				in[j] = x;	
				
				x = (Int16)(x/scale);
				
				for (i = 0; i < FSIZE; i++){
//					out[i] = firc(j, in, h + i*FSIZE, FSIZE);
					o = fir(&x, h + i*FSIZE, out + i, buffer + i*(FSIZE+2), 1, FSIZE);		
					if (o){
						printf("Overflow!\n");
					}		
				}
				
				
				AIC_write2(out[j], out[j]);
				j++; j %= FSIZE;
				break;
        }        	
    }
}

