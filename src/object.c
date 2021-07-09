#include "common.h"
#include "game/actor/actor.h"
#include "sys/gfx/animation.h"
#include "variables.h"

void alloc_some_object_arrays(void);
void func_80020D34(void);

void init_objects(void) {
    int i;

    //allocate some buffers
    gLoadedObjDefs = malloc(0x2D0, ALLOC_TAG_OBJECTS_COL, NULL);
    D_800B1918     = malloc(0x60, ALLOC_TAG_OBJECTS_COL,  NULL);
    D_800B18E4     = malloc(0x10, ALLOC_TAG_OBJECTS_COL,  NULL);

    //load OBJINDEX.BIN and count number of entries
    queue_alloc_load_file((void **) (&gFile_OBJINDEX), OBJINDEX_BIN);
    gObjIndexCount = (get_file_size(OBJINDEX_BIN) >> 1) - 1;
    while(!gFile_OBJINDEX[gObjIndexCount]) gObjIndexCount--;

    //load OBJECTS.TAB and count number of entries
    queue_alloc_load_file((void **)&gFile_OBJECTS_TAB, OBJECTS_TAB);
    gNumObjectsTabEntries = 0;
    while(gFile_OBJECTS_TAB[gNumObjectsTabEntries] != -1) gNumObjectsTabEntries++;
    gNumObjectsTabEntries--;

    //init ref count and pointers
    gLoadedObjData = malloc(gNumObjectsTabEntries * 4, ALLOC_TAG_OBJECTS_COL, NULL);
    gObjRefCount   = malloc(gNumObjectsTabEntries,     ALLOC_TAG_OBJECTS_COL, NULL);
    for(i = 0; i < gNumObjectsTabEntries; i++) gObjRefCount[i] = 0; //why not memset?

    //load TABLES.BIN and TABLES.TAB and count number of entries
    queue_alloc_load_file((void **) (&gFile_TABLES_BIN), TABLES_BIN);
    queue_alloc_load_file((void **) (&gFile_TABLES_TAB), TABLES_TAB);
    gNumTablesTabEntries = 0;
    while(gFile_TABLES_TAB[gNumTablesTabEntries] != -1) gNumTablesTabEntries++;

    //allocate global object list and some other buffers
    gObjList = malloc(0x2D0, ALLOC_TAG_OBJECTS_COL, NULL);
    alloc_some_object_arrays();
    func_80020D34();
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/update_objects.s")
#if 0
extern char D_800994E0;

void _update_objects(void) {
    s16 size;
    TActor *obj2;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    TActor *child;
    void *temp_t4;
    HitState *hitState;
    TActor *player;
    void *temp_v0_3;
    TActor *phi_s0;
    TActor *obj3;
    void *phi_s0_3;
    TActor *obj;
    void *phi_s0_4;
    void *phi_s0_5;
    void *phi_s0_6;

    size = gObjList->size;
    func_80058FE8();
    update_obj_models();
    update_obj_hitboxes(gNumObjs);

    obj = gObjList->obj;
    while(obj != NULL && obj->priority == 0x64) {
        update_object(obj);
        obj = obj + size;
    }
    while(obj != NULL && obj->data->flags & OBJDATA_FLAG44_HasChildren) {
        update_object(obj);
        obj->matrixIdx = func_80004258(obj);
        obj = obj + size;
    }
    func_80025E58();

    while(obj) {
        hitState = obj->hitState;
        if(hitState != 0) {
            if ((hitState->flags_0x5A != HITSTATE_FLAGS62_DontUpdate)
            || ((hitState->flags_0x58 & HITSTATE_FLAG60_Disabled) == 0)) { //disabled
                update_object(obj);
            }
        } else {
            update_object(obj);
        }
        obj = obj + size;
    }

    player = get_player();
    if(player) {
        child = player->children[0];
        if(child != 0) {
            update_object(player->children[0]);
        }
    }

    obj_do_hit_detection(gNumObjs);

    obj = gObjList->obj;
    while(obj) {
        func_8002272C(phi_s0_6);
        obj = obj + size;
    }

    player = get_player();
    if (player != 0) {
        child = player->children;
        if (child != 0) {
            child->ptr0x30 = player->ptr0x30;
            func_8002272C(player->children);
        }
    }

    (*gDLL_waterfx)->func[0].withOneArg(delayByte);
    (*gDLL_projgfx)->func[2].withTwoArgs(delayByte, 0);
    (*gDLL_modgfx)->func[2].withThreeArgs(0, 0, 0);
    (*gDLL_expgfx)->func[2].withFourArgs(0, delayByte, 0, 0);
    func_8002B6EC();
    (*gDLL_ANIM)->func[9].asVoid();
    (*gDLL_ANIM)->func[5].asVoid();
    (*gDLL_Camera)->func[1].withOneArg(delayByte);
    write_cFile_label_pointers(&D_800994E0, 0x169);
}
#endif

void doNothing_80020A40(void) {}

#pragma GLOBAL_ASM("asm/nonmatchings/object/update_obj_models.s")

void func_80020BB8() {
    int i;
    for(i = 0; i < gNumLoadedObjDefs; i++) {
        func_80022F94(gLoadedObjDefs[i], 0); //possibly some type of free?
        gLoadedObjDefs[i] = 0;
    }
    gNumLoadedObjDefs = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80020C48.s")

void func_80020D34(void) {
    gNumLoadedObjDefs = 0;
    D_800B191C = 0;
    D_800B1988 = 0;
    gNumObjs = 0;
    func_8000BA60(&D_800B1928, 0x38);
    D_800B18E0 = 0;
    func_80030EC0();
    func_80025DF0();
}


void func_80020D90(void) { D_800B18E0 = 0; }

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80020DA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80020EE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800210DC.s")

/**
 * @param outFirst Receives index of first object (always 0). (can be NULL)
 * @param outCount Receives number of objects. (can be NULL)
 * @return gObjList.
 */
TActor** get_world_actors(s32 *outFirst, s32 *outCount) {
    if(outFirst != 0) *outFirst = 0;
    if(outCount != 0) *outCount = gNumObjs;
    return gObjList;
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80021178.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800211B4.s")

s32 get_num_objects(void) { return gNumObjs; }

s32 ret0_800212E8(void) { return 0; } //get_first_object()?

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800212F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800213A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800213EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/objSetupObjectActual.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80021A84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80021CC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80021E74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80022150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80022200.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80022274.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800222AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80022338.s")

void copy_obj_position_mirrors(TActor *obj)
{
    DLLInstance **dll;
    obj->objId = obj->data->objId;
    dll = obj->dll;
    if(1) {
        if(dll != NULL) {
            obj->dll[0]->func[0].withOneArg((s32)obj);
        }
    }

    obj->positionMirror2.x = obj->srt.transl.x;
    obj->positionMirror3.x = obj->srt.transl.x;
    obj->positionMirror2.y = obj->srt.transl.y;
    obj->positionMirror3.y = obj->srt.transl.y;
    obj->positionMirror2.z = obj->srt.transl.z;
    obj->positionMirror3.z = obj->srt.transl.z;
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/update_object.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_8002272C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800227AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80022828.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80022868.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800228D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_8002298C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800229E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80022AA4.s")

//SFA's objFreeObjDef is much more complex.
//this might be a subroutine that got inlined in SFA,
//rather than objFreeObjDef itself.
void objFreeObjDef(s32 defNo) {
    ObjData *obj;

    if(gObjRefCount[defNo] == 0) {
        //this line is present in SFA
        //debugPrintf("objFreeObjdef: Error!! (%d)\n",defNo >> 8);
    }
    else {
        gObjRefCount[defNo] = gObjRefCount[defNo] - 1;
        if (gObjRefCount[defNo] == 0) {
            obj = gLoadedObjData[defNo];
            if (obj->pModLines != 0) {
                free(obj->pModLines);
            }
            if (obj->pIntersectPoints != 0) {
                free(obj->pIntersectPoints);
            }
            free(obj);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80022D00.s")

void doNothing_80022DD8(s32 a0, s32 a1, s32 a2) { }

s32 getObjIndexCount(void) { return gObjIndexCount; }

BOOL isObjIndexEntryValid(s32 defNo) {
    if (gObjIndexCount < defNo) {
        return 0;
    }
    return gFile_OBJINDEX[defNo] != -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80022E3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80022EC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80022F94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800233F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80023464.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80023628.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80023894.s")

TActor *get_player(void) {
    TActor **obj;
    int idx;
    obj = TActor_getter(0, &idx);
    if(idx) {} else {}; //wat
    if(idx) return *obj;
    else return NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_8002394C.s")

void objClearMapId(TActor *arg) { arg->mapId = -1; }

void objUpdateMapId(TActor *obj) {
    obj->mapId = map_get_map_id_from_xz_ws(obj->srt.transl.x, obj->srt.transl.z);
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800239C0.s")

//arg0 is most likely TActor*
void func_80023A00(s8 *arg0, s8 arg1) {
    arg0[0xAE] = arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80023A18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80023A78.s")

void func_80023B34(s32 arg0) {
    s8   idx;
    s8  *count = &D_800B1930;
    s32 *val   = &D_800B1938;
    idx = *count;
    val[idx] = arg0;
    *count = idx + 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80023B60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80023BF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80023C6C.s")

void func_80023CD8(TActor *obj, u16 arg1) {
    if(obj->data->unk9B < arg1) arg1 = 0;
    obj->unk_0xd0[4] = arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80023D08.s")
#if 0
//this matches with -g3
void _func_80023D08(s8 *arg0, u16 arg1) {
    if (arg1 >= 5) {
        arg0[0xD8] = arg1;
        arg1 = 0;
    }
    arg0[0xD8] = arg1;
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80023D30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800240BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80024108.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_8002493C.s")

void func_80024D74(TActor *obj, s32 arg1) {
    ModelInstance *mInst;
    AnimState *anim;

    mInst = obj->modelInsts[obj->modelInstIdx];
    if (mInst != 0) {
        anim = mInst->animState0;
        anim->unk_0x5e = 0x3FF / arg1;
    }
}

void func_80024DD0(TActor *obj, s32 arg1, s16 arg2, s16 arg3) {
    ModelInstance *mInst;
    AnimState *anim;

    mInst = obj->modelInsts[obj->modelInstIdx];
    if(mInst != NULL) {
        if(arg1 != 0) {
            anim = mInst->animState1;
        } else {
            anim = mInst->animState0;
        }
        (&anim->unk_0x58)[arg2] = arg3;
    }
}

s16 func_80024E2C(TActor *arg0) {
    ModelInstance *mInst = arg0->modelInsts[arg0->modelInstIdx];
    AnimState *anim = mInst->animState0;
    return anim->unk_0x58;
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80024E50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800250F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80025140.s")

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80025540.s")
#else
//in retail SFA 1.0 I believe this is at 8002ed18
//but it's different because SFA doesn't use Model Instances
//or, this might be a completely different function...
void func_80025540(TActor *obj, s32 a1, s32 a2)
{
    Model *model = obj->models[obj->curModel];
    void **anims; //this is a struct of some sort.
    if(model->unk66) {
        anims = model->animations;
        if (!anims) { }
        func_800255F8(obj, model, anims, a1, (short) a2); //probably ObjSetBlendMove
        //not certain about the order/count of params here.
    }
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_8002559C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800255F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80025780.s")

u8 func_80025CD4(s32 arg0) {
    if (arg0 >= 0x21) {
        return (u8)0U;
    }
    return *(&D_800916B0 + arg0);
}
