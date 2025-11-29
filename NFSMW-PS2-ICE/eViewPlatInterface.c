#include "eViewPlatInterface.h"
#include "includes/minjector.h"

void(*p_eViewPlatInterface_Render)(void* obj, void* poly, void* texture_info, int use_previous_data) = (void(*)(void*, void*, void*, int))(0);
//void(*p_eViewPlatInterface_Render_WithMask)(void* obj, void* poly, void* texture_info, void* mask_texinfo, int use_previous_data) = (void(*)(void*, void*, void*, void*, int))(0);

//uintptr_t p_eViews;

void eViewPlatInterface_Render(void* obj, void* poly, void* texture_info, int use_previous_data)
{
	return p_eViewPlatInterface_Render(obj, poly, texture_info, use_previous_data);
}

//void eViewPlatInterface_Render_WithMask(void* obj, void* poly, void* texture_info, void* mask_texinfo, int use_previous_data)
//{
//	return p_eViewPlatInterface_Render_WithMask(obj, poly, texture_info, mask_texinfo, use_previous_data);
//}


void eViewPlatInterface_Init()
{
	//p_eViews = 0x4F68A0;

	uintptr_t loc_256390 = 0x256390;
	p_eViewPlatInterface_Render = (void(*)(void*, void*, void*, int))(minj_GetBranchDestination(loc_256390));

	//uintptr_t loc_256370 = 0x256370;
	//p_eViewPlatInterface_Render_WithMask = (void(*)(void*, void*, void*, void*, int))(minj_GetBranchDestination(loc_256370));
}