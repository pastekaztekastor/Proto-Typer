#ifndef KEY_H
#define KEY_H

#include <vector>
#include <string>
#include <functional>
#include "define.h"
#include "imgui.h"

class Key {
public:
    // Constructeur
    Key(const std::string& label, const std::vector<int>& positions);
    Key();

    bool is_afficher_reglage    = false;
    bool is_doit_etre_presser   = false;
    bool est_presser            = false;

    std::string get_label();

    void set_couleur_remplissage(ImVec4 color);
    void set_couleur_attente(ImVec4 color);
    void set_couleur_presse(ImVec4 color);
    void set_couleur_text(ImVec4 color);

    int nombre_de_char();
    char get_char_by_index(int index);
    std::vector<int> get_modifiers_by_index(int index);

    void render(
        ImGuiIO     io, 
        ImVec2      position_fenetre, 
        float       bordure_touche, 
        ImVec2      taille_de_touche, 
        float       bordure_clavier, 
        float       bordure_clavier_top_, 
        ImDrawList* draw_list);
    void vue_reglages(ImGuiIO& ImGui); 


private:
    std::string                     label                   = _DEFAULT_KEY_LABEL_;
    int                             key_modifier            = _default_key_modifier_::_NONE_;
    std::vector<std::vector<int>>   key_modifier_by_char    = {{_default_key_modifier_::_NONE_}};
    std::vector<char>               chars                   = _DEFAULT_KEY_CHAR_;
    std::vector<int>                positions_touche        = {_DEFAULT_KEY_POSITION_X_, _DEFAULT_KEY_POSITION_Y_};
    std::vector<int>                position_label          = {_DEFAULT_KEY_POSITION_X_, _DEFAULT_KEY_POSITION_Y_};
    int                             finger_assignastion     = _DEFAULT_FINGER_AFFECT_;
    ImVec4                          couleur_remplissage     = _DEFAULT_COLOR_BACKGROUND_KEY_;
    ImVec4                          couleur_attente         = _DEFAULT_COLOR_KEY_WAITING_1_;
    ImVec4                          couleur_presse          = _DEFAULT_COLOR_KEY_PRESSED_;
    ImVec4                          couleur_text            = _DEFAULT_COLOR_TEXT_;
};

#endif // KEY_H
