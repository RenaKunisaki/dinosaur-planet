#include "common.h"
#include "game/actor/actor.h"
#include "sys/gfx/animation.h"
#include "variables.h"

void alloc_some_object_arrays(void);
void func_80020D34(void);

/** Initialize the object system.
 */
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

/** Update all active objects.
 */
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

/** Retrieve list and count of active objects.
 * @param outFirst Receives index of first object (always 0). (can be NULL)
 * @param outCount Receives number of objects. (can be NULL)
 * @return gObjList.
 */
TActor** get_world_actors(s32 *outFirst, s32 *outCount) {
    if(outFirst != 0) *outFirst = 0;
    if(outCount != 0) *outCount = gNumObjs;
    return gObjList;
}

/** Retrieve one active object.
 *  @param idx Index into gObjList to retrieve.
 *  @return The object, or NULL if idx is not valid.
 */
TActor* get_actor(s32 idx) {
    if ((idx < 0) || (idx >= gNumObjs)) return NULL;
    return gObjList[idx];
}


#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800211B4.s")

/** Retrieve the number of active objects.
 *  @return gNumObjs,
 */
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

void func_80022274(TActor *arg0) {
    if ((arg0->flags_B0 & 0x10) != 0) {
        func_8000BB5C(&D_800B1928, arg0);
    }
}

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

UNK_TYPE_32 func_80022828(TActor *obj) {
    DLLInstance **dll;

    dll = obj->dll;
    if (dll != NULL) {
        //also matches with asVoidS32(), but seems unlikely
        return (*dll)->func[5].asS32_S32((s32)obj);
    }
    return 0;
}

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

/** Retrieve the number of entries in OBJINDEX.
 *  @return Number of entries in OBJINDEX.BIN.
 */
s32 getObjIndexCount(void) { return gObjIndexCount; }

/** Check if an OBJINDEX entry is valid.
 *  @param defNo the entry index to check.
 *  @return True if valid, false if not.
 */
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

/** Retrieve the current player object.
 *  @return Current player object, or NULL.
 */
TActor *get_player(void) {
    TActor **obj;
    s32 idx;
    obj = TActor_getter(0, &idx);
    if(idx) {} else {}; //wat
    if(idx) return *obj;
    else return NULL;
}

//probably get Tricky or Staff or something
TActor* func_8002394C(void) {
    TActor **obj;
    s32 idx;
    obj = TActor_getter(1, &idx);
    if(idx) return *obj;
    if(!idx) {}
    return 0;
}

/** Set object's map ID to -1 (ie none).
 *  @param obj Object to set.
 */
void objClearMapId(TActor *obj) { obj->mapId = -1; }

/** Ensure object's map ID is correct for the object's location.
 *  @param obj Object to update.
 */
void objUpdateMapId(TActor *obj) {
    obj->mapId = map_get_map_id_from_xz_ws(obj->srt.transl.x, obj->srt.transl.z);
}

/** Add the given values to the given object's position.
 */
