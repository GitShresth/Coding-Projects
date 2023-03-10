#include <limits.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "parking.h"
#include "hashdb.h"

/*
 * freetickets
 *      tears down the database freeing all allocated memory
 *      count the number of tickets freed in the database and
 *      print it out before returning
 */
void
freetickets(void)
{
	unsigned long cnt= 0UL;	  //counter of tickets freed
	int empty = 1;		  //zero if database is not empty

	struct vehicle *vehicle;  //current vehicle being searched	
	for (uint32_t i = 0;i < tabsz;i++) {
		if(*(htable+i) != NULL) {
			vehicle = *(htable+i);
			while (vehicle != NULL) {
				struct ticket *tick = vehicle->head;	/*main ticket searched*/
				struct ticket *nextTick;	/*ticket after main ticket*/
				if (tick != NULL) {
					nextTick = tick->next;
				}
				struct vehicle *localNextVehicle;	/*vehicle after current vehicle*/
				if (tick != NULL) {
					while (nextTick != NULL) {
						free(tick);
						cnt++;
						tick = nextTick;
						nextTick = tick->next;
					}
					free(tick);
					cnt++;
				}
				localNextVehicle = vehicle->next;
				free(vehicle->state);
				free(vehicle->plate);
				free(vehicle);
				vehicle = localNextVehicle;
				tick = NULL;
			}
		}
		*(htable+i) = NULL;	
	}
	vehicle = NULL;
	if (cnt == 0) {
		empty = 1;
	}
	else {
		empty = 0;
	}
    	if (empty) {
        	printf("Empty Database\n");
	}
   	printf("Total tickets freed: %lu\n", cnt);
    	return;
}
#endif
