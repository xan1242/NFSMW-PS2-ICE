#ifndef EVIEWPLATINTERFACE_H
#define EVIEWPLATINTERFACE_H

void eViewPlatInterface_Render(void* obj, void* poly, void* texture_info, int use_previous_data);
//void eViewPlatInterface_Render_WithMask(void* obj, void* poly, void* texture_info, void* mask_texinfo, int use_previous_data);
void eViewPlatInterface_Init();

#endif