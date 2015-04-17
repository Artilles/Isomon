#include <vector>
struct MONSTERACTUAL
{
	char mst_nickname[LONG_TEXT_LENGTH];
	char spc_name[LONG_TEXT_LENGTH];
	int mst_id;
	int mst_level;
    int attack;
	int defence;
	int speed;
	int hp;
	int currenthp;
	int typ_1;
	int typ_2;
	char spc_model[LONG_TEXT_LENGTH];
	int att_1;
	int att_2;
	int att_3;
	int att_4;
	int cool_1;
	int cool_2;
	int cool_3;
	int cool_4;
	int mst_xp;
int spc_id;
};
struct SPECIESSET
{
	int spc_id;
	int mst_lvl;
	int enc_rate;
};
struct ENCOUNTERACTUAL
{
	vector<SPECIESSET> species;
	int enc_steprate;
	int enc_id;
};
struct ITEM
{
	int id;
	char name[LONG_TEXT_LENGTH];
	int count;
};