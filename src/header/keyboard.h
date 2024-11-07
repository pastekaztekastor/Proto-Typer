#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <vector>
#include <string>
#include "imgui.h"
#include "define.h"
#include "key.h"

class Keyboard {
public:
    // Constructeur
    Keyboard();

    void initialise();
    void addKey(const Key key);

    void render(ImGuiIO io) ;
    void vue_clavier(ImGuiIO io);
    void vue_reglage(ImGuiIO io);
    void vue_liste_touche(ImGuiIO io);

    std::vector<Key> get_keys ();

    bool is_afficher_settings_              = true;
    bool is_afficher_liste_touches          = true;
    bool is_afficher_clavier                = true;

    bool is_afficher_points_                = false;
    bool is_afficher_cases_                 = false;

private:
    // Méthodes
    void plot_cases(ImGuiIO io)             ;
    void plot_points(ImGuiIO io)            ;
    void update_listes()                    ;
    int key_index_of_char(char c)           ;

    // Attributs
    std::vector<Key> keys_;
    ImVec2 taille_de_touche                 = _INITIALISE_IMVEC2_;                     // Pour l'initialisation
    float bordure_touche                    = _DEFAULT_KEY_BORDER_ ;
    float bordure_clavier                   = _DEFAULT_KEYBOARD_BORDER_;
    int bordure_clavier_top_                = _DEFAULT_KEYBOARD_BORDER_TOP_;
    float rayon_points                      = _DEFAULT_POINT_RADIUS_;
    float taille_texte                      = _DEFAULT_TEXT_SIZE_;          // TOOD
    std::vector<int> grille                 = _DEFAULT_GRID_DIMENTION_;
    ImVec2 position_fenetre                 ;
    
    std::vector<char> liste_des_char                  = _INITIALISE_VECTOR_;    // Liste de tous les char contenue sur toutes les touches
    std::vector<std::vector<int>> liste_des_modifier  = {_INITIALISE_VECTOR_};  // Liste de tous les modifier de chaque char 
    std::vector<int> liste_des_index_des_touches      = _INITIALISE_VECTOR_;    // Index de chaque touche dans le liste de touche
    int index_des_listes                              = 0;                      // Index des listes

    ImVec4  couleur_remplissage     = _DEFAULT_COLOR_BACKGROUND_KEY_;
    ImVec4  couleur_attente_1       = _DEFAULT_COLOR_KEY_WAITING_1_;
    ImVec4  couleur_attente_2       = _DEFAULT_COLOR_KEY_WAITING_2_;
    ImVec4  couleur_attente_3       = _DEFAULT_COLOR_KEY_WAITING_3_;
    ImVec4  couleur_attente_4       = _DEFAULT_COLOR_KEY_WAITING_4_;
    ImVec4  couleur_attente_5       = _DEFAULT_COLOR_KEY_WAITING_5_;
    ImVec4  couleur_presse          = _DEFAULT_COLOR_KEY_PRESSED_;
    ImVec4  couleur_text            = _DEFAULT_COLOR_TEXT_;
    ImVec4  couleur_points          = _DEFAULT_COLOR_GRID_EDITION_;
};

#endif // KEYBOARD_H
