/** Animation system
 */
#ifndef _SYS_GFX_ANIMATION_H
#define _SYS_GFX_ANIMATION_H

typedef struct
{
/*0000*/    u8 unk_0x0;
/*0001*/	u8 unk_0x1;
/*0002*/	s16 unk_0x2;
} Animation;

typedef struct
{
/*0000*/    u32 unk_0x0;
/*0004*/    f32 unk_0x4_cur;
/*0008*/    f32 unk_0x4_prev;
/*000C*/    u32 unk_0xc_cur;
/*0010*/    u32 unk_0xc_prev;
/*0014*/    f32 unk_0x14_cur;
/*0018*/    f32 unk_0x14_prev;
/*001C*/    u8 *anims_cur; // Each item contains 0x80 bytes of amap data, followed by an Animation structure
/*0020*/    u8 *anims_prev;
/*0024*/    u8 *anims2_cur;
/*0028*/    u8 *anims2_prev;
/*002C*/	u8 *unk_0x2c_cur;
/*0030*/	u8 *unk_0x2c_prev;
/*0034*/    u8 *unk_0x34_cur;
/*0038*/    u8 *unk_0x34_prev;
/*003C*/    u8 unk_0x3c_cur;
/*003D*/    u8 unk_0x3c_prev;
/*003E*/    u8 unk_0x3e[0x44 - 0x3e];
/*0044*/    u16 animIndexes_cur;
/*0046*/    u16 animIndexes_prev;
/*0048*/	u32 unk_0x48;
/*004C*/	u16 unk_0x4c_cur[3];
/*0052*/	u16 unk_0x4c_prev[3];
/*0058*/    s16 unk_0x58; //array of unknown size
/*005A*/	s16 unk_0x5a;
/*005C*/	s16 unk_0x5c;
/*005E*/	u16 unk_0x5e;
/*0060*/    s8 unk_0x60_cur;
/*0061*/    s8 unk_0x60_prev;
/*0062*/    u8 unk_0x62; //probably bool
/*0063*/    s8 unk_0x63;
/*0064*/    s8 unk_0x64;
} AnimState;

#endif //_SYS_GFX_ANIMATION_H
