#include "fpm_add_password.h"
#include "../../flipper_password_manager.h"
#include <flipper_format/flipper_format.h>

// password name
void fpm_add_password_name_callback(void* context) {
    PasswordManagerState* state = (PasswordManagerState*)context;
    scene_manager_handle_custom_event(state->scene_manager, FPM_ADD_PASSWORD_INPUT_PASSWORD_EVENT);
}

void fpm_scene_add_password_name_on_enter(void* context) {
    PasswordManagerState* state = (PasswordManagerState*)context;

    text_input_reset(state->text_input);
    text_input_set_header_text(state->text_input, "Enter password name");
    text_input_set_result_callback(
        state->text_input,
        fpm_add_password_name_callback,
        state,
        state->last_added_password_name,
        FPM_PASSWORD_SIZE,
        true);
    view_dispatcher_switch_to_view(state->view_dispatcher, FPM_INPUT_TEXT_VIEW);
}

bool fpm_scene_add_password_name_on_event(void* context, SceneManagerEvent event) {
    PasswordManagerState* state = (PasswordManagerState*)context;
    bool consimed = false;
    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == FPM_ADD_PASSWORD_INPUT_PASSWORD_EVENT) {
            scene_manager_next_scene(state->scene_manager, FPM_ADD_PASSWORD_SCENE);
            consimed = true;
        }
    }
    return consimed;
}

void fpm_scene_add_password_name_on_exit(void* context) {
    UNUSED(context);
}

// password itself
void fpm_add_password_callback(void* context) {
    PasswordManagerState* state = (PasswordManagerState*)context;
    scene_manager_handle_custom_event(state->scene_manager, FPM_ADD_PASSWORD_SAVE_EVENT);
}

void fpm_scene_add_password_on_enter(void* context) {
    PasswordManagerState* state = (PasswordManagerState*)context;

    text_input_reset(state->text_input);
    text_input_set_header_text(state->text_input, "Enter password");
    text_input_set_result_callback(
        state->text_input,
        fpm_add_password_callback,
        state,
        state->last_added_password,
        FPM_PASSWORD_SIZE,
        true);
    view_dispatcher_switch_to_view(state->view_dispatcher, FPM_INPUT_TEXT_VIEW);
}

bool fpm_scene_add_password_on_event(void* context, SceneManagerEvent event) {
    PasswordManagerState* state = (PasswordManagerState*)context;
    bool consumed = false;
    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == FPM_ADD_PASSWORD_SAVE_EVENT) {
            if(fpm_save_password(state)) {
                memset(state->last_added_password_name, 0, FPM_PASSWORD_SIZE);
                memset(state->last_added_password, 0, FPM_PASSWORD_SIZE);
                scene_manager_search_and_switch_to_previous_scene(
                    state->scene_manager, FPM_MAIN_SCENE);
                // TODO: Succes save scene
            }
            consumed = true;
        }
    }
    return consumed;
}

void fpm_scene_add_password_on_exit(void* context) {
    UNUSED(context);
}

// save password in storage
bool fpm_make_folder(PasswordManagerState* state) {
    return storage_simply_mkdir(state->storage, FPM_FOLDER);
}

// TODO: save encrypted password
bool fpm_save_password(PasswordManagerState* state) {
    if(!fpm_make_folder(state)) {
        return false;
        // TODO: dialog_message_show_storage_error
    }

    FuriString* file_path = furi_string_alloc_set(FPM_FOLDER);
    furi_string_cat_printf(file_path, "/%s%s", state->last_added_password_name, FPM_EXTENSION);

    FlipperFormat* ff = flipper_format_buffered_file_alloc(state->storage);

    if(!flipper_format_buffered_file_open_always(ff, furi_string_get_cstr(file_path))) {
        return false;
    }

    if(!flipper_format_write_string_cstr(ff, "Password", state->last_added_password)) {
        return false;
    }

    furi_string_free(file_path);
    flipper_format_free(ff);

    return true;
}