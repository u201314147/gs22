// refactorization
#include <common.h>

struct Instance* DECOMP_LinkedCollide_Hitbox_Desc(struct HitboxDesc* objBoxDesc) {
  struct Instance* thInst;
  int diff_y;
  MATRIX thInstMatrix;
  SVECTOR thInstPos;
  VECTOR outVec;
  long flags[2];

  // Loop over thBucket Linked List
  for (struct Thread* thBucket = objBoxDesc->bucket; thBucket != 0; thBucket = thBucket->siblingThread){
    thInst = thBucket->inst;

    thInstPos.vx = thInst->matrix.t[0];
    thInstPos.vy = thInst->matrix.t[1];
    thInstPos.vz = thInst->matrix.t[2];

    diff_y = thInst->matrix.t[1] - objBoxDesc->inst->matrix.t[1] ;

	#ifndef REBUILD_PS1
    MATH_HitboxMatrix(&thInstMatrix, &objBoxDesc->inst->matrix);
	#endif

    SetRotMatrix(&thInstMatrix);
    SetTransMatrix(&thInstMatrix);

    RotTrans(&thInstPos,&outVec, flags);

    if ( (objBoxDesc->bbox.min[0] < outVec.vx) && (objBoxDesc->bbox.max[0] > outVec.vx) &&
         (objBoxDesc->bbox.min[2] < outVec.vz) && (objBoxDesc->bbox.max[2] > outVec.vz) &&
         (objBoxDesc->bbox.min[1] < diff_y)    && (objBoxDesc->bbox.max[1] > diff_y) ) {
        return thInst; //collision thread instance
      }
    }
  return 0;
}



void DECOMP_MainDB_PrimMem(struct PrimMem* primMem, u_int size)
{
	void* pvVar1;
		
	pvVar1 = DECOMP_MEMPACK_AllocMem(size);
	primMem->size = size;
	primMem->unk2 = (int)pvVar1;
	primMem->curr = pvVar1;
	primMem->start = pvVar1;
	
	// skip alignment by & 0xfffffffc,
	// all possible size inputs are already aligned
	pvVar1 = (void*)((int)pvVar1 + size);
	primMem->end = pvVar1;
	primMem->endMin100 = (void*)((int)pvVar1 - 0x100);
	
	return;
}

void DECOMP_MainDB_OTMem(struct OTMem* otMem, u_int size)
{
	void* pvVar1;
	
	pvVar1 = DECOMP_MEMPACK_AllocMem(size);
	otMem->size = size;
	otMem->curr = pvVar1;
	otMem->start = pvVar1;
	
	// skip alignment by & 0xfffffffc,
	// all possible size inputs are already aligned
	otMem->end = (void*)((int)pvVar1 + size);
	
	return;
}

struct OverlayRDATA_230 R230 =
{
	.s_title = "title",

	.s_4 = "4",
	.s_3 = "3",
	.s_2 = "2",
	.s_1 = "1",

	.s_teststr1 = "\\TEST.STR;1"
};


struct OverlayDATA_230 D230 =
{
	// MAIN MENU CONSTS
	
	.rowsMainMenuBasic =
	{
		{0x4C, 0,1,0,0},
		{0x4D, 0,2,1,1},
		{0x4E, 1,3,2,2},
		{0x4F, 2,4,3,3},
		{0x50, 3,5,4,4},
		{0x51, 4,5,5,5},
		{-1},
	},
	
	.rowsMainMenuWithScrapbook =
	{
		{0x4C, 0,1,0,0},
		{0x4D, 0,2,1,1},
		{0x4E, 1,3,2,2},
		{0x4F, 2,4,3,3},
		{0x50, 3,5,4,4},
		{0x51, 4,6,5,5},
		{0x234,5,6,6,6},
		{-1},
	},
	
	.menuMainMenu =
	{
		.stringIndexTitle = -1,
		
		.posX_curr = 0x180,
		.posY_curr = 0x6c,
		
		.state = 0x403,
		.rows = &D230.rowsMainMenuBasic,
		.funcPtr = DECOMP_MM_MenuProc_Main,
		
		.unk1e = 1,
	},
	
	.rowsPlayers1P2P =
	{
		{0x54,   0,1,0,0},
		{0x8055, 0,1,1,1},
		{-1},
	},
	
	.menuPlayers1P2P =
	{
		.stringIndexTitle = 0x53,
		
		.state = 9,
		.rows = &D230.rowsPlayers1P2P,
		.funcPtr = DECOMP_MM_MenuProc_1p2p,	
	},
	
	.rowsPlayers2P3P4P =
	{
		{0x8055, 0,1,0,0},
		{0x8056, 0,2,1,1},
		{0x8057, 1,2,2,2},
		{-1},
	},
	
	.menuPlayers2P3P4P =
	{
		.stringIndexTitle = 0x53,
		
		.state = 9,
		.rows = &D230.rowsPlayers2P3P4P,
		.funcPtr = DECOMP_MM_MenuProc_2p3p4p,	
	},
	
	.rowsDifficulty =
	{
		{0x15A, 0,1,0,0},
		{0x15B, 0,2,1,1},
		{0x15C, 1,2,2,2},
		{-1},
	},
	
	.menuDifficulty =
	{
		.stringIndexTitle = 0x159,
		
		.state = 1,
		.rows = &D230.rowsDifficulty,
		.funcPtr = DECOMP_MM_MenuProc_Difficulty,	
	},
	
	.rowsRaceType =
	{
		{0x15E, 0,1,0,0},
		{0x15F, 0,1,1,1},
		{-1},
	},
	
	.menuRaceType =
	{
		.stringIndexTitle = 0x15D,
		
		.state = 1,
		.rows = &D230.rowsRaceType,
		.funcPtr = DECOMP_MM_MenuProc_SingleCup,	
	},
	
	.rowsAdventure =
	{
		{0x8d, 0,1,0,0},
		{0x8e, 0,1,1,1},
		{-1},
	},
	
	.menuAdventure =
	{
		.stringIndexTitle = -1,
		
		.state = 9,
		.rows = &D230.rowsAdventure,
		.funcPtr = DECOMP_MM_MenuProc_NewLoad,	
	},

#if 0
	.langIndex = {2,3,4,5,6,7},

	.rowsLanguage = 
	{
		{0x85, 0,1,0,0},
		{0x86, 0,2,1,1},
		{0x87, 1,3,2,2},
		{0x88, 2,4,3,3},
		{0x89, 3,5,4,4},
		{0x8a, 4,5,5,5},
		{-1}
	},

	.menuLanguage = 
	{
		.stringIndexTitle = -1,
		
		.state = 0x400001,
		.rows = &D230.rowsLngBoot,
		.funcPtr = DECOMP_MM_MenuProc_Language
	},

#endif
	
	.menuCharacterSelect =
	{
		.stringIndexTitle = -1,
		
		.state = 0x28,
		.funcPtr = DECOMP_MM_Characters_MenuProc,
	},
	
