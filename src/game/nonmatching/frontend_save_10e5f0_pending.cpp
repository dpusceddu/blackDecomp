// Unmatched: func_0010E5F0: two instructions in the item-count comparison.
#ifdef NONMATCHING
#include "game/frontend_resources.hpp"
extern "C" {
extern char *D_0040F0E0;
extern char *D_0040F4EC;
int func_0010B338(FrontendSaveState *, const char *);
void func_0010B3A8(FrontendSaveState *, const char *, const char *,
                   const char *, const char *);
int func_0010B4D8(FrontendSaveState *, int);
void func_0010B5B0(FrontendSaveState *);
void func_00215028(void *);
}
void FrontendSaveState::Disable() {
  switch (disableState) {
  case 0:
    if (((unsigned char *)D_0040F0E0)[0x20164] != 0) {
      func_0010B5B0(this);
      disableState = 1;
      break;
    }
    disableState = 2;
    break;
  case 1:
    if (!waiting) {
      func_0010B338(this, text[35]);
      func_0010B3A8(this, text[43], text[44], 0, 0);
      selected = 1;
      if (itemCount <= 1)
        selected = 0;
      func_0010B4D8(this, 2);
      break;
    }
    if (choice == 0) {
      ((unsigned char *)D_0040F0E0)[0x20164] = 0;
      func_00215028(D_0040F0E0 + 0x20258);
    } else if (choice != 1)
      break;
    disableState = 2;
    break;
  case 2:
    complete = 1;
    func_0010B5B0(this);
    break;
  }
}

#endif
