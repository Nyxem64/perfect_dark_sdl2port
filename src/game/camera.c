#include <ultra64.h>
#include "constants.h"
#include "game/atan2f.h"
#include "game/camera.h"
#include "game/tex.h"
#include "game/playermgr.h"
#include "game/bg.h"
#include "game/texdecompress.h"
#include "bss.h"
#include "lib/mtx.h"
#include "data.h"
#include "types.h"

struct coord var8009dd20;
f32 var8009dd2c;
struct coord var8009dd30;
f32 var8009dd3c;
struct coord var8009dd40;
f32 var8009dd4c;
struct coord var8009dd50;
f32 var8009dd5c;
struct coord var8009dd60;
f32 var8009dd6c;

void cam0f0b4950(void)
{
	// empty
}

void camSetScreenSize(f32 width, f32 height)
{
	struct player *player = g_Vars.currentplayer;

	player->c_screenwidth = width;
	player->c_screenheight = height;
	player->c_halfwidth = width * 0.5f;
	player->c_halfheight = height * 0.5f;
}

void camSetScreenPosition(f32 left, f32 top)
{
	struct player *player = g_Vars.currentplayer;

	player->c_screenleft = left;
	player->c_screentop = top;
}

void camSetPerspective(f32 near, f32 fovy, f32 aspect)
{
	struct player *player = g_Vars.currentplayer;

	player->c_perspnear = near;
	player->c_perspfovy = fovy;
	player->c_perspaspect = aspect;
}

f32 cam0f0b49b8(f32 arg0)
{
	f32 result = atan2f(g_Vars.currentplayer->c_scalelod60 * arg0 * g_Vars.currentplayer->c_halfheight, 1.0f);
	result *= 114.591552f;

	if (result < 0) {
		result = -result;
	}

	return result;
}

void camSetScale(void)
{
	struct player *player = g_Vars.currentplayer;
	f32 fVar4;
	f32 tmp;
	f32 fVar5;
	f32 fVar2;

	player->c_scaley = sinf(player->c_perspfovy * (M_PI / 360.0f)) / (cosf(player->c_perspfovy * (M_PI / 360.0f)) * player->c_halfheight);
	player->c_scalelod = player->c_scaley;
	player->c_scalex = (player->c_scaley * player->c_perspaspect * player->c_halfheight) / player->c_halfwidth;

	player->c_recipscalex = 1.0f / player->c_scalex;
	player->c_recipscaley = 1.0f / player->c_scaley;

	fVar4 = sinf(0.52359879016876f) / (cosf(0.52359879016876f) * 120.0f);
	player->c_scalelod60 = fVar4;
	player->c_lodscalez = player->c_scalelod / fVar4;
	tmp = player->c_lodscalez * 65536.0f;

	if (tmp > 4294967296.0f) {
		player->c_lodscalezu32 = 0xffffffff;
	} else {
		player->c_lodscalezu32 = tmp;
	}

	fVar2 = player->c_halfheight * player->c_scaley;
	fVar4 = 1.0f / sqrtf(fVar2 * fVar2 + 1.0f);
	player->c_cameratopnorm.x = 0;
	player->c_cameratopnorm.y = fVar4;
	player->c_cameratopnorm.z = fVar2 * fVar4;

	fVar5 = -player->c_halfwidth * player->c_scalex;
	fVar4 = 1.0f / sqrtf(fVar5 * fVar5 + 1.0f);
	player->c_cameraleftnorm.x = -fVar4;
	player->c_cameraleftnorm.y = 0;
	player->c_cameraleftnorm.z = -fVar5 * fVar4;
}

void cam0f0b4c3c(f32 *crosspos, struct coord *dst, f32 arg2)
{
	struct player *player = g_Vars.currentplayer;
	f32 sp20;
	f32 sp1c;
	f32 sp18 = -1.0f;
	f32 f2;

	sp1c = (player->c_halfheight - (crosspos[1] - player->c_screentop)) * player->c_scaley;
	sp20 = (crosspos[0] - player->c_screenleft - player->c_halfwidth) * player->c_scalex;

	f2 = arg2 / sqrtf(sp20 * sp20 + sp1c * sp1c + sp18 * sp18);

	dst->x = sp20 * f2;
	dst->y = sp1c * f2;
	dst->z = sp18 * f2;
}

void cam0f0b4d04(struct coord *in, f32 *out)
{
	struct player *player = g_Vars.currentplayer;
	f32 value = 1.0f / in->z;

	out[1] = in->y * value * player->c_recipscaley
		+ (player->c_screentop + player->c_halfheight);

	out[0] = (player->c_screenleft + player->c_halfwidth)
		- in->x * value * player->c_recipscalex;
}

void cam0f0b4d68(struct coord *in, f32 out[2])
{
	struct player *player = g_Vars.currentplayer;
	f32 value;

	if (in->z == 0.0f) {
		value = -100000000000000000000.0f;
	} else {
		value = 1.0f / in->z;
	}

	out[1] = in->y * value * player->c_recipscaley + (player->c_screentop + player->c_halfheight);
	out[0] = (player->c_screenleft + player->c_halfwidth) - in->x * value * player->c_recipscalex;
}

void cam0f0b4dec(struct coord *in, f32 out[2])
{
	struct player *player = g_Vars.currentplayer;
	f32 value = 1.0f / in->z;

	if (value < 0) {
		value = -value;
	}

	out[1] = in->y * value * player->c_recipscaley + (player->c_screentop + player->c_halfheight);
	out[0] = (player->c_screenleft + player->c_halfwidth) - in->x * value * player->c_recipscalex;
}

void cam0f0b4e68(struct coord *in, f32 divisor, struct coord *out)
{
	out->y = in->y * (1.0f / divisor) * g_Vars.currentplayer->c_recipscaley;
	out->x = in->x * (1.0f / divisor) * g_Vars.currentplayer->c_recipscalex;
}

void cam0f0b4eb8(struct coord *arg0, f32 arg1[2], f32 zoom, f32 aspect)
{
	f32 f12;
	f32 f14;
	struct player *player = g_Vars.currentplayer;

	f12 = cosf(zoom * 0.008726646f) * player->c_halfheight / (sinf(zoom * 0.008726646f) * arg0->f[2]);
	f14 = f12 * player->c_halfwidth / (aspect * player->c_halfheight);

	arg1[1] = f12 * arg0->f[1] + (player->c_screentop + player->c_halfheight);
	arg1[0] = player->c_screenleft + player->c_halfwidth - f14 * arg0->f[0];
}

void camSetUnk1738(void *value)
{
	g_Vars.currentplayer->unk1738 = value;
}

void *camGetUnk1738(void)
{
	return g_Vars.currentplayer->unk1738;
}

void camSetUnk173c(Mtx *matrix)
{
	g_Vars.currentplayer->unk173c = matrix;
}

Mtx *camGetUnk173c(void)
{
	return g_Vars.currentplayer->unk173c;
}

void camSetUnk006c(Mtxf *matrix)
{
	g_Vars.currentplayer->matrix6c = matrix;
}

Mtxf *camGetUnk006c(void)
{
	return g_Vars.currentplayer->matrix6c;
}

void camSetUnk1750(void *value)
{
	g_Vars.currentplayer->unk1750 = value;
}

void *camGetUnk1750(void)
{
	return g_Vars.currentplayer->unk1750;
}

void camSetUnk1758(Mtx *matrix)
{
	g_Vars.currentplayer->unk1758 = matrix;
}

Mtx *camGetUnk1758(void)
{
	return g_Vars.currentplayer->unk1758;
}

void camSetMatrix1740(Mtxf *matrix)
{
	struct player *player = g_Vars.currentplayer;

	player->prev1740 = player->matrix1740;
	player->matrix1740 = matrix;
	player->c_viewfmdynticknum = g_GfxNumSwaps;
	player->unk0488 = player->unk0484;
	player->unk0484 = g_GfxMemPos;
}