	.menuTrackSelect =
	{
		.stringIndexTitle = -1,
		
		.state = 0x28,
		.funcPtr = DECOMP_MM_TrackSelect_MenuProc,
	},
	
	.rowsCupSelect =
	{
		{0, 0,2,0,1},
		{0, 1,3,0,1},
		{0, 0,2,2,3},
		{0, 1,3,2,3},
		{-1}
	},
	
	.menuCupSelect =
	{
		.stringIndexTitle = -1,
		
		.state = 0x2408,
		.rows = &D230.rowsCupSelect,
		.funcPtr = DECOMP_MM_CupSelect_MenuProc,	
	},
	
	.menuBattleWeapons =
	{
		.stringIndexTitle = -1,
		
		.state = 0x28,
		.funcPtr = DECOMP_MM_Battle_MenuProc,
	},
	
	.menuHighScores =
	{
		.stringIndexTitle = -1,
		
		.state = 0x28,
		.funcPtr = DECOMP_MM_HighScore_MenuProc,
	},
	
	.menuScrapbook =
	{
		.stringIndexTitle = -1,
		
		.state = 0x20,
		.funcPtr = DECOMP_MM_Scrapbook_PlayMovie,
	},
	
	.arrayMenuPtrs =
	{
		&D230.menuMainMenu,
		&D230.menuPlayers1P2P,
		&D230.menuPlayers2P3P4P,
		&D230.menuAdventure,
		&D230.menuCharacterSelect,
		&D230.menuTrackSelect,
		&D230.menuCupSelect,
		&D230.menuBattleWeapons,
		&D230.menuHighScores
	},
	
	.titleInstances =
	{
		{0x68, FPS_DOUBLE(0x4e), 0xe6, 0},
		{0x66, FPS_DOUBLE(0x0), 0xe6, 1},
		{0x67, FPS_DOUBLE(0x14), 0xe6, 0},
		{0x69, FPS_DOUBLE(0x4e), 0xe6, 0},
		{0x6a, FPS_DOUBLE(0x8c), 0xe6, 0},
		{0x6b, FPS_DOUBLE(0xd7), 0xe6, 0}
	},
	
	.titleCameraPos = {0x32, 0xFFE2, 0x64, 0},
	.titleCameraRot = {0, 0xFF9C, 0, 0},
	
	.title_numFrameTotal = FPS_DOUBLE(0xC),
	.title_numTransition = FPS_DOUBLE(8),
	
	.title_mainPosX = 0x180,
	.title_mainPosY = 0x6c,
	
	.title_advPosX = 0,
	.title_advPosY = 0,
	.title_racePosX = 0,
	.title_racePosY = 0,
	.title_plyrPosX = 0,
	.title_plyrPosY = 0,
	.title_diffPosX = 0,
	.title_diffPosY = 0,
	
	.title_camPos = {0x32, 0xFFE2, 0x64, 0},
	
	.transitionMeta_Menu =
	{
		{512, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 2, 0, 0},
		{0, 0, 3, 0, 0},
		{0x4B0, 0xFFE2, 0, 0, 0},
		{0x64, 0xC8, 0, 0, 0},
		{0, 0, -1, 0, 0},
	},
	
	.titleSounds =
	{
		{0x94, 0x9B},
		{0x9E, 0x9C},
		{0xAA, 0x9D},
		{0xB4, 0x9E},
		{0x6C, 0x9F},
		{0x49, 0xA0},
		{0x84, 0xA1},
		{0xC8, 0xA2},
	},
	
	// these are rewritten in MM_CheatCodes
	.cheatButtonEntry = {0},
	
	.cupDifficultyUnlockFlags = {-1, 0xC, 0x10, 0},
	.cupDifficultyLngIndex = {0x15A, 0x15B, 0x15C, 0},
	.cupDifficultySpeed = {0x50, 0xA0, 0xF0},
	
	// CHARACTER SELECT CONSTS
	
	.characterSelectWindowPos =
	{
		// 1P full menu
		{0x7F, 0xA},
		
		// 1P small menu
		{0x4D, 0x1E}, 
		
		// 2P full menu
		{0xA, 0xA},
		{0x101, 0xA},
		
		// 2P small menu
		{0x1E, 0x1E},
		{0x100, 0x1E},
		
		// 3P menu
		{0x136, 0x4},
		{0x136, 0x4A},
		{0x136, 0x90},
		
		// 4P menu
		{0x15, 0x1},
		{0x13F, 0x1},
		{0x15, 0x95},
		{0x13F, 0x95},
	},
	
	.ptrSelectWindowPos =
	{
		// full menus, 1p2p3p4p
		&D230.characterSelectWindowPos[0],
		&D230.characterSelectWindowPos[2],
		&D230.characterSelectWindowPos[6],
		&D230.characterSelectWindowPos[9],
		
		// small menus, 1p2p
		&D230.characterSelectWindowPos[1],
		&D230.characterSelectWindowPos[4],
	},
	
	.windowW =
	{
		0xF6, 0xD6, 0xA0, 0xA0, 0x15A, 0xD6
	},
	
	.windowH =
	{
		0x50, 0x50, 0x40, 0x40, 0x5C, 0x5C
	},
	
	.driverPosZ =
	{
		0xC8, 0xC8, 0xFa, 0xFa, 0xAA, 0xAA
	},
	
	.driverPosY =
	{
		0x28, 0x28, 0x28, 0x28, 0x28, 0x28
	},
	
	.textPosArr =
	{
		0x46, 0x46, 0x36, 0x36, 0x52, 0x52
	},

	.csm_1P2P_limited = 
	{
		// Crash
		{0x80, 0x80,  {0, 4,8,1}, 0, 0xFFFF},
		// Cortex
		{0xC0, 0x80,  {1, 5,0,2}, 1, 0xFFFF},
		// Tiny
		{0x100, 0x80, {2,6,1,3}, 2, 0xFFFF},
		// Coco
		{0x140, 0x80, {3,7,2,9}, 3, 0xFFFF},
		// N. Gin
		{0x80, 0xA7,  {0,12,10,5}, 4, 0xFFFF},
		// Dingo
		{0xC0, 0xA7,  {1,13,4,6}, 5, 0xFFFF},
		// Polar
		{0x100, 0xA7, {2,14,5,7}, 6, 0xFFFF},
		// Pura
		{0x140, 0xA7, {3,14,6,11}, 7, 0xFFFF},
		// N. Tropy
		{0x40, 0x80,  {8,10,8,0}, 12, 0x5},
		// Pinstripe
		{0x180, 0x80, {9,11,3,9}, 8, 0xA},
		// Roo
		{0x40, 0xA7,  {8,10,10,4}, 10, 0x7},
		// Papu
		{0x180, 0xA7, {9,11,7,11}, 9, 0x8},
		// Komodo Joe
		{0xA0, 0xCE,  {4,12,12,13}, 11, 0x9},
		// Penta
		{0xE0, 0xCE,  {5,13,12,14}, 13, 0x6},
		// Fake Crash
		{0x120, 0xCE, {6,14,13,14}, 14, 0xB}
	},

