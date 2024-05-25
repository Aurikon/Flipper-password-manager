#ifndef FPM_ADD_PASSWORD
#define FPM_ADD_PASSWORD

#include <gui/scene_manager.h>
#include "fpm_types.h"

void fpm_add_password_name_callback(void* context);
void fpm_scene_add_password_name_on_enter(void* context);
bool fpm_scene_add_password_name_on_event(void* context, SceneManagerEvent event);
void fpm_scene_add_password_name_on_exit(void* context);

void fpm_add_password_callback(void* context);
void fpm_scene_add_password_on_enter(void* context);
bool fpm_scene_add_password_on_event(void* context, SceneManagerEvent event);
void fpm_scene_add_password_on_exit(void* context);

bool fpm_save_password(PasswordManagerState* state);
bool fpm_make_folder(PasswordManagerState* state);

typedef enum {
    FPM_ADD_PASSWORD_INPUT_PASSWORD_EVENT,
    FPM_ADD_PASSWORD_SAVE_EVENT
} FPMAddPasswordEvent;

#endif
