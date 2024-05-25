#ifndef FPM_TYPES
#define FPM_TYPES

#define FPM_PASSWORD_SIZE 128
#define FPM_FOLDER ANY_PATH("fpm")
#define FPM_EXTENSION ".fpm"

#include <storage/storage.h>
#include <gui/scene_manager.h>
#include <gui/modules/widget.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/modules/text_input.h>
#include <applications/services/dialogs/dialogs.h>

typedef struct PasswordManagerState {
    Gui* gui;
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    Widget* widget;
    Submenu* submenu;
    TextInput* text_input;
    Storage* storage;
    DialogsApp* dialogs;

    char password_name[FPM_PASSWORD_SIZE + 1];
    char password[FPM_PASSWORD_SIZE + 1];
} PasswordManagerState;

typedef enum {
    FPM_MAIN_SCENE, /*scenes/main*/
    FPM_ADD_PASSWORD_NAME_SCENE, /*scenes/add_password*/
    FPM_ADD_PASSWORD_SCENE, /*scenes/add_password*/
    FPM_READ_PASSWORDS_SCENE, /*scenes/read_passwords*/
    FPM_READ_PASSWORDS_SHOW_SCENE, /*scenes/read_passwords*/
    FPM_SCENE_NUMBER /*always last*/
} FPMScene;

typedef enum { FPM_SUBMENU_VIEW, FPM_INPUT_TEXT_VIEW, FPM_WIDGET_VIEW } FPMView;

#endif
