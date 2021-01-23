#include <ultra64.h>
#include "constants.h"
#include "game/cheats.h"
#include "game/data/data_000000.h"
#include "game/data/data_0083d0.h"
#include "game/data/data_00e460.h"
#include "game/data/data_0160b0.h"
#include "game/data/data_01a3a0.h"
#include "game/data/data_020df0.h"
#include "game/data/data_02da90.h"
#include "game/inventory/items.h"
#include "game/game_097ba0.h"
#include "game/game_0b0fd0.h"
#include "game/game_0b69d0.h"
#include "game/game_0dcdb0.h"
#include "game/game_127910.h"
#include "game/mplayer/setup.h"
#include "game/game_197600.h"
#include "game/lang.h"
#include "game/mplayer/mplayer.h"
#include "game/pdoptions.h"
#include "gvars/gvars.h"
#include "lib/lib_13130.h"
#include "types.h"

struct weapon *weaponFindById(s32 itemid)
{
	if (itemid < 0) {
		return NULL;
	}

	if (itemid >= NUM_WEAPONS) {
		return NULL;
	}

	return g_Weapons[itemid];
}

struct weaponfunc *weaponGetFunctionById(u32 weaponnum, u32 which)
{
	struct weapon *weapon = weaponFindById(weaponnum);

	if (weapon) {
		return weapon->functions[which];
	}

	return NULL;
}

struct weaponfunc *handGetWeaponFunction2(struct hand *hand)
{
	struct weapon *weapon = weaponFindById(hand->weaponnum);

	if (weapon) {
		return weapon->functions[hand->weaponfunc];
	}

	return NULL;
}

struct weaponfunc *handGetWeaponFunction(struct hand *hand)
{
	struct weapon *weapon = g_Weapons[hand->weaponnum];

	if (weapon) {
		return weapon->functions[hand->weaponfunc];
	}

	return NULL;
}

struct weaponfunc *weaponGetFunction(u8 *arg0, s32 which)
{
	struct weapon *weapon = g_Weapons[*arg0];

	if (weapon) {
		return weapon->functions[which];
	}

	return NULL;
}

struct weaponfunc *currentPlayerGetWeaponFunction(u32 hand)
{
	struct weapon *weapon = weaponFindById(g_Vars.currentplayer->hands[hand].weaponnum);

	if (weapon) {
		return weapon->functions[g_Vars.currentplayer->hands[hand].weaponfunc];
	}

	return NULL;
}

u32 weaponGetNumFunctions(u32 weaponnum)
{
	struct weapon *weapon = weaponFindById(weaponnum);
	s32 i;

	if (!weapon) {
		return 0;
	}

	for (i = 0; i < 2; i++) {
		if (weapon->functions[i] == NULL) {
			return i;
		}
	}

	return 2;
}

GLOBAL_ASM(
glabel func0f0b11bc
/*  f0b11bc:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*  f0b11c0:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f0b11c4:	0fc2c3f4 */ 	jal	weaponFindById
/*  f0b11c8:	90840000 */ 	lbu	$a0,0x0($a0)
/*  f0b11cc:	10400003 */ 	beqz	$v0,.L0f0b11dc
/*  f0b11d0:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f0b11d4:	10000003 */ 	b	.L0f0b11e4
/*  f0b11d8:	8c420024 */ 	lw	$v0,0x24($v0)
.L0f0b11dc:
/*  f0b11dc:	3c028007 */ 	lui	$v0,%hi(inve_000110c0)
/*  f0b11e0:	2442b0a0 */ 	addiu	$v0,$v0,%lo(inve_000110c0)
.L0f0b11e4:
/*  f0b11e4:	03e00008 */ 	jr	$ra
/*  f0b11e8:	27bd0018 */ 	addiu	$sp,$sp,0x18
);

struct inventory_ammo *weaponGetAmmoByFunction(u32 weaponnum, u32 funcnum)
{
	struct weapon *weapon = weaponFindById(weaponnum);
	struct weaponfunc *func = weaponGetFunctionById(weaponnum, funcnum);

	if (func && weapon && func->ammoindex >= 0) {
		return weapon->ammos[func->ammoindex];
	}

	return NULL;
}

void currentPlayerGetWeaponSway(struct coord *sway)
{
	struct weapon *weapon = weaponFindById(handGetWeaponNum(HAND_RIGHT));

	if (weapon) {
		sway->x = weapon->leftright;
		sway->y = weapon->updown;
		sway->z = weapon->frontback;
	}
}

