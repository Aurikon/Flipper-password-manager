#include "fpm_read_passwords.h"
#include "../../flipper_password_manager.h"

#include <applications/services/dialogs/dialogs.h>
#include <flipper_format/flipper_format.h>
#include <toolbox/path.h>
#include "flipper_password_manager_icons.h"

bool fpm_select_and_load_password(PasswordManagerState* state) {
    DialogsFileBrowserOptions browser_options;
    bool succes = false;
    dialog_file_browser_set_basic_options(&browser_options, FPM_EXTENSION, &I_password_10x10);
    browser_options.base_path = FPM_FOLDER;
    FuriString* file_path = furi_string_alloc();
    if(furi_string_empty(file_path)) {
        furi_string_set(file_path, browser_options.base_path);
    }

    do {
        if(!dialog_file_browser_show(state->dialogs, file_path, file_path, &browser_options)) {
            break;
        }
        succes = fpm_load_password(state, file_path);
    } while(!succes);
    return succes;
}

bool fpm_load_password(PasswordManagerState* state, FuriString* file_path) {
    Storage* storage = furi_record_open(RECORD_STORAGE);
    FlipperFormat* ff = flipper_format_buffered_file_alloc(storage);
    FuriString* file_content = furi_string_alloc();

    if(!flipper_format_buffered_file_open_existing(ff, furi_string_get_cstr(file_path))) {
        return false;
    }

    if(!flipper_format_read_string(ff, "Password", file_content)) {
        return false;
    }

    strncpy(state->password, furi_string_get_cstr(file_content), FPM_PASSWORD_SIZE);

    furi_string_free(file_content);
    flipper_format_free(ff);
    furi_record_close(RECORD_STORAGE);

    FuriString* file_name = furi_string_alloc();
    path_extract_filename(file_path, file_name, true);
    strncpy(state->password_name, furi_string_get_cstr(file_name), FPM_PASSWORD_SIZE);
    furi_string_free(file_name);
    return true;
}

// FPM_READ_PASSWORDS
void fpm_scene_read_passwords_on_enter(void* context) {
    PasswordManagerState* state = (PasswordManagerState*)context;
    if(fpm_select_and_load_password(state)) {
        scene_manager_next_scene(state->scene_manager, FPM_READ_PASSWORDS_SHOW_SCENE);
    } else {
        scene_manager_search_and_switch_to_previous_scene(state->scene_manager, FPM_MAIN_SCENE);
    }
    UNUSED(context);
}

bool fpm_scene_read_passwords_on_event(void* context, SceneManagerEvent event) {
    //TODO
    UNUSED(context);
    UNUSED(event);
    return false;
}
void fpm_scene_read_passwords_on_exit(void* context) {
    UNUSED(context);
}

void fpm_read_passwords_callback(void* context, uint32_t index) {
    UNUSED(context);
    UNUSED(index);
}

// FPM_READ_PASSWORDS_SHOW
void fpm_scene_read_passwords_show_on_enter(void* context) {
    PasswordManagerState* state = (PasswordManagerState*)context;
    widget_reset(state->widget);
    FuriString* message = furi_string_alloc();
    furi_string_printf(message, state->password);
    widget_add_string_multiline_element(
        state->widget, 5, 15, AlignLeft, AlignCenter, FontPrimary, furi_string_get_cstr(message));
    furi_string_free(message);
    view_dispatcher_switch_to_view(state->view_dispatcher, FPM_WIDGET_VIEW);
}
bool fpm_scene_read_passwords_show_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}
void fpm_scene_read_passwords_show_on_exit(void* context) {
    PasswordManagerState* state = (PasswordManagerState*)context;
    widget_reset(state->widget);
}
