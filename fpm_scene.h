#ifndef FPM_SCENE
#define FPM_SCENE

#include "scenes/main/fpm_scene_main.h"

void (*const fpm_scene_on_enter_handlers[])(void*) = {fpm_scene_main_on_enter, /*FPM_MAIN*/};
bool (*const fpm_scene_on_event_handlers[])(void*, SceneManagerEvent) = {
    fpm_scene_main_on_event, /*FPM_MAIN*/
};
void (*const fpm_scene_on_exit_handlers[])(void*) = {fpm_scene_main_on_exit, /*FPM_MAIN*/};

#endif
