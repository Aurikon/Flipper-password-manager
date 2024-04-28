#include "fpm_add_password.h"
#include "../../flipper_password_manager.h"

void fpm_scene_add_password_on_enter(void* context) {
    UNUSED(context);
    PasswordManagerState* state = (PasswordManagerState*)context;

    text_input_reset(state->text_input);
    text_input_set_header_text(state->text_input, "Enter password name");
    text_input_set_result_callback(
        state->text_input,
        fpm_scene_add_password_callback,
        state,
        state->last_added_password_name,
        state->last_added_password_name_len,
        true);
    view_dispatcher_switch_to_view(state->view_dispatcher, FPM_INPUT_TEXT_VIEW);
}

bool fpm_scene_add_password_on_event(void* context, SceneManagerEvent event) {
    //TODO
    UNUSED(context);
    UNUSED(event);
    return false;
}

void fpm_scene_add_password_on_exit(void* context) {
    //TODO

    UNUSED(context);
}

void fpm_scene_add_password_callback(void* context) {
    //TODO

    UNUSED(context);
}