void currentPlayerSetWeaponSway(struct coord *sway)
{
	struct weapon *weapon = weaponFindById(handGetWeaponNum(HAND_RIGHT));

	if (weapon) {
		weapon->leftright = sway->x;
		weapon->updown = sway->y;
		weapon->frontback = sway->z;
	}
}

f32 handGetXOffset(u32 hand)
{
	return g_Vars.currentplayer->hands[hand].xoffset;
}

f32 func0f0b131c(u32 hand)
{
	f32 x;
	struct weapon *weapon;

	if (hand == 0) {
		weapon = weaponFindById(getCurrentPlayerWeaponIdWrapper(0));
		x = weapon->leftright;

		if (PLAYERCOUNT() == 2 && optionsGetScreenSplit() == SCREENSPLIT_VERTICAL) {
			x -= 3.5f;

			if (g_Vars.currentplayernum == 0) {
				x += 2.0f;
			}
		}
	} else {
		weapon = weaponFindById(getCurrentPlayerWeaponIdWrapper(1));
		x = -weapon->leftright;

		if (PLAYERCOUNT() == 2 && optionsGetScreenSplit() == SCREENSPLIT_VERTICAL) {
			x += 3.5f;

			if (g_Vars.currentplayernum == 0) {
				x += 2.0f;
			}
		}
	}

	return x;
}

f32 currentPlayerGetGunZoomFov(void)
{
	s32 index = -1;
	struct weapon *weapon;

	switch (getCurrentPlayerWeaponIdWrapper(0)) {
	case WEAPON_SNIPERRIFLE:    index = 0; break;
	case WEAPON_FARSIGHTXR20:   index = 1; break;
	case WEAPON_HORIZONSCANNER: index = 2; break;
	}

	if (index >= 0) {
		return g_Vars.currentplayer->gunzoomfovs[index];
	}

	weapon = weaponFindById(getCurrentPlayerWeaponIdWrapper(0));

	if (weapon) {
		f32 fov = weapon->eptr->zoomfov;
		return fov;
	}

	return 0;
}

void currentPlayerZoomOut(f32 fovpersec)
{
	s32 index = -1;

	switch (getCurrentPlayerWeaponIdWrapper(0)) {
	case WEAPON_SNIPERRIFLE:    index = 0; break;
	case WEAPON_FARSIGHTXR20:   index = 1; break;
	case WEAPON_HORIZONSCANNER: index = 2; break;
	}

	if (index >= 0) {
		f32 amount = fovpersec * 0.25f * g_Vars.lvupdate240f;

		if (getCurrentPlayerWeaponIdWrapper(0) == WEAPON_FARSIGHTXR20) {
			amount *= 0.5f;
		}

		g_Vars.currentplayer->gunzoomfovs[index] *= 1.0f + amount * 0.1f;

		if (g_Vars.currentplayer->gunzoomfovs[index] > 60) {
			g_Vars.currentplayer->gunzoomfovs[index] = 60;
		}
	}
}

void currentPlayerZoomIn(f32 fovpersec)
{
	s32 index = -1;

	switch (getCurrentPlayerWeaponIdWrapper(0)) {
	case WEAPON_SNIPERRIFLE:    index = 0; break;
	case WEAPON_FARSIGHTXR20:   index = 1; break;
	case WEAPON_HORIZONSCANNER: index = 2; break;
	}

	if (index >= 0) {
		f32 amount = fovpersec * 0.25f * g_Vars.lvupdate240f;

		if (getCurrentPlayerWeaponIdWrapper(0) == WEAPON_FARSIGHTXR20) {
			amount *= 0.5f;
		}

		g_Vars.currentplayer->gunzoomfovs[index] /= 1 + amount * 0.1f;

		if (g_Vars.currentplayer->gunzoomfovs[index] < 2) {
			g_Vars.currentplayer->gunzoomfovs[index] = 2;
		}
	}
}

bool weaponHasFlag(s32 itemid, u32 flag)
{
	struct weapon *weapon = weaponFindById(itemid);

	if (!weapon) {
		return false;
	}

	return (weapon->flags & flag) != 0;
}

bool weaponHasInvEFlag(s32 weaponnum, u32 flag)
{
	struct weapon *weapon = weaponFindById(weaponnum);

	if (!weapon) {
		return false;
	}

	return (weapon->eptr->flags & flag) != 0;
}

