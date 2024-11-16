/**
 *   _  __          
 *  | |/ /          
 *  | ' / ___ _   _ 
 *  |  < / _ \ | | |
 *  | . \  __/ |_| |
 *  |_|\_\___|\__, |
 *             __/ |
 *            |___/ 
 * 
 * @file key.h
 * @brief Classe représentant une touche sur le clavier.
 *
 * La classe qui gère l'affichage de chaque touche grâce aux variables de position.
 *
 * Elle gère un ensemble de caractères propres à chaque touche rangés dans des vecteurs. 
 * Elle possède quatre vecteurs représentant respectivement le label de la touche le caractère 
 * de la touche le produit est modificateur pour atteindre ce caractère et le second modificateur 
 * pour atteindre ce caractère
 * 
 * Sa position et sa forme sont décrits par une ensemble de coordonnées rangées dans un vecteur 
 * permettant de savoir à quel emplacement sur une grille elles sont attachés.
 * 
 * Elle peut aussi être une touche modificatrice (comme ALT ou CTRL) permettant de changer 
 * l'accessibilité 
 * au reste du clavier.
 * 
 * ELLE POSSÈDE UNE FONCTION DE PARAMÉTRAGE QUI PERMET DE MODIFIER L'ENSEMBLE DE SES PARAMÈTRES.
 * 
 * @author Mathurin Champémont
 * @date 16 novembre 2024
 *
 * @version 1.0.0
 *
 * @copyright MIT License
 *
 * @note 
 */


#ifndef KEY_H
#define KEY_H

#include "define.h"
#include "imgui.h"
#include <vector>
#include <string>
#include <utility> // Pour std::pair

class Key {
public:
    // CONSTRUCTEUR ET INITIALISATION DE LA TOUCHE
    /**
     * @brief Constructeur par défaut qui initialise la touche avec tous les paramètres par défaut 
     * tels que définis dans le fichier define.h et le fichier key.h
     */
    Key();
    /**
     * @brief Constructeur qui initialise une touche dite "blank", celle-ci possède un ensemble de 
     * coordonnées et l'index permettant de savoir à quelle coordonnées doit être afficher le label 
     * de la touche.
     * @param pos_key vecteur des coordonnées de position de la touche. -> [position_key]
     * @param pos_lbl Index de la coordonnées contenues dans la variable pos_key doit être affiché 
     * le label. ->[position_label] (par défaut _DEFAULT_LABEL_POSITION_ = 0)
     * @throws std::invalid_argument Si le vecteur pos_key est vide.
     * @throws std::invalid_argument Si l'index du label ne permet pas de pointer sur un élément du 
     * vecteur de position.
     */
    Key
    (
        const std::vector<_coordinate_>  pos_key,
        const int                        pos_lbl = _DEFAULT_LABEL_POSITION_
    );
    /**
     * @brief Permet d'ajouter des caractères à la touche en précisant le label. Les modificateur de 
     * la touche sont accessibles depuis la structure _key_modifier_.
     * @param lbl Le label afficher sur la touche lorsque l'on veut taper ce caractère. -> 
     * [list_labels]
     * @param c Le caractère de la touche. -> [list_chars]
     * @param m1 Le premier modificateur pour atteindre celle-ci. Par défaut celui-ci est 
     * _DEFAULT_KEY_MODIFIER_. -> [list_modifier_1]
     * @param m2 Le second modificateur pour attendre celle-ci. Par défaut celui-ci est 
     * _DEFAULT_KEY_MODIFIER_. -> [list_modifier_2]
     */
    void add_char
    (
        const std::string& lbl, 
        const char c = _DEFAULT_KEY_CHAR_, 
        const int m1 = _DEFAULT_KEY_MODIFIER_, // La valeur de base est en _NONE_
        const int m2 = _DEFAULT_KEY_MODIFIER_  // La valeur de base est en _NONE_
    );
    /**
     * @brief Permet d'ajouter des caractères à la touche sans préciser le label celui-ci sera égale 
     * au caractère de la touche. Les modificateur de la touche sont accessibles depuis la structure 
     * _key_modifier_.
     * @param c Le label afficher sur la touche lorsque l'on veut taper ce caractère. -> [list_chars]
     * @param m1 Le premier modificateur pour atteindre celle-ci. Par défaut celui-ci est 
     * _DEFAULT_KEY_MODIFIER_. ->[list_modifier_1]
     * @param m2 Le second modificateur pour attendre celle-ci. Par défaut celui-ci est 
     * _DEFAULT_KEY_MODIFIER_. -> [list_modifier_2]
     */
    void add_char
    (
        const char c, 
        const int m1 = _DEFAULT_KEY_MODIFIER_, // La valeur de base est en _NONE_
        const int m2 = _DEFAULT_KEY_MODIFIER_  // La valeur de base est en _NONE_
    );
    /**
     * @brief Permet d'ajouter une nouvelle coordonnées à la touche.
     * @param pos Nouvelle position à ajouter de type _coordinate_ contenant les indices en X et en Y
     */
    void add_position
    (
        const _coordinate_ pos
    );

