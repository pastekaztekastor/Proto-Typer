// defaults.h
// Fichier de configuration des valeurs par défaut

#ifndef _DEFAULTS_H_
#define _DEFAULTS_H_

// SECTION : Inisitialisation
#define _INITIALISE_IMVEC2_         {.0, .0}
#define _INITIALISE_VECTOR_         {}

// SECTION : Paramètres généraux
#define _DEFAULT_WINDOW_WIDTH_      1280
#define _DEFAULT_WINDOW_HEIGHT_     720
#define _DEFAULT_FULLSCREEN_MODE_   0  // 0 = fenêtré, 1 = plein écran
#define _DEFAULT_FRAME_RATE_        60

// SECTION : Couleurs par défaut (en ImVec4)
#define _DEFAULT_COLOR_BACKGROUND_      ImVec4(0.9f, 0.0f, 0.0f, 1.0f)
#define _DEFAULT_COLOR_TEXT_            ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
#define _DEFAULT_COLOR_BACKGROUND_KEY_  ImVec4(0.1f, 0.1f, 0.9f, 1.0f)
#define _DEFAULT_COLOR_WARNING_BUTTON_  ImVec4(0.9f, 0.0f, 0.0f, 1.0f) // ROUGE
#define _DEFAULT_COLOR_GRID_EDITION_    ImVec4(0.9f, 0.0f, 0.0f, 0.3f) // ROUGE
#define _DEFAULT_COLOR_KEY_WAITING_1_   ImVec4(0.9f, 0.0f, 0.0f, 1.0f) // ROUGE
#define _DEFAULT_COLOR_KEY_WAITING_2_   ImVec4(0.9f, 0.0f, 0.0f, 1.0f) // ROUGE
#define _DEFAULT_COLOR_KEY_WAITING_3_   ImVec4(0.9f, 0.0f, 0.0f, 1.0f) // ROUGE
#define _DEFAULT_COLOR_KEY_WAITING_4_   ImVec4(0.9f, 0.0f, 0.0f, 1.0f) // ROUGE
#define _DEFAULT_COLOR_KEY_WAITING_5_   ImVec4(0.9f, 0.0f, 0.0f, 1.0f) // ROUGE
#define _DEFAULT_COLOR_KEY_PRESSED_     ImVec4(0.9f, 0.0f, 0.0f, 1.0f) // ROUGE

// SECTION : Paramètres des touches
#define _DEFAULT_KEY_LABEL_         "Undefined"
#define _DEFAULT_KEY_CHAR_          {' '}
#define _DEFAULT_KEY_POSITION_X_    0
#define _DEFAULT_KEY_POSITION_Y_    0

struct _default_key_modifier_ {
    static constexpr int _SHIFT_        = 0;
    static constexpr int _CTRL_         = 1;
    static constexpr int _CAPS_LOCK_    = 2;
    static constexpr int _ALT_          = 3;
    static constexpr int _OPTION_       = 4;
    static constexpr int _COMMANDE_     = 5;
    static constexpr int _ALT_GR_       = 6;
    static constexpr int _WINDOWS_      = 7;
    static constexpr int _FUNCTION_     = 8;
    static constexpr int _NONE_         = 9;
};

struct _default_finger_ {
    static constexpr int _INDEX_FINGER_     = 0;
    static constexpr int _MIDDLE_FINGER_    = 1;
    static constexpr int _RING_FINGER_      = 2;
    static constexpr int _LITTLE_FINGER_    = 3;
    static constexpr int _THUMB_            = 4;
};

#define _DEFAULT_FINGER_AFFECT_     _default_finger_::_INDEX_FINGER_

// SECTION : Paramètres de clavier
#define _DEFAULT_KEY_BORDER_            2
#define _DEFAULT_KEYBOARD_BORDER_       20
#define _DEFAULT_KEYBOARD_BORDER_TOP_   15
#define _DEFAULT_POINT_RADIUS_          1.0f
#define _DEFAULT_TEXT_SIZE_             2
#define _DEFAULT_GRID_DIMENTION_        {15, 5}

// SECTION : Limites et tolérances
#define _MAX_KEYS_ 100
#define _MIN_KEY_SIZE_ 10
#define _MAX_KEY_SIZE_ 100

// SECTION : Autres configurations
#define _DEFAULT_VOLUME_LEVEL_ 50
#define _DEFAULT_BRIGHTNESS_LEVEL_ 75

#endif // DEFAULTS_H
