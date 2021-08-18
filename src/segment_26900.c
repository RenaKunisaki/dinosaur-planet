#include "common.h"
#include "game/actor/actor.h"

//#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/alloc_some_object_arrays.s")
#if 1
int func_80028D90(); // extern
void* malloc(s32 size, s32 tag, const char *name); // extern
extern f32 D_800B1990;
extern void *D_800B1994;
extern void *D_800B199C;
extern void *D_800B20A0;
extern void *D_800B20A8;
extern void *D_800B20AC;
extern void *D_800B20B0;
extern void *D_800B20B4;

void alloc_some_object_arrays(void) {
    D_800B1994 = malloc( 160, ALLOC_TAG_OBJECTS_COL, NULL);
    D_800B199C = malloc(1800, ALLOC_TAG_OBJECTS_COL, NULL);
    D_800B20A0 = malloc(6400, ALLOC_TAG_OBJECTS_COL, NULL);
    D_800B20A8 = malloc(1024, ALLOC_TAG_OBJECTS_COL, NULL);
    D_800B20AC = malloc(1024, ALLOC_TAG_OBJECTS_COL, NULL);
    D_800B20B0 = malloc(1024, ALLOC_TAG_OBJECTS_COL, NULL);
    D_800B20B4 = malloc(1024, ALLOC_TAG_OBJECTS_COL, NULL);
    D_800B1990 = 2.0f;
    func_80028D90();
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80025DD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80025DF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80025E58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80025F40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002601C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80026128.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80026160.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80026184.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_800261E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002635C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_800264D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002667C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_800266E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80026724.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002674C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_800267A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_800267C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002681C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002683C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80026940.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_800269CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80026A20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80026AB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80026B84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80026BD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/update_obj_hitboxes.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80026DF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/obj_do_hit_detection.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80027934.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80027DAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80028238.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_800287E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80028D2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80028D90.s")
#if 0
extern s32 D_800916E0;
extern TActor *D_800916E4[];

int _func_80028D90(void) {
    int new_var;
    TActor **new_var3;
    if (1) { }
    new_var3 = D_800916E4;
    new_var = 1;
    D_800916E0 = 0;
    new_var3[1] = 0;
    new_var3[2] = 0;
    new_var3[3] = 0;
    return new_var;
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80028DC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80028DCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002949C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80029A14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80029AB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80029C04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002AD3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002B2D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002B410.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002B5A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002B5C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002B61C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002B68C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002B6EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002B74C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002B7CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002B910.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002BD04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002BF0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002C0C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002C278.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002C3EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002C658.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002C8C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002CBD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002CEC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002D0DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002D69C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002DC58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002DFB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002E3D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002E84C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002E88C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002E904.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002E964.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002EA0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002EAD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002EBA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002EE38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002F04C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002F164.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002F214.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002F24C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002F2D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002F3DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002F498.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_8002F998.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_800302B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80030338.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_800307C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80030880.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80030994.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80030A24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80030AEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/segment_26900/func_80030E2C.s")
