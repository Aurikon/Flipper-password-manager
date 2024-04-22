#ifndef FPM_SCENE
#define FPM_SCENE

#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include "scenes/main/fpm_scene_main.h"

typedef enum {
    FPM_MAIN, // scenes/main
    FPM_SCENE_NUMBER // always last
} FPMScene;

typedef enum { FPM_SUBMENU_VIEW } FPMView;

#endif
