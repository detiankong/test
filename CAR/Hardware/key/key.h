#ifndef __KEY_H
#define __KEY_H

#define WK_UP  PAin(0)
#define KEY2   PEin(2)
#define KEY1   PEin(3)
#define KEY0   PEin(4)

#define WKUP_PRESS 1
#define KEY2_PRESS 2
#define KEY1_PRESS 3
#define KEY0_PRESS 4

void Key_Init(void);
int KeyScan(unsigned char mode);

#endif
