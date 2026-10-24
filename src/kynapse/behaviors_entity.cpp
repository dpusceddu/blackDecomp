#include "include_asm.h"

#include "kynapse/agents/entity.hpp"
namespace KaimEntity {

Entity::Entity(const char*newName,int id) {
 child=0;ownerId=id;field24=0;owner=0;
 if(newName){name=(char*)KaimAllocate(strlen(newName)+1);strcpy(name,newName);}
 else{name=(char*)KaimAllocate(5);strcpy(name,"none");}
 int slots=GetAttributeRegistry()->count;attributeCount=slots;
 if(slots){attributes=(ObjectRoot**)KaimAllocate(slots*4);for(int i=0;i<attributeCount;++i)attributes[i]=0;}else attributes=0;
 handlers=new List<Handler*>(4);
}

Entity::~Entity() {
 Iterator<Handler*> it;
 while((it=handlers->Begin()).node)it.node->value->Detach(this);
 delete child;delete handlers;memoryRelease(name);
 if(attributeCount){for(int i=0;i<attributeCount;++i)if(attributes[i])delete attributes[i];memoryRelease(attributes);}
}

void Entity::Detach(Handler*value){Iterator<Handler*>it(handlers->head);for(;it.node;it.node=it.node->next){if(value==it.node->value){handlers->Remove(it);break;}}}

unsigned int Entity::GetId(){if(!node.node)return (unsigned int)-1;return ((unsigned int)node.node-(unsigned int)gWorld->entities->storage)/sizeof(Node<Entity*>);}
// Unmatched: Attach retains iterator return temporaries and register allocation differences.
// Unmatched: FindById retains iterator return/copy lifetime differences.
// Unmatched: attribute lookup and creation retain branch layout and index lifetime differences.
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E4798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E4860);
