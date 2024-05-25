#ifndef FPM_SCENE
#define FPM_SCENE

#include "scenes/main/fpm_scene_main.h"
#include "scenes/add_password/fpm_add_password.h"
#include "scenes/read_passwords/fpm_read_passwords.h"

void (*const fpm_scene_on_enter_handlers[])(void*) = {
    fpm_scene_main_on_enter, /*FPM_MAIN*/
    fpm_scene_add_password_name_on_enter, /*FPM_ADD_PASSWORD_NAME*/
    fpm_scene_add_password_on_enter, /*FPM_ADD_PASSWORD*/
    fpm_scene_read_passwords_on_enter, /*FPM_READ_PASSWORDS*/
};
bool (*const fpm_scene_on_event_handlers[])(void*, SceneManagerEvent) = {
    fpm_scene_main_on_event, /*FPM_MAIN*/
    fpm_scene_add_password_name_on_event, /*FPM_ADD_PASSWORD_NAME*/
    fpm_scene_add_password_on_event, /*FPM_ADD_PASSWORD*/
    fpm_scene_read_passwords_on_event, /*FPM_READ_PASSWORDS*/
};
void (*const fpm_scene_on_exit_handlers[])(void*) = {
    fpm_scene_main_on_exit, /*FPM_MAIN*/
    fpm_scene_add_password_name_on_exit, /*FPM_ADD_PASSWORD_NAME*/
    fpm_scene_add_password_on_exit, /*FPM_ADD_PASSWORD*/
    fpm_scene_read_passwords_on_exit, /*FPM_READ_PASSWORDS*/
};

#endif
