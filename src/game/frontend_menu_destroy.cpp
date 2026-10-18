#include "game/frontend_resources.hpp"
extern "C" {
void func_00109E70(void *);
void func_0010A860(void *);
int func_00102080(void *);
}
void FrontendMenuState::Destroy() {
  func_00109E70(loader);
  func_0010A860(message);
  if (archive) {
    func_00102080(archive);
    archive = 0;
  }
  state = 57;
}
