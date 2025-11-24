#include "ActionQueue.h"

bool(*pActionQueue_IsEmpty)(void* ActionQ) = (bool(*)(void*))(0x2DAD38);
ActionRef(*pActionQueue_GetAction)(void* ActionQ) = (ActionRef(*)(void*))(0x2DAF88);
void(*pActionQueue_PopAction)(void* ActionQ) = (void(*)(void*))(0x002DAED0);
//void(*pActionQueue_Flush)(void* ActionQ) = (void(*)(void*))(0x2DAF10);
void(*pActionQueue_ActionQueue)(void* ActionQ, int port, uint64_t config, const char* queue_name, bool required) = (void(*)(void*, int, uint64_t, const char*, bool))(0x2DA3E8);


bool ActionQueue_IsEmpty(void* ActionQ)
{
	return pActionQueue_IsEmpty(ActionQ);
}

ActionRef ActionQueue_GetAction(void* ActionQ)
{
	return pActionQueue_GetAction(ActionQ);
}

void ActionQueue_PopAction(void* ActionQ)
{
	return pActionQueue_PopAction(ActionQ);
}

void ActionQueue_ActionQueue(void* ActionQ, int port, uint64_t config, const char* queue_name, bool required)
{
	return pActionQueue_ActionQueue(ActionQ, port, config, queue_name, required);
}
