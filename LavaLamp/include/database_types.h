#pragma once
struct INDEX;
struct SPECIES;
struct MONSTER;
struct ATTACK;
struct EFFECT;
struct TAMER;
struct MOVESET;
struct TYPE;
struct EVOLUTION;
struct CONDITION;


enum { 
	LONG_TEXT_LENGTH = 101,
	STANDARD_TEXT_LENGTH = 51,
	SHORT_TEXT_LENGTH = 26,
	REAL_SHORT_TEXT_LENGTH = 6,
	THREE_LETTER_TEXT_LENGTH = 4,
	SIX_LETTER_TEXT_LENGTH = 7
};
#ifdef PLATFORM_MAC
#pragma options align=packed
#endif
typedef bool	CBOOL;
typedef char	CHAR;
typedef unsigned char	UCHAR;
typedef short	SHORT;
typedef unsigned short	USHORT;
typedef double	DOUBLE;
typedef long	LONG;
typedef unsigned long	ULONG;
struct INDEX
{
	char file_name[LONG_TEXT_LENGTH];       //
	int file_id;							// Data filename ID number
};
struct SPECIES
{
	char spc_name[LONG_TEXT_LENGTH];
	int spc_id;
	int spc_attack;
	int spc_defence;
	int spc_speed;
	int spc_hp;
	int typ_1;
	int typ_2;
	char spc_model[LONG_TEXT_LENGTH];
};
struct MONSTER
{
	char mst_nickname[LONG_TEXT_LENGTH];
	int spc_id;
	int mst_id;
	int mst_level;
	int mst_attack_i;
	int mst_defence_i;
	int mst_speed_i;
	int mst_hp_i;
	int mst_attack_e;
	int mst_defence_e;
	int mst_speed_e;
	int mst_hp_e;
	int mst_attack1;
	int mst_attack2;
	int mst_attack3;
	int mst_attack4;
};
struct ATTACK
{
	CHAR att_name[LONG_TEXT_LENGTH];
	int att_id;
	int att_pow;
	int att_acc;
	int att_cool;
	int eff_id;
	int typ_1;
};
struct EFFECT
{
	int eff_id;
	CHAR eff_detail[LONG_TEXT_LENGTH];
};
struct TAMER
{
	CHAR tmr_title[LONG_TEXT_LENGTH];
	CHAR tmr_name[LONG_TEXT_LENGTH];
	int tmr_id;
	int tmr_x;
	int tmr_y;
	int mst_1;
	int mst_2;
	int mst_3;
};
struct MOVESET
{
	int mst_id;
	int att_id;
	int mv_lev;
};
struct TYPE
{
	int typ_id;
	CHAR typ_detail[LONG_TEXT_LENGTH];
};
struct EVOLUTION
{
	int mst_from;
	int mst_to;
	int cnd_id;//condition
	int cnd_lvl;
};
struct CONDITION
{
	int cnd_id;
	CHAR cnd_detail[LONG_TEXT_LENGTH];
};
struct ENCOUNTER
{
	int enc_id;
	int enc_set;
	int spc_id;
	int mst_lvl;
	int enc_rate;
};