GLOBAL_ASM(
glabel func0f0b184c
/*  f0b184c:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*  f0b1850:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f0b1854:	afa5001c */ 	sw	$a1,0x1c($sp)
/*  f0b1858:	0fc2c3f4 */ 	jal	weaponFindById
/*  f0b185c:	afa60020 */ 	sw	$a2,0x20($sp)
/*  f0b1860:	14400003 */ 	bnez	$v0,.L0f0b1870
/*  f0b1864:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f0b1868:	1000000e */ 	b	.L0f0b18a4
/*  f0b186c:	00001025 */ 	or	$v0,$zero,$zero
.L0f0b1870:
/*  f0b1870:	8fae001c */ 	lw	$t6,0x1c($sp)
/*  f0b1874:	8fa80020 */ 	lw	$t0,0x20($sp)
/*  f0b1878:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f0b187c:	004fc021 */ 	addu	$t8,$v0,$t7
/*  f0b1880:	8f03001c */ 	lw	$v1,0x1c($t8)
/*  f0b1884:	00001025 */ 	or	$v0,$zero,$zero
/*  f0b1888:	10600006 */ 	beqz	$v1,.L0f0b18a4
/*  f0b188c:	00000000 */ 	nop
/*  f0b1890:	90790010 */ 	lbu	$t9,0x10($v1)
/*  f0b1894:	03281024 */ 	and	$v0,$t9,$t0
/*  f0b1898:	0002482b */ 	sltu	$t1,$zero,$v0
/*  f0b189c:	10000001 */ 	b	.L0f0b18a4
/*  f0b18a0:	01201025 */ 	or	$v0,$t1,$zero
.L0f0b18a4:
/*  f0b18a4:	03e00008 */ 	jr	$ra
/*  f0b18a8:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*  f0b18ac:	03e00008 */ 	jr	$ra
/*  f0b18b0:	afa40000 */ 	sw	$a0,0x0($sp)
/*  f0b18b4:	03e00008 */ 	jr	$ra
/*  f0b18b8:	afa40000 */ 	sw	$a0,0x0($sp)
);

s32 currentPlayerGetDeviceState(s32 weaponnum)
{
	struct weapon *weapon = weaponFindById(weaponnum);
	s32 i;

	if (!weapon) {
		return DEVICESTATE_UNEQUIPPED;
	}

	for (i = 0; i < ARRAYCOUNT(weapon->functions); i++) {
		if (weapon->functions[i]) {
			struct weaponfunc_device *devicefunc = weapon->functions[i];

			if ((devicefunc->base.type & 0xff) == INVENTORYFUNCTYPE_DEVICE) {
				if ((g_Vars.currentplayer->devicesactive & devicefunc->device) == 0) {
					return DEVICESTATE_INACTIVE;
				}

				return DEVICESTATE_ACTIVE;
			}
		}
	}

	return DEVICESTATE_UNEQUIPPED;
}

void currentPlayerSetDeviceActive(s32 weaponnum, bool active)
{
	struct weapon *weapon = weaponFindById(weaponnum);
	s32 i;

	if (!weapon) {
		return;
	}

	for (i = 0; i < ARRAYCOUNT(weapon->functions); i++) {
		if (weapon->functions[i]) {
			struct weaponfunc_device *devicefunc = weapon->functions[i];

			if ((devicefunc->base.type & 0xff) == INVENTORYFUNCTYPE_DEVICE) {
				if (active) {
					if (devicefunc->device & (DEVICE_NIGHTVISION | DEVICE_XRAYSCANNER | DEVICE_EYESPY | DEVICE_IRSCANNER)) {
						g_Vars.currentplayer->devicesactive &= ~(DEVICE_NIGHTVISION | DEVICE_XRAYSCANNER | DEVICE_EYESPY | DEVICE_IRSCANNER);
					}

					g_Vars.currentplayer->devicesactive |= devicefunc->device;
					return;
				}

				g_Vars.currentplayer->devicesactive &= ~devicefunc->device;
				return;
			}
		}
	}
}

u16 weaponGetModelNum(s32 weaponnum)
{
	struct weapon *weapon = NULL;

	if (weaponnum != -1) {
		weapon = g_Weapons[weaponnum];
	}

	if (weapon) {
		if (PLAYERCOUNT() >= 2) {
			return weapon->lo_model;
		}

		return weapon->hi_model;
	}

	return 0;
}

u16 weaponGetModelNum2(s32 weaponnum)
{
	return weaponGetModelNum(weaponnum);
}

