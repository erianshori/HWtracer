this is the stable version for getting the frq:
version 1.3 : 
modified by	: Eri Anshori Nurhadi
date		: 31/01/2016
change log :
1. in avr sampling per 1ms
2. frequency from avr is used for tracing frequency
3. clear code
4. parsing apdu
5. supported CLA : 0x00, 0xFA, 0xA0
6. save to txt file, open from txt file

version 1.0 :
modify by 	: Eri Anshori Nurhadi
date 		: 25/11/2016

description :
the frq : 16MHz
scaller : 64
Timer 0 : timer
Timer 1 : counter
frq sampling is 1ms at avr
data frq mining 50 frequencies from avr at once
frq that are obtained from avr has to be multiplied by 1000