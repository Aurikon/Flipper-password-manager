#ifndef FPM_ADD_PASSWORD
#define FPM_ADD_PASSWORD

#include <gui/scene_manager.h>

void fpm_scene_add_password_on_enter(void* context);
bool fpm_scene_add_password_on_event(void* context, SceneManagerEvent event);
void fpm_scene_add_password_on_exit(void* context);

void fpm_scene_add_password_callback(void* context);

#endif
