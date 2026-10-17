// Declarations of the Kynapse source module "settings" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_SETTINGS_HPP
#define BLACK_KYNAPSE_MODULE_SETTINGS_HPP
#include "kynapse/compat.hpp"

// Engine settings record: 29 integer slots, copied member by member.

struct Settings {
    int field00;
    int field04;
    int field08;
    int field0c;
    int field10;
    int field14;
    int field18;
    int field1c;
    int field20;
    int field24;
    int field28;
    int field2c;
    int field30;
    int field34;
    int field38;
    int field3c;
    int field40;
    int field44;
    int field48;
    int field4c;
    int field50;
    int field54;
    int field58;
    int field5c;
    int field60;
    int field64;
    int field68;
    int field6c;
    int field70;

    Settings(int first, int unused);
    Settings& operator=(const Settings& other);
};





#endif
