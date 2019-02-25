#ifndef _Grips_
#define _Grips_

#define ACTIVE 1
#define INACTIVE 0

#include "Header.h"
#include "string.h"

struct gripName
{
	char *GripName;
	
	uint32_t ThumbEncVal;
	uint32_t IndexEncVal;
	uint32_t MiddleEncVal;
	uint32_t RingEncVal;
	uint32_t PinkyEncVal;
	
	bool ThumbStatus;
	bool IndexStatus;
	bool MiddleStatus;
	bool RingStatus;
	bool PinkyStatus;
};

extern struct gripName grips[10];

typedef enum
{
	REST_OPP,		POWER, TRIPOD,	ACTIVE_INDEX,	PRECISION_OPEN,
	REST_NOPP,	HOOK,	 KEY,			MOUSE,				FINGER_POINT
} grip;

extern grip Grip;

extern int lastgrip;

void initGrip(void);
void makeGrip(struct gripName gripVal);
void makeGripException(struct gripName gripVal);

int RestOppGrip(void);
int PowerGrip(void);
int TripodGrip(void);
int ActiveIndexGrip(void);
int PrecisionOpenGrip(void);

int RestNoppGrip(void);
int HookGrip(void);
int KeyGrip(void);
int MouseGrip(void);
int FingerPointGrip(void);	

void ProportionalGrip(int8_t GripVal, bool dir, uint16_t FSRadc);
void StopAllFinger(void);

#endif