GLOBAL_ASM(
glabel cam0f0b5050
/*  f0b5050:	3c02800b */ 	lui	$v0,%hi(g_GfxActiveBufferIndex)
/*  f0b5054:	9042a5a0 */ 	lbu	$v0,%lo(g_GfxActiveBufferIndex)($v0)
/*  f0b5058:	3c03800b */ 	lui	$v1,%hi(g_VtxBuffers)
/*  f0b505c:	2463a590 */ 	addiu	$v1,$v1,%lo(g_VtxBuffers)
/*  f0b5060:	00027080 */ 	sll	$t6,$v0,0x2
/*  f0b5064:	27bdffb0 */ 	addiu	$sp,$sp,-80
/*  f0b5068:	006e7821 */ 	addu	$t7,$v1,$t6
/*  f0b506c:	8df80000 */ 	lw	$t8,0x0($t7)
/*  f0b5070:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f0b5074:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f0b5078:	0098082b */ 	sltu	$at,$a0,$t8
/*  f0b507c:	0080a025 */ 	or	$s4,$a0,$zero
/*  f0b5080:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f0b5084:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f0b5088:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f0b508c:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f0b5090:	1420005a */ 	bnez	$at,.L0f0b51fc
/*  f0b5094:	00009025 */ 	or	$s2,$zero,$zero
/*  f0b5098:	0002c880 */ 	sll	$t9,$v0,0x2
/*  f0b509c:	00794021 */ 	addu	$t0,$v1,$t9
/*  f0b50a0:	8d090004 */ 	lw	$t1,0x4($t0)
/*  f0b50a4:	3c10800a */ 	lui	$s0,%hi(g_Vars)
/*  f0b50a8:	26109fc0 */ 	addiu	$s0,$s0,%lo(g_Vars)
/*  f0b50ac:	0089082b */ 	sltu	$at,$a0,$t1
/*  f0b50b0:	10200052 */ 	beqz	$at,.L0f0b51fc
/*  f0b50b4:	00000000 */ 	nop
/*  f0b50b8:	8e0a006c */ 	lw	$t2,0x6c($s0)
/*  f0b50bc:	00008825 */ 	or	$s1,$zero,$zero
/*  f0b50c0:	00003025 */ 	or	$a2,$zero,$zero
/*  f0b50c4:	11400003 */ 	beqz	$t2,.L0f0b50d4
/*  f0b50c8:	00002025 */ 	or	$a0,$zero,$zero
/*  f0b50cc:	10000001 */ 	b	.L0f0b50d4
/*  f0b50d0:	24060001 */ 	addiu	$a2,$zero,0x1
.L0f0b50d4:
/*  f0b50d4:	8e0b0068 */ 	lw	$t3,0x68($s0)
/*  f0b50d8:	00001825 */ 	or	$v1,$zero,$zero
/*  f0b50dc:	00001025 */ 	or	$v0,$zero,$zero
/*  f0b50e0:	11600003 */ 	beqz	$t3,.L0f0b50f0
/*  f0b50e4:	3c138008 */ 	lui	$s3,%hi(g_GfxNumSwaps)
/*  f0b50e8:	10000001 */ 	b	.L0f0b50f0
/*  f0b50ec:	24040001 */ 	addiu	$a0,$zero,0x1
.L0f0b50f0:
/*  f0b50f0:	8e0c0064 */ 	lw	$t4,0x64($s0)
/*  f0b50f4:	26734008 */ 	addiu	$s3,$s3,%lo(g_GfxNumSwaps)
/*  f0b50f8:	11800003 */ 	beqz	$t4,.L0f0b5108
/*  f0b50fc:	00000000 */ 	nop
/*  f0b5100:	10000001 */ 	b	.L0f0b5108
/*  f0b5104:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f0b5108:
/*  f0b5108:	8e0d0070 */ 	lw	$t5,0x70($s0)
/*  f0b510c:	11a00003 */ 	beqz	$t5,.L0f0b511c
/*  f0b5110:	00000000 */ 	nop
/*  f0b5114:	10000001 */ 	b	.L0f0b511c
/*  f0b5118:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f0b511c:
/*  f0b511c:	00437021 */ 	addu	$t6,$v0,$v1
/*  f0b5120:	01c47821 */ 	addu	$t7,$t6,$a0
/*  f0b5124:	01e6c021 */ 	addu	$t8,$t7,$a2
/*  f0b5128:	5b000096 */ 	blezl	$t8,.L0f0b5384
/*  f0b512c:	8fbf002c */ 	lw	$ra,0x2c($sp)
.L0f0b5130:
/*  f0b5130:	0fc4a39e */ 	jal	playermgrGetOrderOfPlayer
/*  f0b5134:	02202025 */ 	or	$a0,$s1,$zero
/*  f0b5138:	8e190290 */ 	lw	$t9,0x290($s0)
/*  f0b513c:	00114080 */ 	sll	$t0,$s1,0x2
/*  f0b5140:	00003025 */ 	or	$a2,$zero,$zero
/*  f0b5144:	0322082a */ 	slt	$at,$t9,$v0
/*  f0b5148:	1420000d */ 	bnez	$at,.L0f0b5180
/*  f0b514c:	02084821 */ 	addu	$t1,$s0,$t0
/*  f0b5150:	8d220064 */ 	lw	$v0,0x64($t1)
/*  f0b5154:	8e6a0000 */ 	lw	$t2,0x0($s3)
/*  f0b5158:	8c4b1744 */ 	lw	$t3,0x1744($v0)
/*  f0b515c:	554b0009 */ 	bnel	$t2,$t3,.L0f0b5184
/*  f0b5160:	8e0c006c */ 	lw	$t4,0x6c($s0)
/*  f0b5164:	8c430484 */ 	lw	$v1,0x484($v0)
/*  f0b5168:	0283082b */ 	sltu	$at,$s4,$v1
/*  f0b516c:	14200004 */ 	bnez	$at,.L0f0b5180
/*  f0b5170:	0243082b */ 	sltu	$at,$s2,$v1
/*  f0b5174:	50200003 */ 	beqzl	$at,.L0f0b5184
/*  f0b5178:	8e0c006c */ 	lw	$t4,0x6c($s0)
/*  f0b517c:	8c521740 */ 	lw	$s2,0x1740($v0)
.L0f0b5180:
/*  f0b5180:	8e0c006c */ 	lw	$t4,0x6c($s0)
.L0f0b5184:
/*  f0b5184:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f0b5188:	00002025 */ 	or	$a0,$zero,$zero
/*  f0b518c:	11800003 */ 	beqz	$t4,.L0f0b519c
/*  f0b5190:	00001825 */ 	or	$v1,$zero,$zero
/*  f0b5194:	10000001 */ 	b	.L0f0b519c
/*  f0b5198:	24060001 */ 	addiu	$a2,$zero,0x1
.L0f0b519c:
/*  f0b519c:	8e0d0068 */ 	lw	$t5,0x68($s0)
/*  f0b51a0:	00001025 */ 	or	$v0,$zero,$zero
/*  f0b51a4:	11a00003 */ 	beqz	$t5,.L0f0b51b4
/*  f0b51a8:	00000000 */ 	nop
/*  f0b51ac:	10000001 */ 	b	.L0f0b51b4
/*  f0b51b0:	24040001 */ 	addiu	$a0,$zero,0x1
.L0f0b51b4:
/*  f0b51b4:	8e0e0064 */ 	lw	$t6,0x64($s0)
/*  f0b51b8:	11c00003 */ 	beqz	$t6,.L0f0b51c8
/*  f0b51bc:	00000000 */ 	nop
/*  f0b51c0:	10000001 */ 	b	.L0f0b51c8
/*  f0b51c4:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f0b51c8:
/*  f0b51c8:	8e0f0070 */ 	lw	$t7,0x70($s0)
/*  f0b51cc:	11e00003 */ 	beqz	$t7,.L0f0b51dc
/*  f0b51d0:	00000000 */ 	nop
/*  f0b51d4:	10000001 */ 	b	.L0f0b51dc
/*  f0b51d8:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f0b51dc:
/*  f0b51dc:	0043c021 */ 	addu	$t8,$v0,$v1
/*  f0b51e0:	0304c821 */ 	addu	$t9,$t8,$a0
/*  f0b51e4:	03264021 */ 	addu	$t0,$t9,$a2
/*  f0b51e8:	0228082a */ 	slt	$at,$s1,$t0
/*  f0b51ec:	1420ffd0 */ 	bnez	$at,.L0f0b5130
/*  f0b51f0:	00000000 */ 	nop
/*  f0b51f4:	10000063 */ 	b	.L0f0b5384
/*  f0b51f8:	8fbf002c */ 	lw	$ra,0x2c($sp)
.L0f0b51fc:
/*  f0b51fc:	3c10800a */ 	lui	$s0,%hi(g_Vars)
/*  f0b5200:	26109fc0 */ 	addiu	$s0,$s0,%lo(g_Vars)
/*  f0b5204:	8e09006c */ 	lw	$t1,0x6c($s0)
/*  f0b5208:	00008825 */ 	or	$s1,$zero,$zero
/*  f0b520c:	00003025 */ 	or	$a2,$zero,$zero
/*  f0b5210:	11200003 */ 	beqz	$t1,.L0f0b5220
/*  f0b5214:	00002025 */ 	or	$a0,$zero,$zero
/*  f0b5218:	10000001 */ 	b	.L0f0b5220
/*  f0b521c:	24060001 */ 	addiu	$a2,$zero,0x1
.L0f0b5220:
/*  f0b5220:	8e0a0068 */ 	lw	$t2,0x68($s0)
/*  f0b5224:	00001825 */ 	or	$v1,$zero,$zero
/*  f0b5228:	00001025 */ 	or	$v0,$zero,$zero
/*  f0b522c:	11400003 */ 	beqz	$t2,.L0f0b523c
/*  f0b5230:	0011c080 */ 	sll	$t8,$s1,0x2
/*  f0b5234:	10000001 */ 	b	.L0f0b523c
/*  f0b5238:	24040001 */ 	addiu	$a0,$zero,0x1
.L0f0b523c:
/*  f0b523c:	8e0b0064 */ 	lw	$t3,0x64($s0)
/*  f0b5240:	3c138008 */ 	lui	$s3,%hi(g_GfxNumSwaps)
/*  f0b5244:	26734008 */ 	addiu	$s3,$s3,%lo(g_GfxNumSwaps)
/*  f0b5248:	11600003 */ 	beqz	$t3,.L0f0b5258
/*  f0b524c:	02182821 */ 	addu	$a1,$s0,$t8
/*  f0b5250:	10000001 */ 	b	.L0f0b5258
/*  f0b5254:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f0b5258:
/*  f0b5258:	8e0c0070 */ 	lw	$t4,0x70($s0)
/*  f0b525c:	11800003 */ 	beqz	$t4,.L0f0b526c
/*  f0b5260:	00000000 */ 	nop
/*  f0b5264:	10000001 */ 	b	.L0f0b526c
/*  f0b5268:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f0b526c:
/*  f0b526c:	00436821 */ 	addu	$t5,$v0,$v1
/*  f0b5270:	01a47021 */ 	addu	$t6,$t5,$a0
/*  f0b5274:	01c67821 */ 	addu	$t7,$t6,$a2
/*  f0b5278:	19e00041 */ 	blez	$t7,.L0f0b5380
/*  f0b527c:	02202025 */ 	or	$a0,$s1,$zero
.L0f0b5280:
/*  f0b5280:	0fc4a39e */ 	jal	playermgrGetOrderOfPlayer
/*  f0b5284:	afa50034 */ 	sw	$a1,0x34($sp)
/*  f0b5288:	8e190290 */ 	lw	$t9,0x290($s0)
/*  f0b528c:	00003025 */ 	or	$a2,$zero,$zero
/*  f0b5290:	00002025 */ 	or	$a0,$zero,$zero
/*  f0b5294:	0322082a */ 	slt	$at,$t9,$v0
/*  f0b5298:	1420000f */ 	bnez	$at,.L0f0b52d8
/*  f0b529c:	8fa50034 */ 	lw	$a1,0x34($sp)
/*  f0b52a0:	8ca20064 */ 	lw	$v0,0x64($a1)
/*  f0b52a4:	8e680000 */ 	lw	$t0,0x0($s3)
/*  f0b52a8:	8c491764 */ 	lw	$t1,0x1764($v0)
/*  f0b52ac:	252a0001 */ 	addiu	$t2,$t1,0x1
/*  f0b52b0:	550a0017 */ 	bnel	$t0,$t2,.L0f0b5310
/*  f0b52b4:	8e0e006c */ 	lw	$t6,0x6c($s0)
/*  f0b52b8:	8c430488 */ 	lw	$v1,0x488($v0)
/*  f0b52bc:	0283082b */ 	sltu	$at,$s4,$v1
/*  f0b52c0:	14200012 */ 	bnez	$at,.L0f0b530c
/*  f0b52c4:	0243082b */ 	sltu	$at,$s2,$v1
/*  f0b52c8:	50200011 */ 	beqzl	$at,.L0f0b5310
/*  f0b52cc:	8e0e006c */ 	lw	$t6,0x6c($s0)
/*  f0b52d0:	1000000e */ 	b	.L0f0b530c
/*  f0b52d4:	8c521760 */ 	lw	$s2,0x1760($v0)
.L0f0b52d8:
/*  f0b52d8:	8ca20064 */ 	lw	$v0,0x64($a1)
/*  f0b52dc:	8e6b0000 */ 	lw	$t3,0x0($s3)
/*  f0b52e0:	8c4c1744 */ 	lw	$t4,0x1744($v0)
/*  f0b52e4:	258d0001 */ 	addiu	$t5,$t4,0x1
/*  f0b52e8:	556d0009 */ 	bnel	$t3,$t5,.L0f0b5310
/*  f0b52ec:	8e0e006c */ 	lw	$t6,0x6c($s0)
/*  f0b52f0:	8c430484 */ 	lw	$v1,0x484($v0)
/*  f0b52f4:	0283082b */ 	sltu	$at,$s4,$v1
/*  f0b52f8:	14200004 */ 	bnez	$at,.L0f0b530c
/*  f0b52fc:	0243082b */ 	sltu	$at,$s2,$v1
/*  f0b5300:	50200003 */ 	beqzl	$at,.L0f0b5310
/*  f0b5304:	8e0e006c */ 	lw	$t6,0x6c($s0)
/*  f0b5308:	8c521740 */ 	lw	$s2,0x1740($v0)
.L0f0b530c:
/*  f0b530c:	8e0e006c */ 	lw	$t6,0x6c($s0)
.L0f0b5310:
/*  f0b5310:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f0b5314:	24a50004 */ 	addiu	$a1,$a1,0x4
/*  f0b5318:	11c00003 */ 	beqz	$t6,.L0f0b5328
/*  f0b531c:	00001825 */ 	or	$v1,$zero,$zero
/*  f0b5320:	10000001 */ 	b	.L0f0b5328
/*  f0b5324:	24060001 */ 	addiu	$a2,$zero,0x1
.L0f0b5328:
/*  f0b5328:	8e0f0068 */ 	lw	$t7,0x68($s0)
/*  f0b532c:	00001025 */ 	or	$v0,$zero,$zero
/*  f0b5330:	11e00003 */ 	beqz	$t7,.L0f0b5340
/*  f0b5334:	00000000 */ 	nop
/*  f0b5338:	10000001 */ 	b	.L0f0b5340
/*  f0b533c:	24040001 */ 	addiu	$a0,$zero,0x1
.L0f0b5340:
/*  f0b5340:	8e180064 */ 	lw	$t8,0x64($s0)
/*  f0b5344:	13000003 */ 	beqz	$t8,.L0f0b5354
/*  f0b5348:	00000000 */ 	nop
/*  f0b534c:	10000001 */ 	b	.L0f0b5354
/*  f0b5350:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f0b5354:
/*  f0b5354:	8e190070 */ 	lw	$t9,0x70($s0)
/*  f0b5358:	13200003 */ 	beqz	$t9,.L0f0b5368
/*  f0b535c:	00000000 */ 	nop
/*  f0b5360:	10000001 */ 	b	.L0f0b5368
/*  f0b5364:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f0b5368:
/*  f0b5368:	00434821 */ 	addu	$t1,$v0,$v1
/*  f0b536c:	01244021 */ 	addu	$t0,$t1,$a0
/*  f0b5370:	01065021 */ 	addu	$t2,$t0,$a2
/*  f0b5374:	022a082a */ 	slt	$at,$s1,$t2
/*  f0b5378:	5420ffc1 */ 	bnezl	$at,.L0f0b5280
/*  f0b537c:	02202025 */ 	or	$a0,$s1,$zero
.L0f0b5380:
/*  f0b5380:	8fbf002c */ 	lw	$ra,0x2c($sp)
.L0f0b5384:
/*  f0b5384:	02401025 */ 	or	$v0,$s2,$zero
/*  f0b5388:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f0b538c:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f0b5390:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f0b5394:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f0b5398:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f0b539c:	03e00008 */ 	jr	$ra
/*  f0b53a0:	27bd0050 */ 	addiu	$sp,$sp,0x50
);

