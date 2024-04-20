#include "flipper_password_manager.h"
#include <furi.h>
#include <gui/gui.h>

typedef struct {
    FuriMessageQueue* event_queue;
    InputEvent input_event;
    ViewPort* view_port;
    Gui* gui;
} PasswordManagerState;

void free_state(PasswordManagerState* state) {
    gui_remove_view_port(state->gui, state->view_port);
    view_port_free(state->view_port);
    furi_message_queue_free(state->event_queue);
    free(state);
}

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

PasswordManagerState* init() {
    PasswordManagerState* state = malloc(sizeof(PasswordManagerState));
    state->event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));
    state->view_port = view_port_alloc();
    view_port_draw_callback_set(state->view_port, draw_start_callback, NULL);
    view_port_input_callback_set(state->view_port, input_callback, state->event_queue);

    state->gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(state->gui, state->view_port, GuiLayerFullscreen);

    return state;
}

int32_t flipper_password_manager_app(void* p) {
    UNUSED(p);

    PasswordManagerState* state = init();
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