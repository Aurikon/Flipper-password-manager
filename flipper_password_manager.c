#include "flipper_password_manager.h"
#include "fpm_scene.h"
#include <furi.h>
#include <gui/gui.h>

typedef struct {
    FuriMessageQueue* event_queue;
    InputEvent input_event;
    Gui* gui;
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
} PasswordManagerState;

void (*const fpm_scene_on_enter_handlers[])(void*) = {fpm_scene_main_on_enter};
void (*const fpm_scene_on_event_handlers[])(void*) = {fpm_scene_main_on_event};
void (*const fpm_scene_on_exit_handlers[])(void*) = {fpm_scene_main_on_exit};

static const SceneManagerHandlers fpm_scene_manager_handlers = {
    .on_enter_handlers = fpm_scene_on_enter_handlers,
    .on_event_handlers = fpm_scene_on_event_handlers,
    .on_exit_handlers = fpm_scene_on_exit_handlers,
    .scene_num = FPM_SCENE_NUMBER};

void draw_start_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);
    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 2, 20, "Password Manager");
}

void input_callback(InputEvent* input_event, void* ctx) {
    furi_assert(ctx);
    FuriMessageQueue* event_queue = ctx;
    furi_message_queue_put(event_queue, input_event, FuriWaitForever);
}

PasswordManagerState* alloc_state() {
    PasswordManagerState* state = malloc(sizeof(PasswordManagerState));
    state->event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));
    state->scene_manager = scene_manager_alloc(&fpm_scene_manager_handlers, state);
    state->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(state->view_dispatcher);
    view_dispatcher_set_event_callback_context(state->view_dispatcher, state);
    state->submenu = submenu_alloc();
    view_dispatcher_add_view(
        state->view_dispatcher, FPM_SUBMENU_VIEW, submenu_get_view(state->submenu));

    // view_port_draw_callback_set(state->view_port, draw_start_callback, NULL);
    // view_port_input_callback_set(state->view_port, input_callback, state->event_queue);

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
    while(true) {
        FuriStatus event_status =
            furi_message_queue_get(state->event_queue, &state->input_event, 50);
        if(event_status == FuriStatusOk) {
            //Exit
            if(state->input_event.key == InputKeyBack &&
               state->input_event.type == InputTypeShort) {
                break;
            }
        }
    }

    free_state(state);

    return 0;
}