void *cam0f0b53a4(u8 *arg0)
{
	u8 *result = NULL;
	s32 i;

	if (arg0 >= g_VtxBuffers[g_GfxActiveBufferIndex] && arg0 < g_VtxBuffers[g_GfxActiveBufferIndex + 1]) {
		for (i = 0; i < PLAYERCOUNT(); i++) {
			if (g_Vars.currentplayerindex >= playermgrGetOrderOfPlayer(i)) {
				if (g_GfxNumSwaps == g_Vars.players[i]->c_viewfmdynticknum) {
					if (arg0 >= g_Vars.players[i]->unk0484 && result < g_Vars.players[i]->unk0484) {
						result = (u8 *)g_Vars.players[i]->unk174c;
					}
				}
			}
		}
	} else {
		for (i = 0; i < PLAYERCOUNT(); i++) {
			if (g_Vars.currentplayerindex >= playermgrGetOrderOfPlayer(i)) {
				if (g_GfxNumSwaps == g_Vars.players[i]->c_prevviewfmdynticknum + 1) {
					if (arg0 >= g_Vars.players[i]->unk0488 && result < g_Vars.players[i]->unk0488) {
						result = (u8 *)g_Vars.players[i]->unk1768;
					}
				}
			} else {
				if (g_GfxNumSwaps == g_Vars.players[i]->c_viewfmdynticknum + 1) {
					if (arg0 >= g_Vars.players[i]->unk0484 && result < g_Vars.players[i]->unk0484) {
						result = (u8 *)g_Vars.players[i]->unk174c;
					}
				}
			}
		}
	}

	return result;
}

