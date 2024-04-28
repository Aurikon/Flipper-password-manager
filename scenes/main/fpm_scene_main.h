#ifndef FPM_SCENE_MAIN
#define FPM_SCENE_MAIN

#include <gui/scene_manager.h>
#include "../../fpm_types.h"

void fpm_scene_main_on_enter(void* context);
bool fpm_scene_main_on_event(void* context, SceneManagerEvent event);
void fpm_scene_main_on_exit(void* context);

void fpm_scene_main_callback(void* context, uint32_t index);

typedef enum { FPM_MENU_ADD_PASSWORD_INDEX, FPM_MENU_READ_PASSWRODS_INDEX } FPMMenuIndex;
typedef enum { FPM_MENU_ADD_PASSWORD_EVENT, FPM_MENU_READ_PASSWORDS_EVENT } FPMMenuEvent;

#endif
