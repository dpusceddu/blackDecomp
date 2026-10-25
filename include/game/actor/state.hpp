// Partial actor view. Names and full allocation size remain unverified.
#ifndef BLACK_ACTOR_STATE_HPP
#define BLACK_ACTOR_STATE_HPP
namespace ActorParts {
struct Request {int kind;int unknown;int first;int second;unsigned char flag;};
struct Owner {
 inline void * Animation() {return *(void**)((char*)this+0x330);}
 inline void * Action() {return *(void**)((char*)this+0x2a4);}
};
class Controller {
public:
 inline Owner*& OwnerRef(){return *(Owner**)((char*)this+0x7c);}
 inline int& State(){return *(int*)((char*)this+0x90);}
 inline unsigned char& Active(){return *(unsigned char*)((char*)this+0xb8);}
 inline unsigned char& Player(){return *(unsigned char*)((char*)this+0xb9);}
 inline int& Target(){return *(int*)((char*)this+0xbc);}
 inline unsigned char& Entered(){return *(unsigned char*)((char*)this+0xc1);}
 void Update();
 unsigned char Aim() __asm__("func_0013DF58");
 void Follow(int) __asm__("func_0013EB00");
 void Finish() __asm__("func_0013EE20");
};
}
#endif
