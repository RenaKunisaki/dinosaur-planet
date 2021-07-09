/** Object (actor) data in OBJECTS.BIN.
 */
#ifndef _GAME_ACTOR_OBJDATA_H
#define _GAME_ACTOR_OBJDATA_H

enum ObjDataFlags44 { //copied from SFA; may be incorrect
    OBJDATA_FLAG44_HaveModels               = 0x00000001,
    OBJDATA_FLAG44_DifferentLightColor      = 0x00000010,
    OBJDATA_FLAG44_ModelRelated             = 0x00000020,
    OBJDATA_FLAG44_HasChildren              = 0x00000040,
    OBJDATA_FLAG44_EnableCulling            = 0x00000400,
    OBJDATA_FLAG44_UseDifferentModelLoading = 0x00000800,
    OBJDATA_FLAG44_DifferentCulling         = 0x00080000,
    OBJDATA_FLAG44_KeepHitboxWhenInvisible  = 0x00200000,
    OBJDATA_FLAG44_HasEvent                 = 0x00400000,
    OBJDATA_FLAG44_DidLoadModels            = 0x00800000
};

enum ObjShadowType { //copied from SFA; may be incorrect
    OBJ_SHADOW_NONE = 0x0,
    OBJ_SHADOW_BOX = 0x1,
    OBJ_SHADOW_GEOM = 0x2,
    OBJ_SHADOW_UNK03 = 0x3,
    OBJ_SHADOW_BLUE_GLOWING_RECT = 0x4
};

enum ObjDataFlags5F { //copied from SFA; may be incorrect
    OBJDATA_FLAG5F_CrazyTranslucentEffect   = 0x01, //for HagabonMk2?
    OBJDATA_FLAG5F_ShadowUsesNoTexture      = 0x02,
    OBJDATA_FLAG5F_ShadowUsesDepthTest      = 0x04,
    OBJDATA_FLAG5F_DontFollowParentRotation = 0x08,
    OBJDATA_FLAG5F_NoShadow                 = 0x10, //force depth test if 0x01 also set
    OBJDATA_FLAG5F_Visible                  = 0x20,
    OBJDATA_FLAG5F_DifferentTextures        = 0x80  //Super dark
};

//A point on a model where something like a weapon can be attached.
typedef struct AttachPoint { //copied from SFA; may be incorrect
/*00*/ Vec3f pos; //offset from bone
/*0C*/ Vec3s rot; //offset from bone
/*12*/ s8 bone; //bone idx to use
/*13*/ s8 unk13; //always same as bone?
/*14*/ s8 unk14; //always same as bone?
/*15*/ u8 unk15; //always 0xCD?
/*16*/ u8 unk16; //always 0xCD?
/*17*/ u8 unk17; //always 0xCD?
} AttachPoint;

typedef struct AButtonInteraction { //copied from SFA; may be incorrect
/*00*/ s16 unk00;
/*02*/ s16 unk02;
/*04*/ s16 unk04;
/*06*/ UNK_TYPE_8 unk06;
/*07*/ UNK_TYPE_8 unk07;
/*08*/ UNK_TYPE_8 unk08;
/*09*/ UNK_TYPE_8 unk09;
/*0a*/ UNK_TYPE_8 unk0a;
/*0b*/ UNK_TYPE_8 unk0b;
/*0c*/ UNK_TYPE_8 unk0c;
/*0d*/ UNK_TYPE_8 unk0d;
/*0e*/ UNK_TYPE_8 unk0e;
/*0f*/ UNK_TYPE_8 unk0f;
/*10*/ u8 unk10;
/*11*/ UNK_TYPE_8 unk11;
/*12*/ UNK_TYPE_8 unk12;
/*13*/ UNK_TYPE_8 unk13;
/*14*/ UNK_TYPE_8 unk14;
/*15*/ UNK_TYPE_8 unk15;
/*16*/ UNK_TYPE_8 unk16;
/*17*/ UNK_TYPE_8 unk17;
} AButtonInteraction;

//Entry in OBJECTS.BIN, aka ObjectFileStruct (made-up name)
//debug messages imply ObjData is the correct name or close to it
//offsets are converted to pointers when loaded
/*eg:  0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F   0123 4567 89AB CDEF
0000  40 40 00 00  3D 4A C0 83  00 00 00 AC  00 00 03 94   @@.. =J.. .... ....
0010  00 00 03 B2  00 00 00 00  00 00 00 00  00 00 04 D4   .... .... .... ....
0020  00 00 00 F4  00 00 00 BC  00 00 03 54  00 00 03 E4   .... .... ...T ....
0030  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00   .... .... .... ....
0040  00 00 00 00  00 00 00 10  00 02 00 30  00 31 FF 9C   .... .... ...0 .1..
0050  00 0A 03 00  02 00 00 00  80 01 00 01  00 04 03 53   .... .... .... ...S
0060  61 62 72 65  00 00 00 00  00 00 00 00  00 00 00 0C   abre .... .... ....
0070  0A 0F 0A 00  01 00 00 00  FF FF 00 0C  02 05 FF 00   .... .... .... ....
0080  00 00 00 B3  27 51 FF 02  00 00 00 00  00 00 00 01   .... 'Q.. .... ....
0090  08 0A 14 12  FF FF 00 25  01 7F 7F 00  00 00 00 00   .... ...% .... ....
00A0  FF FF FF FF  FF FF FF FF  FF FF FF FF  00 00 00 07   .... .... .... ....
       0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F   0123 4567 89AB CDEF */
