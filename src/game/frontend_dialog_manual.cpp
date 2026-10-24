#include "game/frontend/save_dialog.hpp"

extern "C" int func_00275260(const char *, void *, int);
extern "C" void func_0010B4D8(void *, int);
void FrontendSaveDialog::SetMessage(const char* text)
{
  short changed;
  changed = 1;
  message[0] = 0;
  message[1] = 0;
  if (text != 0)
  {
    func_00275260(text, message, 0x188);
    timeout = 3.2f;
  }
  else
  {
    timeout = 0;
    func_0010B4D8(this, 0);
  }
  flags[2] = changed;
  slot = -1;
}

#include "game/frontend/save_dialog.hpp"
extern "C" void func_0010B338(void*,const short*);
extern "C" void func_0010B3A8(void*,const short*,const short*,const short*,const short*);
extern "C" void func_0010B4D8(void*,int);
void FrontendSaveDialog::ClearMessage() { func_0010B338(this,0);func_0010B3A8(this,0,0,0,0);func_0010B4D8(this,0);flags[3]=0;slot=-1;}
