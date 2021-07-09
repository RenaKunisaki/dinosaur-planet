/** Actor/Game Object system
 */
#ifndef _GAME_ACTOR_ACTOR_H
#define _GAME_ACTOR_ACTOR_H

//used for PlayerPosBuffer and something else
struct Vec3_Int{
	Vec3f f;
	u32 i; //seems to be a 32-bit bool. (for player pos buffer it's a frame count)
};

typedef struct {
/*0000*/    u8 unk_0x0[0x10 - 0x0];
/*0010*/	u8 *unk_0x10;
/*0014*/	u8 unk_0x14[0x44 - 0x14];
/*0044*/    s32 unk_0x44;
/*0048*/	u8 unk_0x48[0x5d - 0x48];
/*005D*/	s8 unk_0x5d;
/*005E*/    u8 unk_0x5e[0x71 - 0x5e];
/*0071*/    u8 unk_0x71;
/*0072*/	u8 unk_0x72;
} ActorUnk0x50;

typedef struct {
/*0000*/    u8 unk_0x0[0xc - 0x0];
/*000C*/    Gfx *gdl;
/*0010*/    u8 unk_0x10[0x20 - 0x10];
/*0020*/    Vec3f tr;
/*002C*/    u32 unk_0x2c;
/*0030*/    u32 flags;
} ActorUnk0x64;

//prelimnary, lots of unknowns
//contains pointer-to-own-type fields, so `typedef struct _TActor {`
//must be used instead of `typedef struct {`
typedef struct TActor {
/*0000*/    SRT srt;
/*0018*/    Vec3f positionMirror; //local vs global?
/*0024*/    Vec3f speed;
/*0030*/    struct TActor *linkedActor; //only used by update_objects?
/*0034*/    u8 unk_0x34;
/*0035*/    s8 matrixIdx;
/*0036*/    u8 unk_0x36;
/*0037*/    u8 unk_0x37;
/*0038*/    u32 unk_0x38;
/*003C*/    u8 unk0x3c[0x44 - 0x3c];
/*0044*/    UNK_TYPE_16 objId; //guessed from SFA
/*0046*/    s16 unk0x46;
/*0048*/    void* ptr0x48;
/*004C*/    UNK_TYPE_32 unk0x4c;
/*0050*/    ObjData* data;
/*0054*/    ActorObjhitInfo* objhitInfo;
/*0058*/    UNK_TYPE_32 unk0x58;
/*005C*/    void* ptr0x5c;
/*0060*/    void* ptr0x60;
/*0064*/    ActorUnk0x64* ptr0x64;
/*0068*/    DLLInstance **dll; //same in SFA
/*006C*/    u16 *ptr0x6c;
/*0070*/    void* ptr0x70;
/*0074*/    u32 unk0x74;
/*0078*/    u32 unk_0x78;
/*007C*/    ModelInstance **modelInsts;
/*0080*/    Vec3f positionMirror2; //gets copied twice.
/*008C*/    Vec3f positionMirror3; //not sure why.
/*0098*/    float animTimer; //guessed from SFA
/*009C*/    f32 unk0x9c;
/*00A0*/    s16 curAnimId;
/*00A2*/	s16 unk_0xa2;
/*00A4*/    u8 unk0xa4[0xac - 0xa4];
/*00AC*/    s8 mapId;
/*00AD*/    s8 modelInstIdx;
/*00AE*/    u8 unk0xae;
/*00AF*/    u8 unk0xaf;
/*00B0*/    u16 flags_B0;
/*00B2*/    u8 unk0xb2[6];
/*00B8*/    void* state; //type depends on object
/*00BC*/    UNK_TYPE_32 unk0xbc;
/*00C0*/    UNK_TYPE_32 unk0xc0;
/*00C4*/    UNK_TYPE_32 unk0xc4;
/*00C8*/    struct TActor *linkedActor2;
/*00CC*/    void* ptr0xcc;
/*00D0*/    u8 unk_0xd0[0xe4 - 0xd0];
} TActor; // size is 0xe4; other actor-related data is placed in the following memory

typedef struct ObjListItem {
	s16 count;
	s16 size;
	TActor *obj;
} ObjListItem;


extern u8 delayByte; //60/int(x) FPS x<=6
extern u8 delayByteMirror;
extern float delayFloat;
extern float delayFloatMirror;
extern float inverseDelay; // 1/delayByte
extern float inverseDelayMirror; // why the mirrors, if they aren't used?

extern struct TActor * object_pointer_array[]; //first is always player character.
extern u16 objectCount;
extern struct Vec3_Int Vec3_Int_array[];

extern int gNumObjs;
extern TActor **gObjList; //global object list

extern void **gLoadedObjDefs;
extern int gNumLoadedObjDefs;

extern ObjData **gLoadedObjData;
extern u8 *gObjRefCount; //pObjectRefCount

extern u8    D_800916B0;
extern s16   D_800B18E0;
extern void *D_800B18E4;
extern void *D_800B1918;
extern s32   D_800B191C;
extern s32   D_800B1928; //struct 0x38 bytes
extern s8    D_800B1930;
extern s32   D_800B1938; //some array
extern s32   D_800B1988;

TActor **TActor_getter(s32 idx, s32 *count);
void alloc_some_object_arrays(void);
void func_80020D34(void);
void init_objects(void);
void doNothing_80020A40(void);
void func_80020BB8();
void func_80020D34(void);
void func_80020D90(void);
TActor** get_world_actors(s32 *outFirst, s32 *outCount);
s32 get_num_objects(void);
s32 ret0_800212E8(void);
void copy_obj_position_mirrors(TActor *obj);
void objFreeObjDef(s32 defNo);
void doNothing_80022DD8(s32 a0, s32 a1, s32 a2);
s32 getObjIndexCount(void);
BOOL isObjIndexEntryValid(s32 defNo);
TActor *get_player(void);
void objClearMapId(TActor *arg);
void objUpdateMapId(TActor *obj);
void func_80023A00(s8 *arg0, s8 arg1);
void func_80023B34(s32 arg0);
void func_80024D74(TActor *obj, s32 arg1);
void func_80024DD0(TActor *obj, s32 arg1, s16 arg2, s16 arg3);
s16 func_80024E2C(TActor *arg0);
u8 func_80025CD4(s32 arg0);

#endif //_GAME_ACTOR_ACTOR_H
