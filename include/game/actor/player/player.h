/** Player system
 */
#ifndef _GAME_ACTOR_PLAYER_PLAYER_H
#define _GAME_ACTOR_PLAYER_PLAYER_H

//pointer at 0x34c of "state" struct
struct CharacterStats{
	u8 unk0x0;
	s8 HPCurr;
	s8 HPMax; //only shows up to 104, code caps it at 80.
	u8 unk0x3; //aligning?
	s16 ManaCurr; //only mods when byte at "state"0x8bb is set.
	s16 ManaMax; //capped at 100.
	s16 Scarabs; //capped at 999.
	u8 unk0xa;
	u8 unk0xb;
};//seemingly consistent addrs: Fox/Sabre at 0x805c3964, Krystal 0x805c3970.

extern struct CharacterStats * charStats_pointer;

extern s32 PlayerPosBuffer_index;
extern struct Vec3_Int PlayerPosBuffer[60]; //seems to buffer player coords with "timestamp"

#endif //_GAME_ACTOR_PLAYER_PLAYER_H