GLOBAL_ASM(
glabel func0f0b1af0
/*  f0b1af0:	3c06800a */ 	lui	$a2,%hi(g_Vars)
/*  f0b1af4:	24c69fc0 */ 	addiu	$a2,$a2,%lo(g_Vars)
/*  f0b1af8:	8cce0284 */ 	lw	$t6,0x284($a2)
/*  f0b1afc:	00041100 */ 	sll	$v0,$a0,0x4
/*  f0b1b00:	00441023 */ 	subu	$v0,$v0,$a0
/*  f0b1b04:	81cf1580 */ 	lb	$t7,0x1580($t6)
/*  f0b1b08:	00021080 */ 	sll	$v0,$v0,0x2
/*  f0b1b0c:	00441021 */ 	addu	$v0,$v0,$a0
/*  f0b1b10:	a0af0000 */ 	sb	$t7,0x0($a1)
/*  f0b1b14:	8cd80284 */ 	lw	$t8,0x284($a2)
/*  f0b1b18:	000210c0 */ 	sll	$v0,$v0,0x3
/*  f0b1b1c:	00441021 */ 	addu	$v0,$v0,$a0
/*  f0b1b20:	00021080 */ 	sll	$v0,$v0,0x2
/*  f0b1b24:	0302c821 */ 	addu	$t9,$t8,$v0
/*  f0b1b28:	9328063b */ 	lbu	$t0,0x63b($t9)
/*  f0b1b2c:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0b1b30:	31e300ff */ 	andi	$v1,$t7,0xff
/*  f0b1b34:	a0a80003 */ 	sb	$t0,0x3($a1)
/*  f0b1b38:	8cc90284 */ 	lw	$t1,0x284($a2)
/*  f0b1b3c:	01225021 */ 	addu	$t2,$t1,$v0
/*  f0b1b40:	914b063a */ 	lbu	$t3,0x63a($t2)
/*  f0b1b44:	a0ab0002 */ 	sb	$t3,0x2($a1)
/*  f0b1b48:	8ccc0284 */ 	lw	$t4,0x284($a2)
/*  f0b1b4c:	01826821 */ 	addu	$t5,$t4,$v0
/*  f0b1b50:	91ae0639 */ 	lbu	$t6,0x639($t5)
/*  f0b1b54:	1461002a */ 	bne	$v1,$at,.L0f0b1c00
/*  f0b1b58:	a0ae0001 */ 	sb	$t6,0x1($a1)
/*  f0b1b5c:	8ccf0284 */ 	lw	$t7,0x284($a2)
/*  f0b1b60:	3c014120 */ 	lui	$at,0x4120
/*  f0b1b64:	44813000 */ 	mtc1	$at,$f6
/*  f0b1b68:	01e2c021 */ 	addu	$t8,$t7,$v0
/*  f0b1b6c:	c7040874 */ 	lwc1	$f4,0x874($t8)
/*  f0b1b70:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f0b1b74:	3c014f00 */ 	lui	$at,0x4f00
/*  f0b1b78:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f0b1b7c:	4459f800 */ 	cfc1	$t9,$31
/*  f0b1b80:	44c8f800 */ 	ctc1	$t0,$31
/*  f0b1b84:	00000000 */ 	nop
/*  f0b1b88:	460042a4 */ 	cvt.w.s	$f10,$f8
/*  f0b1b8c:	4448f800 */ 	cfc1	$t0,$31
/*  f0b1b90:	00000000 */ 	nop
/*  f0b1b94:	31080078 */ 	andi	$t0,$t0,0x78
/*  f0b1b98:	51000013 */ 	beqzl	$t0,.L0f0b1be8
/*  f0b1b9c:	44085000 */ 	mfc1	$t0,$f10
/*  f0b1ba0:	44815000 */ 	mtc1	$at,$f10
/*  f0b1ba4:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f0b1ba8:	460a4281 */ 	sub.s	$f10,$f8,$f10
/*  f0b1bac:	44c8f800 */ 	ctc1	$t0,$31
/*  f0b1bb0:	00000000 */ 	nop
/*  f0b1bb4:	460052a4 */ 	cvt.w.s	$f10,$f10
/*  f0b1bb8:	4448f800 */ 	cfc1	$t0,$31
/*  f0b1bbc:	00000000 */ 	nop
/*  f0b1bc0:	31080078 */ 	andi	$t0,$t0,0x78
/*  f0b1bc4:	15000005 */ 	bnez	$t0,.L0f0b1bdc
/*  f0b1bc8:	00000000 */ 	nop
/*  f0b1bcc:	44085000 */ 	mfc1	$t0,$f10
/*  f0b1bd0:	3c018000 */ 	lui	$at,0x8000
/*  f0b1bd4:	10000007 */ 	b	.L0f0b1bf4
/*  f0b1bd8:	01014025 */ 	or	$t0,$t0,$at
.L0f0b1bdc:
/*  f0b1bdc:	10000005 */ 	b	.L0f0b1bf4
/*  f0b1be0:	2408ffff */ 	addiu	$t0,$zero,-1
/*  f0b1be4:	44085000 */ 	mfc1	$t0,$f10
.L0f0b1be8:
/*  f0b1be8:	00000000 */ 	nop
/*  f0b1bec:	0500fffb */ 	bltz	$t0,.L0f0b1bdc
/*  f0b1bf0:	00000000 */ 	nop
.L0f0b1bf4:
/*  f0b1bf4:	44d9f800 */ 	ctc1	$t9,$31
/*  f0b1bf8:	a0a80002 */ 	sb	$t0,0x2($a1)
/*  f0b1bfc:	90a30000 */ 	lbu	$v1,0x0($a1)
.L0f0b1c00:
/*  f0b1c00:	2401001d */ 	addiu	$at,$zero,0x1d
/*  f0b1c04:	14610005 */ 	bne	$v1,$at,.L0f0b1c1c
/*  f0b1c08:	00000000 */ 	nop
/*  f0b1c0c:	8cc90284 */ 	lw	$t1,0x284($a2)
/*  f0b1c10:	01225021 */ 	addu	$t2,$t1,$v0
/*  f0b1c14:	8d4c0b90 */ 	lw	$t4,0xb90($t2)
/*  f0b1c18:	a0ac0002 */ 	sb	$t4,0x2($a1)
.L0f0b1c1c:
/*  f0b1c1c:	03e00008 */ 	jr	$ra
/*  f0b1c20:	00000000 */ 	nop
);

