#ifndef FPM_TYPES
#define FPM_TYPES

#define FPM_PASSWORD_SIZE 128
#define FPM_FOLDER ANY_PATH("fpm")
#define FPM_EXTENSION ".fpm"

#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/modules/text_input.h>
#include <storage/storage.h>

typedef struct PasswordManagerState {
    Gui* gui;
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    TextInput* text_input;
    Storage* storage;

    char last_added_password_name[FPM_PASSWORD_SIZE];
    char last_added_password[FPM_PASSWORD_SIZE];
} PasswordManagerState;

typedef enum {
    FPM_MAIN_SCENE, /*scenes/main*/
    FPM_ADD_PASSWORD_NAME_SCENE, /*scenes/add_password*/
    FPM_ADD_PASSWORD_SCENE, /*scenes/add_password*/
    FPM_READ_PASSWORDS_SCENE, /*secens/read_passwords*/
    FPM_SCENE_NUMBER /*always last*/
} FPMScene;

typedef enum { FPM_SUBMENU_VIEW, FPM_INPUT_TEXT_VIEW } FPMView;

#endif