Mtxf *camGetMatrix1740(void)
{
	return g_Vars.currentplayer->matrix1740;
}

void camSetUnk1754(Mtxf *matrix)
{
	g_Vars.currentplayer->unk1754 = matrix;
}

Mtxf *camGetUnk1754(void)
{
	return g_Vars.currentplayer->unk1754;
}

Mtxf *camGetPrevMatrix(void)
{
	return g_Vars.currentplayer->prev1740;
}

void camSetUnk1748(u32 value)
{
	g_Vars.currentplayer->unk1748 = value;
}

u32 camGetUnk1748(void)
{
	return g_Vars.currentplayer->unk1748;
}

void camSetUnk174c(Mtxf *matrix)
{
	struct player *player = g_Vars.currentplayer;

	player->c_prevviewfmdynticknum = player->c_viewfmdynticknum;
	player->unk1768 = player->unk174c;
	player->unk174c = matrix;
}

Mtxf *camGetUnk174c(void)
{
	return g_Vars.currentplayer->unk174c;
}

Mtxf *camGetUnk1768(void)
{
	return g_Vars.currentplayer->unk1768;
}

void camSetUnk175c(Mtxf *mtx)
{
	g_Vars.currentplayer->unk175c = mtx;
}

Mtxf *camGetUnk175c(void)
{
	return g_Vars.currentplayer->unk175c;
}

f32 camGetLodScaleZ(void)
{
	return g_Vars.currentplayer->c_lodscalez;
}

u32 camGetLodScaleZU32(void)
{
	return g_Vars.currentplayer->c_lodscalezu32;
}

f32 camGetScreenWidth(void)
{
	return g_Vars.currentplayer->c_screenwidth;
}

f32 camGetScreenHeight(void)
{
	return g_Vars.currentplayer->c_screenheight;
}

f32 camGetScreenLeft(void)
{
	return g_Vars.currentplayer->c_screenleft;
}

f32 camGetScreenTop(void)
{
	return g_Vars.currentplayer->c_screentop;
}

f32 camGetPerspFovY(void)
{
	return g_Vars.currentplayer->c_perspfovy;
}

f32 camGetPerspAspect(void)
{
	return g_Vars.currentplayer->c_perspaspect;
}

void cam0f0b5838(void)
{
	f32 sp2c;
	f32 sp28;
	f32 sp24;
	f32 sp20;
	struct player *player;
	Mtxf *mtx;
	f32 sp14;
	f32 sp10;

	player = g_Vars.currentplayer;
	sp24 = player->c_halfheight * player->c_scaley;
	mtx = player->unk174c;

	sp2c = 1.0f / sqrtf(sp24 * sp24 + 1.0f);
	sp24 *= sp2c;
	sp20 = -sp2c;

	var8009dd20.f[0] = -sp20 * mtx->m[1][0] + (sp24) * mtx->m[2][0];
	var8009dd20.f[1] = -sp20 * mtx->m[1][1] + (sp24) * mtx->m[2][1];
	var8009dd20.f[2] = -sp20 * mtx->m[1][2] + (sp24) * mtx->m[2][2];

	var8009dd2c = var8009dd20.f[0] * mtx->m[3][0] + var8009dd20.f[1] * mtx->m[3][1] + var8009dd20.f[2] * mtx->m[3][2];

	var8009dd30.f[0] = sp20 * mtx->m[1][0] + (sp24) * mtx->m[2][0];
	var8009dd30.f[1] = sp20 * mtx->m[1][1] + (sp24) * mtx->m[2][1];
	var8009dd30.f[2] = sp20 * mtx->m[1][2] + (sp24) * mtx->m[2][2];

	var8009dd3c = var8009dd30.f[0] * mtx->m[3][0] + var8009dd30.f[1] * mtx->m[3][1] + var8009dd30.f[2] * mtx->m[3][2];

	sp28 = -player->c_halfwidth * player->c_scalex;

	sp10 = 1.0f / sqrtf(sp28 * sp28 + 1.0f);
	sp28 *= sp10;
	sp14 = -sp10;

	var8009dd40.f[0] = sp14 * mtx->m[0][0] - sp28 * mtx->m[2][0];
	var8009dd40.f[1] = sp14 * mtx->m[0][1] - sp28 * mtx->m[2][1];
	var8009dd40.f[2] = sp14 * mtx->m[0][2] - sp28 * mtx->m[2][2];

	var8009dd4c = var8009dd40.f[0] * mtx->m[3][0] + var8009dd40.f[1] * mtx->m[3][1] + var8009dd40.f[2] * mtx->m[3][2];

	var8009dd50.f[0] = -sp14 * mtx->m[0][0] - sp28 * mtx->m[2][0];
	var8009dd50.f[1] = -sp14 * mtx->m[0][1] - sp28 * mtx->m[2][1];
	var8009dd50.f[2] = -sp14 * mtx->m[0][2] - sp28 * mtx->m[2][2];

	var8009dd5c = var8009dd50.f[0] * mtx->m[3][0] + var8009dd50.f[1] * mtx->m[3][1] + var8009dd50.f[2] * mtx->m[3][2];

	var8009dd60.f[0] = -mtx->m[3][0];
	var8009dd60.f[1] = -mtx->m[3][1];
	var8009dd60.f[2] = -mtx->m[3][2];

	var8009dd6c = mtx->m[2][0] * mtx->m[3][0] + mtx->m[2][1] * mtx->m[3][1] + mtx->m[2][2] * mtx->m[3][2];
}

bool cam0f0b5b9c(struct coord *arg0, f32 arg1)
{
	Mtxf *mtx = g_Vars.currentplayer->unk174c;

	if (var8009dd6c + arg1 < mtx->m[2][0] * arg0->f[0] + mtx->m[2][1] * arg0->f[1] + mtx->m[2][2] * arg0->f[2]) {
		return false;
	}

	if (var8009dd4c + arg1 < var8009dd40.f[0] * arg0->f[0] + var8009dd40.f[1] * arg0->f[1] + var8009dd40.f[2] * arg0->f[2]) {
		return false;
	}

	if (var8009dd5c + arg1 < var8009dd50.f[0] * arg0->f[0] + var8009dd50.f[1] * arg0->f[1] + var8009dd50.f[2] * arg0->f[2]) {
		return false;
	}

	if (var8009dd2c + arg1 < var8009dd20.f[0] * arg0->f[0] + var8009dd20.f[1] * arg0->f[1] + var8009dd20.f[2] * arg0->f[2]) {
		return false;
	}

	if (var8009dd3c + arg1 < var8009dd30.f[0] * arg0->f[0] + var8009dd30.f[1] * arg0->f[1] + var8009dd30.f[2] * arg0->f[2]) {
		return false;
	}

	return true;
}

