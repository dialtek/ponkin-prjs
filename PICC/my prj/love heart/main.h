#include <33FJ64GP204.h>

#FUSES WPRES32               	//Watch Dog Timer PreScalar 1:32
#FUSES WPOSTS1               	//Watch Dog Timer PostScalar 1:1
#FUSES PROTECT_HIGH          	//General Segment Code Protect High Security
#FUSES CKSFSM                	//Clock Switching is enabled, fail Safe clock monitor is enabled

#use delay(clock=20000000)

