/** Actor hit detection system
 */

enum PolygonType { //copied from SFA, may be incorrect
    POLY_TYPE_WATER = 0x0E,
    POLY_TYPE_METAL_OR_ROCK = 0x19,
    NUM_POLY_TYPES = 0x24
};

enum HitboxFlags60 { //copied from SFA, may be incorrect
    HITBOX_FLAG60_Disabled = 0x1,
    HITBOX_FLAG60_NeedPosUpdate = 0x40,
    HITBOX_FLAG60_LockRotY = 0x800,
    HITBOX_FLAG60_LockRotZ = 0x1000
};

enum HitboxFlags62 { //copied from SFA, may be incorrect
    HITBOX_FLAG62_ScaleBySize = 0x1,
    HITBOX_FLAG62_SizeFlag2 = 0x2,
    HITBOX_FLAG62_DontUpdate = 0x8,
    HITBOX_FLAG62_UseModelField14 = 0x20
};

typedef struct {
/*0000*/    u8 unk_0x0[0x5a - 0x0];
/*005A*/    u8 unk_0x5a;
/*005B*/    u8 unk_0x5b[0x9f - 0x5b];
/*009F*/    s8 unk_0x9f;
} ActorObjhitInfo;

typedef struct {
    //copied from SFA. some fields don't exist in this version,
    //but not sure which. they come before 0x60
/*0x00*/ TActor *curTouchedObject;
/*0x04*/ s16 objHitsSize; //this >> 2 = #ptrs at field 8
/*0x06*/ s16 maxHitsSize;
/*0x08*/ ObjHitsEntry *objHits; //from OBJHITS.bin
/*0x0c*/ float sizeXY_0C;
/*0x10*/ vec3f pos;
/*0x1c*/ vec3f prevPos;
/*0x28*/ vec3f size;
/*0x34*/ float minSizeY;
/*0x38*/ float sizeY;
/*0x3c*/ vec3f unk3C;
/*0x48*/ undefined4 unk48;
/*0x4c*/ UNK_TYPE_32 unk4C;
/*0x50*/ TActor *lastTouchedObject;
/*0x54*/ UNK_TYPE_8 unk54;
/*0x55*/ UNK_TYPE_8 unk55;
/*0x56*/ UNK_TYPE_8 unk56;
/*0x57*/ UNK_TYPE_8 unk57;
/*0x58*/ u16 lowestDist; //never resets?
/*0x5a*/ s16 sizeXY;
/*0x5c*/ s16 sizeX1;
/*0x5e*/ s16 sizeX2;
/*0x60*/ u16 flags_0x60; //HitboxFlags60
/*0x62*/ u8 flags_0x62; //HitboxFlags62
/*0x63*/ UNK_TYPE_8 unk63;
/*0x64*/ s16 sizeZ;
/*0x66*/ s16 sizeZ1;
/*0x68*/ s16 sizeZ2;
/*0x6a*/ UNK_TYPE_8 unk6A;
/*0x6b*/ UNK_TYPE_8 unk6B;
/*0x6c*/ s8 damage;
/*0x6d*/ UNK_TYPE_8 unk6D;
/*0x6e*/ UNK_TYPE_8 unk6E;
/*0x6f*/ UNK_TYPE_8 unk6F;
/*0x70*/ UNK_TYPE_8 unk70;
/*0x71*/ byte nHits; //max 3; only used for damage?
/*0x72*/ u8 sphereIdxs[3];
/*0x75*/ u8 objField6C[3];
/*0x78*/ u8 recordedDamage[3];
/*0x7b*/ UNK_TYPE_8 unk7B;
/*0x7c*/ TActor *objs[3];
/*0x88*/ float objX[3];
/*0x94*/ float objY[3];
/*0xa0*/ float objZ[3];
/*0xac*/ u8 typeOfPolyHit; //PolygonType
/*0xad*/ UNK_TYPE_8 unkAD;
/*0xae*/ s8 disable; //probably bool
/*0xaf*/ s8 state;
/*0xb0*/ UNK_TYPE_8 unkB0;
/*0xb1*/ UNK_TYPE_8 unkB1;
/*0xb2*/ s16 unkB2;
/*0xb4*/ UNK_TYPE_8 unkB4;
/*0xb5*/ UNK_TYPE_8 unkB5;
/*0xb6*/ u8 flagsB6; //HitboxFlags62
} HitState;