struct inventory_ammo *handGetAmmoDefinition(struct hand *hand)
{
	struct weaponfunc *func = handGetWeaponFunction(hand);
	struct weapon *weapon = weaponFindById(hand->weaponnum);

	if (func && func->ammoindex >= 0) {
		return weapon->ammos[func->ammoindex];
	}

	return NULL;
}

u8 handGetSingleUnk3c(struct hand *hand)
{
	struct weaponfunc *func = handGetWeaponFunction(hand);

	if (func && (func->type & 0xff) == INVENTORYFUNCTYPE_SHOOT_SINGLE) {
		struct weaponfunc_shootsingle *funcshoot = (struct weaponfunc_shootsingle *)func;
		return funcshoot->unk3c;
	}

	return 0;
}

u32 handGetCasingEject(struct hand *hand)
{
	u32 result = 0;
	struct inventory_ammo *ammo = handGetAmmoDefinition(hand);

	if (ammo) {
		result = ammo->casingeject;
	}

	return result;
}

f32 handGetSingleUnk34(struct hand *hand)
{
	struct weaponfunc *func = handGetWeaponFunction(hand);
	f32 result = 0;

	if (func && (func->type & 0xff) == INVENTORYFUNCTYPE_SHOOT_SINGLE) {
		struct weaponfunc_shootsingle *funcshoot = (struct weaponfunc_shootsingle *)func;
		result = funcshoot->unk34;
	}

	return result;
}

