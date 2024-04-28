#include "flipper_password_manager.h"
#include "fpm_scene.h"
#include <furi.h>
#include <gui/gui.h>

static const SceneManagerHandlers fpm_scene_manager_handlers = {
    .on_enter_handlers = fpm_scene_on_enter_handlers,
    .on_event_handlers = fpm_scene_on_event_handlers,
    .on_exit_handlers = fpm_scene_on_exit_handlers,
    .scene_num = FPM_SCENE_NUMBER};

static bool fpm_custom_event_callback(void* context, uint32_t custom_event) {
    PasswordManagerState* state = (PasswordManagerState*)context;
    return scene_manager_handle_custom_event(state->scene_manager, custom_event);
}

static bool fpm_navigation_event_callback(void* context) {
    PasswordManagerState* state = (PasswordManagerState*)context;
    return scene_manager_handle_back_event(state->scene_manager);
}

PasswordManagerState* alloc_state() {
    PasswordManagerState* state = malloc(sizeof(PasswordManagerState));

    state->scene_manager = scene_manager_alloc(&fpm_scene_manager_handlers, state);

    state->submenu = submenu_alloc();

    state->text_input = text_input_alloc();

    state->last_added_password_name_len = 50;
    state->last_added_password_name =
        malloc(state->last_added_password_name_len * sizeof(uint8_t));

    state->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(state->view_dispatcher);
    view_dispatcher_set_event_callback_context(state->view_dispatcher, state);
    view_dispatcher_set_custom_event_callback(state->view_dispatcher, fpm_custom_event_callback);
    view_dispatcher_set_navigation_event_callback(
        state->view_dispatcher, fpm_navigation_event_callback);
    view_dispatcher_add_view(
        state->view_dispatcher, FPM_SUBMENU_VIEW, submenu_get_view(state->submenu));
    view_dispatcher_add_view(
        state->view_dispatcher, FPM_INPUT_TEXT_VIEW, text_input_get_view(state->text_input));

    state->gui = furi_record_open(RECORD_GUI);

    return state;
}

void free_state(PasswordManagerState* state) {
    view_dispatcher_remove_view(state->view_dispatcher, FPM_SUBMENU_VIEW);
    scene_manager_free(state->scene_manager);
    view_dispatcher_free(state->view_dispatcher);
    text_input_free(state->text_input);
    submenu_free(state->submenu);
    free(state);
}

int32_t flipper_password_manager_app(void* p) {
    UNUSED(p);

    PasswordManagerState* state = alloc_state();
    view_dispatcher_attach_to_gui(
        state->view_dispatcher, state->gui, ViewDispatcherTypeFullscreen);
    scene_manager_next_scene(state->scene_manager, FPM_MAIN_SCENE);
    view_dispatcher_run(state->view_dispatcher);
    free_state(state);

    return 0;
}