#ifndef FPM_READ_PASSWORDS
#define FPM_READ_PASSWORDS

#include <gui/scene_manager.h>

void fpm_scene_read_passwords_on_enter(void* context);
bool fpm_scene_read_passwords_on_event(void* context, SceneManagerEvent event);
void fpm_scene_read_passwords_on_exit(void* context);

void fpm_scene_read_passwords_callback(void* context, uint32_t index);

#endif
