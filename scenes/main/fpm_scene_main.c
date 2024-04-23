#include "fpm_scene_main.h"
#include "../../flipper_password_manager.h"

void fpm_scene_main_on_enter(void* context) {
    PasswordManagerState* state = context;

    submenu_reset(state->submenu);
    submenu_set_header(state->submenu, "Password Manager");
    submenu_add_item(
        state->submenu,
        "Add Password",
        FPM_MENU_ADD_PASSWORD_INDEX,
        fpm_scene_main_callback,
        state);
    submenu_add_item(
        state->submenu,
        "Saved Passwords",
        FPM_MENU_READ_PASSWROD_INDEX,
        fpm_scene_main_callback,
        state);
    view_dispatcher_switch_to_view(state->view_dispatcher, FPM_SUBMENU_VIEW);
}

bool fpm_scene_main_on_event(void* context, SceneManagerEvent event) {
    // TODO
    UNUSED(context);
    UNUSED(event);
    return true;
}

void fpm_scene_main_on_exit(void* context) {
    // TODO
    UNUSED(context);
}

void fpm_scene_main_callback(void* context, uint32_t index) {
    UNUSED(context);
    // PasswordManagerState* state = context;
    switch(index) {
    case FPM_MENU_ADD_PASSWORD_INDEX:
        break;
    case FPM_MENU_READ_PASSWROD_INDEX:
        break;

    default:
        break;
    }
}