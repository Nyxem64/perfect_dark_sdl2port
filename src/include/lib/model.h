#ifndef _IN_LIB_MODEL_H
#define _IN_LIB_MODEL_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

void modelSetDistanceScale(f32 value);
void func0001a518(void *callback);
s32 func0001a524(struct modelnode *node, s32 arg1);
Mtxf *func0001a5cc(struct model *model, struct modelnode *node, s32 arg2);
Mtxf *func0001a60c(struct model *model);
struct modelnode *func0001a634(struct model *model, s32 mtxindex);
struct modelnode *func0001a740(struct modelnode *node);
struct modelnode *func0001a784(struct modelnode *node);
struct modelnode *func0001a7cc(struct modelnode *node);
struct modelnode *func0001a85c(struct modelnode *node);
struct modelnode *modelGetPart(struct modelfiledata *arg0, s32 partnum);
union modelrodata *modelGetPartRodata(struct modelfiledata *modelfiledata, s32 partnum);
f32 func0001a9e8(struct model *model);
void *modelGetNodeRwData(struct model *model, struct modelnode *node);
void modelNodeGetPosition(struct model *model, struct modelnode *node, struct coord *pos);
void modelNodeSetPosition(struct model *model, struct modelnode *node, struct coord *pos);
void modelGetRootPosition(struct model *model, struct coord *pos);
void modelSetRootPosition(struct model *model, struct coord *pos);
void modelNodeGetModelRelativePosition(struct model *model, struct modelnode *node, struct coord *pos);
f32 func0001ae44(struct model *model);
void func0001ae90(struct model *model, f32 angle);
void modelSetScale(struct model *model, f32 scale);
void modelSetAnimScale(struct model *model, f32 scale);
f32 func0001af80(struct model *model);
void func0001af98(struct coord *arg0, struct coord *arg1, f32 frac);
f32 func0001afe8(f32 arg0, f32 angle, f32 frac);
void func0001b07c(struct coord *arg0, struct coord *arg1, f32 mult);
void func0001b0e8(struct model *model, struct modelnode *node);
void func0001b3bc(struct model *model);
void func0001b400(struct objticksp476 *arg0, struct model *model, struct modelnode *node);
u32 func0001b80c(void);
u32 func0001bc14(void);
void func0001bfa8(struct objticksp476 *arg0, struct model *model, struct modelnode *node);
void func0001c5b4(struct objticksp476 *arg0, struct model *model, struct modelnode *node);
void func0001c664(struct model *model, struct modelnode *node);
void func0001c784(struct model *model, struct modelnode *node);
void func0001c7d0(struct model *model, struct modelnode *node);
void modelAttachHead(struct model *model, struct modelnode *node);
void func0001c868(struct modelnode *node, bool visible);
void modelRenderNodeReorder(struct model *model, struct modelnode *node);
void func0001c950(struct model *model, struct modelnode *node);
void func0001cb0c(struct model *model, struct modelnode *node);
void func0001cc20(struct model *model);
void func0001cd18(struct objticksp476 *arg0, struct model *model);
u32 func0001ce64(void);
void func0001cebc(struct objticksp476 *arg0, struct model *model);
s16 modelGetAnimNum(struct model *model);
bool modelIsFlipped(struct model *model);
f32 modelGetCurAnimFrame(struct model *model);
f32 modelGetAnimEndFrame(struct model *model);
s32 modelGetNumAnimFrames(struct model *model);
f32 modelGetAnimSpeed(struct model *model);
f32 modelGetAbsAnimSpeed(struct model *model);
s32 modelConstrainOrWrapAnimFrame(s32 frame, s16 animnum, f32 endframe);
void modelCopyAnimForMerge(struct model *model, f32 arg1);
void func0001d62c(struct model *model, s16 animnum, s32 flip, f32 fstartframe, f32 speed, f32 arg5);
bool modelIsAnimMerging(struct model *model);
void modelSetAnimationWithMerge(struct model *model, s16 animnum, u32 flip, f32 startframe, f32 speed, f32 arg5, bool merge);
void modelSetAnimation(struct model *model, s16 animnum, s32 flip, f32 fstartframe, f32 speed, f32 arg5);
void modelCopyAnimData(struct model *src, struct model *dst);
void modelSetAnimLooping(struct model *model, f32 loopframe, f32 loopmerge);
void modelSetAnimEndFrame(struct model *model, f32 endframe);
void modelSetAnimFlipFunction(struct model *model, void *callback);
void modelSetAnimSpeed(struct model *model, f32 speed, f32 startframe);
void modelSetAnimSpeedAuto(struct model *model, f32 arg1, f32 startframe);
void modelSetAnimPlaySpeed(struct model *model, f32 speed, f32 frame);
void modelSetAnim70(struct model *model, void *callback);
void func0001e018(struct model *model, f32 arg1);
void func0001e14c(struct model *model, f32 arg1, f32 arg2);
void func0001e29c(bool value);
bool func0001e2a8(void);
void func0001e2b4(struct model *model, f32 frame, f32 arg2, f32 frame2, f32 arg4);
void func0001ee18(struct model *model, s32 lvupdate240, bool arg2);
void func0001f314(struct model *model, s32 arg1, bool arg2);
void func0001f7e0(struct modelrenderdata *renderdata);
void func0001f890(struct modelrenderdata *renderdata, bool arg1);
void func00020248(struct modelrenderdata *renderdata, bool arg1);
void func00020bdc(struct modelrenderdata *renderdata);
void modelApplyCullMode(struct modelrenderdata *renderdata);
void modelRenderNodeGundl(struct modelrenderdata *renderdata, struct model *model, struct modelnode *node);
void modelRenderNodeDl(struct modelrenderdata *renderdata, struct model *model, struct modelnode *node);
void modelRenderNodeType16(struct modelrenderdata *renderdata, struct modelnode *node);
u32 func000216cc(void);
void modelRenderNodeGunfire(struct modelrenderdata *renderdata, struct model *model, struct modelnode *node);
void modelRender(struct modelrenderdata *renderdata, struct model *model);
bool func000220fc(union modelrodata *rodata, Mtxf *mtx, struct coord *arg2, struct coord *arg3);
s32 func000225d4(struct model *model, struct coord *arg1, struct coord *arg2, struct modelnode **startnode);
void modelPromoteNodeOffsetsToPointers(struct modelnode *node, u32 vma, u32 fileramaddr);
void modelPromoteOffsetsToPointers(struct modelfiledata *filedata, u32 arg1, u32 arg2);
s32 modelCalculateRwDataIndexes(struct modelnode *node);
void modelCalculateRwDataLen(struct modelfiledata *filedata);
void modelInitRwData(struct model *model, struct modelnode *node);
void modelInit(struct model *model, struct modelfiledata *filedata, union modelrwdata **rwdatas, bool resetanim);
void animInit(struct anim *anim);
u32 func00023108(void);
u32 func0002319c(void);
void modelNodeReplaceGdl(u32 arg0, struct modelnode *node, Gfx *find, Gfx *replacement);

#endif
