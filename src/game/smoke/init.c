#include <ultra64.h>
#include "constants.h"
#include "game/data/data_000000.h"
#include "game/data/data_0083d0.h"
#include "game/data/data_00e460.h"
#include "game/data/data_0160b0.h"
#include "game/data/data_01a3a0.h"
#include "game/data/data_020df0.h"
#include "game/data/data_02da90.h"
#include "gvars/gvars.h"
#include "lib/memory.h"
#include "types.h"

void smokeInit(void)
{
	s32 i;
	s32 j;

	g_MaxSmokes = IS4MB() ? 10 : 20;

	if (g_Vars.stagenum >= STAGE_TITLE) {
		g_MaxSmokes = 0;
	}

	if (g_MaxSmokes == 0) {
		g_Smokes = NULL;
	} else {
		g_Smokes = malloc(g_MaxSmokes * sizeof(struct smoke), MEMPOOL_STAGE);

		for (i = 0; i < g_MaxSmokes; i++) {
			g_Smokes[i].prop = NULL;

			for (j = 0; j < ARRAYCOUNT(g_Smokes[i].parts); j++) {
				g_Smokes[i].parts[j].size = 0;
			}
		}
	}
}