	.csm_1P2P = 
	{
		// Crash
		{0x80, 0x60,  {0,4,8,1}, 0, 0xFFFF},
		// Cortex
		{0xC0, 0x60,  {1,5,0,2}, 1, 0xFFFF},
		// Tiny
		{0x100, 0x60, {2,6,1,3}, 2, 0xFFFF},
		// Coco
		{0x140, 0x60, {3,7,2,9}, 3, 0xFFFF},
		// N. Gin
		{0x80, 0x87,  {0,12,10,5}, 4, 0xFFFF},
		// Dingo
		{0xC0, 0x87,  {1,13,4,6}, 5, 0xFFFF},
		// Polar
		{0x100, 0x87, {2,14,5,7}, 6, 0xFFFF},
		// Pura
		{0x140, 0x87, {3,14,6,11}, 7, 0xFFFF},
		// N. Tropy
		{0x40, 0x60,  {8,10,8,0}, 12, 0x5},
		// Pinstripe
		{0x180, 0x60, {9,11,3,9}, 8, 0xA},
		// Roo
		{0x40, 0x87,  {8,10,10,4}, 10, 0x7},
		// Papu
		{0x180, 0x87, {9,11,7,11}, 9, 0x8},
		// Komodo Joe
		{0xA0, 0xAE,  {4,12,12,13}, 11, 0x9},
		// Penta
		{0xE0, 0xAE,  {5,13,12,14}, 13, 0x6},
		// Fake Crash
		{0x120, 0xAE, {6,14,13,14}, 14, 0xB}
	},

	.csm_3P = 
	{
		// Crash
		{0x20, 0x47,  {12,4,0,1}, 0, 0xFFFF},
		// Cortex
		{0x60, 0x47,  {13,5,0,2}, 1, 0xFFFF},
		// Tiny
		{0xA0, 0x47,  {14,6,1,3}, 2, 0xFFFF},
		// Coco
		{0xE0, 0x47,  {14,7,2,3}, 3, 0xFFFF},
		// N. Gin
		{0x20, 0x6E,  {0,8,4,5}, 4, 0xFFFF},
		// Dingo
		{0x60, 0x6E,  {1,9,4,6}, 5, 0xFFFF},
		// Polar
		{0xA0, 0x6E,  {2,10,5,7}, 6, 0xFFFF},
		// Pura
		{0xE0, 0x6E,  {3,11,6,7}, 7, 0xFFFF},
		// N. Tropy
		{0x20, 0x95,  {4,8,8,9}, 12, 0x5},
		// Pinstripe
		{0x60, 0x95,  {5,9,8,10}, 8, 0xA},
		// Roo
		{0xA0, 0x95,  {6,10,9,11}, 10, 0x7},
		// Papu
		{0xE0, 0x95,  {7,11,10,11}, 9, 0x8},
		// Komodo Joe
		{0x40, 0x20,  {12,1,12,13}, 11, 0x9},
		// Penta
		{0x80, 0x20,  {13,2,12,14}, 13, 0x6},
		// Fake Crash
		{0xC0, 0x20,  {14,3,13,14}, 14, 0xB}
	},

	.csm_4P = 
	{
		// Crash
		{0x80, 0x47,  {0,4,10,1}, 0, 0xFFFF},
		// Cortex
		{0xC0, 0x47,  {14,5,0,2}, 1, 0xFFFF},
		// Tiny
		{0x100, 0x47,  {14,6,1,3}, 2, 0xFFFF},
		// Coco
		{0x140, 0x47,  {3,7,2,11}, 3, 0xFFFF},
		// N. Gin
		{0x80, 0x6E,  {0,4,12,5}, 4, 0xFFFF},
		// Dingo
		{0xC0, 0x6E,  {1,8,4,6}, 5, 0xFFFF},
		// Polar
		{0x100, 0x6E,  {2,9,5,7}, 6, 0xFFFF},
		// Pura
		{0x140, 0x6E,  {3,7,6,13}, 7, 0xFFFF},
		// N. Tropy
		{0xC0, 0x95,  {5,8,8,9}, 12, 0x5},
		// Fake Crash
		{0x100, 0x95,  {6,9,8,9}, 14, 0xB},
		// Roo
		{0x40, 0x47,  {10,12,10,0}, 10, 0x7},
		// Papu
		{0x180, 0x47,  {11,13,3,11}, 9, 0x8},
		// Komodo Joe
		{0x40, 0x6E,  {10,12,12,4}, 11, 0x9},
		// Pinstripe
		{0x180, 0x6E,  {11,13,7,13}, 8, 0xA},
		// Penta
		{0xE0, 0x20,  {14,1,14,14}, 13, 0x6}
	},
	
	.ptrCsmArr = 
	{
		&D230.csm_1P2P,
		&D230.csm_1P2P,
		&D230.csm_3P,
		&D230.csm_4P,
		&D230.csm_1P2P_limited,
		&D230.csm_1P2P_limited
	},

	.characterMenuID = 
	{
		-1, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},

	.transitionMeta_csm_1P2P = 
	{
		{0, 0xC8, 6, 0, 0},
		{0, 0xC8, 5, 0, 0},
		{0, 0xC8, 4, 0, 0},
		{0, 0xC8, 3, 0, 0},
		{0, 0xC8, 5, 0, 0},
		{0, 0xC8, 4, 0, 0},
		{0, 0xC8, 3, 0, 0},
		{0, 0xC8, 2, 0, 0},
		{0, 0xC8, 7, 0, 0},
		{0, 0xC8, 1, 0, 0},
		{0, 0xC8, 6, 0, 0},
		{0, 0xC8, 0, 0, 0},
		{0, 0xC8, 4, 0, 0},
		{0, 0xC8, 3, 0, 0},
		{0, 0xC8, 2, 0, 0},
		{-512, 0, 2, 0, 0},
		{512, 0, 3, 0, 0},
		{512, 0, 1, 0, 0},
		{512, 0, 7, 0, 0},
		{512, 0, 5, 0, 0},
		{0, 0, -1, 0, 0},
	},

	.transitionMeta_csm_3P = 
	{
		{-512, 0, 2, 0, 0},
		{-512, 0, 3, 0, 0},
		{-512, 0, 4, 0, 0},
		{-512, 0, 5, 0, 0},
		{-512, 0, 1, 0, 0},
		{-512, 0, 2, 0, 0},
		{-512, 0, 3, 0, 0},
		{-512, 0, 4, 0, 0},
		{-512, 0, 0, 0, 0},
		{-512, 0, 1, 0, 0},
		{-512, 0, 2, 0, 0},
		{-512, 0, 3, 0, 0},
		{-512, 0, 2, 0, 0},
		{-512, 0, 3, 0, 0},
		{-512, 0, 4, 0, 0},
		{-512, 0, 0, 0, 0},
		{512, 0, 5, 0, 0},
		{512, 0, 3, 0, 0},
		{512, 0, 1, 0, 0},
		{512, 0, 5, 0, 0},
		{0, 0, -1, 0, 0},
	},