    // GETTER 
    /**
     * @brief Obtenir le caractère à l'index demandé dans le vecteur contenant l'ensemble des 
     * caractères.
     * @param i index pointant sur le caractère souhaité.
     * @return char Du caractère demandé.
     * @throws std::out_of_range Si l'index est supérieur à la taille du vecteur.
     */
    char get_char_by_index(int i);
    /**
     * @brief Obtenir le label à l'index demandé dans le vecteur contenant l'ensemble des label.
     * @param i index pointant sur le label souhaité.
     * @return std::string label du caractère demandé.
     * @throws std::out_of_range Si l'index est supérieur à la taille du vecteur.
     */
    std::string get_labels_by_index(int i);
    /**
     * @brief Obtenir le Premier modificateur à l'index demandé dans le vecteur contenant l'ensemble 
     * des Premier modificateur.
     * @param i Index pointant sur le Premier modificateur souhaité.
     * @return int Du Premier modificateur demandé.
     * @throws std::out_of_range Si l'index est supérieur à la taille du vecteur.
     */
    int get_mod_1_by_index(int i);
    /**
     * @brief Obtenir le second modificateur à l'index demandé dans le vecteur contenant l'ensemble
     *  des second modificateur.
     * @param i Index pointant sur le second modificateur souhaité.
     * @return int Du second modificateur demandé.
     * @throws std::out_of_range Si l'index est supérieur à la taille du vecteur.
     */
    int get_mod_2_by_index(int i);
    /**
     * @brief Obtenir le nombre de caractères associé à la touche.
     * @return Le nombre de caractères de la touche. C'est la longueur des vecteurs appelés
     *  list_xxxxx.
     * @throws std::logic_error Si les différents Victor n'ont pas la même taille.
     */
    int get_nb_char();

    // SETER
    /**
     * @brief Change le paramètre de la couleur de la touche lorsque celle-ci est à l'état 
     * _key_state_::_IDLE_ (0).
     * @param color de type ImVec4, il représente le pourcentage de rouge, vert, bleu, alpha.
     */
    void set_color_idle(ImVec4 color);
    /**
     * @brief Change le paramètre de la couleur de la touche lorsque celle-ci est à l'état 
     * _key_state_::_WAITING_ (1).
     * @param color de type ImVec4, il représente le pourcentage de rouge, vert, bleu, alpha.
     */
    void set_color_waiting(ImVec4 color);
    /**
     * @brief Change le paramètre de la couleur de la touche lorsque celle-ci est à l'état
     *  _key_state_::_PRESSED_ (2).
     * @param color de type ImVec4, il représente le pourcentage de rouge, vert, bleu, alpha.
     */
    void set_couleur_presse(ImVec4 color);
    /**
     * @brief Change le paramètre de la couleur du labal de la touche.
     * @param color de type ImVec4, il représente le pourcentage de rouge, vert, bleu, alpha.
     */
    void set_couleur_text(ImVec4 color);
    /**
     * @brief Change le doigt qui est assigné pour appuyer sur la touche.
     * @param f (pour finger) Il est recommandé d'utiliser les variables définies dans la structure
     *  _finger_ -> [finger_assignment]
     * qui peuvent être : _INDEX_FINGER_(0), _MIDDLE_FINGER_(1), _RING_FINGER_(2), _LITTLE_FINGER_
     * (3) et _THUMB_(4)
     * @throws std::out_of_range si l'entier n'est pas compris entre 0 et 4.
     */
    void set_finger_assignment(int f);

