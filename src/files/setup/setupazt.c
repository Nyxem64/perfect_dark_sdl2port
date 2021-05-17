//
// Crash Site
//

#include "stagesetup.h"

// Characters
#define CHR_ELVIS           0x00
#define CHR_TRENT           0x02
#define CHR_MRBLONDE        0x03
#define CHR_SKEDAR          0x04
#define CHR_PRESIDENT       0x05
#define CHR_PRESIDENT_OUTRO 0x06
#define CHR_PRES_CLONE      0x08
#define CHR_ROBOT1          0x26
#define CHR_ROBOT2          0x27
#define CHR_ROBOT3          0x28
#define CHR_ROBOT4          0x29
#define CHR_ELVIS_OUTRO     0x38

// Objects
#define OBJ_CRATE          0x00
#define OBJ_ESCAPEPOD      0x01
#define OBJ_MEDICALSCANNER 0x02
#define OBJ_SKEDAR_SHUTTLE 0x03
#define OBJ_PROXYMINE      0x08
#define OBJ_HOVERBIKE      0x09

// Stage flags
#define STAGEFLAG_BEACON_ACTIVATED          0x00000100
#define STAGEFLAG_ESCAPEPOD_DESTROYED       0x00000200
#define STAGEFLAG_SKEDAR_SHUTTLE_DESTROYED  0x00000400
#define STAGEFLAG_PRESIDENT_DEAD            0x00000800
#define STAGEFLAG_PRESIDENT_RESCUED         0x00001000
#define STAGEFLAG_CLONE_DEAD                0x00002000
#define STAGEFLAG_TRIGGER_PRESIDENT_RUNNING 0x00004000
#define STAGEFLAG_TRENT_RUNNING             0x00008000
#define STAGEFLAG_ELVIS_GAVE_PROXYMINE      0x00010000
#define STAGEFLAG_OUTRO_STARTED             0x00020000

