#include "flipper_password_manager.h"
#include "fpm_scene.h"
#include <furi.h>
#include <gui/gui.h>

static const SceneManagerHandlers fpm_scene_manager_handlers = {
    .on_enter_handlers = fpm_scene_on_enter_handlers,
    .on_event_handlers = fpm_scene_on_event_handlers,
    .on_exit_handlers = fpm_scene_on_exit_handlers,
    .scene_num = FPM_SCENE_NUMBER};

PasswordManagerState* alloc_state() {
    PasswordManagerState* state = malloc(sizeof(PasswordManagerState));
    state->scene_manager = scene_manager_alloc(&fpm_scene_manager_handlers, state);
    state->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(state->view_dispatcher);
    view_dispatcher_set_event_callback_context(state->view_dispatcher, state);
    state->submenu = submenu_alloc();
    view_dispatcher_add_view(
        state->view_dispatcher, FPM_SUBMENU_VIEW, submenu_get_view(state->submenu));

    state->gui = furi_record_open(RECORD_GUI);

    return state;
}

void free_state(PasswordManagerState* state) {
    view_dispatcher_remove_view(state->view_dispatcher, FPM_SUBMENU_VIEW);
    scene_manager_free(state->scene_manager);
    view_dispatcher_free(state->view_dispatcher);
    submenu_free(state->submenu);
    free(state);
}

int32_t flipper_password_manager_app(void* p) {
    UNUSED(p);

    PasswordManagerState* state = alloc_state();
    view_dispatcher_attach_to_gui(
        state->view_dispatcher, state->gui, ViewDispatcherTypeFullscreen);
    scene_manager_next_scene(state->scene_manager, FPM_MAIN);
    free_state(state);

    return 0;
}