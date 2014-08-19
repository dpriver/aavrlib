#ifndef _D7SEG_
#define _D7SEG_


/*-------------------- ZHS110561K -----------------------------------
 Single 7seg display with 10 ports and common anode

	  7 Seg Display             Package pin distribution
	  =============             ========================

           a                        g f     a b
        ________                    7 6 Vcc 5 4
        |      |                    ___________
      f |  g   | b                  |		  |
	    |______|                    |         |
	    |      |                    |         |
	  e |	   | c                  |_________|
	    |______| · p                
                                    0 1 Vcc 2 3
           d                        e d     c p

----------------------------------------------------------------------*/

/*-------------------- FYQ5641BS  -----------------------------------
 Quad 7seg display with 12 ports and common anode

	  7 Seg Display               Package pin distribution
	  =============               ========================

           a                           a  f          b
        ________                    V1 7  6  V2  V3  5
        |      |                    _________________
      f |  g   | b                  |	        	|
	    |______|                    |               |
	    |      |                    |               |
	  e |	   | c                  |_______________|
	    |______| · p                
                                    0  1  2  3  4  V4
           d                        e  d  p  c  g

 V1, V2, V3 and V4 represent the Vcc input for displays 1,2,3 and 4
----------------------------------------------------------------------*/

/*

	a  b  c  d  e  f  g  P
    10 6  3  1  0  9 4  2

*/

#ifdef DISPLAY_ZHS110561K
	#define SEGMENT_A ~_BV(5)
	#define SEGMENT_B ~_BV(4)
	#define SEGMENT_C ~_BV(2)
	#define SEGMENT_D ~_BV(1)
	#define SEGMENT_E ~_BV(0)
	#define SEGMENT_F ~_BV(6)
	#define SEGMENT_G ~_BV(7)
	#define SEGMENT_P ~_BV(3)
#else
	#ifdef DISPLAY_FYQ5641BS
		#define SEGMENT_A ~_BV(7)
		#define SEGMENT_B ~_BV(5)
		#define SEGMENT_C ~_BV(3)
		#define SEGMENT_D ~_BV(1)
		#define SEGMENT_E ~_BV(0)
		#define SEGMENT_F ~_BV(6)
		#define SEGMENT_G ~_BV(4)
		#define SEGMENT_P ~_BV(2)
	#endif
#endif

#define D7SEG_0 SEGMENT_A & SEGMENT_B & SEGMENT_C & SEGMENT_D & SEGMENT_E & SEGMENT_F
#define D7SEG_1 SEGMENT_B & SEGMENT_C
#define D7SEG_2 SEGMENT_A & SEGMENT_B & SEGMENT_G & SEGMENT_E & SEGMENT_D
#define D7SEG_3 SEGMENT_A & SEGMENT_B & SEGMENT_C & SEGMENT_D & SEGMENT_G
#define D7SEG_4 SEGMENT_B & SEGMENT_C & SEGMENT_F & SEGMENT_G
#define D7SEG_5 SEGMENT_A & SEGMENT_C & SEGMENT_D & SEGMENT_F & SEGMENT_G
#define D7SEG_6 SEGMENT_A & SEGMENT_C & SEGMENT_D & SEGMENT_E & SEGMENT_F & SEGMENT_G
#define D7SEG_7 SEGMENT_A & SEGMENT_B & SEGMENT_C
#define D7SEG_8 SEGMENT_A & SEGMENT_B & SEGMENT_C & SEGMENT_D & SEGMENT_E & SEGMENT_F & SEGMENT_G
#define D7SEG_9 SEGMENT_A & SEGMENT_B & SEGMENT_C & SEGMENT_F & SEGMENT_G
#define D7SEG_A SEGMENT_A & SEGMENT_B & SEGMENT_C & SEGMENT_E & SEGMENT_F & SEGMENT_G
#define D7SEG_B SEGMENT_C & SEGMENT_D & SEGMENT_E & SEGMENT_F & SEGMENT_G
#define D7SEG_C SEGMENT_A & SEGMENT_D & SEGMENT_E & SEGMENT_F
#define D7SEG_D SEGMENT_B & SEGMENT_C & SEGMENT_D & SEGMENT_E & SEGMENT_G
#define D7SEG_E SEGMENT_A & SEGMENT_D & SEGMENT_E & SEGMENT_F & SEGMENT_G
#define D7SEG_F SEGMENT_A & SEGMENT_E & SEGMENT_F & SEGMENT_G



#endif