// AI Lists
#define AILIST_OUTRO               0x0402
#define AILIST_INIT_ELVIS          0x0403
#define AILIST_ELVIS               0x0404
#define AILIST_INIT_STRIPES        0x0406
#define AILIST_INIT_BLONDE         0x0407
#define AILIST_SPAWNER             0x0414
#define AILIST_SPAWNED_GUARD       0x0416
#define AILIST_INIT_ROBOT          0x0417
#define AILIST_ROBOT               0x0418
#define AILIST_INIT_PRESIDENT      0x041b
#define AILIST_PRESIDENT_WAITING   0x041c
#define AILIST_PRESIDENT_RUNNING   0x041d
#define AILIST_TRENT_WAITING       0x041e
#define AILIST_TRENT_SHOOTING      0x041f
#define AILIST_TRENT_RUNNING       0x0420
#define AILIST_STARTING_AREA_GUARD 0x0421
#define AILIST_HIDE                0x0422

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
	briefing(BRIEFINGTYPE_LOCATION, L_AZT_001)
	briefing(BRIEFINGTYPE_TEXT_PA,  L_AZT_000)
	briefing(BRIEFINGTYPE_TEXT_SA,  L_AZT_002)
	briefing(BRIEFINGTYPE_TEXT_A,   L_AZT_003)

	beginobjective(0, L_AZT_005, (DIFFBIT_SA | DIFFBIT_PA | DIFFBIT_PD)) // "Retrieve Presidential medical scanner"
		require_object_collected(OBJ_MEDICALSCANNER)
	endobjective

	beginobjective(1, L_AZT_006, (DIFFBIT_A | DIFFBIT_SA | DIFFBIT_PA | DIFFBIT_PD)) // "Activate distress beacon"
		complete_flags(STAGEFLAG_BEACON_ACTIVATED)
		fail_flags(STAGEFLAG_ESCAPEPOD_DESTROYED)
	endobjective

	beginobjective(2, L_AZT_007, (DIFFBIT_PA | DIFFBIT_PD)) // "Shut down enemy jamming device"
		complete_flags(STAGEFLAG_SKEDAR_SHUTTLE_DESTROYED)
	endobjective

	beginobjective(3, L_AZT_008, (DIFFBIT_A | DIFFBIT_SA | DIFFBIT_PA | DIFFBIT_PD)) // "Retire Presidential clone"
		complete_flags(STAGEFLAG_CLONE_DEAD)
	endobjective

	beginobjective(4, L_AZT_009, (DIFFBIT_A | DIFFBIT_SA | DIFFBIT_PA | DIFFBIT_PD)) // "Locate and rescue President"
		complete_flags(STAGEFLAG_PRESIDENT_RESCUED)
		fail_flags(STAGEFLAG_PRESIDENT_DEAD)
	endobjective

	tag(0x09, 1)
	hoverbike(0x0100, MODEL_HOVBIKE, 0x0000, OBJFLAG_00000001 | OBJFLAG_00000100 | OBJFLAG_INVINCIBLE | OBJFLAG_UNCOLLECTABLE | OBJFLAG_01000000 | OBJFLAG_04000000, OBJFLAG2_00000100 | OBJFLAG2_00000200 | OBJFLAG2_00004000 | OBJFLAG2_00100000 | OBJFLAG2_00200000, OBJFLAG3_PUSHABLE | OBJFLAG3_GRABBABLE | OBJFLAG3_GEOTYPE3, 1000)
	chr(0x00010400, 0x00, 0x0106, BODY_THEKING, HEAD_ELVIS, AILIST_INIT_ELVIS, -1, -1, 1000, 200, 0x00002000, 0x00300000, TEAM_ALLY, SQUADRON_01, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRMAIANPISTOL, 0x0000, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_PHOENIX)
	chr(0x00010400, 0x38, 0x011f, BODY_THEKING, HEAD_ELVIS, AILIST_HIDE, -1, -1, 1000, 200, 0x00002000, 0x00300000, TEAM_NONCOMBAT, SQUADRON_01, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRMAIANPISTOL, 0x0038, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_PHOENIX)
	chr(0x00010400, 0x06, 0x0110, BODY_PRESIDENT, HEAD_PRESIDENT, AILIST_HIDE, -1, -1, 1000, 200, 0x00002000, 0x00300000, TEAM_NONCOMBAT, SQUADRON_01, -1, 0, 0x00000000)
	chr(0x00000400, 0x02, 0x010e, BODY_TRENT, HEAD_TRENT, AILIST_HIDE, -1, -1, 1000, 200, 0x80002000, 0x00300000, TEAM_NONCOMBAT, SQUADRON_08, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRDY357TRENT, 0x0002, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_DY357LX)
	chr(0x00000200, 0x09, 0x005a, BODY_STRIPES, HEAD_RANDOM, 0x0408, -1, -1, 100, 13, 0xc0082000, 0x00000000, TEAM_ENEMY, SQUADRON_01, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0009, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x0a, 0x0059, BODY_STRIPES, HEAD_RANDOM, 0x0408, -1, -1, 100, 13, 0xc0082000, 0x00000000, TEAM_ENEMY, SQUADRON_01, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x000a, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x0b, 0x0058, BODY_MRBLONDE, HEAD_MRBLONDE, 0x0408, -1, -1, 100, 13, 0xc0082000, 0x00000040, TEAM_ENEMY, SQUADRON_01, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRSNIPERRIFLE, 0x000b, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_SNIPERRIFLE)
	chr(0x00000200, 0x0c, 0x00d1, BODY_STRIPES, HEAD_RANDOM, 0x0409, -1, -1, 100, 13, 0xc0082000, 0x00000000, TEAM_ENEMY, SQUADRON_02, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x000c, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x0d, 0x00d4, BODY_STRIPES, HEAD_RANDOM, 0x0409, -1, -1, 100, 13, 0xc0082000, 0x00000000, TEAM_ENEMY, SQUADRON_02, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x000d, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x0e, 0x00d5, BODY_MRBLONDE, HEAD_MRBLONDE, 0x0409, -1, -1, 100, 13, 0xc0082000, 0x00000040, TEAM_ENEMY, SQUADRON_02, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRSNIPERRIFLE, 0x000e, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_SNIPERRIFLE)
	chr(0x00000200, 0x13, 0x004c, BODY_STRIPES, HEAD_RANDOM, 0x040a, -1, -1, 100, 13, 0xe0082000, 0x00000000, TEAM_ENEMY, SQUADRON_03, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0013, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x14, 0x005f, BODY_STRIPES, HEAD_RANDOM, 0x040b, -1, -1, 100, 13, 0xc0082000, 0x00000000, TEAM_ENEMY, SQUADRON_03, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0014, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x15, 0x004d, BODY_STRIPES, HEAD_RANDOM, 0x040c, -1, -1, 100, 13, 0xe0082000, 0x00000000, TEAM_ENEMY, SQUADRON_03, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0015, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x16, 0x0055, BODY_STRIPES, HEAD_RANDOM, 0x040d, -1, -1, 100, 13, 0xc0082000, 0x00000000, TEAM_ENEMY, SQUADRON_03, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0016, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x17, 0x0081, BODY_STRIPES, HEAD_RANDOM, AILIST_INIT_STRIPES, -1, -1, 100, 13, 0xe0082000, 0x00000000, TEAM_ENEMY, SQUADRON_04, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0017, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x18, 0x0079, BODY_STRIPES, HEAD_RANDOM, AILIST_INIT_STRIPES, -1, -1, 100, 13, 0xc0082000, 0x00000000, TEAM_ENEMY, SQUADRON_04, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0018, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x19, 0x007b, BODY_STRIPES, HEAD_RANDOM, AILIST_INIT_STRIPES, -1, -1, 100, 13, 0xe0082000, 0x00000000, TEAM_ENEMY, SQUADRON_04, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0019, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x1a, 0x007c, BODY_STRIPES, HEAD_RANDOM, AILIST_INIT_STRIPES, -1, -1, 100, 13, 0xc0082000, 0x00000000, TEAM_ENEMY, SQUADRON_04, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x001a, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x1b, 0x016b, BODY_STRIPES, HEAD_RANDOM, 0x040e, -1, -1, 100, 13, 0xe0082000, 0x00000000, TEAM_ENEMY, SQUADRON_05, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x001b, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x1c, 0x016c, BODY_STRIPES, HEAD_RANDOM, 0x040f, -1, -1, 100, 13, 0xc0082000, 0x00000000, TEAM_ENEMY, SQUADRON_05, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x001c, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x1d, 0x0048, BODY_STRIPES, HEAD_RANDOM, 0x0410, -1, -1, 100, 13, 0xe0082000, 0x00000000, TEAM_ENEMY, SQUADRON_06, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x001d, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x1e, 0x017e, BODY_STRIPES, HEAD_RANDOM, 0x0411, -1, -1, 100, 13, 0xc0082000, 0x00000000, TEAM_ENEMY, SQUADRON_06, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x001e, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x1f, 0x0177, BODY_STRIPES, HEAD_RANDOM, 0x0412, -1, -1, 100, 13, 0xe0082000, 0x00000000, TEAM_ENEMY, SQUADRON_07, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x001f, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x20, 0x0189, BODY_STRIPES, HEAD_RANDOM, 0x0413, -1, -1, 100, 13, 0xc0082000, 0x00000000, TEAM_ENEMY, SQUADRON_07, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0020, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000000, 0x26, 0x01bb, BODY_CHICROB, 0x00, AILIST_INIT_ROBOT, -1, -1, 1000, 50, 0x00080000, 0x00000000, TEAM_ENEMY, SQUADRON_08, -1, 0, 0x00000000)
	chr(0x00000000, 0x27, 0x01bc, BODY_CHICROB, 0x00, AILIST_INIT_ROBOT, -1, -1, 1000, 50, 0x00080000, 0x00000000, TEAM_ENEMY, SQUADRON_08, -1, 0, 0x00000000)
	chr(0x00000000, 0x28, 0x01bd, BODY_CHICROB, 0x00, AILIST_INIT_ROBOT, -1, -1, 1000, 50, 0x00080000, 0x00000000, TEAM_ENEMY, SQUADRON_08, -1, 0, 0x00000000)
	chr(0x00000000, 0x29, 0x01be, BODY_CHICROB, 0x00, AILIST_INIT_ROBOT, -1, -1, 1000, 50, 0x00080000, 0x00000000, TEAM_ENEMY, SQUADRON_08, -1, 0, 0x00000000)
	chr(0x00000400, 0x01, 0x01b5, BODY_TRENT, HEAD_TRENT, AILIST_TRENT_WAITING, -1, -1, 1000, 200, 0x80002000, 0x00300000, TEAM_ENEMY, SQUADRON_08, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRDY357TRENT, 0x0001, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_DY357LX)
	chr(0x00018400, 0x05, 0x01b6, BODY_PRESIDENT, HEAD_PRESIDENT, AILIST_INIT_PRESIDENT, -1, -1, 1000, 200, 0x00002000, 0x00300000, TEAM_ALLY, SQUADRON_01, -1, 0, 0x00000000)
	chr(0x00008400, 0x08, 0x0086, BODY_PRESIDENT_CLONE2, HEAD_PRESIDENT, 0x041a, -1, -1, 1000, 20, 0x00002000, 0x00300000, TEAM_ENEMY, SQUADRON_09, -1, 0, 0x02001400)
	chr(0x00000200, 0x2a, 0x0088, BODY_MRBLONDE, HEAD_MRBLONDE, AILIST_INIT_BLONDE, -1, -1, 1000, 100, 0x80004608, 0x00008080, TEAM_ENEMY, SQUADRON_09, -1, 0, 0x02001400)
	weapon(0x0100, MODEL_CHRAVENGER, 0x002a, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x2b, 0x0087, BODY_MRBLONDE, HEAD_MRBLONDE, AILIST_INIT_BLONDE, -1, -1, 1000, 100, 0x80004608, 0x00008080, TEAM_ENEMY, SQUADRON_09, -1, 0, 0x02001400)
	weapon(0x0100, MODEL_CHRAVENGER, 0x002b, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x2c, 0x0085, BODY_MRBLONDE, HEAD_MRBLONDE, AILIST_INIT_BLONDE, -1, -1, 1000, 100, 0x80004608, 0x00008080, TEAM_ENEMY, SQUADRON_09, -1, 0, 0x02001400)
	weapon(0x0100, MODEL_CHRAVENGER, 0x002c, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x2d, 0x019e, BODY_MRBLONDE, HEAD_MRBLONDE, AILIST_INIT_BLONDE, -1, -1, 1000, 100, 0x80004608, 0x00008080, TEAM_ENEMY, SQUADRON_0A, -1, 0, 0x02001400)
	weapon(0x0100, MODEL_CHRAVENGER, 0x002d, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x2e, 0x018e, BODY_MRBLONDE, HEAD_MRBLONDE, AILIST_INIT_BLONDE, -1, -1, 1000, 100, 0x80004608, 0x00008080, TEAM_ENEMY, SQUADRON_0A, -1, 0, 0x02001400)
	weapon(0x0100, MODEL_CHRAVENGER, 0x002e, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x2f, 0x01a7, BODY_MRBLONDE, HEAD_MRBLONDE, AILIST_INIT_BLONDE, -1, -1, 1000, 100, 0x80004608, 0x00008080, TEAM_ENEMY, SQUADRON_0A, -1, 0, 0x02001400)
	weapon(0x0100, MODEL_CHRAVENGER, 0x002f, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000000, 0x30, 0x002d, BODY_STRIPES, HEAD_RANDOM, AILIST_SPAWNER, -1, -1, 100, 13, 0xe0082000, 0x00000000, TEAM_ENEMY, SQUADRON_0B, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0030, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000000, 0x31, 0x0029, BODY_STRIPES, HEAD_RANDOM, AILIST_SPAWNER, -1, -1, 100, 13, 0xe0082000, 0x00000000, TEAM_ENEMY, SQUADRON_0B, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0031, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x32, 0x009a, BODY_STRIPES, HEAD_RANDOM, AILIST_STARTING_AREA_GUARD, -1, -1, 100, 13, 0xc0082000, 0x10000000, TEAM_ENEMY, SQUADRON_0C, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0032, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x33, 0x009b, BODY_STRIPES, HEAD_RANDOM, AILIST_STARTING_AREA_GUARD, -1, -1, 100, 13, 0xc0082000, 0x10000000, TEAM_ENEMY, SQUADRON_0C, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0033, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x34, 0x01b7, BODY_MRBLONDE, HEAD_MRBLONDE, AILIST_STARTING_AREA_GUARD, -1, -1, 100, 13, 0xc0082000, 0x10000000, TEAM_ENEMY, SQUADRON_0C, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRSNIPERRIFLE, 0x0034, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_SNIPERRIFLE)
	chr(0x00000200, 0x35, 0x0004, BODY_STRIPES, HEAD_RANDOM, AILIST_STARTING_AREA_GUARD, -1, -1, 100, 13, 0x80082000, 0x10000000, TEAM_ENEMY, SQUADRON_0D, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0035, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x36, 0x01b9, BODY_STRIPES, HEAD_RANDOM, AILIST_STARTING_AREA_GUARD, -1, -1, 100, 13, 0x80082101, 0x10000000, TEAM_ENEMY, SQUADRON_0D, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRAVENGER, 0x0036, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_K7AVENGER)
	chr(0x00000200, 0x37, 0x0012, BODY_MRBLONDE, HEAD_MRBLONDE, AILIST_STARTING_AREA_GUARD, -1, -1, 100, 13, 0x80082000, 0x10000000, TEAM_ENEMY, SQUADRON_0D, -1, 0, 0x00000000)
	weapon(0x0100, MODEL_CHRSNIPERRIFLE, 0x0037, OBJFLAG_ASSIGNEDTOCHR, 0, 0, WEAPON_SNIPERRIFLE)
	chr(0x00000000, 0x03, 0x0121, BODY_MRBLONDE, HEAD_MRBLONDE, AILIST_HIDE, -1, -1, 1000, 200, 0x00002000, 0x00300000, TEAM_ENEMY, SQUADRON_01, -1, 0, 0x00000000)
	chr(0x00004000, 0x04, 0x012f, BODY_SKEDAR, 0x00, AILIST_HIDE, -1, -1, 1000, 200, 0x00002000, 0x00300000, TEAM_ENEMY, SQUADRON_01, -1, 0, 0x00000000)
	tag(0x00, 1)
	stdobject(0x0100, MODEL_A51_CRATE1, 0xffff, OBJFLAG_00000001 | OBJFLAG_00000100 | OBJFLAG_ILLUMINATED | OBJFLAG_00001000 | OBJFLAG_INVINCIBLE, 0, 0, 1000)
	tag(0x01, 1)
	stdobject(0x0100, MODEL_PRESCAPSULE, 0x01d8, OBJFLAG_00000001 | OBJFLAG_00000020 | OBJFLAG_00000040 | OBJFLAG_00000080 | OBJFLAG_00000100, OBJFLAG2_00000001 | OBJFLAG2_00000100, OBJFLAG3_00010000, 12000)
	tag(0x03, 1)
	stdobject(0x0100, MODEL_SK_SHUTTLE, 0xffff, OBJFLAG_00000001 | OBJFLAG_00000020 | OBJFLAG_00000040 | OBJFLAG_00000080 | OBJFLAG_00000100, OBJFLAG2_00000100 | OBJFLAG2_00002000, 0, 12500)
	tag(0x02, 1)
	weapon(0x0180, MODEL_CHRBRIEFCASE, 0x000c, OBJFLAG_00000001, OBJFLAG2_00000001, OBJFLAG3_00400000, WEAPON_PRESIDENTSCANNER)
	autogun(0x0100, MODEL_GROUNDGUN, 0x0043, OBJFLAG_00000001, 0, 0, 4000, 0x003d, 0x00020000, 0xfffe0000, 0x0000016c, 0x001e0000)
	autogun(0x0100, MODEL_GROUNDGUN, 0x003b, OBJFLAG_00000001, 0, 0, 4000, 0x0038, 0x00020000, 0xfffe0000, 0x0000016c, 0x001e0000)
	tag(0x06, 1)
	shield(0x0100, MODEL_CHRSHIELD, 0x0106, OBJFLAG_00000001, OBJFLAG2_EXCLUDE_SA | OBJFLAG2_EXCLUDE_PA | OBJFLAG2_EXCLUDE_PD, 0, 1000)
	tag(0x07, 1)
	shield(0x0100, MODEL_CHRSHIELD, 0x0090, OBJFLAG_00000001, OBJFLAG2_EXCLUDE_PA | OBJFLAG2_EXCLUDE_PD, 0, 1000)
	tag(0x08, 1)
	weapon(0x0100, MODEL_MULTI_AMMO_CRATE, 0x0106, OBJFLAG_00000001 | OBJFLAG_INVINCIBLE | OBJFLAG_UNCOLLECTABLE, OBJFLAG2_00000001 | OBJFLAG2_INVISIBLE, 0, WEAPON_PROXIMITYMINE)
	pad_effect(PADEFFECT_SPARKS, 0x000001db)
	pad_effect(PADEFFECT_SMOKE, 0x000001dc)
	pad_effect(PADEFFECT_SPARKS, 0x000001dd)
	pad_effect(PADEFFECT_SPARKS, 0x000001de)
	endprops
};

s32 intro[] = {
	outfit(OUTFIT_SNOW)
	intro_weapon(WEAPON_FALCON2_SCOPE, -1)
	ammo(AMMOTYPE_PISTOL, 50)
	ammo(AMMOTYPE_RIFLE, 100)
	intro_weapon(WEAPON_REMOTEMINE, -1)
	ammo(AMMOTYPE_REMOTE_MINE, 3)
	intro_weapon(WEAPON_NIGHTVISION, -1)
	intro_weapon(WEAPON_HORIZONSCANNER, -1)
	spawn(0x00b8)
	endintro
};

s32 path00[] = {
	0x0059,
	0x0096,
	0x0095,
	0x0094,
	0x00be,
	0x00bd,
	0x009e,
	-1,
};

s32 path01[] = {
	0x00d1,
	0x00d2,
	0x00d3,
	0x00b1,
	0x00cd,
	0x00a6,
	0x00b3,
	0x00c3,
	-1,
};

s32 path02[] = {
	0x004c,
	0x0057,
	0x005e,
	0x005d,
	0x005b,
	0x005f,
	-1,
};

s32 path03[] = {
	0x005f,
	0x005b,
	0x005c,
	0x005d,
	0x0066,
	0x005d,
	0x005c,
	0x005b,
	-1,
};

s32 path04[] = {
	0x004d,
	0x0051,
	0x0050,
	0x0053,
	0x0054,
	0x0056,
	0x006e,
	-1,
};