GLOBAL_ASM(
glabel func0f0b1d28
/*  f0b1d28:	27bdffe0 */ 	addiu	$sp,$sp,-32
/*  f0b1d2c:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f0b1d30:	0fc2c41f */ 	jal	handGetWeaponFunction
/*  f0b1d34:	afa40020 */ 	sw	$a0,0x20($sp)
/*  f0b1d38:	44801000 */ 	mtc1	$zero,$f2
/*  f0b1d3c:	10400016 */ 	beqz	$v0,.L0f0b1d98
/*  f0b1d40:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f0b1d44:	8c430000 */ 	lw	$v1,0x0($v0)
/*  f0b1d48:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0b1d4c:	306e00ff */ 	andi	$t6,$v1,0xff
/*  f0b1d50:	15c10002 */ 	bne	$t6,$at,.L0f0b1d5c
/*  f0b1d54:	01c01825 */ 	or	$v1,$t6,$zero
/*  f0b1d58:	c442001c */ 	lwc1	$f2,0x1c($v0)
.L0f0b1d5c:
/*  f0b1d5c:	24010003 */ 	addiu	$at,$zero,0x3
/*  f0b1d60:	5461000a */ 	bnel	$v1,$at,.L0f0b1d8c
/*  f0b1d64:	24010002 */ 	addiu	$at,$zero,0x2
/*  f0b1d68:	908f0000 */ 	lbu	$t7,0x0($a0)
/*  f0b1d6c:	24010014 */ 	addiu	$at,$zero,0x14
/*  f0b1d70:	c4420014 */ 	lwc1	$f2,0x14($v0)
/*  f0b1d74:	15e10004 */ 	bne	$t7,$at,.L0f0b1d88
/*  f0b1d78:	3c01800a */ 	lui	$at,%hi(g_Vars+0x44)
/*  f0b1d7c:	c424a004 */ 	lwc1	$f4,%lo(g_Vars+0x44)($at)
/*  f0b1d80:	46041082 */ 	mul.s	$f2,$f2,$f4
/*  f0b1d84:	00000000 */ 	nop
.L0f0b1d88:
/*  f0b1d88:	24010002 */ 	addiu	$at,$zero,0x2
.L0f0b1d8c:
/*  f0b1d8c:	54610003 */ 	bnel	$v1,$at,.L0f0b1d9c
/*  f0b1d90:	90980000 */ 	lbu	$t8,0x0($a0)
/*  f0b1d94:	c4420020 */ 	lwc1	$f2,0x20($v0)
.L0f0b1d98:
/*  f0b1d98:	90980000 */ 	lbu	$t8,0x0($a0)
.L0f0b1d9c:
/*  f0b1d9c:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0b1da0:	57010012 */ 	bnel	$t8,$at,.L0f0b1dec
/*  f0b1da4:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f0b1da8:	90990002 */ 	lbu	$t9,0x2($a0)
/*  f0b1dac:	3c014f80 */ 	lui	$at,0x4f80
/*  f0b1db0:	44993000 */ 	mtc1	$t9,$f6
/*  f0b1db4:	07210004 */ 	bgez	$t9,.L0f0b1dc8
/*  f0b1db8:	46803220 */ 	cvt.s.w	$f8,$f6
/*  f0b1dbc:	44815000 */ 	mtc1	$at,$f10
/*  f0b1dc0:	00000000 */ 	nop
/*  f0b1dc4:	460a4200 */ 	add.s	$f8,$f8,$f10
.L0f0b1dc8:
/*  f0b1dc8:	3c014040 */ 	lui	$at,0x4040
/*  f0b1dcc:	44818000 */ 	mtc1	$at,$f16
/*  f0b1dd0:	3c013f80 */ 	lui	$at,0x3f80
/*  f0b1dd4:	44812000 */ 	mtc1	$at,$f4
/*  f0b1dd8:	46104483 */ 	div.s	$f18,$f8,$f16
/*  f0b1ddc:	46049180 */ 	add.s	$f6,$f18,$f4
/*  f0b1de0:	46023082 */ 	mul.s	$f2,$f6,$f2
/*  f0b1de4:	00000000 */ 	nop
/*  f0b1de8:	24040001 */ 	addiu	$a0,$zero,0x1
.L0f0b1dec:
/*  f0b1dec:	0fc2883f */ 	jal	handIsAttackingOnThisTick
/*  f0b1df0:	e7a20018 */ 	swc1	$f2,0x18($sp)
/*  f0b1df4:	10400007 */ 	beqz	$v0,.L0f0b1e14
/*  f0b1df8:	c7a20018 */ 	lwc1	$f2,0x18($sp)
/*  f0b1dfc:	00002025 */ 	or	$a0,$zero,$zero
/*  f0b1e00:	0fc2883f */ 	jal	handIsAttackingOnThisTick
/*  f0b1e04:	e7a20018 */ 	swc1	$f2,0x18($sp)
/*  f0b1e08:	10400002 */ 	beqz	$v0,.L0f0b1e14
/*  f0b1e0c:	c7a20018 */ 	lwc1	$f2,0x18($sp)
/*  f0b1e10:	46021080 */ 	add.s	$f2,$f2,$f2
.L0f0b1e14:
/*  f0b1e14:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f0b1e18:	27bd0020 */ 	addiu	$sp,$sp,0x20
/*  f0b1e1c:	46001006 */ 	mov.s	$f0,$f2
/*  f0b1e20:	03e00008 */ 	jr	$ra
/*  f0b1e24:	00000000 */ 	nop
);

