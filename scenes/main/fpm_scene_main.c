#include "fpm_scene_main.h"
#include "../../flipper_password_manager.h"

void fpm_scene_main_on_enter(void* context) {
    PasswordManagerState* state = (PasswordManagerState*)context;

    submenu_reset(state->submenu);
    submenu_set_header(state->submenu, "Password Manager");
    submenu_add_item(
        state->submenu,
        "Add Password",
        FPM_MENU_ADD_PASSWORD_INDEX,
        fpm_scene_main_callback, // TRY: diff functions for each submenu item and next scene there
        state);
    submenu_add_item(
        state->submenu,
        "Saved Passwords",
        FPM_MENU_READ_PASSWRODS_INDEX,
        fpm_scene_main_callback, // TRY: diff functions for each submenu item and next scene there
        state);
    view_dispatcher_switch_to_view(state->view_dispatcher, FPM_SUBMENU_VIEW);
}

bool fpm_scene_main_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    PasswordManagerState* state = (PasswordManagerState*)context;
    bool consumed = false;

    switch(event.type) {
    case SceneManagerEventTypeCustom:
        switch(event.event) {
        case FPM_MENU_ADD_PASSWORD_EVENT:
            scene_manager_next_scene(state->scene_manager, FPM_ADD_PASSWORD_NAME_SCENE);
            consumed = true;
            break;

        case FPM_MENU_READ_PASSWORDS_EVENT:
            scene_manager_next_scene(state->scene_manager, FPM_READ_PASSWORDS_SCENE);
            consumed = true;
            break;

        default:
            break;
        }

    default:
        break;
    }
    return consumed;
}

void fpm_scene_main_on_exit(void* context) {
    PasswordManagerState* state = (PasswordManagerState*)context;
    submenu_reset(state->submenu);
}

void fpm_scene_main_callback(void* context, uint32_t index) {
    UNUSED(context);
    PasswordManagerState* state = context;
    switch(index) {
    case FPM_MENU_ADD_PASSWORD_INDEX:
        scene_manager_handle_custom_event(state->scene_manager, FPM_MENU_ADD_PASSWORD_EVENT);
        break;
    case FPM_MENU_READ_PASSWRODS_INDEX:
        scene_manager_handle_custom_event(state->scene_manager, FPM_MENU_READ_PASSWORDS_EVENT);
        break;

    default:
        break;
    }
}