	.transitionMeta_csm_4P = 
	{
		{-512, 0, 1, 0, 0},
		{-512, 0, 2, 0, 0},
		{-512, 0, 3, 0, 0},
		{-512, 0, 4, 0, 0},
		{-512, 0, 2, 0, 0},
		{-512, 0, 3, 0, 0},
		{-512, 0, 4, 0, 0},
		{-512, 0, 5, 0, 0},
		{-512, 0, 3, 0, 0},
		{-512, 0, 4, 0, 0},
		{-512, 0, 0, 0, 0},
		{-512, 0, 5, 0, 0},
		{-512, 0, 1, 0, 0},
		{-512, 0, 6, 0, 0},
		{-512, 0, 2, 0, 0},
		{-512, 0, 0, 0, 0},
		{512, 0, 3, 0, 0},
		{512, 0, 1, 0, 0},
		{512, 0, 7, 0, 0},
		{512, 0, 5, 0, 0},
		{0, 0, -1, 0, 0},
	},

	.ptr_transitionMeta_csm = 
	{
		&D230.transitionMeta_csm_1P2P,
		&D230.transitionMeta_csm_1P2P,
		&D230.transitionMeta_csm_3P,
		&D230.transitionMeta_csm_4P
	},

	.csm_instPos = {0, 0x28, 0xFA, 0},

	.csm_instRot = {0x800, 0, 0},
	
	.moveModels = FPS_DOUBLE(4),

	.unkCharacterWindows = 0x8C,

	.PlayerNumberStrings = 
	{
		&R230.s_1,
		&R230.s_2,
		&R230.s_3,
		&R230.s_4
	},

	.getNextDriver1 = {2, 2, 1, 1},

	.getNextDriver2 = {3, 3, 0, 0},

	.characterSelect_Outline = 0,

	.characterSelect_NeutralColor = 0x808080, 

	.characterSelect_ChosenColor = 0,

	.characterSelect_BlueRectColors = 
	{ 
		0x1b, 0x6a, 0xcb, 0x00, 
		0x9b, 0xd2, 0xf2, 0x40, 
		0xb7, 0xe1, 0xed, 0x43, 
		0x65, 0x4b, 0x03, 0x46, 
		0xa6, 0x83, 0x23, 0x50, 
		0xdf, 0xc8, 0x95, 0x64 
	},

	// TRACK SELECT CONSTS

	.arcadeTracks = 
	{
		// CRASH_COVE
		{3, 0x51, 0x6a, 0xFFFF, 0x1e4, 0x258},
		// ROO_TUBES
		{6, 0x5b, 0x7e, 0xFFFF, 0x1fa, 0x283},
		// TIGER_TEMPLE
		{4, 0x59, 0x7a, 0xFFFF, 0x1e5, 0x31f},
		// COCO_PARK
		{14, 0x43, 0x5c, 0xFFFF, 0x1ee, 0x2a1},
		// MYSTERY_CAVES
		{9, 0x4e, 0x64, 0xFFFF, 0x1e9, 0x39b},
		// BLIZZARD_BLUFF
		{2, 0x4f, 0x66, 0xFFFF, 0x1e3, 0x2cd},
		// SEWER_SPEEDWAY
		{8, 0x57, 0x76, 0xFFFF, 0x1e8, 0x373},
		// DINGO_CANYON
		{0, 0x53, 0x6e, 0xFFFF, 0x1e1, 0x2a3},
		// PAPU_PYRAMID
		{5, 0x5a, 0x7c, 0xFFFF, 0x1e6, 0x309},
		// DRAGON_MINES
		{1, 0x54, 0x70, 0xFFFF, 0x1e2, 0x285},
		// POLAR_PASS
		{12, 0x50, 0x68, 0xFFFF, 0x1ec, 0x4ca},
		// CORTEX_CASTLE
		{10, 0x4d, 0x62, 0xFFFF, 0x1ea, 0x41b},
		// TINY_ARENA
		{15, 0x44, 0x5e, 0xFFFF, 0x1ef, 0x58f},
		// HOT_AIR_SKYWAY
		{7, 0x4c, 0x60, 0xFFFF, 0x1e7, 0x4f9},
		// N_GIN_LABS
		{11, 0x52, 0x6c, 0xFFFF, 0x1eb, 0x448},
		// OXIDE_STATION
		{13, 0x58, 0x78, 0xFFFE, 0x1ed, 0x5da},
		// SLIDE_COLISEUM
		{16, 0x55, 0x72, 0xFFFF, 0x1f0, 0x39a},
		// TURBO_TRACK
		{17, 0x56, 0x74, 0x1, 0x1f1, 0x3d5},
	},

	.battleTracks = 
	{
		// NITRO_COURT
		{18, 0x45, 0xFFFF, 0xFFFF, 0x1f2, 0x197},
		// RAMPAGE_RUINS
		{19, 0x46, 0xFFFF, 0xFFFF, 0x1f3, 0x19a},
		// PARKING_LOT
		{20, 0x47, 0xFFFF, 0x2, 0x1f4, 0x199},
		// SKULL_ROCK
		{21, 0x48, 0xFFFF, 0xFFFF, 0x1f5, 0x19a},
		// THE_NORTH_BOWL
		{22, 0x49, 0xFFFF, 0x3, 0x1f6, 0x19a},
		// ROCKY_ROAD
		{23, 0x4a, 0xFFFF, 0xFFFF, 0x1f7, 0x19a},
		// LAB_BASEMENT
		{24, 0x4b, 0xFFFF, 0x4, 0x1f8, 0x19a},
	},

	.transitionMeta_trackSel = 
	{
		{-512, 0, 1, 0, 0},
		{0, -200, 2, 0, 0},
		{0, 200, 3, 0, 0},
		{512, 0, 4, 0, 0},
		{0, 0, -1, 0, 0}
	},

	.lapRowVal = {3, 5, 7, 0},

	.rowsLapSel = 
	{
		{0x9b, 0,1,0,0},
		{0x9c, 0,2,1,1},
		{0x9d, 1,2,2,2},
		{-1}
	},

	.menuLapSel = 
	{
		.stringIndexTitle = 0x9a,
		
		.posX_curr = 0x18C,
		.posY_curr = 0x7c,

		.state = 0x81,
		.rows = &D230.rowsLapSel,
	},

	.videoCol = 0x808080,

	.timeTrialStarCol = {0xE, 0x16},
	.timeTrialFlagGet = {0x1, 0x2},

	.drawMapOffset =
	{
		{0,0,1},
		{-2,0,3},
		{2,0,3},
		{0,1,3},
		{0,-1,3},
		{12,6,2}
	},

	// CUP SELECT CONSTS

