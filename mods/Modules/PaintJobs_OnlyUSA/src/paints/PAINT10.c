#include <common.h>
#include "../tex.h"

short brown_papu[16] __attribute__ ((section (".data"))) = {
0x232,0x1d0,0x1ae,0x16c,0x14b,0xe8,0x214d,0x190b,0x2d8f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,};
short motortop_papu[16] __attribute__ ((section (".data"))) = {
0x2fa,0x35d,0x275,0x24c2,0x1462,0x12b,0x1f1,0x2d03,0x16c,0x79e,0x2f9e,0x3fbe,0x3d88,0x4e2d,0x3545,0x41a9,};
short motorside_papu[16] __attribute__ ((section (".data"))) = {
0x212,0x298,0x2da,0x109,0xc42,0x1ca2,0x2905,0x37e,0x4186,0x49ea,0x524f,0x820,0x33c,0x139e,0x43de,0x63de,};
short front_papu[16] __attribute__ ((section (".data"))) = {
0x1ce6,0x35ee,0x4737,0x677c,0x1af,0x252,0x2f9,0x33b,0x39e,0x2fbe,0x35d,0x3fde,0x12a,0x85,0x3ab3,0x4f38,};
short back_papu[16] __attribute__ ((section (".data"))) = {
0x1cc5,0x39ac,0x3651,0x4b37,0x5b7a,0x46d5,0x1ae,0x211,0x2d8,0x33b,0x2f9e,0x139e,0x35d,0x3fbe,0x109,0x64,};
short bridge_papu[16] __attribute__ ((section (".data"))) = {
0x18a3,0x2926,0xe8,0x2f3,0xea4,0x14b,0x296,0x131a,0x3dca,0x1d0,0x35b,0x33de,0x4a2e,0x5ed3,0x5271,0x6f57,};
short exhaust_papu[16] __attribute__ ((section (".data"))) = {
0xe9,0x16d,0x296,0x39e,0x4630,0x56b3,0x5ed6,0x4a52,0x6b37,0x779c,0x6f59,0x41ec,0x318a,0x18c5,0x2528,0xc63,};

Texture PAINT10[] __attribute__ ((section (".sdata"))) = {
	[0] =
	{
		.front = (char*)front_papu,
		.back = (char*)back_papu,
		.floor = (char*)front_papu,
		.brown = (char*)brown_papu,
		.motorside = (char*)motorside_papu,
		.motortop = (char*)motortop_papu,
		.bridge = (char*)bridge_papu,
		.exhaust = (char*)exhaust_papu,
	},
};