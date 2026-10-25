#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/settings.hpp"

// /SLUS_213.76 0x2e4070

Settings& Settings::operator=(const Settings& other)
{
    field00 = other.field00;
    field04 = other.field04;
    field08 = other.field08;
    field0c = other.field0c;
    field10 = other.field10;
    field14 = other.field14;
    field18 = other.field18;
    field1c = other.field1c;
    field20 = other.field20;
    field24 = other.field24;
    field28 = other.field28;
    field2c = other.field2c;
    field30 = other.field30;
    field34 = other.field34;
    field38 = other.field38;
    field3c = other.field3c;
    field40 = other.field40;
    field44 = other.field44;
    field48 = other.field48;
    field4c = other.field4c;
    field50 = other.field50;
    field54 = other.field54;
    field58 = other.field58;
    field5c = other.field5c;
    field60 = other.field60;
    field64 = other.field64;
    field68 = other.field68;
    field6c = other.field6c;
    field70 = other.field70;
    return *this;
}