GLOBAL_ASM(
glabel cam0f0b5d38
/*  f0b5d38:	27bdff80 */ 	addiu	$sp,$sp,-128
/*  f0b5d3c:	afb00028 */ 	sw	$s0,0x28($sp)
/*  f0b5d40:	3c10800a */ 	lui	$s0,%hi(g_Vars+0x284)
/*  f0b5d44:	8e10a244 */ 	lw	$s0,%lo(g_Vars+0x284)($s0)
/*  f0b5d48:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f0b5d4c:	f7b60020 */ 	sdc1	$f22,0x20($sp)
/*  f0b5d50:	f7b40018 */ 	sdc1	$f20,0x18($sp)
/*  f0b5d54:	afa60088 */ 	sw	$a2,0x88($sp)
/*  f0b5d58:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b5d5c:	3c01800a */ 	lui	$at,%hi(var8009dd6c)
/*  f0b5d60:	4485b000 */ 	mtc1	$a1,$f22
/*  f0b5d64:	c424dd6c */ 	lwc1	$f4,%lo(var8009dd6c)($at)
/*  f0b5d68:	c48a0000 */ 	lwc1	$f10,0x0($a0)
/*  f0b5d6c:	c4480020 */ 	lwc1	$f8,0x20($v0)
/*  f0b5d70:	46162180 */ 	add.s	$f6,$f4,$f22
/*  f0b5d74:	c4440024 */ 	lwc1	$f4,0x24($v0)
/*  f0b5d78:	460a4482 */ 	mul.s	$f18,$f8,$f10
/*  f0b5d7c:	c4880004 */ 	lwc1	$f8,0x4($a0)
/*  f0b5d80:	8fae0088 */ 	lw	$t6,0x88($sp)
/*  f0b5d84:	46082282 */ 	mul.s	$f10,$f4,$f8
/*  f0b5d88:	c4880008 */ 	lwc1	$f8,0x8($a0)
/*  f0b5d8c:	460a9100 */ 	add.s	$f4,$f18,$f10
/*  f0b5d90:	c4520028 */ 	lwc1	$f18,0x28($v0)
/*  f0b5d94:	46124282 */ 	mul.s	$f10,$f8,$f18
/*  f0b5d98:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f0b5d9c:	4608303c */ 	c.lt.s	$f6,$f8
/*  f0b5da0:	00000000 */ 	nop
/*  f0b5da4:	45020004 */ 	bc1fl	.L0f0b5db8
/*  f0b5da8:	85cf0004 */ 	lh	$t7,0x4($t6)
/*  f0b5dac:	10000126 */ 	b	.L0f0b6248
/*  f0b5db0:	00001025 */ 	or	$v0,$zero,$zero
/*  f0b5db4:	85cf0004 */ 	lh	$t7,0x4($t6)
.L0f0b5db8:
/*  f0b5db8:	c604170c */ 	lwc1	$f4,0x170c($s0)
/*  f0b5dbc:	c6081720 */ 	lwc1	$f8,0x1720($s0)
/*  f0b5dc0:	448f9000 */ 	mtc1	$t7,$f18
/*  f0b5dc4:	3c013f80 */ 	lui	$at,0x3f80
/*  f0b5dc8:	4481a000 */ 	mtc1	$at,$f20
/*  f0b5dcc:	468092a0 */ 	cvt.s.w	$f10,$f18
/*  f0b5dd0:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f0b5dd4:	c60a1728 */ 	lwc1	$f10,0x1728($s0)
/*  f0b5dd8:	afa40080 */ 	sw	$a0,0x80($sp)
/*  f0b5ddc:	46083481 */ 	sub.s	$f18,$f6,$f8
/*  f0b5de0:	460a9082 */ 	mul.s	$f2,$f18,$f10
/*  f0b5de4:	00000000 */ 	nop
/*  f0b5de8:	46021102 */ 	mul.s	$f4,$f2,$f2
/*  f0b5dec:	e7a20038 */ 	swc1	$f2,0x38($sp)
/*  f0b5df0:	0c012974 */ 	jal	sqrtf
/*  f0b5df4:	46142300 */ 	add.s	$f12,$f4,$f20
/*  f0b5df8:	4600a303 */ 	div.s	$f12,$f20,$f0
/*  f0b5dfc:	3c10800a */ 	lui	$s0,%hi(g_Vars+0x284)
/*  f0b5e00:	8e10a244 */ 	lw	$s0,%lo(g_Vars+0x284)($s0)
/*  f0b5e04:	c7a20038 */ 	lwc1	$f2,0x38($sp)
/*  f0b5e08:	8fa40080 */ 	lw	$a0,0x80($sp)
/*  f0b5e0c:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b5e10:	8fb80088 */ 	lw	$t8,0x88($sp)
/*  f0b5e14:	c4460000 */ 	lwc1	$f6,0x0($v0)
/*  f0b5e18:	c4520020 */ 	lwc1	$f18,0x20($v0)
/*  f0b5e1c:	460c1082 */ 	mul.s	$f2,$f2,$f12
/*  f0b5e20:	46006387 */ 	neg.s	$f14,$f12
/*  f0b5e24:	46067202 */ 	mul.s	$f8,$f14,$f6
/*  f0b5e28:	00000000 */ 	nop
/*  f0b5e2c:	46029282 */ 	mul.s	$f10,$f18,$f2
/*  f0b5e30:	460a4101 */ 	sub.s	$f4,$f8,$f10
/*  f0b5e34:	e7a40054 */ 	swc1	$f4,0x54($sp)
/*  f0b5e38:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b5e3c:	c4460004 */ 	lwc1	$f6,0x4($v0)
/*  f0b5e40:	c4480024 */ 	lwc1	$f8,0x24($v0)
/*  f0b5e44:	46067482 */ 	mul.s	$f18,$f14,$f6
/*  f0b5e48:	00000000 */ 	nop
/*  f0b5e4c:	46024282 */ 	mul.s	$f10,$f8,$f2
/*  f0b5e50:	460a9181 */ 	sub.s	$f6,$f18,$f10
/*  f0b5e54:	e7a60058 */ 	swc1	$f6,0x58($sp)
/*  f0b5e58:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b5e5c:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*  f0b5e60:	c44a0028 */ 	lwc1	$f10,0x28($v0)
/*  f0b5e64:	46087482 */ 	mul.s	$f18,$f14,$f8
/*  f0b5e68:	00000000 */ 	nop
/*  f0b5e6c:	46025202 */ 	mul.s	$f8,$f10,$f2
/*  f0b5e70:	46089281 */ 	sub.s	$f10,$f18,$f8
/*  f0b5e74:	e7aa005c */ 	swc1	$f10,0x5c($sp)
/*  f0b5e78:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b5e7c:	c4520030 */ 	lwc1	$f18,0x30($v0)
/*  f0b5e80:	46122202 */ 	mul.s	$f8,$f4,$f18
/*  f0b5e84:	c4520034 */ 	lwc1	$f18,0x34($v0)
/*  f0b5e88:	46123482 */ 	mul.s	$f18,$f6,$f18
/*  f0b5e8c:	46124200 */ 	add.s	$f8,$f8,$f18
/*  f0b5e90:	c4520038 */ 	lwc1	$f18,0x38($v0)
/*  f0b5e94:	460a9482 */ 	mul.s	$f18,$f18,$f10
/*  f0b5e98:	46089400 */ 	add.s	$f16,$f18,$f8
/*  f0b5e9c:	c4880000 */ 	lwc1	$f8,0x0($a0)
/*  f0b5ea0:	46082102 */ 	mul.s	$f4,$f4,$f8
/*  f0b5ea4:	c4880004 */ 	lwc1	$f8,0x4($a0)
/*  f0b5ea8:	46168480 */ 	add.s	$f18,$f16,$f22
/*  f0b5eac:	46083182 */ 	mul.s	$f6,$f6,$f8
/*  f0b5eb0:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f0b5eb4:	c4840008 */ 	lwc1	$f4,0x8($a0)
/*  f0b5eb8:	460a2182 */ 	mul.s	$f6,$f4,$f10
/*  f0b5ebc:	46083100 */ 	add.s	$f4,$f6,$f8
/*  f0b5ec0:	4604903c */ 	c.lt.s	$f18,$f4
/*  f0b5ec4:	00000000 */ 	nop
/*  f0b5ec8:	45000003 */ 	bc1f	.L0f0b5ed8
/*  f0b5ecc:	00000000 */ 	nop
/*  f0b5ed0:	100000dd */ 	b	.L0f0b6248
/*  f0b5ed4:	00001025 */ 	or	$v0,$zero,$zero
.L0f0b5ed8:
/*  f0b5ed8:	87190008 */ 	lh	$t9,0x8($t8)
/*  f0b5edc:	c608170c */ 	lwc1	$f8,0x170c($s0)
/*  f0b5ee0:	c6041720 */ 	lwc1	$f4,0x1720($s0)
/*  f0b5ee4:	44995000 */ 	mtc1	$t9,$f10
/*  f0b5ee8:	00000000 */ 	nop
/*  f0b5eec:	468051a0 */ 	cvt.s.w	$f6,$f10
/*  f0b5ef0:	46083481 */ 	sub.s	$f18,$f6,$f8
/*  f0b5ef4:	c6081728 */ 	lwc1	$f8,0x1728($s0)
/*  f0b5ef8:	afa40080 */ 	sw	$a0,0x80($sp)
/*  f0b5efc:	46049281 */ 	sub.s	$f10,$f18,$f4
/*  f0b5f00:	46005187 */ 	neg.s	$f6,$f10
/*  f0b5f04:	46083082 */ 	mul.s	$f2,$f6,$f8
/*  f0b5f08:	00000000 */ 	nop
/*  f0b5f0c:	46021482 */ 	mul.s	$f18,$f2,$f2
/*  f0b5f10:	e7a20038 */ 	swc1	$f2,0x38($sp)
/*  f0b5f14:	0c012974 */ 	jal	sqrtf
/*  f0b5f18:	46149300 */ 	add.s	$f12,$f18,$f20
/*  f0b5f1c:	4600a303 */ 	div.s	$f12,$f20,$f0
/*  f0b5f20:	3c10800a */ 	lui	$s0,%hi(g_Vars+0x284)
/*  f0b5f24:	8e10a244 */ 	lw	$s0,%lo(g_Vars+0x284)($s0)
/*  f0b5f28:	c7a20038 */ 	lwc1	$f2,0x38($sp)
/*  f0b5f2c:	8fa40080 */ 	lw	$a0,0x80($sp)
/*  f0b5f30:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b5f34:	8fa80088 */ 	lw	$t0,0x88($sp)
/*  f0b5f38:	c4440000 */ 	lwc1	$f4,0x0($v0)
/*  f0b5f3c:	c4460020 */ 	lwc1	$f6,0x20($v0)
/*  f0b5f40:	460c1082 */ 	mul.s	$f2,$f2,$f12
/*  f0b5f44:	46006387 */ 	neg.s	$f14,$f12
/*  f0b5f48:	46007387 */ 	neg.s	$f14,$f14
/*  f0b5f4c:	46047282 */ 	mul.s	$f10,$f14,$f4
/*  f0b5f50:	00000000 */ 	nop
/*  f0b5f54:	46023202 */ 	mul.s	$f8,$f6,$f2
/*  f0b5f58:	46085481 */ 	sub.s	$f18,$f10,$f8
/*  f0b5f5c:	e7b20044 */ 	swc1	$f18,0x44($sp)
/*  f0b5f60:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b5f64:	c4440004 */ 	lwc1	$f4,0x4($v0)
/*  f0b5f68:	c44a0024 */ 	lwc1	$f10,0x24($v0)
/*  f0b5f6c:	46047182 */ 	mul.s	$f6,$f14,$f4
/*  f0b5f70:	00000000 */ 	nop
/*  f0b5f74:	46025202 */ 	mul.s	$f8,$f10,$f2
/*  f0b5f78:	46083101 */ 	sub.s	$f4,$f6,$f8
/*  f0b5f7c:	e7a40048 */ 	swc1	$f4,0x48($sp)
/*  f0b5f80:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b5f84:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f0b5f88:	c4480028 */ 	lwc1	$f8,0x28($v0)
/*  f0b5f8c:	460a7182 */ 	mul.s	$f6,$f14,$f10
/*  f0b5f90:	00000000 */ 	nop
/*  f0b5f94:	46024282 */ 	mul.s	$f10,$f8,$f2
/*  f0b5f98:	460a3201 */ 	sub.s	$f8,$f6,$f10
/*  f0b5f9c:	e7a8004c */ 	swc1	$f8,0x4c($sp)
/*  f0b5fa0:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b5fa4:	c4460030 */ 	lwc1	$f6,0x30($v0)
/*  f0b5fa8:	46069282 */ 	mul.s	$f10,$f18,$f6
/*  f0b5fac:	c4460034 */ 	lwc1	$f6,0x34($v0)
/*  f0b5fb0:	46062182 */ 	mul.s	$f6,$f4,$f6
/*  f0b5fb4:	46065280 */ 	add.s	$f10,$f10,$f6
/*  f0b5fb8:	c4460038 */ 	lwc1	$f6,0x38($v0)
/*  f0b5fbc:	46083182 */ 	mul.s	$f6,$f6,$f8
/*  f0b5fc0:	460a3400 */ 	add.s	$f16,$f6,$f10
/*  f0b5fc4:	c48a0000 */ 	lwc1	$f10,0x0($a0)
/*  f0b5fc8:	460a9482 */ 	mul.s	$f18,$f18,$f10
/*  f0b5fcc:	c48a0004 */ 	lwc1	$f10,0x4($a0)
/*  f0b5fd0:	46168180 */ 	add.s	$f6,$f16,$f22
/*  f0b5fd4:	460a2102 */ 	mul.s	$f4,$f4,$f10
/*  f0b5fd8:	46049280 */ 	add.s	$f10,$f18,$f4
/*  f0b5fdc:	c4920008 */ 	lwc1	$f18,0x8($a0)
/*  f0b5fe0:	46089102 */ 	mul.s	$f4,$f18,$f8
/*  f0b5fe4:	460a2480 */ 	add.s	$f18,$f4,$f10
/*  f0b5fe8:	4612303c */ 	c.lt.s	$f6,$f18
/*  f0b5fec:	00000000 */ 	nop
/*  f0b5ff0:	45000003 */ 	bc1f	.L0f0b6000
/*  f0b5ff4:	00000000 */ 	nop
/*  f0b5ff8:	10000093 */ 	b	.L0f0b6248
/*  f0b5ffc:	00001025 */ 	or	$v0,$zero,$zero
.L0f0b6000:
/*  f0b6000:	85090006 */ 	lh	$t1,0x6($t0)
/*  f0b6004:	c60a1710 */ 	lwc1	$f10,0x1710($s0)
/*  f0b6008:	c6121724 */ 	lwc1	$f18,0x1724($s0)
/*  f0b600c:	44894000 */ 	mtc1	$t1,$f8
/*  f0b6010:	00000000 */ 	nop
/*  f0b6014:	46804120 */ 	cvt.s.w	$f4,$f8
/*  f0b6018:	460a2181 */ 	sub.s	$f6,$f4,$f10
/*  f0b601c:	c604172c */ 	lwc1	$f4,0x172c($s0)
/*  f0b6020:	afa40080 */ 	sw	$a0,0x80($sp)
/*  f0b6024:	46069201 */ 	sub.s	$f8,$f18,$f6
/*  f0b6028:	46044082 */ 	mul.s	$f2,$f8,$f4
/*  f0b602c:	00000000 */ 	nop
/*  f0b6030:	46021282 */ 	mul.s	$f10,$f2,$f2
/*  f0b6034:	e7a20034 */ 	swc1	$f2,0x34($sp)
/*  f0b6038:	0c012974 */ 	jal	sqrtf
/*  f0b603c:	46145300 */ 	add.s	$f12,$f10,$f20
/*  f0b6040:	4600a303 */ 	div.s	$f12,$f20,$f0
/*  f0b6044:	c7a20034 */ 	lwc1	$f2,0x34($sp)
/*  f0b6048:	3c10800a */ 	lui	$s0,%hi(g_Vars+0x284)
/*  f0b604c:	8e10a244 */ 	lw	$s0,%lo(g_Vars+0x284)($s0)
/*  f0b6050:	8fa40080 */ 	lw	$a0,0x80($sp)
/*  f0b6054:	8faa0088 */ 	lw	$t2,0x88($sp)
/*  f0b6058:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b605c:	c4520020 */ 	lwc1	$f18,0x20($v0)
/*  f0b6060:	c4480010 */ 	lwc1	$f8,0x10($v0)
/*  f0b6064:	460c1082 */ 	mul.s	$f2,$f2,$f12
/*  f0b6068:	46006387 */ 	neg.s	$f14,$f12
/*  f0b606c:	46007387 */ 	neg.s	$f14,$f14
/*  f0b6070:	46029182 */ 	mul.s	$f6,$f18,$f2
/*  f0b6074:	00000000 */ 	nop
/*  f0b6078:	46087102 */ 	mul.s	$f4,$f14,$f8
/*  f0b607c:	46043280 */ 	add.s	$f10,$f6,$f4
/*  f0b6080:	e7aa0074 */ 	swc1	$f10,0x74($sp)
/*  f0b6084:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b6088:	c4520024 */ 	lwc1	$f18,0x24($v0)
/*  f0b608c:	c4460014 */ 	lwc1	$f6,0x14($v0)
/*  f0b6090:	46029202 */ 	mul.s	$f8,$f18,$f2
/*  f0b6094:	00000000 */ 	nop
/*  f0b6098:	46067102 */ 	mul.s	$f4,$f14,$f6
/*  f0b609c:	46044480 */ 	add.s	$f18,$f8,$f4
/*  f0b60a0:	e7b20078 */ 	swc1	$f18,0x78($sp)
/*  f0b60a4:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b60a8:	c4460028 */ 	lwc1	$f6,0x28($v0)
/*  f0b60ac:	c4440018 */ 	lwc1	$f4,0x18($v0)
/*  f0b60b0:	46023202 */ 	mul.s	$f8,$f6,$f2
/*  f0b60b4:	00000000 */ 	nop
/*  f0b60b8:	46047182 */ 	mul.s	$f6,$f14,$f4
/*  f0b60bc:	46064100 */ 	add.s	$f4,$f8,$f6
/*  f0b60c0:	e7a4007c */ 	swc1	$f4,0x7c($sp)
/*  f0b60c4:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b60c8:	c4480030 */ 	lwc1	$f8,0x30($v0)
/*  f0b60cc:	46085182 */ 	mul.s	$f6,$f10,$f8
/*  f0b60d0:	c4480034 */ 	lwc1	$f8,0x34($v0)
/*  f0b60d4:	46089202 */ 	mul.s	$f8,$f18,$f8
/*  f0b60d8:	46083180 */ 	add.s	$f6,$f6,$f8
/*  f0b60dc:	c4480038 */ 	lwc1	$f8,0x38($v0)
/*  f0b60e0:	46044202 */ 	mul.s	$f8,$f8,$f4
/*  f0b60e4:	46064400 */ 	add.s	$f16,$f8,$f6
/*  f0b60e8:	c4860000 */ 	lwc1	$f6,0x0($a0)
/*  f0b60ec:	46065282 */ 	mul.s	$f10,$f10,$f6
/*  f0b60f0:	c4860004 */ 	lwc1	$f6,0x4($a0)
/*  f0b60f4:	46168200 */ 	add.s	$f8,$f16,$f22
/*  f0b60f8:	46069482 */ 	mul.s	$f18,$f18,$f6
/*  f0b60fc:	46125180 */ 	add.s	$f6,$f10,$f18
/*  f0b6100:	c48a0008 */ 	lwc1	$f10,0x8($a0)
/*  f0b6104:	46045482 */ 	mul.s	$f18,$f10,$f4
/*  f0b6108:	46069280 */ 	add.s	$f10,$f18,$f6
/*  f0b610c:	460a403c */ 	c.lt.s	$f8,$f10
/*  f0b6110:	00000000 */ 	nop
/*  f0b6114:	45000003 */ 	bc1f	.L0f0b6124
/*  f0b6118:	00000000 */ 	nop
/*  f0b611c:	1000004a */ 	b	.L0f0b6248
/*  f0b6120:	00001025 */ 	or	$v0,$zero,$zero
.L0f0b6124:
/*  f0b6124:	854b000a */ 	lh	$t3,0xa($t2)
/*  f0b6128:	c6061710 */ 	lwc1	$f6,0x1710($s0)
/*  f0b612c:	c60a1724 */ 	lwc1	$f10,0x1724($s0)
/*  f0b6130:	448b2000 */ 	mtc1	$t3,$f4
/*  f0b6134:	00000000 */ 	nop
/*  f0b6138:	468024a0 */ 	cvt.s.w	$f18,$f4
/*  f0b613c:	46069201 */ 	sub.s	$f8,$f18,$f6
/*  f0b6140:	c606172c */ 	lwc1	$f6,0x172c($s0)
/*  f0b6144:	afa40080 */ 	sw	$a0,0x80($sp)
/*  f0b6148:	46085101 */ 	sub.s	$f4,$f10,$f8
/*  f0b614c:	46002487 */ 	neg.s	$f18,$f4
/*  f0b6150:	46069082 */ 	mul.s	$f2,$f18,$f6
/*  f0b6154:	00000000 */ 	nop
/*  f0b6158:	46021282 */ 	mul.s	$f10,$f2,$f2
/*  f0b615c:	e7a20034 */ 	swc1	$f2,0x34($sp)
/*  f0b6160:	0c012974 */ 	jal	sqrtf
/*  f0b6164:	46145300 */ 	add.s	$f12,$f10,$f20
/*  f0b6168:	4600a303 */ 	div.s	$f12,$f20,$f0
/*  f0b616c:	c7a20034 */ 	lwc1	$f2,0x34($sp)
/*  f0b6170:	3c10800a */ 	lui	$s0,%hi(g_Vars+0x284)
/*  f0b6174:	8e10a244 */ 	lw	$s0,%lo(g_Vars+0x284)($s0)
/*  f0b6178:	8fa40080 */ 	lw	$a0,0x80($sp)
/*  f0b617c:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b6180:	c4480020 */ 	lwc1	$f8,0x20($v0)
/*  f0b6184:	c4520010 */ 	lwc1	$f18,0x10($v0)
/*  f0b6188:	460c1082 */ 	mul.s	$f2,$f2,$f12
/*  f0b618c:	46006387 */ 	neg.s	$f14,$f12
/*  f0b6190:	46024102 */ 	mul.s	$f4,$f8,$f2
/*  f0b6194:	00000000 */ 	nop
/*  f0b6198:	46127182 */ 	mul.s	$f6,$f14,$f18
/*  f0b619c:	46062280 */ 	add.s	$f10,$f4,$f6
/*  f0b61a0:	e7aa0064 */ 	swc1	$f10,0x64($sp)
/*  f0b61a4:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b61a8:	c4480024 */ 	lwc1	$f8,0x24($v0)
/*  f0b61ac:	c4440014 */ 	lwc1	$f4,0x14($v0)
/*  f0b61b0:	46024482 */ 	mul.s	$f18,$f8,$f2
/*  f0b61b4:	00000000 */ 	nop
/*  f0b61b8:	46047182 */ 	mul.s	$f6,$f14,$f4
/*  f0b61bc:	46069200 */ 	add.s	$f8,$f18,$f6
/*  f0b61c0:	e7a80068 */ 	swc1	$f8,0x68($sp)
/*  f0b61c4:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b61c8:	c4440028 */ 	lwc1	$f4,0x28($v0)
/*  f0b61cc:	c4460018 */ 	lwc1	$f6,0x18($v0)
/*  f0b61d0:	46022482 */ 	mul.s	$f18,$f4,$f2
/*  f0b61d4:	00000000 */ 	nop
/*  f0b61d8:	46067102 */ 	mul.s	$f4,$f14,$f6
/*  f0b61dc:	46049180 */ 	add.s	$f6,$f18,$f4
/*  f0b61e0:	e7a6006c */ 	swc1	$f6,0x6c($sp)
/*  f0b61e4:	8e02174c */ 	lw	$v0,0x174c($s0)
/*  f0b61e8:	c4520030 */ 	lwc1	$f18,0x30($v0)
/*  f0b61ec:	46125102 */ 	mul.s	$f4,$f10,$f18
/*  f0b61f0:	c4520034 */ 	lwc1	$f18,0x34($v0)
/*  f0b61f4:	46124482 */ 	mul.s	$f18,$f8,$f18
/*  f0b61f8:	46122100 */ 	add.s	$f4,$f4,$f18
/*  f0b61fc:	c4520038 */ 	lwc1	$f18,0x38($v0)
/*  f0b6200:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f0b6204:	46069482 */ 	mul.s	$f18,$f18,$f6
/*  f0b6208:	46049400 */ 	add.s	$f16,$f18,$f4
/*  f0b620c:	c4840000 */ 	lwc1	$f4,0x0($a0)
/*  f0b6210:	46045282 */ 	mul.s	$f10,$f10,$f4
/*  f0b6214:	c4840004 */ 	lwc1	$f4,0x4($a0)
/*  f0b6218:	46168480 */ 	add.s	$f18,$f16,$f22
/*  f0b621c:	46044202 */ 	mul.s	$f8,$f8,$f4
/*  f0b6220:	46085100 */ 	add.s	$f4,$f10,$f8
/*  f0b6224:	c48a0008 */ 	lwc1	$f10,0x8($a0)
/*  f0b6228:	46065202 */ 	mul.s	$f8,$f10,$f6
/*  f0b622c:	46044280 */ 	add.s	$f10,$f8,$f4
/*  f0b6230:	460a903c */ 	c.lt.s	$f18,$f10
/*  f0b6234:	00000000 */ 	nop
/*  f0b6238:	45000003 */ 	bc1f	.L0f0b6248
/*  f0b623c:	00000000 */ 	nop
/*  f0b6240:	10000001 */ 	b	.L0f0b6248
/*  f0b6244:	00001025 */ 	or	$v0,$zero,$zero
.L0f0b6248:
/*  f0b6248:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f0b624c:	d7b40018 */ 	ldc1	$f20,0x18($sp)
/*  f0b6250:	d7b60020 */ 	ldc1	$f22,0x20($sp)
/*  f0b6254:	8fb00028 */ 	lw	$s0,0x28($sp)
/*  f0b6258:	03e00008 */ 	jr	$ra
/*  f0b625c:	27bd0080 */ 	addiu	$sp,$sp,0x80
);

