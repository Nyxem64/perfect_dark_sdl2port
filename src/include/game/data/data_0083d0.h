#ifndef IN_GAME_DATA_0083D0_H
#define IN_GAME_DATA_0083D0_H
#include <ultra64.h>
#include "types.h"

extern u32 var800623b0;
extern s32 g_WeatherEnabled;
extern u32 var80062400;
extern u32 var80062410;
extern u32 var80062414;
extern u32 var80062448;
extern u32 var80062450;
extern u32 var80062460;
extern u32 var8006246c;
extern u32 var80062478;
extern u32 var80062484;
extern u32 var80062488;
extern u32 var80062498;
extern s16 var800624a0;
extern s32 var800624a4;
extern u32 var800624a8;
extern u32 var800624ac;
extern u32 var800624b0;
extern s32 g_TitleMode;
extern s32 g_TitleNextMode;
extern u32 g_TitleDelayedTimer;
extern s32 g_TitleDelayedMode;
extern s32 g_TitleTimer;
extern u32 var800624e0;
extern s32 g_TitleNextStage;
extern u32 var800624e8;
extern u32 var800624ec;
extern u32 var800624f0;
extern u32 var800624f4;
extern struct model *g_TitleModel;
extern struct model *g_TitleModel2;
extern struct model *var80062508;
extern struct model *var8006250c;
extern u32 var80062530;
extern u32 var80062538;
extern u32 var80062560;
extern u32 var80062568;
extern u32 var80062578;
extern u32 var80062580;
extern u32 var80062590;
extern u32 var80062598;
extern u32 var800625a8;
extern u32 var800625f0;
extern u32 var800626ec;
extern s32 var80062730;
extern u32 var80062738;
extern u32 var80062744;
extern u32 var80062750;
extern u32 var8006275c;
extern u32 var80062768;
extern f32 var800627a8;
extern f32 var800627ac;
extern f32 var800627b0;
extern f32 var800627b4;
extern f32 var800627c4;
extern f32 var800627c8;
extern u32 var800627cc;
extern u32 var800627d4;
extern u32 var800627dc;
extern u32 var800627e0;
extern u32 var800627e8;
extern u32 var800627f0;
extern s32 var800627f8;
extern s32 var800627fc;
extern u32 var80062800;
extern f32 var80062808;
extern s32 var80062810;
extern f32 var80062814;
extern u32 var80062818;
extern u32 var80062858;
extern struct audiohandle *g_TitleAudioHandle;
extern u32 var80062868;
extern u32 var80062870;
extern u32 var8006287c;
extern u32 var800628bc;
extern u32 var800628c8;
extern u32 var800628d4;
extern u32 var80062914;
extern s32 g_NumPlayers;
extern u8 var80062940;
extern u8 var80062944;
extern u8 var80062948;
extern u8 var8006294c;
extern u32 var80062950;
extern bool g_WeatherTickEnabled;
extern void *var80062960;
extern u32 var80062964;
extern f32 var80062968;
extern u32 var8006296c;
extern u32 var80062970;
extern u32 var80062974;
extern u32 var80062978;
extern u32 var8006297c;
extern u32 var80062980;
extern s32 g_NextChrnum;
extern u32 var80062990;
extern u32 var80062998;
extern u32 var800629d8;
extern u32 var800629fc;
extern u32 var80062a3c;
extern u8 var80062a48[];
extern u32 var80062a4c;
extern struct var80062a8c *var80062a8c; // pointer to array
extern s32 var80062a90; // true if var80062a8c has anything in its array
extern u32 var80062a94;
extern u32 var80062aa0;
extern s32 g_NumBondBodies;
extern s32 g_NumMaleGuardHeads;
extern s32 g_NumFemaleGuardHeads;
extern s32 g_NumMaleGuardTeamHeads;
extern s32 g_NumFemaleGuardTeamHeads;
extern s32 var80062b14;
extern s32 var80062b18;
extern s32 g_BondBodies[];
extern s32 g_MaleGuardHeads[];
extern s32 g_MaleGuardTeamHeads[];
extern s32 g_FemaleGuardHeads[];
extern s32 g_FemaleGuardTeamHeads[];
extern s32 var80062c80;
extern s32 g_ActiveMaleHeadsIndex;
extern s32 g_ActiveFemaleHeadsIndex;
extern s32 g_FemGuardHeads[3];
extern f32 var80062ca0;
extern f32 var80062ca4;
extern f32 var80062ca8;
extern f32 var80062cac;
extern u32 var80062cb0;
extern u32 var80062cb4;
extern u32 var80062cb8;
extern s32 var80062cbc;
extern struct somedruggedracething *var800652b8[NUM_RACES];
extern u32 var800652bc;
extern u32 var800652c0;
extern u32 var800652c8;
extern u32 var800652cc;
extern u32 var80065548;
extern u32 var80065640;
extern u32 var80065680;
extern struct var80065750 *var80065ae0[][32];
extern struct var80065750 *var800662d8[][32];
extern u32 var800666c8;
extern u32 var80066a70;
extern u32 var80066ef0;
extern struct animfloats var80067428;
extern struct animfloats var80067470;
extern struct animfloats var800674b8;
extern struct animfloats var80067500;
extern struct animfloats var80067548;
extern struct animfloats var80067590;
extern struct animfloats var800675d8;
extern struct animfloats var80067620;
extern struct animfloats var80067668;
extern struct animfloats var800676b0;
extern struct animfloats var800676f8;
extern struct animfloats var80067740;
extern struct animfloats var80067788;
extern struct animfloats var800677d0;
extern struct animfloats var80067818;
extern struct animfloats var80067860;
extern struct animfloats var800678a8;
extern struct animfloats var800678f0;
extern struct animfloats var80067938;
extern struct animfloats var80067980[];
extern struct animfloats var80067bc0;
extern struct animfloats var80067c08[];
extern struct animfloats var80067d28[];
extern struct animfloats var80067d70[];
extern u32 var80067e50;
extern struct chrdata *g_BgChrs;
extern s16 *g_BgChrnums;
extern s32 g_NumBgChrs;
extern s16 *g_TeamList;
extern s16 *g_SquadronList;
extern struct var80067e6c *var80067fdc[5];
extern s16 var80067ff0[];
extern s16 *var80068008[5];
extern u32 var8006801c;
extern u32 var80068024;
extern u32 var8006802c;
extern u32 var80068034;
extern u32 var8006803c;
extern u32 var80068044;
extern u32 var8006804c;
extern u32 var80068054;
extern u32 var8006805c;
extern u32 var80068064;
extern u32 var8006806c;
extern u32 var80068074;
extern s32 g_DrCarollDyingTimer;
extern u8 var80068080;
extern u32 var80068084;
extern u32 var800680bc;
extern u32 var8006819c;
extern u32 var800681a8;
extern u32 var800681b0;
extern u32 var800681bc;
extern u32 var800681c4;
extern u32 var800681e0;
extern u32 var80068214;
extern u32 var80068228;
extern u32 var80068230;
extern u32 var8006823c;
extern u32 var80068268;
extern u32 var80068270;
extern u32 var8006827c;
extern u32 var80068288;
extern u32 var8006829c;
extern u32 var8006835c;

#endif