s32 path05[] = {
	0x0055,
	0x0052,
	0x0054,
	0x0056,
	0x006e,
	-1,
};

s32 path06[] = {
	0x0030,
	0x002f,
	0x0167,
	0x0166,
	0x0165,
	0x0164,
	0x016a,
	0x0169,
	0x016b,
	-1,
};

s32 path07[] = {
	0x016c,
	0x016d,
	0x016e,
	0x016f,
	0x0170,
	0x0171,
	0x0172,
	0x0173,
	-1,
};

s32 path08[] = {
	0x0048,
	0x0049,
	0x004a,
	0x0182,
	0x0183,
	0x0180,
	0x0181,
	-1,
};

s32 path09[] = {
	0x017e,
	0x017f,
	0x017b,
	0x017c,
	0x017d,
	0x0034,
	-1,
};

s32 path10[] = {
	0x0177,
	0x0175,
	0x0176,
	0x0189,
	-1,
};

s32 path11[] = {
	0x0189,
	0x0188,
	0x0187,
	0x0186,
	0x0185,
	0x0184,
	-1,
};

s32 path12[] = {
	0x0106,
	0x0107,
	0x00f6,
	0x0104,
	-1,
};

struct path paths[] = {
	{ path00, 0, 0 },
	{ path01, 1, 0 },
	{ path02, 2, 0 },
	{ path03, 3, 0 },
	{ path04, 4, 0 },
	{ path05, 5, 0 },
	{ path06, 6, 0 },
	{ path07, 7, 0 },
	{ path08, 8, 0 },
	{ path09, 9, 0 },
	{ path10, 10, 0 },
	{ path11, 11, 0 },
	{ path12, 12, 0 },
	{ NULL, 0, 0 },
};

u8 func1001_objectives_failed_msg[] = {
	yield
	set_chr_chrflag(CHR_PRES_CLONE, CHRCFLAG_KEEPCORPSEKO)
	set_chr_chrflag(CHR_ELVIS, CHRCFLAG_KEEPCORPSEKO)
	set_chr_chrflag(CHR_PRESIDENT, CHRCFLAG_KEEPCORPSEKO)
	set_ailist(CHR_SELF, GAILIST_SHOW_OBJ_FAILED_MSG)
	endlist
};

u8 func1400_setup_counterop[] = {
	yield
	set_chr_team(CHR_ANTI, TEAM_ENEMY)
	set_ailist(CHR_SELF, GAILIST_REBUILD_GROUPS)
	endlist
};