GLOBAL_ASM(
glabel cam0f0b6260
/*  f0b6260:	27bdffb0 */ 	addiu	$sp,$sp,-80
/*  f0b6264:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f0b6268:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f0b626c:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f0b6270:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f0b6274:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f0b6278:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f0b627c:	afa50054 */ 	sw	$a1,0x54($sp)
/*  f0b6280:	afa60058 */ 	sw	$a2,0x58($sp)
/*  f0b6284:	84860000 */ 	lh	$a2,0x0($a0)
/*  f0b6288:	2412ffff */ 	addiu	$s2,$zero,-1
/*  f0b628c:	00008825 */ 	or	$s1,$zero,$zero
/*  f0b6290:	10d20036 */ 	beq	$a2,$s2,.L0f0b636c
/*  f0b6294:	00808025 */ 	or	$s0,$a0,$zero
/*  f0b6298:	3c13800a */ 	lui	$s3,%hi(g_Rooms)
/*  f0b629c:	26734928 */ 	addiu	$s3,$s3,%lo(g_Rooms)
/*  f0b62a0:	2414008c */ 	addiu	$s4,$zero,0x8c
.L0f0b62a4:
/*  f0b62a4:	00d40019 */ 	multu	$a2,$s4
/*  f0b62a8:	8e6e0000 */ 	lw	$t6,0x0($s3)
/*  f0b62ac:	00007812 */ 	mflo	$t7
/*  f0b62b0:	01cfc021 */ 	addu	$t8,$t6,$t7
/*  f0b62b4:	97190000 */ 	lhu	$t9,0x0($t8)
/*  f0b62b8:	33280004 */ 	andi	$t0,$t9,0x4
/*  f0b62bc:	51000028 */ 	beqzl	$t0,.L0f0b6360
/*  f0b62c0:	86060002 */ 	lh	$a2,0x2($s0)
/*  f0b62c4:	0fc56050 */ 	jal	func0f158140
/*  f0b62c8:	00c02025 */ 	or	$a0,$a2,$zero
/*  f0b62cc:	2e230001 */ 	sltiu	$v1,$s1,0x1
/*  f0b62d0:	1060000a */ 	beqz	$v1,.L0f0b62fc
/*  f0b62d4:	24110001 */ 	addiu	$s1,$zero,0x1
/*  f0b62d8:	84490004 */ 	lh	$t1,0x4($v0)
/*  f0b62dc:	a7a90038 */ 	sh	$t1,0x38($sp)
/*  f0b62e0:	844a0006 */ 	lh	$t2,0x6($v0)
/*  f0b62e4:	a7aa003a */ 	sh	$t2,0x3a($sp)
/*  f0b62e8:	844b0008 */ 	lh	$t3,0x8($v0)
/*  f0b62ec:	a7ab003c */ 	sh	$t3,0x3c($sp)
/*  f0b62f0:	844c000a */ 	lh	$t4,0xa($v0)
/*  f0b62f4:	10000019 */ 	b	.L0f0b635c
/*  f0b62f8:	a7ac003e */ 	sh	$t4,0x3e($sp)
.L0f0b62fc:
/*  f0b62fc:	84430004 */ 	lh	$v1,0x4($v0)
/*  f0b6300:	87ad0038 */ 	lh	$t5,0x38($sp)
/*  f0b6304:	006d082a */ 	slt	$at,$v1,$t5
/*  f0b6308:	50200003 */ 	beqzl	$at,.L0f0b6318
/*  f0b630c:	84430006 */ 	lh	$v1,0x6($v0)
/*  f0b6310:	a7a30038 */ 	sh	$v1,0x38($sp)
/*  f0b6314:	84430006 */ 	lh	$v1,0x6($v0)
.L0f0b6318:
/*  f0b6318:	87ae003a */ 	lh	$t6,0x3a($sp)
/*  f0b631c:	006e082a */ 	slt	$at,$v1,$t6
/*  f0b6320:	50200003 */ 	beqzl	$at,.L0f0b6330
/*  f0b6324:	84430008 */ 	lh	$v1,0x8($v0)
/*  f0b6328:	a7a3003a */ 	sh	$v1,0x3a($sp)
/*  f0b632c:	84430008 */ 	lh	$v1,0x8($v0)
.L0f0b6330:
/*  f0b6330:	87af003c */ 	lh	$t7,0x3c($sp)
/*  f0b6334:	01e3082a */ 	slt	$at,$t7,$v1
/*  f0b6338:	50200003 */ 	beqzl	$at,.L0f0b6348
/*  f0b633c:	8443000a */ 	lh	$v1,0xa($v0)
/*  f0b6340:	a7a3003c */ 	sh	$v1,0x3c($sp)
/*  f0b6344:	8443000a */ 	lh	$v1,0xa($v0)
.L0f0b6348:
/*  f0b6348:	87b8003e */ 	lh	$t8,0x3e($sp)
/*  f0b634c:	0303082a */ 	slt	$at,$t8,$v1
/*  f0b6350:	50200003 */ 	beqzl	$at,.L0f0b6360
/*  f0b6354:	86060002 */ 	lh	$a2,0x2($s0)
/*  f0b6358:	a7a3003e */ 	sh	$v1,0x3e($sp)
.L0f0b635c:
/*  f0b635c:	86060002 */ 	lh	$a2,0x2($s0)
.L0f0b6360:
/*  f0b6360:	26100002 */ 	addiu	$s0,$s0,0x2
/*  f0b6364:	14d2ffcf */ 	bne	$a2,$s2,.L0f0b62a4
/*  f0b6368:	00000000 */ 	nop
.L0f0b636c:
/*  f0b636c:	16200003 */ 	bnez	$s1,.L0f0b637c
/*  f0b6370:	8fa40054 */ 	lw	$a0,0x54($sp)
/*  f0b6374:	10000004 */ 	b	.L0f0b6388
/*  f0b6378:	00001025 */ 	or	$v0,$zero,$zero
.L0f0b637c:
/*  f0b637c:	8fa50058 */ 	lw	$a1,0x58($sp)
/*  f0b6380:	0fc2d74e */ 	jal	cam0f0b5d38
/*  f0b6384:	27a60034 */ 	addiu	$a2,$sp,0x34
.L0f0b6388:
/*  f0b6388:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f0b638c:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f0b6390:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f0b6394:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f0b6398:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f0b639c:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f0b63a0:	03e00008 */ 	jr	$ra
/*  f0b63a4:	27bd0050 */ 	addiu	$sp,$sp,0x50
);

