//if you delete blue fire you need to delete the lines in buildlist.txt too
#include <common.h>
#include "global.h"
#ifdef USE_RETROFUELED
//apparently if you use [0] or just [] idk why but it gives you white fire
u_long redFlames_clut[8] __attribute__ ((section (".data"))) = {0x80DA809A, 0x805A80BA, 0x811A803A, 0x819A81DA, 0x813A817A, 0x829A821A, 0x835A839A, 0x82DA831A};
u_long blueFlames_clut[8] __attribute__ ((section (".data"))) = {0xFF25FF65, 0xFFA5FF45, 0xFEE5FFC5, 0xFE65FE25, 0xFEC5FE85, 0xFD65FDE5, 0xFCA5FC65, 0xFD25FCE5};
u_long redPlumes_clut[8] __attribute__ ((section (".data"))) = {0x000083FF, 0x821B833E, 0x829D81B8, 0x80F6800D, 0x819A8054, 0x80D98011, 0x80078019, 0x84008015};
u_long bluePlumes_clut[8] __attribute__ ((section (".data"))) = {0x7FFFF260, 0xFC20F980, 0xF400FC20, 0xF980AC00, 0xF260F980, 0xB400FCA0, 0x8800FC20, 0x8800FC20};


RECT flames_pos __attribute__ ((section (".data"))) = {
    .x = 176,
    .y = 256,
    .w = 16,
    .h = 1
};

RECT plumes_pos __attribute__ ((section (".data"))) = {
    .x = 464,
    .y = 257,
    .w = 16,
    .h = 1
};

char blueFire = 0;

void InjectBlueFire()
{
	if (!blueFire)
	{
		LoadImage(&flames_pos, blueFlames_clut);
		LoadImage(&plumes_pos, bluePlumes_clut);
		blueFire = 1;
	}
}

void InjectRedFire()
{
	if (blueFire)
	{
		LoadImage(&flames_pos, redFlames_clut);
		LoadImage(&plumes_pos, redPlumes_clut);
		blueFire = 0;
	}
}

void UpdateFire() {

	struct GameTracker* gGT;
	struct Driver* driver;
	gGT = sdata->gGT;
	driver = gGT->drivers[0];
	
	if (octr->special != 5) {
		InjectRedFire();
      return;
	}
	if (driver->reserves)
	{
		if (driver->fireSpeedCap == 0x4800)
			InjectBlueFire();
		else
			InjectRedFire();
	}
}
#endif