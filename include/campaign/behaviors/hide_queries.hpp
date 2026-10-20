// PS2 query temporary: vptr at 0, axis at 0x24, component at 0x30.
#ifndef BLACK_CAMPAIGN_HIDE_QUERIES_HPP
#define BLACK_CAMPAIGN_HIDE_QUERIES_HPP
#include "campaign/behaviors/hide.hpp"
namespace HideQueries {
struct Root { virtual ~Root() {} };
struct Base:Root {
    int fields[8];
    Base() __asm__("func_002E7360");
    virtual ~Base() {}
};
struct Vec3 {
    float x,y,z;
    Vec3(const HideRecovery::Vec3& v):x(v.x),y(v.y),z(v.z) {}
};
struct Query:Base {
    Vec3 axis;
    int component,extra;
    Query(const HideRecovery::Vec3& source,int c,int e):axis(source),component(c),extra(e) {}
    virtual ~Query() {}
};
typedef char QuerySize[sizeof(Query)==0x38?1:-1];
}
#endif
