#ifndef ICEMANAGER_H
#define ICEMANAGER_H

#include <stdbool.h>

void ICEManager_SetActionQ(void* ActionQ);
void ICEManager_EditorOn();
void ICEManager_EditorOff();
bool ICEManager_IsEditorOn();
//uintptr_t ICEManager_Get();

#endif