typedef struct ObjData { //originally copied from SFA; many fields likely incorrect
/*00*/ float unk00; //copied to shadow field 0
/*04*/ float scale;
/*08*/ u32 *pModelList; //-> list of model IDs
/*0c*/ UNK_PTR *textures;
/*10*/ UNK_PTR *unk10;
/*14*/ UNK_PTR *unk14;
/*18*/ UNK_PTR *unk18;
/*1c*/ UNK_PTR *unk1C;
/*20*/ UNK_PTR *unk20;
/*24*/ UNK_PTR *unk24;
/*28*/ UNK_PTR *unk28;
/*2c*/ UNK_PTR *unk2C;
/*30*/ s16 *pModLines; //should be correct (see objFreeObjDef)
/*34*/ UNK_PTR *pIntersectPoints; //should be correct (see objFreeObjDef)
/*38*/ u32 unk38;
/*3c*/ u32 unk3C;
/*40*/ u32 unk40;
/*44*/ u32 flags; //ObjDataFlags44
/*48*/ s16 shadowType; //ObjShadowType (guessed)
/*4a*/ s16 shadowTexture;
/*4c*/ UNK_TYPE_8 unk4C;
/*4d*/ UNK_TYPE_8 unk4D;
/*4e*/ u16 hitbox_flags60; //HitboxFlags60
/*50*/ s16 dllNo; //if not -1, load this DLL; func 0 is a model callback
/*52*/ UNK_TYPE_8 unk52;
/*53*/ UNK_TYPE_8 unk53;
/*54*/ UNK_TYPE_8 unk54;
/*55*/ u8 nModels;
/*56*/ u8 numPlayerObjs; //if > 0, objAddObjectType(obj, 8)
/*57*/ u8 unk57; //never read?
/*58*/ u8 nAttachPoints;
/*59*/ u8 nTextures; //-> 0x10 bytes
/*5a*/ s16 objId;
/*5c*/ s8 modLinesSize; //ignored in file
/*5d*/ s8 modLinesIdx;
/*5e*/ u8 numSeqs;
/*5f*/ char name[15];
//most fields beyond here are copied from SFA and probably are wrong.
/*60*/ u8 hitbox_fieldB0;
/*61*/ u8 hasHitbox; //or # hitboxes, but should only be 1
/*62*/ u8 hitboxSizeXY;
/*63*/ u8 hitbox_field6A;
/*64*/ u8 hitbox_field6B;
/*65*/ u8 hitbox_flags62;
/*66*/ u8 unk66;
/*67*/ u8 hitbox_fieldB5;
/*68*/ s16 hitboxSizeX1;
/*6a*/ s16 hitboxSizeY1; // > 0x169 = no shadow; also hitbox related
/*6c*/ s16 hitboxSizeZ1;
/*6e*/ s16 hitboxSizeZ2;
/*70*/ u8 hitbox_fieldB4; //related to hitbox (height?)
/*71*/ u8 flags_0x71; //related to hitbox
/*72*/ u8 numAButtonInteractions;
/*73*/ u8 stateVar73; //1=translucent; 3=invincible - not flags
/*74*/ u8 unk74;
/*75*/ u8 unk75;
/*76*/ s16 modLineCount;
/*78*/ s16 modLineNo;
/*7a*/ u8 unk7A;
/*7b*/ u8 unk7B;
/*7c*/ s16 helpTexts[4]; //one per model (GameTextId)
/*84*/ s16 unk84;
/*86*/ s16 unk86;
/*88*/ float lagVar88; //causes lag at ~65536.0; GPU hang at much more; related to shadow; maybe causing excessive map loads?
/*8c*/ u8 nLights;
/*8d*/ u8 lightIdx;
/*8e*/ u8 colorIdx; //related to textures; 1=dark, 2=default, 3+=corrupt, 77=crash, 0=normal
/*8f*/ u8 unk8F; //related to hitbox
/*90*/ u8 hitbox_flagsB6; // < 0xE = invincible (HitboxFlags62)
/*91*/ UNK_TYPE_8 unk91;
/*92*/ UNK_TYPE_8 unk92;
/*93*/ UNK_TYPE_8 unk93;
/*94*/ UNK_TYPE_8 unk94;
/*95*/ UNK_TYPE_8 unk95;
/*96*/ UNK_TYPE_8 unk96;
/*97*/ UNK_TYPE_8 unk97;
/*98*/ UNK_TYPE_8 unk98;
/*99*/ UNK_TYPE_8 unk99;
/*9A*/ UNK_TYPE_8 unk9A;
/*9B*/ u8 unk9B;
/*9C*/ UNK_TYPE_8 unk9C;
/*9D*/ UNK_TYPE_8 unk9D;
/*9E*/ UNK_TYPE_8 unk9E;
/*9F*/ UNK_TYPE_8 unk9F;
/*A0*/ UNK_TYPE_32 unkA0;
/*A4*/ UNK_TYPE_32 unkA4;
/*A8*/ UNK_TYPE_32 unkA8;
/*AC*/ UNK_TYPE_32 unkAC;
} ObjData; //size = 0xB0; other data follows, is pointed to by this struct


#endif //_GAME_ACTOR_OBJDATA_H