u8 handGetSingleUnk38(struct hand *hand)
{
	struct weaponfunc *func = handGetWeaponFunction(hand);

	if (func && (func->type & 0xff) == INVENTORYFUNCTYPE_SHOOT_SINGLE) {
		struct weaponfunc_shootsingle *funcshoot = (struct weaponfunc_shootsingle *)func;
		return funcshoot->unk38;
	}

	return 0;
}

u16 handGetSingleShootSound(struct hand *hand)
{
	struct weaponfunc *func = handGetWeaponFunction(hand);

	if (func && (func->type & 0xff) == INVENTORYFUNCTYPE_SHOOT_SINGLE) {
		struct weaponfunc_shootsingle *funcshoot = (struct weaponfunc_shootsingle *)func;
		return funcshoot->shootsound;
	}

	return 0;
}

bool handHasFunctionFlags(struct hand *hand, u32 flags)
{
	struct weaponfunc *func = handGetWeaponFunction(hand);

	if (func) {
		return (func->flags & flags) == flags;
	}

	return false;
}

s8 weaponGetMaxFireRatePerTick(u32 weaponnum, u32 funcindex)
{
	u32 stack[2];
	s32 result = 0;
	struct weapon *weapon = weaponFindById(weaponnum);
	struct weaponfunc *func = weapon->functions[funcindex];

	if (func && func->type == INVENTORYFUNCTYPE_SHOOT_AUTOMATIC) {
		struct weaponfunc_shootauto *autofunc = (struct weaponfunc_shootauto *)func;

		result = 3600.0f / autofunc->maxfirerate;
	}

	return result;
}

u32 currentPlayerGetSight(void)
{
	struct weaponfunc *func = weaponGetFunctionById(
			g_Vars.currentplayer->hands[HAND_RIGHT].weaponnum,
			g_Vars.currentplayer->hands[HAND_RIGHT].weaponfunc);

	if (func && (func->type & 0xff) == INVENTORYFUNCTYPE_CLOSE) {
		return SIGHT_NONE;
	}

	if (cheatIsActive(CHEAT_CLASSICSIGHT)) {
		return SIGHT_CLASSIC;
	}

	switch (g_Vars.currentplayer->hands[HAND_RIGHT].weaponnum) {
	case WEAPON_HORIZONSCANNER:
		return SIGHT_NONE;
	case WEAPON_NONE:
	case WEAPON_UNARMED:
	case WEAPON_FALCON2:
	case WEAPON_FALCON2_SILENCER:
	case WEAPON_DY357MAGNUM:
	case WEAPON_DY357LX:
	case WEAPON_CMP150:
	case WEAPON_CYCLONE:
	case WEAPON_RCP120:
	case WEAPON_SHOTGUN:
	case WEAPON_DEVASTATOR:
	case WEAPON_ROCKETLAUNCHER:
	case WEAPON_SLAYER:
	case WEAPON_COMBATKNIFE:
	case WEAPON_CROSSBOW:
	case WEAPON_TRANQUILIZER:
	case WEAPON_LASER:
	case WEAPON_GRENADE:
	case WEAPON_NBOMB:
	case WEAPON_TIMEDMINE:
	case WEAPON_PROXIMITYMINE:
	case WEAPON_REMOTEMINE:
	case WEAPON_ECMMINE:
		return SIGHT_DEFAULT;
	case WEAPON_FALCON2_SCOPE:
	case WEAPON_MAGSEC4:
	case WEAPON_SNIPERRIFLE:
	case WEAPON_LAPTOPGUN:
	case WEAPON_DRAGON:
	case WEAPON_K7AVENGER:
	case WEAPON_AR34:
	case WEAPON_SUPERDRAGON:
		return SIGHT_ZOOM;
	case WEAPON_MAULER:
	case WEAPON_REAPER:
		return SIGHT_SKEDAR;
	case WEAPON_PHOENIX:
	case WEAPON_CALLISTONTG:
	case WEAPON_FARSIGHTXR20:
		return SIGHT_MAIAN;
	case WEAPON_PP9I:
	case WEAPON_CC13:
	case WEAPON_KL01313:
	case WEAPON_KF7SPECIAL:
	case WEAPON_ZZT:
	case WEAPON_DMC:
	case WEAPON_AR53:
	case WEAPON_RCP45:
		return SIGHT_CLASSIC;
	}

	return SIGHT_DEFAULT;
}

