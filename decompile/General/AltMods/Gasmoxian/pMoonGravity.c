//moon mode
#include "global.h"



void moongravity() {
    int gravity = (octr->special == 4) ? 369 : 900;  {

        // low gravity event
		// space gravity (369) in og ctr is 41% of normal gravity (900)
        for (int i = 0; i < NUM_CLASSES; i++) {
            data.metaPhys[0].value[i] = gravity;         		
        }
    }
}