// Mismatch: Too much compiler-managed stack
//bool cam0f0b6260(s16 *rooms, struct coord *coord, f32 arg2)
//{
//	s8 hasdata = false;
//	s16 room;
//	s32 i;
//	struct var800a4640_00 *thisthing;
//	struct var800a4640_00 thing; // 34
//
//	for (i = 0, room = rooms[0]; room != -1; i++, room = rooms[i]) {
//		if (g_Rooms[room].flags & ROOMFLAG_VISIBLEBYPLAYER) {
//			thisthing = func0f158140(room);
//
//			if (hasdata == false) {
//				thing.box.xmin = thisthing->box.xmin;
//				thing.box.ymin = thisthing->box.ymin;
//				thing.box.xmax = thisthing->box.xmax;
//				thing.box.ymax = thisthing->box.ymax;
//			} else {
//				if (thisthing->box.xmin < thing.box.xmin) {
//					thing.box.xmin = thisthing->box.xmin;
//				}
//
//				if (thisthing->box.ymin < thing.box.ymin) {
//					thing.box.ymin = thisthing->box.ymin;
//				}
//
//				if (thisthing->box.xmax > thing.box.xmax) {
//					thing.box.xmax = thisthing->box.xmax;
//				}
//
//				if (thisthing->box.ymax > thing.box.ymax) {
//					thing.box.ymax = thisthing->box.ymax;
//				}
//			}
//
//			hasdata = true;
//		}
//	}
//
//	if (!hasdata) {
//		return false;
//	}
//
//	return cam0f0b5d38(coord, arg2, &thing);
//}