	.transitionMeta_cupSel = 
	{
		{-256, -100, 5, 0, 0},
		{256, -100, 4, 0, 0},
		{-256, 100, 3, 0, 0},
		{256, 100, 2, 0, 0},
		{0, -100, 0, 0, 0},
		{0, 0, -1, 0, 0}
	},

	.cupSel_StarColorIndex = {0x11, 0xE, 0x16, 0},

	.cupSel_StarUnlockFlag = {0xC, 0x10, 0x14, 0},

	.cupSel_Color = 0xC0C0C0,

	// BATTLE CONSTS

	.transitionMeta_battle = 
	{
		{400, 0, 5, 0, 0},
		{-200, 0, 5, 0, 0},
		{400, 0, 4, 0, 0},
		{-200, 0, 4, 0, 0},
		{400, 0, 3, 0, 0},
		{-200, 0, 3, 0, 0},
		{400, 0, 2, 0, 0},
		{-200, 0, 2, 0, 0},
		{400, 0, 0, 0, 0},
		{0, -100, 0, 0, 0},
		{0, 0, -1, 0, 0}
	},

	.rowsBattleType = 
	{
		{0x92, 0,1,0,0},
		{0x93, 0,2,1,1},
		{0x94, 1,2,2,2},
		{-1}
	},

	.menuBattleType = 
	{
		.stringIndexTitle = -1,

		.state = 0x10280,
		.rows = &D230.rowsBattleType,
		.funcPtr = DECOMP_MM_Battle_CloseSubMenu
	},

	.rowsBattleLengthLifeTime =
	{
		{0xA4, 0,1,0,0},
		{0xA5, 0,2,1,1},
		{0xA6, 1,2,2,2},
		{-1}
	},

	.menuBattleLengthLifeTime = 
	{
		.stringIndexTitle = -1,

		.state = 0x10280,
		.rows = &D230.rowsBattleLengthLifeTime,
		.funcPtr = DECOMP_MM_Battle_CloseSubMenu
	},

	.rowsBattleLengthTimeTime =
	{
		{0xA7, 0,1,0,0},
		{0xA8, 0,2,1,1},
		{0xA9, 1,2,2,2},
		{-1}
	},

	.menuBattleLengthTimeTime = 
	{
		.stringIndexTitle = -1,

		.state = 0x10280,
		.rows = &D230.rowsBattleLengthTimeTime,
		.funcPtr = DECOMP_MM_Battle_CloseSubMenu
	},

	.rowsBattleLengthPoints =
	{
		{0xA1, 0,1,0,0},
		{0xA2, 0,2,1,1},
		{0xA3, 1,2,2,2},
		{-1}
	},

	.menuBattleLengthPoints = 
	{
		.stringIndexTitle = -1,

		.state = 0x10280,
		.rows = &D230.rowsBattleLengthPoints,
		.funcPtr = DECOMP_MM_Battle_CloseSubMenu
	},

	.rowsBattleLengthLifeLife =
	{
		{0x9e, 0,1,0,0},
		{0x9f, 0,2,1,1},
		{0xA0, 1,2,2,2},
		{-1}
	},

	.menuBattleLengthLifeLife = 
	{
		.stringIndexTitle = -1,

		.state = 0x10280,
		.rows = &D230.rowsBattleLengthLifeLife,
		.funcPtr = DECOMP_MM_Battle_CloseSubMenu
	},

	.rowsBattleStartGame =
	{
		{0xAE, 0,0,0,0},
		{-1}
	},

	.menuBattleStartGame = 
	{
		.stringIndexTitle = -1,

		.state = 0x10280,
		.rows = &D230.rowsBattleStartGame,
		.funcPtr = DECOMP_MM_Battle_CloseSubMenu
	},

	.battleMenuArray =
	{
		&D230.menuBattleType,
		&D230.menuBattleLengthTimeTime,
		&D230.menuBattleLengthPoints,
		&D230.menuBattleLengthLifeLife,
		&D230.menuBattleLengthLifeTime
	},

	.battleWeaponsEnabled =
	{
		0x1,    0x2,   0x2,    0x6,
		0x4,    0x7,   0x8,    0x8,
		0x10,   0x9,   0x40,   0xB,
		0x80,   0xC,   0x400,  0xF,
		0x800,  0x10,  0x1000, 0x11,
		0x2000, 0x12
	},

	.FlagesGameMode1_BattleType = 
		{POINT_LIMIT,TIME_LIMIT,LIFE_LIMIT},

	.time_3_6_9 = {3,6,9},
	.time_3_6_INF = {3,6,0xFF},
	.lives_3_6_9 = {3,6,9},
	.points_5_10_15 = {5,10,15},

	.color1 = 0x808080,
	.color2 = 0x101010,
	.color3 = 0x806050,

	// HIGH SCORE CONSTS

	.transitionMeta_HighScores =
	{
		{0, -100, 0, 0, 0},
		{-256, 0, 6, 0, 0},
		{-256, 0, 5, 0, 0},
		{-256, 0, 4, 0, 0},
		{-256, 0, 3, 0, 0},
		{-256, 0, 2, 0, 0},
		{-256, 0, 1, 0, 0},
		{256, 0, 3, 0, 0},
		{256, 0, 2, 0, 0},
		{256, 0, 1, 0, 0},
		{256, 0, 0, 0, 0},
		{0, 0, -1, 0, 0}
	},

	.colorIndexArray = {0xE, 0x16},

	.highscore_unkflags = {0x1, 0x2},

	.highscore_iconColor = 0x808080,

	.rowsHighScore = 
	{
		{0xAF, 0,1,0,0},
		{0xB1, 0,2,0,0},
		{0xB2, 1,2,0,0},
		{-1}
	},

	.menuHighScore =
	{
		.stringIndexTitle = -1,
		.posX_curr = 0x17C,
		.posY_curr = 0xAF,

		.state = 0x81,
		.rows = &D230.rowsHighScore
	},

	.highScore_trackDesired = 0,
	.highScore_rowDesired = 0,
	.highScore_trackCurr = 0,
	.highScore_rowCurr = 0,

#if 0

	.fileIndexLngBoot = {2,3,4,5,6,7},
	
	.rowsLngBoot = 
	{
		{0x85, 0,1,0,0},
		{0x86, 0,2,1,1},
		{0x87, 1,3,2,2},
		{0x88, 2,4,3,3},
		{0x89, 3,5,4,4},
		{0x8a, 4,5,5,5},
		{-1}
	}

	.menuLngBoot = 
	{
		.stringIndexTitle = -1,
		
		.posX_curr = 256,
		.posY_curr = 118,
		
		.state = 0xC03,
		.rows = &D230.rowsLngBoot,
		.funcPtr = DECOMP_MM_MenuProc_LanguageBoot
	}

#endif

	.titleObj = 0,

	// TRACK SELECT DYN
	.trackSel_changeTrack_frameCount = 0,
	.trackSel_currTrack = 0,
	.trackSel_direction = 0,
	.trackSel_boolOpenLapBox = 0,
	.trackSel_transitionState = 0,
	.trackSel_StartRaceAfterFadeOut = 0,
	.trackSel_transitionFrames = 0,
	.trackSel_video_frameCount = 0,
	.trackSel_video_boolAllocated = 0,
	.trackSel_video_state = 0,
	.trackSel_unk = 0,