    // AFFICHAGE
    /**
     * @brief Fonction d'affichage du rendu. C'est elle qui charge les différentes vues de la classe
     * et les initialises. C'est aussi elle qui ajoute à l'ensemble des éléments affichés dans la 
     * boucle de rendu
     * principal l'ensemble des touches du clavier.
     * @param io Adresse de l'objet contenant l'ensemble des éléments nécessaires à l'affichage 
     * d'une fenêtre
     * @param pos_win Position de la fenêtre
     * @param key_border Bordure autour de chaque touche du clavier
     * @param key_size Dimensions d'une touche
     * @param keyboard_border Bordure entre le clavier et la fenêtre
     * @param keyboard_border_top Bordure supérieur du clavier pour permettre l'affichage dans menu
     * @param draw_list Pointeur sur la liste de l'ensemble des éléments que l'on va devoir ajouter
     *  à la boucle de rendu
     * @param i_of_list Indice pour choisir le bon caractère à afficher sur le clavier quand nous 
     * utilisons les modifier
     */
    void render
    (
        ImGuiIO&    io, 
        ImVec2      pos_win, 
        float       key_border, 
        ImVec2      key_size, 
        float       keyboard_border, 
        float       keyboard_border_top, 
        ImDrawList* draw_list,
        int         i_of_list
    );

    /**
     * @brief Fonction qui ne gère que l'affichage des paramètres de la touche. Elle permet de 
     * modifier l'ensemble des 
     * variables privées de celle-ci.
     * @param io Adresse de l'objet contenant l'ensemble des éléments nécessaires à l'affichage
     * d'une fenêtre
     */
    bool view_settings(ImGuiIO& io); // retourne True si un réglage est modifié.

    // Variables
    bool is_plot_settings    = false;


private:
    /* 
    Liste des caratères de la touche
    Tous les caractère sont dans des tableaux qui ont tous la même longueurs 
    */
    std::vector<std::string>            list_labels             = {_DEFAULT_KEY_LABEL_};            // Liste de tous les label des caratère que le touche peut écrire
    std::vector<char>                   list_chars              = {_DEFAULT_KEY_CHAR_};             // Liste de tous les caractère que le touche peux avoir
    std::vector<int>                    list_modifier_1         = {_DEFAULT_KEY_MODIFIER_};         // Liste de tous les premier modifiacteur relatif au caractère de même index
    std::vector<int>                    list_modifier_2         = {_DEFAULT_KEY_MODIFIER_};         // Liste de tous les seconde modificateur relatif au caractère de même index
    // paramètre de la touche
    int                                 key_modifier            = _DEFAULT_KEY_MODIFIER_;           // 
    int                                 finger_assignment       = _DEFAULT_FINGER_ASSIGNMENT_;      // 
    // Postitions 
    std::vector<_coordinate_>           position_key            = {_DEFAULT_COORDINATE_};           // 
    int                                 position_label          = _DEFAULT_LABEL_POSITION_;         // index de la coordonée de la positions dans le vecteur position_key
    // Description de la touche pour l'affichage
    int                                 state_key               = _DEFAULT_KEY_STATE_;              // 
    ImVec4                              color_idle              = _DEFAULT_COLOR_BACKGROUND_KEY_;   // 
    ImVec4                              color_waiting           = _DEFAULT_COLOR_KEY_WAITING_1_;    // 
    ImVec4                              color_pressed           = _DEFAULT_COLOR_KEY_PRESSED_;      // 
    ImVec4                              color_text              = _DEFAULT_COLOR_TEXT_;             // 
    // Variables pour les paramètre
    int                                 selected_mod_1          = _DEFAULT_KEY_MODIFIER_;           // 
    int                                 selected_mod_2          = _DEFAULT_KEY_MODIFIER_;           // 
    std::vector<std::pair<int, int>>    modificateurs_selectionnes;                                 // 
    char                                buffer_label[256];                                          // 
};

#endif // KEY_H
