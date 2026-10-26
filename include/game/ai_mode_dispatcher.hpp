#ifndef GAME_AI_MODE_DISPATCHER_HPP
#define GAME_AI_MODE_DISPATCHER_HPP
#include "game/ai_action.hpp"

/* Partial mode lifecycle API. Native mode numbers and most virtual operations
 * still lack gameplay names. Bit 0x10 excludes the other flag bits. */
extern "C" {
void ModeDispatcher_ReplaceStorageKind(Game::ModeDispatcher* self, signed char kind);
Game::Recovered_DispatchedMode* ModeDispatcher_ActiveMode(Game::ModeDispatcher* self);
void ModeDispatcher_SetMode(Game::ModeDispatcher* self, Game::Recovered_ModeDescriptor* descriptor);
void ModeDispatcher_FindAndSetMode(Game::ModeDispatcher* self, void* key);
int ModeDispatcher_Reset(Game::ModeDispatcher* self);
void ModeDispatcher_ClearBinding(Game::ModeDispatcher* self);
unsigned char ModeDispatcher_IsPaused(Game::ModeDispatcher* self);
void ModeDispatcher_Resume(Game::ModeDispatcher* self);
void ModeDispatcher_Pause(Game::ModeDispatcher* self);
void ModeDispatcher_SetParameter(Game::ModeDispatcher* self, int value);
void ModeDispatcher_SetFlags(Game::ModeDispatcher* self, signed char flags);
void ModeDispatcher_ClearFlags(Game::ModeDispatcher* self);
void ModeDispatcher_SetFlag2(Game::ModeDispatcher* self);
}
#endif
