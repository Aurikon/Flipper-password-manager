#ifndef PASSWORD_MANAGER_STATE
#define PASSWORD_MANAGER_STATE

#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>

typedef struct PasswordManagerState {
    Gui* gui;
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
} PasswordManagerState;

typedef enum {
    FPM_MAIN, // scenes/main
    FPM_SCENE_NUMBER // always last
} FPMScene;

typedef enum { FPM_SUBMENU_VIEW } FPMView;

#endif