	// CUP SELECT DYN
	.cupSel_transitionState = 0,
	.cupSel_postTransition_boolStart = 0,
	.cupSel_transitionFrames = 0,

	// BATTLE DYN
	.battle_transitionState = 0,
	.battle_postTransition_boolStart = 0,
	.battle_transitionFrames = 0,

	// HIGHSCORE DYN
	.highScore_transitionState = 0,
	.highScore_transitionFrames = {0,0,0},
	.highScore_horizontalMove = {0,0},
	.highScore_verticalMove = {0,0},

	// SCRAPBOOK
	.scrapbookState = 0,

	// CHAR SELECT AND TITLE DYN
	.characterSelect_sizeY = 0,
	.desiredMenuIndex = 0,
	.movingToTrackMenu = 0,

	.characterSelect_MoveDir = {0,0,0,0},
	.characterSelect_charIDs_desired = {0,0,0,0},
	.characterSelect_charIDs_curr = {0,0,0,0},
	.characterSelect_angle = {0,0,0,0},
	.characterSelect_transitionState = 0,
	.characterSelect_ptrWindowXY = 0,
	.characterSelectIconLayout = 0,

	.timerInTitle = 0,
	.csm_Active = 0,
	.MM_State = 0,
	.isMenuTransitioning = 0,

	.timerPerPlayer = {0,0,0,0},
#if 0
	.langMenuTimer = 0,
#endif
	.isRosterExpanded = 0,
	.characterSelect_sizeX = 0,
	.ptrIntroCam = 0,
	.textPos = 0,
	.ptrTransitionMeta = 0,
	.countMeta0xD = 0,
	.transitionFrames = 0,

	.s_SliceBuf = "SliceBuf",
	.s_VlcBuf = "VlcBuf",
	.s_RingBuf = "RingBuf",
};

struct OverlayDATA_232 D232 =
{
	// 800b4ddc
	.specLightGem = 
	{
		0xA0A, 0xF5F6, 0x787,
		0xA0A, 0xF5F6, 0x787,
		0xA0A, 0xF5F6, 0x787,
		0xA0A, 0xF5F6, 0x787,
		0xA0A, 0xF5F6, 0x787
	},
	
	// 800b4dfc
	.specLightRelic = 
	{
		0x690, 0xD20, 0x690,
		0x690, 0xD20, 0x690,
		0x690, 0xD20, 0x690,
		0x690, 0xD20, 0x690,
		0x690, 0xD20, 0x690,
	},
	
	// 800b4e1c
	.specLightToken = 
	{
		0xF5F6, 0x787, 0xA0A,
		0xF5F6, 0x787, 0xA0A,
		0xF5F6, 0x787, 0xA0A,
		0xF5F6, 0x787, 0xA0A,
		0xF5F6, 0x787, 0xA0A,
	},

	// 800b4e3c
	.rowsTokenRelic =
	{
		{0x176, 0, 1, 0, 0}, // CTR CHALLENGE
		{0xb8,  0, 1, 1, 1}, // RELIC RACE
		{-1,  0, 0, 0, 0}  // NULL
	},

	// 800b4e50
	.menuTokenRelic =
	{
		.stringIndexTitle = 0xb6,
		.posX_curr = 0x100,
		.posY_curr = 0x6c,
		.unk1 = 0,
		.state = 0x100803,
		.rows = &D232.rowsTokenRelic[0],
		.funcPtr = DECOMP_AH_WarpPad_MenuProc,
		.drawStyle = 4,
	},

	// 800b4e7c
	.arrKeysNeeded = 
	{
		2, 1, 2, 3, 4
	},

	// 800b4e86
	.levelID = -1,

	// 800b4e88
	.timeCrystalChallenge =
	{
		0x1c200,	// NITRO_COURT
		0x13ec0,	// RAMPAGE_RUINS
		0xe100,		// PARKING_LOT (null)
		0x13740,	// SKULL_ROCK
		0xe100,		// THE_NORTH_BOWL (null)
		0x12c00,	// ROCKY_ROAD
		0xe100,		// LAB_BASEMENT (null)
	},
	
	// 800b4ea4
	.saveObjCameraOffset =
	{
		0x800, 0, 0
	},
	
	// 800b4eac
	.primOffsetXY_LoadSave =
	{
		0, 0,
		-2, 0,
		2, 0,
		0, -1,
		0, 1
	},
	
	// 800b4ec0
	.primOffsetXY_HubArrow =
	{
		0, 0,
		-2, 0,
		2, 0,
		0, -1,
		0, 1
	},
	
	// 800b4ed4
	.hubItems_hub1 =
	{
		{0xB780, 0x3D00, 0, 4},
		{0xC824, 0x46e,  0, -2},
		{0xFB50, 0x44c0, 0xc00, -3},
		{0xbcd0, 0x1482, 0x800, 100},
		{-1}
	},
	
	// 800b4efc
	.hubItems_hub2 =
	{
		{0xC178, 0xE493, 0, 0},
		{0xD6FC, 0x1093, 0x800, -1},
		{0xE890, 0xDECC, 0xc00, -4},
		{0xCC0C, 0xE764, 0x400, 100},
		{-1}
	},
	
	// 800b4f24
	.hubItems_hub3 =
	{
		{0x1099, 0x38b3, 0, 1},
		{0x23C9, 0x1ffc, 0, -4},
		{0xDE99, 0x3EB3, 0x400, -1},
		{0xEA6,  0x4556, 0x400, 100},
		{-1}
	},
	
	// 800b4f4c
	.hubItems_hub4 =
	{
		{0x2AF8, 0xEE13, 0, 2},
		{0xd5f8, 0xc993, 0x400, -2},
		{0x1678, 0xc593, 0, -5},
		{0x2ee0, 0x32c8, 0x800, -3},
		{0x109a, 0xdcd8, 0x576, 100},
		{-1}
	},
	
	// 800b4f7c
	.hubItems_hub5 =
	{
		{0x9f8,  0xac93, 0, 3},
		{0x5dc,  0xd493, 0x800, -4},
		{0x157c, 0xab3c, 0, 100},
		{-1}
	},
	
	.hubItemsXY_ptrArray =
	{
		&D232.hubItems_hub1[0],
		&D232.hubItems_hub2[0],
		&D232.hubItems_hub3[0],
		&D232.hubItems_hub4[0],
		&D232.hubItems_hub5[0],
	},
	
	.hubArrowXY_Inner =
	{
		3, 4,
		6, 2,
		5, 4
	},
	
	.hubArrowXY_Outter =
	{
		0, 3,
		-2, 1,
		0, 0,
		2, 1,
	},
	
	.loadSave_pos =
	{
		-4, -2,
		4, -2,
		-4, 2,
		4, 2,
	},
	
