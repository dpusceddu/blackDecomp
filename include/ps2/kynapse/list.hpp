// PS2 list/iterator prefixes used by the exact shooter traversal. Full container sizes,
// allocation policies and unused node fields remain UNVERIFIED. Do not conflate with
// the older full List hypotheses in kynapse/kynapse.hpp.
#ifndef BLACK_PS2_KYNAPSE_LIST_HPP
#define BLACK_PS2_KYNAPSE_LIST_HPP
namespace Kaim {
struct PolyRoot { virtual ~PolyRoot() {} };
template <class T> struct ListNode : PolyRoot {
    virtual ~ListNode() {}
    T value;
    ListNode* previous;
    ListNode* next;
};
template <class T> struct List : PolyRoot {
    virtual ~List() {}
    ListNode<T>* storage;
    ListNode<T>* head;
};

struct Actor;
struct ActorIterator : PolyRoot {
    ListNode<Actor*>* node;
    ActorIterator(ListNode<Actor*>* n) : node(n) {}
    ~ActorIterator() {}
    ActorIterator& operator++() { node=node->next;return *this; }
};

typedef char ActorIteratorNodeAt4[(unsigned int)&((ActorIterator*)0)->node == 4 ? 1 : -1];
typedef char ActorNodeValueAt4[(unsigned int)&((ListNode<Actor*>*)0)->value == 4 ? 1 : -1];
typedef char ActorNodeNextAt12[(unsigned int)&((ListNode<Actor*>*)0)->next == 12 ? 1 : -1];
typedef char ActorListHeadAt8[(unsigned int)&((List<Actor*>*)0)->head == 8 ? 1 : -1];
}
#endif
