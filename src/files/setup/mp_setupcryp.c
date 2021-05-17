//
// G5 Building (MP)
//

#include "stagesetup.h"

s32 intro[];
u32 props[];
struct path paths[];
struct ailist ailists[];

struct stagesetup setup = {
	NULL,
	NULL,
	NULL,
	intro,
	props,
	paths,
	ailists,
	NULL,
};

u32 props[] = {
	weapon(0x0100, 0x0000, 0x00b2, OBJFLAG_00000001, 0, 0, 240)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00bc, OBJFLAG_00000001, 0, 0, 1000)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00bd, OBJFLAG_00000001, 0, 0, 1000)
	weapon(0x0100, 0x0000, 0x00b3, OBJFLAG_00000001, 0, 0, 241)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00be, OBJFLAG_00000001, 0, 0, 1000)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00bf, OBJFLAG_00000001, 0, 0, 1000)
	weapon(0x0100, 0x0000, 0x00b4, OBJFLAG_00000001, 0, 0, 242)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00c0, OBJFLAG_00000001, 0, 0, 1000)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00c1, OBJFLAG_00000001, 0, 0, 1000)
	weapon(0x0100, 0x0000, 0x00b5, OBJFLAG_00000001, 0, 0, 243)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00c2, OBJFLAG_00000001, 0, 0, 1000)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00c3, OBJFLAG_00000001, 0, 0, 1000)
	weapon(0x0100, 0x0000, 0x00b6, OBJFLAG_00000001, 0, 0, 244)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00c4, OBJFLAG_00000001, 0, 0, 1000)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00c5, OBJFLAG_00000001, 0, 0, 1000)
	weapon(0x0100, 0x0000, 0x00b7, OBJFLAG_00000001, 0, 0, 245)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00c6, OBJFLAG_00000001, 0, 0, 1000)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00c7, OBJFLAG_00000001, 0, 0, 1000)
	weapon(0x0100, 0x0000, 0x00b8, OBJFLAG_00000001, 0, 0, 246)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00c8, OBJFLAG_00000001, 0, 0, 1000)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00c9, OBJFLAG_00000001, 0, 0, 1000)
	weapon(0x0100, 0x0000, 0x00b9, OBJFLAG_00000001, 0, 0, 247)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00ca, OBJFLAG_00000001, 0, 0, 1000)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00cb, OBJFLAG_00000001, 0, 0, 1000)
	weapon(0x0100, 0x0000, 0x00ba, OBJFLAG_00000001, 0, 0, 248)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00cc, OBJFLAG_00000001, 0, 0, 1000)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00cd, OBJFLAG_00000001, 0, 0, 1000)
	weapon(0x0100, 0x0000, 0x00bb, OBJFLAG_00000001, 0, 0, 249)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00ce, OBJFLAG_00000001, 0, 0, 1000)
	ammocratemulti(0x00cc, MODEL_MULTI_AMMO_CRATE, 0x00cf, OBJFLAG_00000001, 0, 0, 1000)
	endprops
};

s32 intro[] = {
	spawn(0x009d)
	spawn(0x009e)
	spawn(0x009f)
	spawn(0x00a0)
	spawn(0x00a1)
	spawn(0x00a2)
	spawn(0x00a3)
	spawn(0x00a4)
	spawn(0x00a5)
	spawn(0x00a6)
	spawn(0x00a7)
	spawn(0x00a8)
	spawn(0x00a9)
	spawn(0x00aa)
	spawn(0x00ab)
	spawn(0x00ac)
	spawn(0x00ad)
	spawn(0x00ae)
	spawn(0x00af)
	spawn(0x00b0)
	spawn(0x00b1)
	case(0, 0x0087)
	case_respawn(0, 0x0081)
	case_respawn(0, 0x0082)
	case_respawn(0, 0x0083)
	case_respawn(0, 0x0084)
	case_respawn(0, 0x0085)
	case_respawn(0, 0x0086)
	case(1, 0x0088)
	case_respawn(1, 0x0089)
	case_respawn(1, 0x008a)
	case_respawn(1, 0x008b)
	case_respawn(1, 0x008c)
	case_respawn(1, 0x008d)
	case_respawn(1, 0x008e)
	case(2, 0x0095)
	case_respawn(2, 0x008f)
	case_respawn(2, 0x0090)
	case_respawn(2, 0x0091)
	case_respawn(2, 0x0092)
	case_respawn(2, 0x0093)
	case_respawn(2, 0x0094)
	case(3, 0x009c)
	case_respawn(3, 0x0096)
	case_respawn(3, 0x0097)
	case_respawn(3, 0x0098)
	case_respawn(3, 0x0099)
	case_respawn(3, 0x009a)
	case_respawn(3, 0x009b)
	hill(0x0033)
	hill(0x004d)
	hill(0x0056)
	hill(0x001a)
	hill(0x0066)
	endintro
};

struct path paths[] = {
	{ NULL, 0, 0 },
};

u8 func1001_13d4[] = {
	cmd01b2_mponly(11)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func1000_13e0[] = {
	mp_init_simulants
	rebuild_teams
	rebuild_squadrons
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

struct ailist ailists[] = {
	{ func1000_13e0, 0x1000 },
	{ func1001_13d4, 0x1001 },
	{ NULL, 0 },
};