	.loadSave_col =
	{
		0xBEFFBE,
		0xFF00,
		0xFF00,
		0xBEFFBE,
	},
	
	.hubArrow_pos =
	{
		0, 0xFFF8,
		0xFFF8, 8,
		8, 8
	},
	
	.hubArrow_col1 =
	{
		0xFF00FF,
		0xFF0000,
		0xFF0000,
	},
	
	.hubArrow_col2 =
	{
		0x80FFFF,
		0xFF0000,
		0xFF0000,
	},
	
	.hubArrowGray1 =
	{
		0x808080,
		0x808080,
		0x808080,
	},
	
	.hubArrowGray2 =
	{
		0x808080,
		0x808080,
		0x808080,
	},
	
	.advPausePages =
	{
		// hubs and bosses
		{0x19, -1, 0, 0xF},
		{0x1A, -1, 0, 0xA},
		{0x1B, -1, 0, 0x9},
		{0x1C, -1, 0, 0xB},
		{0x1D, -1, 0, 0x8},
		
		// gems and relics
		{-1, 0x10, 1, 0},
		{-1, 0x11, 2, 0},
	},
	
	.advPauseInst =
	{
		// gems: red, green, blue, yellow, purple
		{0x5F, 0xAF0, 0x8086c,  USE_SPECULAR_LIGHT, {0xfa5b, 0xf0f, 0xfe1f, 0}},
		{0x5F, 0xAF0, 0x86c08,  USE_SPECULAR_LIGHT, {0xfa5b, 0xf0f, 0xfe1f, 0}},
		{0x5F, 0xAF0, 0x808000, USE_SPECULAR_LIGHT, {0xfa5b, 0xf0f, 0xfe1f, 0}},
		{0x5F, 0xAF0, 0x8080,   USE_SPECULAR_LIGHT, {0xfa5b, 0xf0f, 0xfe1f, 0}},
		{0x5F, 0xAF0, 0x6c086c, USE_SPECULAR_LIGHT, {0xfa5b, 0xf0f, 0xfe1f, 0}},
		
		// key
		{0x63, 0x30D, 0xA6DC, USE_SPECULAR_LIGHT, {0xf368, 0x99f, 0xfd28}},
		
		// relic: blue, gold, platinum
		{0x61, 0x30D, 0xFFA560, USE_SPECULAR_LIGHT, {0xf368, 0x99f, 0x232}},
		{0x61, 0x30D, 0x9d2d8,  USE_SPECULAR_LIGHT, {0xf368, 0x99f, 0x232}},
		{0x61, 0x30D, 0xe9edff, USE_SPECULAR_LIGHT, {0xf368, 0x99f, 0x232}},
		
		// token: red, green, blue, yellow, purple
		{0x7d, 0x500, 0x8086c,  USE_SPECULAR_LIGHT, {0xf5f6, 0x787, 0xa0a, 0}},
		{0x7d, 0x500, 0x86c08,  USE_SPECULAR_LIGHT, {0xf5f6, 0x787, 0xa0a, 0}},
		{0x7d, 0x500, 0x800000, USE_SPECULAR_LIGHT, {0xf5f6, 0x787, 0xa0a, 0}},
		{0x7d, 0x500, 0x8080,   USE_SPECULAR_LIGHT, {0xf5f6, 0x787, 0xa0a, 0}},
		{0x7d, 0x500, 0x6c086c, USE_SPECULAR_LIGHT, {0xf5f6, 0x787, 0xa0a, 0}},
		
		// trophy
		{0x62, 0x500, 0x808080, 0, {0xf368, 0x99f, 0x232}}
	},
	
	.menuHintMenu =
	{
		.stringIndexTitle = 0xFFFF,
		.posX_curr = 0x100,
		.posY_curr = 0x6c, 
		
		.unk1 = 0,
		
		.state = 0x8A3,
		.rows = 0,
		.funcPtr = DECOMP_AH_HintMenu_MenuProc,
		.drawStyle = 4,
	
		// rest of variables all default zero
	},
	
	.fiveArrow_pos =
	{
		0, -5,
		-0x18, 6,
		0x18, 6
	},
	
	.fiveArrow_col1 =
	{
		0xC8FF, 0xFF, 0xFF
	},
	
	.fiveArrow_col2 =
	{
		0x80c8ff, 0x80ff, 0x80ff
	},
	
	.maskPos =
	{
		-0xA0, -0xA, 0x100
	},
	
	.maskRot =
	{
		0, 0x180, 0
	},
	
	.maskScale = 0x1000,
	
	.maskOffsetPos =
	{
		-0x14, 0, 0x50
	},
	
	.maskOffsetRot =
	{
		0x7AF, 0x258, 0x78
	},
	
	.maskVars =
	{
		// pos1
		-0x46, 0, 0x140,
		
		// pos2
		-0x3C, 0, 0x118,
		
		// rot1
		0x7af, 0x258, 0x78,
		
		// rot2
		0x800, 0x64, 0
	},
	
	.maskFrameCurr = 0,
	