u8 func1011_setup_snow[] = {
	enable_snow(TRUE)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func1002_intro[] = {
	set_chr_chrflag(CHR_COOP, CHRCFLAG_HIDDEN)
	set_chr_chrflag(CHR_ANTI, CHRCFLAG_HIDDEN)
	play_cutscene_track(MUSIC_CRASHSITE_INTRO)
	camera_movement(0x01b5)
	cmd0175(60)

	set_chr_chrflag(CHR_BOND, CHRCFLAG_UNPLAYABLE)
	set_chr_hiddenflag(CHR_BOND, CHRHFLAG_00020000)
	chr_do_animation(0x01b6, -1, -1, 0x06, 0x00, CHR_BOND, 4)
	set_chr_hudpiece_visible(CHR_BOND, TRUE)

	restart_timer
	fade_to_color(0x000000ff, 0)
	fade_to_color(0x00000000, 300)
	set_cutscene_weapon(CHR_BOND, WEAPON_NONE, WEAPON_NONE)
	yield
	set_cutscene_weapon(CHR_BOND, WEAPON_NONE, WEAPON_NONE)

	#define wait_until(time, loopid) \
		beginloop(loopid) \
			if_controller_button_pressed(/*goto*/ 0x65) \
			if_timer_gt(time, /*goto*/ 0x08) \
		endloop(loopid) \
		label(0x08)



	wait_until(724, 0x69)
	speak(CHR_BOND, L_AZT_032, MP3_0759, CHANNEL_10, COLOR_09_BLUE) // "Ahhh... uuhhhh..."

	wait_until(830, 0x6a)
	speak(CHR_BOND, L_AZT_034, MP3_0457, CHANNEL_10, COLOR_06_WHITE) // "Agent Dark! Please report!"

	wait_until(980, 0x6b)
	speak(CHR_BOND, L_AZT_033, MP3_075A, CHANNEL_10, COLOR_09_BLUE) // "Ahhh... uhh... owww..."

	wait_until(1030, 0x6c)
	speak(CHR_BOND, L_AZT_035, MP3_0458, CHANNEL_10, COLOR_06_WHITE) // "Perfect Dark, come in!"

	wait_until(1152, 0x6e)
	speak(CHR_BOND, L_AZT_036, MP3_0459, CHANNEL_10, COLOR_09_BLUE) // "A-agent Dark reporting in..."

	wait_until(1372, 0x6f)
	speak(CHR_BOND, L_AZT_037, MP3_045A, CHANNEL_10, COLOR_06_WHITE) // "Agent Dark! Please reply!"

	wait_until(1610, 0x6d)
	speak(CHR_BOND, L_AZT_038, MP3_045B, CHANNEL_10, COLOR_09_BLUE) // "Something's jamming my transmissions... It's comin..."

	wait_until(1875, 0x70)
	speak(CHR_BOND, -1, SFX_FOOTSTEP_8189, CHANNEL_10, COLOR_00_GREEN)

	wait_until(1900, 0x71)
	speak(CHR_BOND, -1, SFX_FOOTSTEP_818A, CHANNEL_10, COLOR_00_GREEN)

	wait_until(1926, 0x72)
	speak(CHR_BOND, -1, SFX_FOOTSTEP_8188, CHANNEL_7, COLOR_00_GREEN)

	wait_until(1958, 0x73)
	speak(CHR_BOND, -1, SFX_FOOTSTEP_8189, CHANNEL_10, COLOR_00_GREEN)

	wait_until(2000, 0x74)
	speak(CHR_BOND, L_AZT_039, MP3_045C, CHANNEL_10, COLOR_09_BLUE) // "I'd better find the jamming device and check that ..."

	wait_until(2116, 0x75)
	speak(CHR_BOND, -1, SFX_FOOTSTEP_8188, CHANNEL_7, COLOR_00_GREEN)

	wait_until(2168, 0x76)
	speak(CHR_BOND, -1, SFX_FOOTSTEP_8187, CHANNEL_6, COLOR_00_GREEN)

	wait_until(2224, 0x78)
	set_cutscene_weapon(CHR_BOND, WEAPON_NONE, WEAPON_NONE)
	yield
	set_cutscene_weapon(CHR_BOND, WEAPON_FALCON2_SCOPE, WEAPON_NONE)

	wait_until(2305, 0x79)
	speak(CHR_BOND, -1, SFX_01DB, CHANNEL_5, COLOR_00_GREEN)

	wait_until(2392, 0x7a)
	speak(CHR_BOND, -1, SFX_FOOTSTEP_8189, CHANNEL_7, COLOR_00_GREEN)

	wait_until(2412, 0x7b)
	speak(CHR_BOND, -1, SFX_FOOTSTEP_8187, CHANNEL_6, COLOR_00_GREEN)

	wait_until(2460, 0x7c)
	speak(CHR_BOND, -1, SFX_FOOTSTEP_8188, CHANNEL_7, COLOR_00_GREEN)

	wait_until(2513, 0x7d)
	speak(CHR_BOND, -1, SFX_FOOTSTEP_8189, CHANNEL_6, COLOR_00_GREEN)

	wait_until(2685, 0x7e)
	speak(CHR_BOND, -1, SFX_FOOTSTEP_818A, CHANNEL_7, COLOR_00_GREEN)

	beginloop(0x0a)
		if_camera_animating(/*goto*/ 0x31)
		goto_next(0x65)

		label(0x31)
		if_controller_button_pressed(/*goto*/ 0x65)
		label(0x31)
	endloop(0x0a)

	label(0x65)
	set_cutscene_weapon(CHR_BOND, WEAPON_NONE, WEAPON_NONE)
	yield
	set_cutscene_weapon(CHR_BOND, WEAPON_FALCON2_SCOPE, WEAPON_NONE)
	mute_channel(CHANNEL_7)
	mute_channel(CHANNEL_6)
	mute_channel(CHANNEL_5)
	mute_channel(CHANNEL_10)
	unset_chr_chrflag(CHR_COOP, CHRCFLAG_HIDDEN)
	unset_chr_chrflag(CHR_ANTI, CHRCFLAG_HIDDEN)
	unset_chr_chrflag(CHR_BOND, CHRCFLAG_UNPLAYABLE)
	set_chr_hiddenflag(CHR_BOND, CHRHFLAG_00020000)
	chr_do_animation(0x01b6, -2, -1, 0x06, 0x00, CHR_BOND, 2)
	stop_cutscene_track
	stop_ambient_track
	set_chr_hudpiece_visible(CHR_BOND, FALSE)
	enter_firstperson
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func0402_outro_from_menu[] = {
	set_ailist(0x06, GAILIST_IDLE)
	set_ailist(0x03, GAILIST_IDLE)
	set_ailist(CHR_SKEDAR, GAILIST_IDLE)
	set_ailist(CHR_ELVIS_OUTRO, GAILIST_IDLE)
#if VERSION >= VERSION_NTSC_FINAL
	set_ailist(CHR_TRENT, GAILIST_IDLE)
#endif
	hide_chr(CHR_ROBOT1)
	hide_chr(CHR_ROBOT2)
	hide_chr(CHR_ROBOT3)
	hide_chr(CHR_ROBOT4)
	set_ailist(CHR_SELF, AILIST_OUTRO)
	endlist
};

u8 func0402_outro[] = {
	set_stage_flag(STAGEFLAG_OUTRO_STARTED)
	hide_object(OBJ_HOVERBIKE)
	set_ailist(CHR_PRESIDENT, GAILIST_IDLE)
	if_chr_death_animation_finished(CHR_BOND, /*goto*/ 0x31)
	set_target_chr(CHR_BOND)
	goto_next(0x08)
	label(0x31)
	set_target_chr(CHR_COOP)
	label(0x08)
	camera_movement(0x01d9)
	play_cutscene_track(MUSIC_CRASHSITE_OUTRO)
	set_chr_chrflag(CHR_ANTI, CHRCFLAG_HIDDEN)
	set_chr_chrflag(0xf1, CHRCFLAG_HIDDEN)
	set_chr_chrflag(CHR_P1P2, CHRCFLAG_HIDDEN)
	unset_chr_chrflag(CHR_TARGET, CHRCFLAG_HIDDEN)
	set_ailist(CHR_TARGET, GAILIST_IDLE)

	remove_chr(CHR_ELVIS)
	set_ailist(CHR_ELVIS, GAILIST_IDLE)

	set_chr_chrflag(CHR_PRESIDENT, CHRCFLAG_HIDDEN)
	set_chr_chrflag(CHR_PRESIDENT, CHRCFLAG_INVINCIBLE)
	set_ailist(CHR_PRESIDENT, GAILIST_IDLE)

	set_chr_chrflag(CHR_TARGET, CHRCFLAG_UNPLAYABLE)
	unset_chr_chrflag(CHR_TARGET, CHRCFLAG_HIDDEN)
	set_chr_hiddenflag(CHR_TARGET, CHRHFLAG_00020000)
	chr_do_animation(0x01df, -1, -1, 0x06, 0x00, CHR_TARGET, 4)

	set_chr_chrflag(CHR_SKEDAR, CHRCFLAG_UNPLAYABLE)
	unset_chr_chrflag(CHR_SKEDAR, CHRCFLAG_HIDDEN)
	set_chr_hiddenflag(CHR_SKEDAR, CHRHFLAG_00020000)
	chr_do_animation(0x01da, -1, -1, 0x06, 0x00, CHR_SKEDAR, 4)

	set_chr_chrflag(CHR_ELVIS_OUTRO, CHRCFLAG_INVINCIBLE)
	set_chr_chrflag(CHR_ELVIS_OUTRO, CHRCFLAG_UNPLAYABLE)
	unset_chr_chrflag(CHR_ELVIS_OUTRO, CHRCFLAG_HIDDEN)
	set_chr_hiddenflag(CHR_ELVIS_OUTRO, CHRHFLAG_00020000)
	chr_do_animation(0x01db, -1, -1, 0x06, 0x00, CHR_ELVIS_OUTRO, 4)

	set_chr_chrflag(CHR_TRENT, CHRCFLAG_INVINCIBLE)
	set_chr_chrflag(CHR_TRENT, CHRCFLAG_UNPLAYABLE)
	unset_chr_chrflag(CHR_TRENT, CHRCFLAG_HIDDEN)
	set_chr_hiddenflag(CHR_TRENT, CHRHFLAG_00020000)
	chr_do_animation(0x01dc, -1, -1, 0x06, 0x00, CHR_TRENT, 4)

	set_chr_chrflag(CHR_MRBLONDE, CHRCFLAG_INVINCIBLE)
	set_chr_chrflag(CHR_MRBLONDE, CHRCFLAG_UNPLAYABLE)
	unset_chr_chrflag(CHR_MRBLONDE, CHRCFLAG_HIDDEN)
	set_chr_hiddenflag(CHR_MRBLONDE, CHRHFLAG_00020000)
	chr_do_animation(0x01dd, -1, -1, 0x06, 0x00, CHR_MRBLONDE, 4)

	set_chr_chrflag(CHR_PRESIDENT_OUTRO, CHRCFLAG_INVINCIBLE)
	set_chr_chrflag(CHR_PRESIDENT_OUTRO, CHRCFLAG_UNPLAYABLE)
	unset_chr_chrflag(CHR_PRESIDENT_OUTRO, CHRCFLAG_HIDDEN)
	set_chr_hiddenflag(CHR_PRESIDENT_OUTRO, CHRHFLAG_00020000)
	chr_do_animation(0x01de, -1, -1, 0x06, 0x00, CHR_PRESIDENT_OUTRO, 4)

	show_object(0x00)
	set_object_flag2(OBJ_CRATE, OBJFLAG2_04000000)
	set_object_flag3(OBJ_CRATE, OBJFLAG3_00000010)
	object_do_animation(0x01e0, OBJ_CRATE, 0x04, 0xffff)
	restart_timer
	set_cutscene_weapon(CHR_TARGET, WEAPON_NONE, WEAPON_NONE)
	yield
	set_cutscene_weapon(CHR_TARGET, WEAPON_NONE, WEAPON_NONE)
	set_cutscene_weapon(CHR_ELVIS_OUTRO, WEAPON_NONE, WEAPON_NONE)
	yield
	set_cutscene_weapon(CHR_ELVIS_OUTRO, WEAPON_HAMMER, WEAPON_NONE)
	show_nonessential_chrs(FALSE)

	wait_until(146, 0x69)
	play_sound(SFX_0594, CHANNEL_7)

	wait_until(200, 0x6a)
	play_sound(SFX_0595, CHANNEL_6)

	wait_until(248, 0x6b)
	speak(CHR_BOND, L_AZT_040, MP3_045D, CHANNEL_10, COLOR_09_BLUE) // "How are you feeling, Mr. President?"

	wait_until(414, 0x6c)
	speak(CHR_BOND, L_AZT_041, MP3_045E, CHANNEL_10, COLOR_08_RED) // "Better now, young lady. Today, I think, will take ..."

	wait_until(490, 0x6e)
	play_sound(SFX_0596, CHANNEL_5)

	wait_until(526, 0x6f)
	play_sound(SFX_0597, CHANNEL_7)

	wait_until(578, 0x6d)
	play_sound(SFX_0427, CHANNEL_6)

	wait_until(1078, 0x71)
	play_sound(SFX_0596, CHANNEL_5)

	wait_until(1116, 0x72)
	play_sound(SFX_0597, CHANNEL_7)

	wait_until(1200, 0x70)
	speak(CHR_BOND, L_AZT_042, MP3_045F, CHANNEL_10, COLOR_09_BLUE) // "Just one thing, sir? What is the Pelagic II that T..."

	wait_until(1474, 0x74)
	play_sound(SFX_ELVIS_HEHE, CHANNEL_5)
	play_sound(SFX_00F8, CHANNEL_10)

	wait_until(1490, 0x75)
	play_sound(SFX_0596, CHANNEL_7)

	wait_until(1492, 0x76)
	play_sound(SFX_0594, CHANNEL_6)

	wait_until(1556, 0x77)
	play_sound(SFX_00F8, CHANNEL_10)

	wait_until(1626, 0x73)
	speak(CHR_BOND, L_AZT_043, MP3_0460, CHANNEL_10, COLOR_08_RED) // "It's a U.S. government deep sea research vessel, o..."

	wait_until(1807, 0x79)
	play_sound(SFX_0595, CHANNEL_7)

	wait_until(1850, 0x7a)
	play_sound(SFX_0597, CHANNEL_6)

	wait_until(1872, 0x7c)
	play_sound(SFX_0595, CHANNEL_7)

	wait_until(2074, 0x7d)
	play_sound(SFX_0594, CHANNEL_6)

	wait_until(2270, 0x7e)
	play_sound(SFX_0596, CHANNEL_5)

	wait_until(2286, 0x7f)
	play_sound(SFX_FOOTSTEP_818A, CHANNEL_7)

	wait_until(2296, 0x80)
	play_sound(SFX_FOOTSTEP_8189, CHANNEL_6)

	wait_until(2316, 0x81)
	play_sound(SFX_FOOTSTEP_8187, CHANNEL_5)

	wait_until(2335, 0x82)
	play_sound(SFX_FOOTSTEP_8188, CHANNEL_7)

	wait_until(2450, 0x7b)
	speak(CHR_BOND, L_AZT_044, MP3_0461, CHANNEL_10, COLOR_09_BLUE) // "Trent has a lot to answer for, but I don't think w..."

	wait_until(3150, 0x83)
	speak(CHR_BOND, L_AZT_045, MP3_0462, CHANNEL_10, COLOR_03_RED) // "You have failed, Easton. You are a flawed device, ..."

	wait_until(3380, 0x88)
	play_sound(SFX_FOOTSTEP_818A, CHANNEL_7)

	wait_until(3580, 0x87)
	speak(CHR_BOND, L_AZT_046, MP3_0463, CHANNEL_10, COLOR_05_GREEN) // "Just try it, you Scandinavian freak!"

	wait_until(3747, 0x84)
	play_sound(SFX_FOOTSTEP_8189, CHANNEL_5)

	wait_until(3875, 0x85)
	play_sound(SFX_FOOTSTEP_8188, CHANNEL_7)

	wait_until(4054, 0x86)
	play_sound(SFX_05A0, CHANNEL_5)
	play_sound(SFX_CLOAK_OFF, CHANNEL_10)
	set_chr_hiddenflag(CHR_MRBLONDE, CHRHFLAG_CLOAKED)
	set_chr_hiddenflag(CHR_SKEDAR, CHRHFLAG_CLOAKED)

	wait_until(4100, 0x95)
	unset_chr_hiddenflag(CHR_SKEDAR, CHRHFLAG_CLOAKED)
	play_sound(SFX_SKEDAR_ROAR_052A, CHANNEL_10)

	wait_until(4200, 0x78)
	speak(CHR_BOND, L_AZT_047, MP3_0464, CHANNEL_10, COLOR_05_GREEN) // "Noooooooo!!!"

	wait_until(4240, 0x93)
	play_sound(SFX_05C0, CHANNEL_10)

	wait_until(4296, 0x89)
	play_sound(SFX_007D, CHANNEL_6)

	wait_until(4444, 0x8a)
	play_sound(SFX_05A0, CHANNEL_5)
	play_sound(SFX_SKEDAR_ROAR_0530, CHANNEL_10)

	wait_until(4506, 0x8b)
	play_sound(SFX_05A1, CHANNEL_7)

	wait_until(4544, 0x96)
	set_chr_hiddenflag(CHR_SKEDAR, CHRHFLAG_CLOAKED)

	wait_until(4566, 0x8c)
	play_sound(SFX_CLOAK_ON, CHANNEL_10)
	unset_chr_hiddenflag(CHR_MRBLONDE, CHRHFLAG_CLOAKED)

	wait_until(4576, 0x8d)

	wait_until(4622, 0x8e)
	play_sound(SFX_FOOTSTEP_8187, CHANNEL_7)

	wait_until(4678, 0x8f)
	play_sound(SFX_FOOTSTEP_8188, CHANNEL_7)

	wait_until(4752, 0x90)
	play_sound(SFX_FOOTSTEP_8189, CHANNEL_7)

	beginloop(0x0a)
		if_camera_animating(/*goto*/ 0x31)
		goto_next(0x65)

		label(0x31)
		if_controller_button_pressed(/*goto*/ 0x65)
		label(0x31)
	endloop(0x0a)

	label(0x65)
	end_level
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func0407_init_blonde[] = {
	set_accuracy(20)
	set_reaction_speed(55)
	set_chr_maxdamage(CHR_SELF, 40)
	add_health_or_armor(60)
	set_recovery_speed(0)
	set_shield(0)
	set_ailist(CHR_SELF, GAILIST_UNALERTED)
	endlist
};

u8 func0406_init_stripes[] = {
	set_chr_dodge_rating(2, 0x0a)
	set_accuracy(16)
	set_reaction_speed(55)
	set_chr_maxdamage(CHR_SELF, 60)
	add_health_or_armor(0)
	set_recovery_speed(30)
	set_shield(0)
	set_ailist(CHR_SELF, GAILIST_UNALERTED)
	endlist
};

u8 func1003_msg_therestheescapepod[] = {
	beginloop(0x06)
		chr_toggle_p1p2(CHR_SELF)
		if_chr_distance_to_pad_lt(CHR_P1P2, 1000, 0x01d8, /*goto*/ 0x31)
	endloop(0x06)

	label(0x31)
	speak(CHR_P1P2, L_AZT_010, MP3_03CC, CHANNEL_6, COLOR_09_BLUE) // "There's the escape pod."
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func1004_msg_maybetheresabeacon[] = {
	restart_timer
	beginloop(0x06)
	endloop(0x06)

	// Unreachable
	label(0x31)
	speak(CHR_BOND, L_AZT_011, MP3_03CD, CHANNEL_6, COLOR_09_BLUE) // "Maybe there's a beacon in there."
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func1005_msg_thejamming[] = {
	if_difficulty_lt(DIFF_PA, /*goto*/ 0x0f)

	beginloop(0x06)
		chr_toggle_p1p2(CHR_SELF)
		if_objective_complete(2, /*goto*/ 0x0f)
		if_chr_in_room(CHR_P1P2, 0x00, 0x0029, /*goto*/ 0x31)
	endloop(0x06)

	label(0x31)
	speak(CHR_P1P2, L_AZT_012, MP3_03CE, CHANNEL_6, COLOR_09_BLUE) // "The jamming... It's coming from that ship."
	label(0x0f)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func1006_msg_elvisbeable[] = {
	beginloop(0x06)
		chr_toggle_p1p2(CHR_SELF)
		if_chr_distance_to_pad_lt(CHR_P1P2, 1000, 0x0105, /*goto*/ 0x31)
	endloop(0x06)

	label(0x31)
	speak(CHR_P1P2, L_AZT_013, MP3_03CF, CHANNEL_6, COLOR_09_BLUE) // "Elvis... He'll be able to protect the President."
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

#define init_path(pathid, function) \
	set_chr_dodge_rating(2, 0x0a) \
	set_accuracy(16) \
	set_reaction_speed(55) \
	set_chr_maxdamage(CHR_SELF, 60) \
	add_health_or_armor(0) \
	set_recovery_speed(30) \
	set_shield(0) \
	set_returnlist(CHR_SELF, function) \
	assign_path(pathid) \
	start_path \
	set_ailist(CHR_SELF, GAILIST_UNALERTED_0004)



u8 func0408_start_path00[] = {
	init_path(0, 0x0408)
	endlist
};

u8 func0409_start_path01[] = {
	init_path(1, 0x0409)
	endlist
};

u8 func040a_start_path02[] = {
	init_path(2, 0x040a)
	endlist
};

u8 func040b_start_path03[] = {
	init_path(3, 0x040b)
	endlist
};

u8 func040c_start_path04[] = {
	init_path(4, 0x040c)
	endlist
};

u8 func040d_start_path05[] = {
	init_path(5, 0x040d)
	endlist
};

u8 func040e_start_path06[] = {
	init_path(6, 0x040e)
	endlist
};

u8 func040f_start_path07[] = {
	init_path(7, 0x040f)
	endlist
};

u8 func0410_start_path08[] = {
	init_path(8, 0x0410)
	endlist
};

u8 func0411_start_path09[] = {
	init_path(9, 0x0411)
	endlist
};

u8 func0412_start_path10[] = {
	init_path(10, 0x0412)
	endlist
};

u8 func0413_start_path11[] = {
	init_path(11, 0x0413)
	endlist
};

/**
 * This function is unfinished. Target labels don't exist.
 *
 * Looks like it was intended to be a spawning function.
 */
u8 unregistered_function1[] = {
	label(0x66)
	restart_timer

	beginloop(0x67)
		dprint 'T','I','M','E','\n',0,
		if_timer_lt(1800, /*goto*/ 0x98)
		label(0x31)
		dprint 'S','Q','U','A','D','\n',0,
		if_num_chrs_in_squadron_gt(1, 0x0f, /*goto*/ 0x98)
		call_rng
		if_rand_gt(64, /*goto*/ 0x69)
		if_rand_gt(128, /*goto*/ 0x6a)
		if_rand_gt(196, /*goto*/ 0x6b)
		label(0x98)
	endloop(0x67)

	label(0x68)
	yield
	rebuild_teams
	rebuild_squadrons
	goto_first(0x66)

	endlist
};

u8 func0415_unused[] = {
	set_chr_dodge_rating(2, 0x0a)
	set_accuracy(16)
	set_reaction_speed(55)
	set_chr_maxdamage(CHR_SELF, 60)
	add_health_or_armor(0)
	set_recovery_speed(30)
	set_shield(0)
	try_equip_weapon(MODEL_CHRAVENGER, WEAPON_K7AVENGER, 0x00000000, /*goto*/ 0x08)
	label(0x08)
	set_chr_team(CHR_SELF, TEAM_ENEMY)
	set_self_flag_bankx(CHRFLAG0_00002000, BANK_0)
	set_squadron(SQUADRON_0F)
	rebuild_teams
	rebuild_squadrons
	set_ailist(CHR_SELF, GAILIST_SEARCH_FOR_PLAYER)
	endlist
};

u8 func100c_spawn_dd_guards[] = {
	label(0x66)
	restart_timer

	beginloop(0x67)
		if_stage_flag_eq(STAGEFLAG_OUTRO_STARTED, TRUE, /*goto*/ 0x0f)
		if_stage_flag_eq(STAGEFLAG_ELVIS_GAVE_PROXYMINE, TRUE, /*goto*/ 0x31)
		if_objective_complete(0, /*goto*/ 0x31)
		if_objective_complete(1, /*goto*/ 0x31)
		if_objective_complete(2, /*goto*/ 0x31)
		if_objective_complete(3, /*goto*/ 0x31)
		if_objective_complete(4, /*goto*/ 0x31)
	endloop(0x67)

	label(0x31)
	dprint 'T','I','M','E','\n',0,
	if_timer_lt(3600, /*goto*/ 0x98)
	label(0x31)
	dprint 'S','Q','U','A','D','\n',0,
	if_num_chrs_in_squadron_gt(1, 0x0e, /*goto*/ 0x98)
	call_rng
	if_rand_gt(64, /*goto*/ 0x69)
	if_rand_gt(128, /*goto*/ 0x6a)
	if_rand_gt(196, /*goto*/ 0x6b)

	// 1
	if_stage_flag_eq(STAGEFLAG_OUTRO_STARTED, TRUE, /*goto*/ 0x0f)
	try_spawn_chr_at_pad(BODY_DD_GUARD, HEAD_RANDOM, 0x0126, AILIST_SPAWNED_GUARD, 0x00000200, /*goto*/ 0x68)
	goto_next(0x98)

	// 2
	label(0x69)
	if_stage_flag_eq(STAGEFLAG_OUTRO_STARTED, TRUE, /*goto*/ 0x0f)
	try_spawn_chr_at_pad(BODY_DD_GUARD, HEAD_RANDOM, 0x00e5, AILIST_SPAWNED_GUARD, 0x00000200, /*goto*/ 0x68)
	goto_next(0x98)

	// 3
	label(0x6a)
	if_stage_flag_eq(STAGEFLAG_OUTRO_STARTED, TRUE, /*goto*/ 0x0f)
	try_spawn_chr_at_pad(BODY_DD_GUARD, HEAD_RANDOM, 0x0130, AILIST_SPAWNED_GUARD, 0x00000200, /*goto*/ 0x68)
	goto_next(0x98)

	// 4
	label(0x6b)
	if_stage_flag_eq(STAGEFLAG_OUTRO_STARTED, TRUE, /*goto*/ 0x0f)
	try_spawn_chr_at_pad(BODY_DD_GUARD, HEAD_RANDOM, 0x00fd, AILIST_SPAWNED_GUARD, 0x00000200, /*goto*/ 0x68)
	goto_next(0x98)

	// Spawn failed
	label(0x98)
	goto_first(0x67)

	// Spawn worked
	label(0x68)
	if_stage_flag_eq(STAGEFLAG_OUTRO_STARTED, TRUE, /*goto*/ 0x0f)
	yield
	rebuild_teams
	rebuild_squadrons
	goto_first(0x66)

	label(0x0f)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func0416_spawned_guard[] = {
	set_chr_dodge_rating(2, 0x0a)
	set_accuracy(16)
	set_reaction_speed(55)
	set_chr_maxdamage(CHR_SELF, 60)
	add_health_or_armor(0)
	set_recovery_speed(30)
	set_shield(0)
	try_equip_weapon(MODEL_CHRAVENGER, WEAPON_K7AVENGER, 0x00000000, /*goto*/ 0x08)
	label(0x08)
	set_chr_team(CHR_SELF, TEAM_ENEMY)
	set_self_flag_bankx(CHRFLAG0_00002000, BANK_0)
	set_self_flag_bankx(CHRFLAG0_AIVSAI, BANK_0)
	set_squadron(SQUADRON_0E)
	rebuild_teams
	rebuild_squadrons
	// Pad is next to UFO
	run_to_pad(0x0105)
	set_returnlist(CHR_SELF, GAILIST_UNALERTED)
	set_ailist(CHR_SELF, GAILIST_UNALERTED)
	endlist
};

u8 func1008_escapepod[] = {
	beginloop(0x06)
		chr_toggle_p1p2(CHR_SELF)
		if_object_in_good_condition(OBJ_ESCAPEPOD, /*goto*/ 0x31)

		// Pod destroyed
		mute_channel(CHANNEL_0)
		show_hudmsg(CHR_BOND, L_AZT_015) // "Critical mission object has been destroyed."
		set_stage_flag(STAGEFLAG_ESCAPEPOD_DESTROYED)
		set_ailist(CHR_SELF, GAILIST_IDLE)

		// Pod healthy
		label(0x31)
		if_stage_flag_eq(STAGEFLAG_BEACON_ACTIVATED, TRUE, /*goto*/ 0x08)
		if_chr_activated_object(CHR_P1P2, OBJ_ESCAPEPOD, /*goto*/ 0x31)
		label(0x08)
		reloop(0x06)

		label(0x31)
		assign_sound(SFX_8115, CHANNEL_0)
		play_sound_from_object(CHANNEL_0, OBJ_ESCAPEPOD, 0x0320, 0x0640)
		show_hudmsg(CHR_P1P2, L_AZT_014) // "Distress beacon has been activated."
		set_stage_flag(STAGEFLAG_BEACON_ACTIVATED)
	endloop(0x06)

	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func1009_check_shuttle_destroyed[] = {
	yield
	yield
	yield
	yield
	yield

	beginloop(0x06)
		if_object_in_good_condition(OBJ_SKEDAR_SHUTTLE, /*goto*/ 0x31)
		show_hudmsg(CHR_BOND, L_AZT_021) // "Jamming device has been shut down."
		set_stage_flag(STAGEFLAG_SKEDAR_SHUTTLE_DESTROYED)
		set_ailist(CHR_SELF, GAILIST_IDLE)
		label(0x31)
	endloop(0x06)

	endlist
};

u8 func100a_check_president_dead[] = {
	beginloop(0x06)
		if_chr_death_animation_finished(CHR_PRESIDENT, /*goto*/ 0x31)
		if_chr_dead(CHR_PRESIDENT, /*goto*/ 0x31)
		if_chr_knockedout(CHR_PRESIDENT, /*goto*/ 0x31)
	endloop(0x06)

	label(0x31)
	show_hudmsg(CHR_BOND, L_AZT_022) // "President has been killed."
	set_stage_flag(STAGEFLAG_PRESIDENT_DEAD)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func100b_check_clone_dead[] = {
	beginloop(0x06)
		if_chr_death_animation_finished(CHR_PRES_CLONE, /*goto*/ 0x31)
		if_chr_dead(CHR_PRES_CLONE, /*goto*/ 0x31)
		if_chr_knockedout(CHR_PRES_CLONE, /*goto*/ 0x31)
	endloop(0x06)

	label(0x31)
	show_hudmsg(CHR_BOND, L_AZT_023) // "Presidential clone has been eliminated."
	set_stage_flag(STAGEFLAG_CLONE_DEAD)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func0403_init_elvis[] = {
	set_shield(100)
	set_chr_hiddenflag(CHR_SELF, CHRHFLAG_INFINITESHIELD)
	set_self_chrflag(CHRCFLAG_INVINCIBLE)
	set_accuracy(100)
	set_reaction_speed(100)
	add_health_or_armor(1000)
	set_chr_maxdamage(CHR_SELF, 1000)
	set_self_chrflag(CHRCFLAG_RUNFASTER)
	assign_path(12)
	start_path
	set_ailist(CHR_SELF, AILIST_ELVIS)
	endlist
};

u8 func0404_elvis[] = {
	set_shotlist(AILIST_ELVIS)
	label(0x04)
	restart_timer

	beginloop(0x06)
		if_chr_idle(/*goto*/ 0x31)
		if_path_started(/*goto*/ 0x31)
		restart_timer
		start_path
		label(0x31)
		dprint 'G','O',' ','T','O',' ','P','A','D','\n',0,
		set_target_chr(CHR_BOND)
		set_chrpreset(CHR_BOND)
		if_stage_flag_eq(STAGEFLAG_ELVIS_GAVE_PROXYMINE, TRUE, /*goto*/ 0x31)
		if_objective_complete(0, /*goto*/ 0x31)
		if_objective_complete(1, /*goto*/ 0x31)
		if_objective_complete(2, /*goto*/ 0x31)
		if_objective_complete(3, /*goto*/ 0x31)
		if_objective_complete(4, /*goto*/ 0x31)
		if_can_see_target(/*goto*/ 0xa5)
		set_target_chr(CHR_COOP)
		set_chrpreset(CHR_COOP)
		if_can_see_target(/*goto*/ 0xa5)
		label(0x31)
		if_enemy_distance_lt_and_los(2540, /*goto*/ 0x0a)
		if_timer_gt(600, /*goto*/ 0x0b)
	endloop(0x06)

	// 10 seconds passed
	label(0x0b)
	call_rng
	if_rand_gt(128, /*goto*/ 0x31)

	// 50% chance of doing look around animation
	call_rng
	if_rand_lt(64, /*goto*/ 0x99)
	if_rand_lt(128, /*goto*/ 0x9a)
	if_rand_lt(196, /*goto*/ 0x9b)

	set_self_flag_bankx(CHRFLAG1_DONE_SEARCH_ANIM, BANK_1)
	chr_do_animation(ANIM_LOOK_AROUND_025B, 0, -1, 0x10, 0x0a, CHR_SELF, 2)
	goto_next(0x31)

	label(0x99)
	chr_do_animation(ANIM_LOOK_AROUND_025C, 0, -1, 0x10, 0x0a, CHR_SELF, 2)
	goto_next(0x31)

	label(0x9a)
	chr_do_animation(ANIM_LOOK_AROUND_025D, 0, -1, 0x10, 0x0a, CHR_SELF, 2)
	goto_next(0x31)

	label(0x9b)
	chr_do_animation(ANIM_LOOK_AROUND_025E, 0, -1, 0x10, 0x0a, CHR_SELF, 2)

	label(0x31)
	goto_first(0x04)

	// Detected enemy
	label(0x0a)
	dprint 'D','E','T','E','C','T','E','D','\n',0,
	set_returnlist(CHR_SELF, AILIST_INIT_ELVIS)
	set_shotlist(AILIST_INIT_ELVIS)
	set_ailist(CHR_SELF, GAILIST_COMBAT_WITH_TARGET)

	// Sees player
	label(0xa5)
	set_target_chr(CHR_PRESET)
	try_run_to_target(/*goto*/ 0x12)

	beginloop(0x12)
		dprint 'G','O',' ','T','O','W','A','R','D','S','\n',0,
		if_distance_to_target_lt(300, /*goto*/ 0x13)
		if_timer_gt(180, /*goto*/ 0x08)
	endloop(0x12)

	// Running towards player for 3 seconds - check if can still see player
	label(0x08)
	if_can_see_target(/*goto*/ 0x31)
	goto_first(0x04)

	label(0x31)
	goto_first(0xa5)

	// Close to player
	label(0x13)
	do_preset_animation(-1)
	speak(CHR_TARGET, L_AZT_031, MP3_02E2, CHANNEL_6, COLOR_04_ORANGE) // "Take this; you should find it useful!"
	give_object_to_chr(OBJ_PROXYMINE, CHR_TARGET)

	beginloop(0x14)
		if_sound_finished(CHANNEL_6, /*goto*/ 0x31)
	endloop(0x14)

	label(0x31)
	stop_chr
	set_stage_flag(STAGEFLAG_ELVIS_GAVE_PROXYMINE)
	goto_first(0x04)

	endlist
};

u8 func0405_unused[] = {
	jog_to_pad(0x0107)
	beginloop(0x06)
	endloop(0x06)

	endlist
};

u8 func0417_init_robot[] = {
	set_accuracy(40)
	set_self_chrflag(CHRCFLAG_FORCEAUTOAIM)
	set_chr_maxdamage(CHR_SELF, 250)
	set_ailist(CHR_SELF, AILIST_ROBOT)
	endlist
};

u8 func0418_robot[] = {
	set_shotlist(AILIST_ROBOT)
	label(0x66)
	set_self_chrflag(CHRCFLAG_00040000)
	if_chr_dead(CHR_SELF, /*goto*/ 0x11)
	if_chr_death_animation_finished(CHR_SELF, /*goto*/ 0x11)
	if_chr_knockedout(CHR_SELF, /*goto*/ 0x08)
	goto_next(0x04)
	label(0x08)
	yield
	damage_chr(CHR_SELF, WEAPON_SUPERDRAGON)
	goto_first(0x66)

	beginloop(0x04)
		dprint 'P','A','R','T',' ','1','\n',0,
		chr_toggle_p1p2(CHR_SELF)
		set_target_chr(CHR_P1P2)
		if_alertness(99, OPERATOR_GREATER_THAN, /*goto*/ 0x0d)
		if_target_in_sight(/*goto*/ 0x0d)
		call_rng
		if_rand_gt(5, /*goto*/ 0x31)
		if_sound_finished(CHANNEL_5, /*goto*/ 0x08)
		goto_next(0x31)

		// Make random noise
		label(0x08)
		call_rng
		if_rand_lt(86, /*goto*/ 0x0b)
		if_rand_lt(172, /*goto*/ 0x0c)
		assign_sound(SFX_046A, CHANNEL_5)
		play_sound_from_entity(CHANNEL_5, CHR_SELF, 0x0bb8, 0x1770, 0x01)
		goto_next(0x31)
		label(0x0b)
		assign_sound(SFX_046B, CHANNEL_5)
		play_sound_from_entity(CHANNEL_5, CHR_SELF, 0x0bb8, 0x1770, 0x01)
		goto_next(0x31)
		label(0x0c)
		assign_sound(SFX_046C, CHANNEL_5)
		play_sound_from_entity(CHANNEL_5, CHR_SELF, 0x0bb8, 0x1770, 0x01)
		label(0x31)
	endloop(0x04)

	// Alerted
	label(0x0d)
	increase_squadron_alertness(100)
	restart_timer
	if_distance_to_target_lt(300, /*goto*/ 0x31)
	if_distance_to_target_gt(1000, /*goto*/ 0x15)
	if_target_in_sight(/*goto*/ 0x13)

	// Distance > 1000 or not in sight
	label(0x15)
	try_jog_to_target(/*goto*/ 0x08)

	// Distance < 300
	label(0x31)
	stop_chr

	label(0x08)
	if_self_flag_bankx_eq(CHRFLAG0_00002000, TRUE, BANK_0, /*goto*/ 0x0a)
	say_quip(CHR_BOND, 0x1f, 0xff, 0x02, 0xff, BANK_1, 0x00, 0x00)
	set_self_flag_bankx(CHRFLAG0_00002000, BANK_0)

	beginloop(0x0a)
		dprint 'P','A','R','T',' ','2','\n',0,
		if_timer_gt(180, /*goto*/ 0x08)
		if_distance_to_target_gt(1000, /*goto*/ 0x15)
		dprint 'P','A','R','T',' ','2','\n',0,
		if_target_in_sight(/*goto*/ 0x13)
		chr_toggle_p1p2(CHR_SELF)
		set_target_chr(CHR_P1P2)
		if_target_in_sight(/*goto*/ 0x13)
		chr_toggle_p1p2(CHR_SELF)
		set_target_chr(CHR_P1P2)
		label(0x15)
	endloop(0x0a)

	// Player in sight
	label(0x13)
	set_target_chr(CHR_P1P2)
	restart_timer
	dprint 'P','A','R','T',' ','3','a','\n',0,
	try_attack_stand(ENTITYTYPE_TARGET, 0, /*goto*/ 0x0e)
	goto_first(0x04)

	beginloop(0x0e)
		if_chr_stopped(/*goto*/ 0x08)
	endloop(0x0e)

	label(0x08)
	goto_first(0x0d)

	label(0x11)
	assign_sound(MP3_ROBOT_ALERT_UNDER_ATTACK, CHANNEL_6)
	play_sound_from_entity(CHANNEL_6, CHR_SELF, 0x0bb8, 0x1770, 0x01)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

/**
 * Assigned to two stripes guards.
 */
u8 func0414_spawner[] = {
	set_self_chrflag(CHRCFLAG_CLONEABLE)

	beginloop(0x06)
		chr_toggle_p1p2(CHR_SELF)
		set_target_chr(CHR_P1P2)
		if_can_see_target(/*goto*/ 0x0a)
		// Room 0x0029 is the skedar shuttle area
		if_chr_in_room(CHR_P1P2, 0x00, 0x0029, /*goto*/ 0x0a)
		reloop(0x06)

		label(0x0a)
		dprint 'H','E','A','R','S','P','A','W','N','\n',0,
		label(0x31)
		if_never_been_onscreen(/*goto*/ 0x52)
		dprint 'N','E','V','E','R',' ','V','I','S','F','A','I','L','\n',0,
		if_can_see_target(/*goto*/ 0x0a)
	endloop(0x06)

	label(0x0a)
	set_ailist(CHR_SELF, GAILIST_ALERTED)

	label(0x52)
	dprint 'C','H','E','C','K',' ','D','U','P','E','\n',0,
	if_chr_death_animation_finished(CHR_CLONE, /*goto*/ 0x52)
	set_ailist(CHR_SELF, AILIST_SPAWNER)

	label(0x52)
	dprint 'C','R','E','A','T','E',' ','S','P','A','W','N','\n',0,
	try_spawn_clone2(CHR_SELF, GAILIST_ALERTED, 0x00000000, /*goto*/ 0x31)
	dprint 'C','R','E','A','T','E',' ','F','A','I','L','\n',0,
	set_ailist(CHR_SELF, AILIST_SPAWNER)

	label(0x31)
	yield
	set_ailist(CHR_SELF, AILIST_SPAWNER)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func0419_unused[] = {
	set_self_chrflag(CHRCFLAG_HIDDEN)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func0422_hide[] = {
	set_self_chrflag(CHRCFLAG_INVINCIBLE)
	set_self_chrflag(CHRCFLAG_UNEXPLODABLE)
	set_self_chrflag(CHRCFLAG_HIDDEN)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func041a_pres_clone[] = {
	set_self_chrflag(CHRCFLAG_FORCEAUTOAIM)
	set_self_chrflag(CHRCFLAG_RUNFASTER)

	beginloop(0x06)
		chr_toggle_p1p2(CHR_SELF)
		set_target_chr(CHR_P1P2)
		if_alertness(99, OPERATOR_GREATER_THAN, /*goto*/ 0x31)
		if_target_outside_my_yvisang(/*goto*/ 0x08)
		if_target_in_sight(/*goto*/ 0x31)
		label(0x08)
	endloop(0x06)

	// Alert, or player in sight and looking at clone
	label(0x31)
	run_to_pad(0x002c)

	beginloop(0x0a)
		if_chr_stopped(/*goto*/ 0x31)
	endloop(0x0a)

	label(0x31)
	stop_chr

	label(0xa5)
	chr_do_animation(ANIM_COWER_0229, -1, -1, 0x10, 0x0a, CHR_SELF, 2)

	beginloop(0x10)
		if_chr_stopped(/*goto*/ 0x31)
	endloop(0x10)

	label(0x31)
	goto_first(0xa5)

	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func041b_init_president[] = {
	set_self_chrflag(CHRCFLAG_RUNFASTER)
	set_chr_maxdamage(CHR_SELF, 300)
	set_shield(0)
	set_ailist(CHR_SELF, AILIST_PRESIDENT_WAITING)
	endlist
};

u8 func041c_president_waiting[] = {
	set_shotlist(AILIST_PRESIDENT_WAITING)
	if_chr_dead(CHR_SELF, /*goto*/ 0x08)
	if_chr_death_animation_finished(CHR_SELF, /*goto*/ 0x08)
	if_chr_knockedout(CHR_SELF, /*goto*/ 0x08)
	goto_next(0x31)

	// Dying
	label(0x08)
	set_shotlist(GAILIST_IDLE)
	set_ailist(CHR_SELF, GAILIST_IDLE)

	label(0x31)
	stop_chr
	yield

	// Wait until trigger and can see player
	beginloop(0x06)
		chr_toggle_p1p2(CHR_SELF)
		set_target_chr(CHR_P1P2)
		if_stage_flag_eq(STAGEFLAG_TRIGGER_PRESIDENT_RUNNING, TRUE, /*goto*/ 0x31)
		goto_first(0x06)

		label(0x31)
		if_can_see_target(/*goto*/ 0x31)
	endloop(0x06)

	label(0x31)
	set_shotlist(AILIST_PRESIDENT_RUNNING)
	set_ailist(CHR_SELF, AILIST_PRESIDENT_RUNNING)
	endlist
};

u8 func041d_president_running[] = {
	set_self_chrflag(CHRCFLAG_PUSHABLE)
	set_alertness(100)
	set_shotlist(AILIST_PRESIDENT_RUNNING)
	dprint 'R','E','S','T','A','R','T','\n',0,
	yield
	if_chr_dead(CHR_SELF, /*goto*/ 0x08)
	if_chr_death_animation_finished(CHR_SELF, /*goto*/ 0x08)
	if_chr_knockedout(CHR_SELF, /*goto*/ 0x08)
	goto_next(0x31)

	// Dying
	label(0x08)
	set_shotlist(GAILIST_IDLE)
	restart_timer

	beginloop(0x9c)
		dprint 'K','I','L','L','E','D','\n',0,
		if_timer_gt(15, /*goto*/ 0x08)
	endloop(0x9c)

	label(0x08)
	assign_sound(MP3_02BF, CHANNEL_6)
	play_sound_from_entity(CHANNEL_6, CHR_SELF, 0x0bb8, 0x1770, 0x01)
	set_shotlist(GAILIST_IDLE)
	set_ailist(CHR_SELF, GAILIST_IDLE)

	// Alive
	label(0x31)
	dprint 'b','4',' ','s','h','i','e','l','d',' ','c','h','e','c','k','\n',0,
	if_just_injured(CHR_SELF, /*goto*/ 0x08)
	goto_next(0x9d)

	// Injured
	label(0x08)
	restart_timer
	assign_sound(MP3_02C2, CHANNEL_6)
	play_sound_from_entity(CHANNEL_6, CHR_SELF, 0x0bb8, 0x1770, 0x01)

	beginloop(0x9e)
		dprint 'I','N','J','U','R','E','D','\n',0,
		if_num_times_shot_lt(1, /*goto*/ 0x08)
		if_timer_lt(20, /*goto*/ 0x08)
		label(0x08)
		if_chr_stopped(/*goto*/ 0x9d)
	endloop(0x9e)

	// Main logic
	label(0x9d)
	stop_chr
	restart_timer

	beginloop(0x9f)
		dprint 'W','A','I','T','\n',0,
		// Room 0x0014 = UFO area
		// Yes, checking this 5 times is unnecessary
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
		dprint 't','a','r','g','e','t','\n',0,
		if_can_see_target(/*goto*/ 0x08)
		goto_next(0xa0)

		label(0x08)
		if_timer_gt(1250, /*goto*/ 0x31)
		if_distance_to_target_gt(200, /*goto*/ 0xa0)
	endloop(0x9f)

	// 20.8 seconds passed
	// Pointless RNG check
	label(0x31)
	call_rng
	if_rand_lt(64, /*goto*/ 0x31)
	goto_first(0x9d)
	label(0x31)
	goto_first(0x9d)

	// Sees player
	label(0x08)
	goto_first(0x9d)

	// Can't see player, or distance > 200
	label(0xa0)
	restart_timer
	label(0x31)
	if_distance_to_target_gt(300, /*goto*/ 0x31)
	try_jog_to_target(/*goto*/ 0xa1)
	label(0x31)
	try_run_to_target(/*goto*/ 0xa1)

	beginloop(0xa1)
		dprint 'F','O','L','L','O','W','\n',0,
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
		if_distance_to_target_lt(100, /*goto*/ 0xa2)
		if_chr_stopped(/*goto*/ 0xa2)
		if_timer_gt(360, /*goto*/ 0x31)
	endloop(0xa1)

	// 6 seconds passed while running
	label(0x31)
	goto_first(0xa0)

	// Unreachable
	label(0x08)
	goto_first(0xa0)

	// Next to player
	label(0xa2)
	goto_first(0x9d)

	// Unreachable
	label(0xa3)
	try_run_to_target(/*goto*/ 0xa4)

	// Unreachable
	beginloop(0xa4)
		dprint 'R','U','N','N','F','O','\n',0,
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
		if_chr_in_room(CHR_SELF, 0x00, 0x0014, /*goto*/ 0xa5)
	endloop(0xa4)

	// Unreachable
	label(0xa6)
	goto_first(0x9d)

	// Jo is near UFO
	label(0xa5)
	run_to_pad(0x0105)

	beginloop(0x0b)
		if_chr_stopped(/*goto*/ 0x08)
	endloop(0x0b)

	label(0x08)
	stop_chr
	set_chr_team(CHR_SELF, TEAM_NONCOMBAT)
	rebuild_teams
	rebuild_squadrons
	if_stage_flag_eq(STAGEFLAG_PRESIDENT_RESCUED, TRUE, /*goto*/ 0x31)
	show_hudmsg(CHR_TARGET, L_AZT_025) // "President has been rescued."
	set_stage_flag(STAGEFLAG_PRESIDENT_RESCUED)
	label(0x31)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func100e_check_robots_left[] = {
	beginloop(0x06)
		if_chr_death_animation_finished(CHR_ROBOT1, /*goto*/ 0x31)
		if_chr_dead(CHR_ROBOT1, /*goto*/ 0x31)
		if_chr_knockedout(CHR_ROBOT1, /*goto*/ 0x31)
		if_chr_in_room(CHR_ROBOT1, 0x00, 0x004a, /*goto*/ 0x08)
		if_chr_in_room(CHR_ROBOT1, 0x00, 0x004b, /*goto*/ 0x08)
		if_chr_in_room(CHR_ROBOT1, 0x00, 0x004c, /*goto*/ 0x08)
		if_chr_in_room(CHR_ROBOT1, 0x00, 0x004d, /*goto*/ 0x08)
		goto_next(0x31)
		label(0x08)
		reloop(0x06)

		label(0x31)
		if_chr_death_animation_finished(CHR_ROBOT2, /*goto*/ 0x31)
		if_chr_dead(CHR_ROBOT2, /*goto*/ 0x31)
		if_chr_knockedout(CHR_ROBOT2, /*goto*/ 0x31)
		if_chr_in_room(CHR_ROBOT2, 0x00, 0x004a, /*goto*/ 0x08)
		if_chr_in_room(CHR_ROBOT2, 0x00, 0x004b, /*goto*/ 0x08)
		if_chr_in_room(CHR_ROBOT2, 0x00, 0x004c, /*goto*/ 0x08)
		if_chr_in_room(CHR_ROBOT2, 0x00, 0x004d, /*goto*/ 0x08)
		goto_next(0x31)
		label(0x08)
		reloop(0x06)

		label(0x31)
		if_chr_death_animation_finished(CHR_ROBOT3, /*goto*/ 0x31)
		if_chr_dead(CHR_ROBOT3, /*goto*/ 0x31)
		if_chr_knockedout(CHR_ROBOT3, /*goto*/ 0x31)
		if_chr_in_room(CHR_ROBOT3, 0x00, 0x004a, /*goto*/ 0x08)
		if_chr_in_room(CHR_ROBOT3, 0x00, 0x004b, /*goto*/ 0x08)
		if_chr_in_room(CHR_ROBOT3, 0x00, 0x004c, /*goto*/ 0x08)
		if_chr_in_room(CHR_ROBOT3, 0x00, 0x004d, /*goto*/ 0x08)
		goto_next(0x31)
		label(0x08)
		reloop(0x06)

		label(0x31)
		if_chr_death_animation_finished(CHR_ROBOT4, /*goto*/ 0x31)
		if_chr_dead(CHR_ROBOT4, /*goto*/ 0x31)
		if_chr_knockedout(CHR_ROBOT4, /*goto*/ 0x31)
		if_chr_in_room(CHR_ROBOT4, 0x00, 0x004a, /*goto*/ 0x08)
		if_chr_in_room(CHR_ROBOT4, 0x00, 0x004b, /*goto*/ 0x08)
		if_chr_in_room(CHR_ROBOT4, 0x00, 0x004c, /*goto*/ 0x08)
		if_chr_in_room(CHR_ROBOT4, 0x00, 0x004d, /*goto*/ 0x08)
		goto_next(0x31)
		label(0x08)
		reloop(0x06)

		label(0x31)
		if_stage_flag_eq(STAGEFLAG_TRENT_RUNNING, TRUE, /*goto*/ 0x31)
	goto_first(0x06)

	label(0x31)
	set_stage_flag(STAGEFLAG_TRIGGER_PRESIDENT_RUNNING)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func041e_trent_waiting[] = {
	set_accuracy(0)
	set_self_chrflag(CHRCFLAG_00000040)
	set_shield(100)
	set_chr_hiddenflag(CHR_SELF, CHRHFLAG_INFINITESHIELD)

	beginloop(0x06)
		chr_toggle_p1p2(CHR_SELF)
		set_target_chr(CHR_P1P2)
		if_can_see_target(/*goto*/ 0x08)
	endloop(0x06)

	label(0x08)
	restart_timer
	speak(CHR_P1P2, L_AZT_024, MP3_02CA, CHANNEL_6, COLOR_05_GREEN) // "You'll never save him now!"
	chr_do_animation(ANIM_TALKING_0231, 0, -1, 0x10, 0x10, CHR_SELF, 2)

	beginloop(0x0a)
		if_timer_gt(120, /*goto*/ 0x08)
	endloop(0x0a)

	label(0x08)
	set_ailist(CHR_SELF, AILIST_TRENT_SHOOTING)
	endlist
};

u8 func041f_trent_shooting[] = {
	label(0x04)
	stop_chr

	beginloop(0x06)
		chr_toggle_p1p2(CHR_SELF)
		set_target_chr(CHR_P1P2)
		try_unset_chr_flag_bank3_02000000(CHR_SELF, /*goto*/ 0x31)
		if_target_in_sight(/*goto*/ 0x08)
	endloop(0x06)

	label(0x31)
	set_ailist(CHR_SELF, AILIST_TRENT_RUNNING)

	label(0x08)
	label(0xa8)
	try_attack_stand(ENTITYTYPE_TARGET | ENTITYTYPE_AIMONLY, 0, /*goto*/ 0xa7)
	label(0xa7)
	say_quip(CHR_BOND, QUIP_ATTACK1, 0x19, 0x02, 0x01, BANK_0, 0x00, 0x00)
	try_modify_attack(ENTITYTYPE_TARGET, 0, /*goto*/ 0x0a)
	goto_next(0x31)

	// Shoot worked
	beginloop(0x0a)
		if_chr_stopped(/*goto*/ 0x08)
	endloop(0x0a)

	label(0x08)
	goto_next(0x0b)

	// Unreachable
	if_chr_dead(CHR_TARGET, /*goto*/ 0x0b)
	goto_first(0x04)

	// Shoot failed
	label(0x31)
	goto_first(0x04)

	label(0x0b)
	restart_timer
	chr_do_animation(ANIM_TALKING_0231, 0, -1, 0x10, 0x10, CHR_SELF, 2)

	beginloop(0x0c)
		if_timer_gt(120, /*goto*/ 0x08)
	endloop(0x0c)

	label(0x08)
	set_ailist(CHR_SELF, AILIST_TRENT_RUNNING)
	endlist
};

u8 func0420_trent_running[] = {
	set_self_chrflag(CHRCFLAG_RUNFASTER)
	set_self_chrflag(CHRCFLAG_INVINCIBLE)
	set_stage_flag(STAGEFLAG_TRENT_RUNNING)
	restart_timer
	run_to_pad(0x0027)

	beginloop(0x0a)
		if_timer_gt(300, /*goto*/ 0x31)
	endloop(0x0a)

	label(0x31)
	chr_toggle_p1p2(CHR_SELF)
	set_target_chr(CHR_P1P2)
	if_can_see_target(/*goto*/ 0x31)
	goto_next(0x08)

	label(0x31)
	if_chr_stopped(/*goto*/ 0x08)
	goto_first(0x0a)

	// Player not in sight, or Trent has reached his destination
	label(0x08)
	if_nearly_in_targets_sight(30, /*goto*/ 0x31)
	goto_next(0x08)

	label(0x31)
	goto_first(0x0a)

	// Player definitely not in sight
	label(0x08)
	set_self_chrflag(CHRCFLAG_HIDDEN)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func100f_check_end_level[] = {
	beginloop(0x0a)
		if_all_objectives_complete(/*goto*/ 0x08)
	endloop(0x0a)

	label(0x08)
	restart_timer

	beginloop(0x0b)
		if_timer_gt(120, /*goto*/ 0x31)
	endloop(0x0b)

	label(0x31)
	if_chr_death_animation_finished(CHR_BOND, /*goto*/ 0x31)
	if_chr_dead(CHR_BOND, /*goto*/ 0x31)
	if_chr_knockedout(CHR_BOND, /*goto*/ 0x31)
	goto_next(0x08)

	label(0x31)
	if_chr_death_animation_finished(CHR_COOP, /*goto*/ 0x31)
	if_chr_dead(CHR_COOP, /*goto*/ 0x31)
	if_chr_knockedout(CHR_COOP, /*goto*/ 0x31)

	// Jo or Velvet alive
	label(0x08)
	if_chr_death_animation_finished(CHR_PRESIDENT, /*goto*/ 0x32)
	if_chr_dead(CHR_PRESIDENT, /*goto*/ 0x32)
	if_chr_knockedout(CHR_PRESIDENT, /*goto*/ 0x32)
	set_ailist(CHR_PRESIDENT, GAILIST_STOP_AND_IDLE)

	if_chr_death_animation_finished(CHR_BOND, /*goto*/ 0x31)
	if_chr_dead(CHR_BOND, /*goto*/ 0x31)
	if_chr_knockedout(CHR_BOND, /*goto*/ 0x31)
	goto_next(0x08)

	// Both players dead
	label(0x31)
	if_chr_death_animation_finished(CHR_COOP, /*goto*/ 0x31)
	if_chr_dead(CHR_COOP, /*goto*/ 0x31)
	if_chr_knockedout(CHR_COOP, /*goto*/ 0x31)
	goto_next(0x08)

	label(0x31)
	end_level
	set_ailist(CHR_SELF, GAILIST_IDLE)

	// Mission complete
	label(0x08)
	set_invincible(CHR_BOND)
	set_ailist(CHR_SELF, AILIST_OUTRO)

	// President dead
	label(0x32)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

/**
 * Assigned to 4 stripes and 2 blondes near the starting area.
 */
u8 func0421_starting_area_guard[] = {
	label(0x0a)
	set_returnlist(CHR_SELF, GAILIST_UNALERTED)
	set_ailist(CHR_SELF, GAILIST_SEARCH_FOR_PLAYER)
	endlist
};

u8 func1010_set_cave_lights[] = {
	yield
	set_lights_state(0x0064, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_lights_state(0x0063, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_lights_state(0x0062, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_lights_state(0x0061, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_lights_state(0x0060, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_lights_state(0x005f, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_lights_state(0x005e, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_lights_state(0x005d, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_lights_state(0x005c, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_lights_state(0x005b, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_lights_state(0x005a, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_lights_state(0x0059, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_lights_state(0x0053, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_lights_state(0x0058, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_lights_state(0x0056, LIGHTOP_1, 0x06, 0x00, 0x00)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func1012_give_medicalscanner[] = {
	yield
	if_difficulty_gt(DIFF_A, /*goto*/ 0x31)
	give_object_to_chr(OBJ_MEDICALSCANNER, CHR_BOND)
	label(0x31)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func1013_setup_rtracker[] = {
	yield
	set_object_flag3(OBJ_PROXYMINE, OBJFLAG3_RTRACKED_BLUE)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func1016_hide_hoverbike[] = {
	yield
	if_savefile_flag_is_set(SAVEFILEFLAG_CRASHSITE_BIKE, /*goto*/ 0x08)
	hide_object(OBJ_HOVERBIKE)
	label(0x08)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func1014_setup_skedar_shuttle[] = {
	yield
	show_object(OBJ_SKEDAR_SHUTTLE)
	set_object_flag3(OBJ_SKEDAR_SHUTTLE, OBJFLAG3_00000010)
	object_set_modelpart_visible(OBJ_SKEDAR_SHUTTLE, MODELPART_SKGANGWAY, FALSE)
	object_do_animation(0x0486, OBJ_SKEDAR_SHUTTLE, 0x01, 0xffff)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

u8 func1415_setup_environment[] = {
	yield
	configure_environment(0x0001, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0001, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0002, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0002, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0003, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0004, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0005, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0006, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0006, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0008, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0009, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0009, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x000a, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x000a, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x000b, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x000b, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x000c, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x000c, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x000d, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x000d, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x000e, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x000e, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x000f, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x000f, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0010, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0010, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0011, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0011, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0012, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0012, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0013, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0013, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0014, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0014, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0015, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0015, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0016, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0016, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0018, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0018, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0019, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0019, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x001a, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x001b, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x001b, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x001c, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x001c, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x001d, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x001e, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x001e, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0025, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0025, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0026, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0026, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0027, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0027, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0028, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0028, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0029, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0029, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x002a, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x002a, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x002b, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x002b, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x002c, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x002c, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x002e, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x002e, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x002f, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x002f, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0030, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0030, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0031, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0031, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0032, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0032, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0033, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0033, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0035, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0035, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0036, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0036, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x0038, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0038, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x003a, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x003a, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x003b, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x003b, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x003c, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x003c, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x003d, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x003d, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x003e, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	configure_environment(0x003f, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0045, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0065, AIENVCMD_ROOM_SETAMBIENT, TRUE)
	configure_environment(0x0065, AIENVCMD_ROOM_SETOUTDOORS, TRUE)
	set_ailist(CHR_SELF, GAILIST_IDLE)
	endlist
};

struct ailist ailists[] = {
	{ func1400_setup_counterop,         0x1400 },
	{ func1001_objectives_failed_msg,   0x1001 },
	{ func1002_intro,                   0x1002 },
	{ func1003_msg_therestheescapepod,  0x1003 },
	{ func1004_msg_maybetheresabeacon,  0x1004 },
	{ func1005_msg_thejamming,          0x1005 },
	{ func1006_msg_elvisbeable,         0x1006 },
	{ func1008_escapepod,               0x1008 },
	{ func1009_check_shuttle_destroyed, 0x1009 },
	{ func100a_check_president_dead,    0x100a },
	{ func100b_check_clone_dead,        0x100b },
	{ func100c_spawn_dd_guards,         0x100c },
	{ func100e_check_robots_left,       0x100e },
	{ func100f_check_end_level,         0x100f },
	{ func1010_set_cave_lights,         0x1010 },
	{ func1011_setup_snow,              0x1011 },
	{ func1012_give_medicalscanner,     0x1012 },
	{ func1013_setup_rtracker,          0x1013 },
	{ func1014_setup_skedar_shuttle,    0x1014 },
	{ func1415_setup_environment,       0x1415 },
	{ func1016_hide_hoverbike,          0x1016 },
	{ func1002_intro,                   0x0401 },
	{ func0402_outro,                   0x0402 },
	{ func0403_init_elvis,              0x0403 },
	{ func0404_elvis,                   0x0404 },
	{ func0405_unused,                  0x0405 },
	{ func1002_intro,                   0x0c00 },
	{ func0402_outro_from_menu,         0x0c01 },
	{ func0406_init_stripes,            0x0406 },
	{ func0407_init_blonde,             0x0407 },
	{ func0408_start_path00,            0x0408 },
	{ func0409_start_path01,            0x0409 },
	{ func040a_start_path02,            0x040a },
	{ func040b_start_path03,            0x040b },
	{ func040c_start_path04,            0x040c },
	{ func040d_start_path05,            0x040d },
	{ func040e_start_path06,            0x040e },
	{ func040f_start_path07,            0x040f },
	{ func0410_start_path08,            0x0410 },
	{ func0411_start_path09,            0x0411 },
	{ func0412_start_path10,            0x0412 },
	{ func0413_start_path11,            0x0413 },
	{ func0414_spawner,                 0x0414 },
	{ func0415_unused,                  0x0415 },
	{ func0416_spawned_guard,           0x0416 },
	{ func0417_init_robot,              0x0417 },
	{ func0418_robot,                   0x0418 },
	{ func0419_unused,                  0x0419 },
	{ func041a_pres_clone,              0x041a },
	{ func041c_president_waiting,       0x041c },
	{ func041b_init_president,          0x041b },
	{ func041d_president_running,       0x041d },
	{ func041e_trent_waiting,           0x041e },
	{ func041f_trent_shooting,          0x041f },
	{ func0420_trent_running,           0x0420 },
	{ func0421_starting_area_guard,     0x0421 },
	{ func0422_hide,                    0x0422 },
	{ NULL, 0 },
};






