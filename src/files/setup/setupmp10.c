//
// Sewers (MP)
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
	lift(0x0100, MODEL_A51_LIFT_THINWALL, 0x006a, OBJFLAG_00000008 | OBJFLAG_00000020 | OBJFLAG_00000040 | OBJFLAG_00000080 | OBJFLAG_ILLUMINATED | OBJFLAG_INVINCIBLE | OBJFLAG_UNCOLLECTABLE | OBJFLAG_00400000 | OBJFLAG_01000000 | OBJFLAG_CANNOT_ACTIVATE, OBJFLAG2_00000100 | OBJFLAG2_00000200 | OBJFLAG2_00004000 | OBJFLAG2_00100000 | OBJFLAG2_00200000, 0, 1000, 0x006a, 0x006b, -1, -1, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00003555, 0x00085555, 0x00000000)
	lift(0x0100, MODEL_A51_LIFT_THINWALL, 0x006c, OBJFLAG_00000008 | OBJFLAG_00000020 | OBJFLAG_00000040 | OBJFLAG_00000080 | OBJFLAG_ILLUMINATED | OBJFLAG_INVINCIBLE | OBJFLAG_UNCOLLECTABLE | OBJFLAG_00400000 | OBJFLAG_01000000 | OBJFLAG_CANNOT_ACTIVATE, OBJFLAG2_00000100 | OBJFLAG2_00000200 | OBJFLAG2_00004000 | OBJFLAG2_00100000 | OBJFLAG2_00200000, 0, 1000, 0x006c, 0x006d, -1, -1, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00003555, 0x00085555, 0x00000000)
	lift(0x0100, MODEL_A51_LIFT_THINWALL, 0x006e, OBJFLAG_00000008 | OBJFLAG_00000020 | OBJFLAG_00000040 | OBJFLAG_00000080 | OBJFLAG_ILLUMINATED | OBJFLAG_INVINCIBLE | OBJFLAG_UNCOLLECTABLE | OBJFLAG_00400000 | OBJFLAG_01000000 | OBJFLAG_CANNOT_ACTIVATE, OBJFLAG2_00000100 | OBJFLAG2_00000200 | OBJFLAG2_00004000 | OBJFLAG2_00100000 | OBJFLAG2_00200000, 0, 1000, 0x006e, 0x006f, -1, -1, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00003555, 0x00085555, 0x00000000)
	endprops
};

s32 intro[] = {
	outfit(OUTFIT_DEFAULT)
	endintro
};

struct path paths[] = {
	{ NULL, 0, 0 },
};

struct ailist ailists[] = {
	{ NULL, 0 },
};