	.emSet_maskSpawn =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0xA1,
						.particle_lifespan = 0x14,
						.particle_Type = 0,
				}
		},
		
		[1] =
		{
			.flags = 0x1B,
			
			// posX
			.initOffset = 0,
			
			.InitTypes.AxisInit =
			{
				.baseValue =
				{
					.startVal = -0x1900,
					.velocity = -0x640,
					.accel = 0,
				},
				
				.rngSeed =
				{
					.startVal = 0x3200,
					.velocity = 0xc80,
					.accel = 0,
				}
			}
			
			// last 0x10 are blank
		},
		
		[2] =
		{
			.flags = 0x1B,
			
			// posZ
			.initOffset = 2,
			
			.InitTypes.AxisInit =
			{
				.baseValue =
				{
					.startVal = -0x1900,
					.velocity = -0x640,
					.accel = 0,
				},
				
				.rngSeed =
				{
					.startVal = 0x3200,
					.velocity = 0xc80,
					.accel = 0,
				}
			}
			
			// last 0x10 are blank
		},
		
		[3] =
		{
			.flags = 0x1B,
			
			// posY
			.initOffset = 1,
			
			.InitTypes.AxisInit =
			{
				.baseValue =
				{
					.startVal = -0xC80,
					.velocity = 0x190,
					.accel = 0,
				},
				
				.rngSeed =
				{
					.startVal = 0x1900,
					.velocity = 0x640,
					.accel = 0,
				}
			}
			
			// last 0x10 are blank
		},
		
		[4] =
		{
			.flags = 3,
			
			// Scale
			.initOffset = 5,
			
			// 50% scale
			.InitTypes.AxisInit.baseValue.startVal = 0x800,
			.InitTypes.AxisInit.baseValue.velocity = -0x20,
			
			// all the rest is untouched
		},
		
		[5] =
		{
			.flags = 9,
			
			// RotX?
			.initOffset = 4,
			
			.InitTypes.AxisInit.baseValue.startVal = 1,
			.InitTypes.AxisInit.rngSeed.startVal = 0x1000,
			
			// all the rest is untouched
		},
		
		[6] =
		{
			.flags = 5,
			
			// colorR
			.initOffset = 7,
			
			.InitTypes.AxisInit.baseValue.startVal = 0x8000,
			.InitTypes.AxisInit.baseValue.accel = -0x100,
			
			// all the rest is untouched
		},
		
		[7] =
		{
			.flags = 5,
			
			// colorG
			.initOffset = 8,
			
			.InitTypes.AxisInit.baseValue.startVal = 0x8000,
			.InitTypes.AxisInit.baseValue.accel = -0x100,
			
			// all the rest is untouched
		},
		
		[8] =
		{
			.flags = 5,
			
			// colorB
			.initOffset = 9,
			
			.InitTypes.AxisInit.baseValue.startVal = 0x8000,
			.InitTypes.AxisInit.baseValue.accel = -0x100,
			
			// all the rest is untouched
		},
		
		// null terminator
		[9] = {0}
	},
	
	.emSet_maskLeave =
	{
		[0] =
		{
				.flags = 1,
				.initOffset = 12,
				.InitTypes.FuncInit =
				{
						.particle_funcPtr = 0x00000000,
						.particle_colorFlags = 0xA1,
						.particle_lifespan = 0x14,
						.particle_Type = 0,
				}
		},
		
		[1] =
		{
			.flags = 0x1B,
			
			// posX
			.initOffset = 0,
			
			.InitTypes.AxisInit =
			{
				.baseValue =
				{
					.startVal = -0x640,
					.velocity = -0xC80,
					.accel = 0,
				},
				
				.rngSeed =
				{
					.startVal = 0xc80,
					.velocity = 0x1900,
					.accel = 0,
				}
			}
			
			// last 0x10 are blank
		},
		
		[2] =
		{
			.flags = 0x1B,
			
			// posZ
			.initOffset = 2,
			
			.InitTypes.AxisInit =
			{
				.baseValue =
				{
					.startVal = -0x640,
					.velocity = -0xC80,
					.accel = 0,
				},
				
				.rngSeed =
				{
					.startVal = 0xc80,
					.velocity = 0x1900,
					.accel = 0,
				}
			}
			
			// last 0x10 are blank
		},
		
		[3] =
		{
			.flags = 0x1B,
			
			// posY
			.initOffset = 1,
			
			.InitTypes.AxisInit =
			{
				.baseValue =
				{
					.startVal = -0x190,
					.velocity = -0x4B0,
					.accel = 0,
				},
				
				.rngSeed =
				{
					.startVal = 0xc80,
					.velocity = 0xc80,
					.accel = 0,
				}
			}
			
			// last 0x10 are blank
		},
		
		[4] =
		{
			.flags = 3,
			
			// Scale
			.initOffset = 5,
			
			// 100% scale
			.InitTypes.AxisInit.baseValue.startVal = 0x1000,
			.InitTypes.AxisInit.baseValue.velocity = -0x80,
			
			// all the rest is untouched
		},
		
		[5] =
		{
			.flags = 9,
			
			// RotX?
			.initOffset = 4,
			
			.InitTypes.AxisInit.baseValue.startVal = 1,
			.InitTypes.AxisInit.rngSeed.startVal = 0x1000,
			
			// all the rest is untouched
		},
		
		[6] =
		{
			.flags = 5,
			
			// colorR
			.initOffset = 7,
			
			.InitTypes.AxisInit.baseValue.startVal = 0x8000,
			.InitTypes.AxisInit.baseValue.accel = -0x100,
			
			// all the rest is untouched
		},
		
		[7] =
		{
			.flags = 5,
			
			// colorG
			.initOffset = 8,
			
			.InitTypes.AxisInit.baseValue.startVal = 0x8000,
			.InitTypes.AxisInit.baseValue.accel = -0x100,
			
			// all the rest is untouched
		},
		
		[8] =
		{
			.flags = 5,
			
			// colorB
			.initOffset = 9,
			
			.InitTypes.AxisInit.baseValue.startVal = 0x8000,
			.InitTypes.AxisInit.baseValue.accel = -0x100,
			
			// all the rest is untouched
		},
		
		// null terminator
		[9] = {0}
	},
	
	.maskAudioSettings =
	{
		0x0, 0x28, 0xFF
	},
	
	.hintMenu_lngIndexArr =
	{
		0x17d, 0x17f, 0x181, 0x183, 0x185, 0x189,
		0x19f, 0x187, 0x197, 0x199, 0x19b, 0x19d,
		0x1a7, 0x1a9, 0x1ab, 0x1ad, 0x1af, 0x1b1,
		0x1b3, 0x1b5, -1, 0
	},
	
	.eyePos =
	{
		0x6d, 0x84, 0x85
	},
	
	.lookAtPos =
	{
		-0x2E5, -0x12D, -0xF1
	}
	
	// the rest all initialize to zeros
};










// original ps1 with fragmented memory,
// but also only if NOT using RAMEX, because
// with RAMEX, we dont need to save 0x1b00 bytes
#if !defined(REBUILD_PS1) && !defined(USE_RAMEX)

// This awful idea stems from a stubbing system we had back
// in the first 2021 CTR rebuild attempts, which was supposed
// to pad functions to a certain size. Now we use it so our
// 0x1B00-byte buffer always comes before the Mods1() function
#define REP0(X)
#define REP1(X) X
#define REP2(X) REP1(X) X
#define REP3(X) REP2(X) X
#define REP4(X) REP3(X) X
#define REP5(X) REP4(X) X
#define REP6(X) REP5(X) X
#define REP7(X) REP6(X) X
#define REP8(X) REP7(X) X
#define REP9(X) REP8(X) X
#define REP10(X) REP9(X) X
#define REPA(X) REP10(X)
#define REPB(X) REPA(X) X
#define REPC(X) REPB(X) X
#define REPD(X) REPC(X) X
#define REPE(X) REPD(X) X
#define REPF(X) REPE(X) X
#define REP16(X) REPF(X) X

#define REP(thousands,hundreds,tens,ones,x) \
  REP##thousands(REP16(REP16(REP16(x)))) \
  REP##hundreds(REP16(REP16(x))) \
  REP##tens(REP16(x)) \
  REP##ones(x)

#define ONES_REP0(x)
#define ONES_REP4(x) NOP
#define ONES_REP8(x) NOP; NOP
#define ONES_REPC(x) NOP; NOP; NOP

#define ONES_REP(ones,x) \
  ONES_REP##ones(x)

#define NOP __asm__("nop");
#define NOP4 NOP; NOP; NOP; NOP

#define FILLER(thousands,hundreds,tens,ones) \
  REP(0,thousands,hundreds,tens,NOP4) \
  ONES_REP(ones,NOP)


void RelocMemory_DefragUI_Mods1()
{
	// 0x2320
	FILLER(1,B,0,0);
}

#endif