GLOBAL_ASM(
glabel func0f0b201c
/*  f0b201c:	27bdffe0 */ 	addiu	$sp,$sp,-32
/*  f0b2020:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f0b2024:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f0b2028:	0fc2c41f */ 	jal	handGetWeaponFunction
/*  f0b202c:	afa50024 */ 	sw	$a1,0x24($sp)
/*  f0b2030:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f0b2034:	10400002 */ 	beqz	$v0,.L0f0b2040
/*  f0b2038:	8fa50024 */ 	lw	$a1,0x24($sp)
/*  f0b203c:	8c430008 */ 	lw	$v1,0x8($v0)
.L0f0b2040:
/*  f0b2040:	54600004 */ 	bnezl	$v1,.L0f0b2054
/*  f0b2044:	c4640000 */ 	lwc1	$f4,0x0($v1)
/*  f0b2048:	3c038007 */ 	lui	$v1,%hi(invmenupos_00010fd0)
/*  f0b204c:	2463afb0 */ 	addiu	$v1,$v1,%lo(invmenupos_00010fd0)
/*  f0b2050:	c4640000 */ 	lwc1	$f4,0x0($v1)
.L0f0b2054:
/*  f0b2054:	e4a40000 */ 	swc1	$f4,0x0($a1)
/*  f0b2058:	c4660004 */ 	lwc1	$f6,0x4($v1)
/*  f0b205c:	e4a60004 */ 	swc1	$f6,0x4($a1)
/*  f0b2060:	c4680008 */ 	lwc1	$f8,0x8($v1)
/*  f0b2064:	e4a80008 */ 	swc1	$f8,0x8($a1)
/*  f0b2068:	c46a000c */ 	lwc1	$f10,0xc($v1)
/*  f0b206c:	e4aa000c */ 	swc1	$f10,0xc($a1)
/*  f0b2070:	c4700010 */ 	lwc1	$f16,0x10($v1)
/*  f0b2074:	e4b00010 */ 	swc1	$f16,0x10($a1)
/*  f0b2078:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f0b207c:	27bd0020 */ 	addiu	$sp,$sp,0x20
/*  f0b2080:	03e00008 */ 	jr	$ra
/*  f0b2084:	00000000 */ 	nop
/*  f0b2088:	908e0000 */ 	lbu	$t6,0x0($a0)
/*  f0b208c:	3c038007 */ 	lui	$v1,%hi(g_Weapons)
/*  f0b2090:	00001025 */ 	or	$v0,$zero,$zero
/*  f0b2094:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f0b2098:	006f1821 */ 	addu	$v1,$v1,$t7
/*  f0b209c:	8c63ff18 */ 	lw	$v1,%lo(g_Weapons)($v1)
/*  f0b20a0:	10600003 */ 	beqz	$v1,.L0f0b20b0
/*  f0b20a4:	00000000 */ 	nop
/*  f0b20a8:	03e00008 */ 	jr	$ra
/*  f0b20ac:	8c620004 */ 	lw	$v0,0x4($v1)
.L0f0b20b0:
/*  f0b20b0:	03e00008 */ 	jr	$ra
/*  f0b20b4:	00000000 */ 	nop
/*  f0b20b8:	908e0000 */ 	lbu	$t6,0x0($a0)
/*  f0b20bc:	3c038007 */ 	lui	$v1,%hi(g_Weapons)
/*  f0b20c0:	00001025 */ 	or	$v0,$zero,$zero
/*  f0b20c4:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f0b20c8:	006f1821 */ 	addu	$v1,$v1,$t7
/*  f0b20cc:	8c63ff18 */ 	lw	$v1,%lo(g_Weapons)($v1)
/*  f0b20d0:	10600003 */ 	beqz	$v1,.L0f0b20e0
/*  f0b20d4:	00000000 */ 	nop
/*  f0b20d8:	03e00008 */ 	jr	$ra
/*  f0b20dc:	8c620008 */ 	lw	$v0,0x8($v1)
.L0f0b20e0:
/*  f0b20e0:	03e00008 */ 	jr	$ra
/*  f0b20e4:	00000000 */ 	nop
);

u32 *handGetPriToSecAnim(struct hand *hand)
{
	struct weapon *weapon = g_Weapons[hand->weaponnum];

	if (weapon) {
		return weapon->pritosec_animation;
	}

	return NULL;
}

u32 *handGetSecToPriAnim(struct hand *hand)
{
	struct weapon *weapon = g_Weapons[hand->weaponnum];

	if (weapon) {
		return weapon->sectopri_animation;
	}

	return NULL;
}