int objAdjustPos(SRT *obj, f32 x, f32 y, f32 z) {
    obj->transl.x = (f32) (obj->transl.x + x);
    obj->transl.y = (f32) (obj->transl.y + y);
    obj->transl.z = (f32) (obj->transl.z + z);
    return 0;
}

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
#if 0
void func_80019118(f32, s16, s16, s32, void *); // extern
void func_800228D0(f32, void *, s16, s32, s32, s32); // extern
void func_80026AB8(f32, void *, void *, s16, void *, s32, s32); // extern
s32 _func_80023D30(TActor *obj, s32 animId, f32 arg2, s32 arg3) {
    //this might be 8002f23c staffAnimateGrabOrPutAway
    //or possibly 80030334 objLoadAnimation
    Model *model_sp48;
    AnimState *sp40;
    s32 sp2C;
    s16 temp_t0;
    s16 prevAnimId;
    s16 temp_v1;
    s32 temp_a2;
    s32 temp_s0;
    s32 temp_t0_2;
    s32 temp_t6;
    s8 temp_t7;
    ModelInstance *mdlInst;
    ActorObjhitInfo *hitInfo;
    Model *model;
    AnimState *animState0;
    void *state;
    void *temp_v1_2;
    TActor *actor_temp_v1_3;
    f32 phi_f12;
    f32 phi_f12_2;
    s32 phi_s0;
    f32 phi_f12_3;
    s16 phi_s0_2;
    void *phi_a0;
    AnimState *animState_phi_v0;
    f32 phi_f12_4;

    temp_t6 = arg3 & 0xFF;
    phi_f12 = arg2;
    if (arg2 > 1.0f) {
        phi_f12 = 1.0f;
    } else if (arg2 < 0.0f) {
        phi_f12 = 0.0f;
    }
    obj->animTimer = phi_f12;
    mdlInst = obj->modelInsts[obj->modelInstIdx];
    phi_f12_2 = phi_f12;
    if (mdlInst == 0) {

    } else {
        model = mdlInst->model;
        model_sp48 = model;
        if (model->animCount == 0) {

        } else {
            animState0 = mdlInst->animState0;
            sp2C = temp_t6;
            temp_t0 = animState0->unk_0x5a;
            animState0->unk_0x63 = (s8) temp_t6;
            animState0->unk_0x5a = 0;
            animState0->unk_0x64 = -1;
            animState0->animIndexes_prev = (u16) animState0->animIndexes_cur;
            animState0->unk_0x4_prev = (f32) animState0->unk_0x4_cur;
            animState0->unk_0x14_prev = (f32) animState0->unk_0x14_cur;
            animState0->unk_0xc_prev = (f32) animState0->unk_0xc_cur;
            animState0->unk_0x34_prev = (s32) animState0->unk_0x34_cur; //fishy
            animState0->unk_0x60_prev = (s8) animState0->unk_0x60_cur;
            animState0->unk_0x4c_prev[0] = (u16) animState0->unk_0x48;
            animState0->unk_0x3c_prev = (s32) animState0->unk_0x3c_cur;
            animState0->unk_0x5c = temp_t0;
            hitInfo = obj->objhitInfo;
            if ((hitInfo != 0) && (hitInfo->unk_0x0[8] != 0)) {
                arg2 = phi_f12;
                sp40 = animState0;
                func_80026AB8(phi_f12, obj, mdlInst, obj->unk0x46, hitInfo, animId, 0);
                phi_f12_2 = arg2;
            }
            temp_a2 = obj->ptr0x60;
            phi_f12_3 = phi_f12_2;
            if (temp_a2 != 0) {
                arg2 = phi_f12_2;
                sp40 = mdlInst->animState0;
                func_800228D0(phi_f12_2, obj, obj->unk0x46, temp_a2, animId, 0);
                phi_f12_3 = arg2;
            }
            prevAnimId = obj->curAnimId;
            obj->curAnimId = (s16) animId;
            temp_v1 = model_sp48->animCount;
            temp_s0 = model_sp48->animIdxs[animId >> 8] + (animId & 0xFF);
            phi_s0 = temp_s0;
            animState_phi_v0 = mdlInst->animState0;
            phi_f12_4 = phi_f12_3;
            phi_f12_4 = phi_f12_3;
            if (temp_s0 >= (s32) temp_v1) {
                phi_s0 = temp_v1 - 1;
            }
            phi_s0_2 = (s16) phi_s0;
            if (phi_s0 < 0) {
                phi_s0_2 = 0;
            }
            if ((model_sp48->unk_0x71 & 0x40) != 0) { //UseLocalModAnimTab
                if (((animId != prevAnimId) & 0xFF) != 0) {
                    mdlInst->animState0->unk_0x62 = (s8) (1 - mdlInst->animState0->unk_0x62);
                    temp_t7 = mdlInst->animState0->unk_0x62;
                    mdlInst->animState0->animIndexes_cur = (s16) temp_t7;
                    arg2 = phi_f12_3;
                    sp40 = mdlInst->animState0;
                    //load animation?
                    func_80019118(phi_f12_3, model_sp48->unk_0x30[phi_s0_2], phi_s0_2,
                        mdlInst->animState0->anims_cur[temp_t7 & 0xFFFF], model_sp48);
                    phi_f12_4 = arg2;
                }
                phi_a0 = (mdlInst->animState0 + (mdlInst->animState0->animIndexes_cur * 4))->anims_cur + 0x80;
                animState_phi_v0 = mdlInst->animState0;
            } else {
                mdlInst->animState0->animIndexes_cur = phi_s0_2;
                phi_a0 = model_sp48->unk_0x28[phi_s0_2 & 0xFFFF];
            }
            temp_v1_2 = phi_a0 + 6;
            animState_phi_v0->unk_0x34_cur = temp_v1_2;
            animState_phi_v0->unk_0x60_cur = (s8) (phi_a0->unk1 & 0xF0);
            animState_phi_v0->unk_0x14_cur = (f32) temp_v1_2->unk1;
            if (animState_phi_v0->unk_0x60_cur == 0) {
                animState_phi_v0->unk_0x14_cur = (f32) (animState_phi_v0->unk_0x14_cur - 1.0f);
            }
            temp_t0_2 = phi_a0->unk1 & 0xF;
            if ((temp_t0_2 != 0) && ((sp2C & 0x10) == 0)) {
                animState_phi_v0->unk_0x5e = (s16) (0x3FF / temp_t0_2);
                animState_phi_v0->unk_0x58 = (s16) 0x3FF;
                animState_phi_v0->unk_0xc_prev = (f32) animState_phi_v0->unk_0xc_cur;
            } else {
                animState_phi_v0->unk_0x58 = 0;
            }
            animState_phi_v0->unk_0xc_cur = 0.0f;
            animState_phi_v0->unk_0x4_cur = (f32) (animState_phi_v0->unk_0x14_cur * phi_f12_4);
            actor_temp_v1_3 = obj->linkedActor2;
            if ((actor_temp_v1_3 != 0) && (actor_temp_v1_3->objId == 0x30)) {
                state = actor_temp_v1_3->state;
                //XXX need to know what objId 0x30 is to know which type state is
                state->unk84 = (u8) (state->unk84 & 0xFFFE); //what?
            }
        }
    }
    return 0;
}
#endif

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

//this is wrong but I'm too tired to find out why
/* extern f32 D_8009983C;
s32 _func_800250F4(TActor *obj, f32 arg1) {
    s32 result = 0;
    if (arg1 > D_8009983C) {
        arg1 = 0;
    }
    else if (arg1 < D_8009983C) {
        arg1 = D_8009983C;
    }

    obj->unk0x9c = arg1;
    return result;
} */


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
