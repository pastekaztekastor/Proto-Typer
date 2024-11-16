#ifndef TRAINING_H
#define TRAINING_H

#include <vector>
#include <string>
#include "imgui.h"
#include "define.h"
#include "key.h"

class Training {
public:

    Training();

    void render(ImGuiIO io);
    void vu_text_a_copier(ImGuiIO io);
    void vu_exercice(ImGuiIO io);

    bool is_vu_text_a_copier = false;
    bool is_vu_exercice = false;

    char get_current_char(int index);

    void set_text_a_copier(std::string t);

private:
    std::string text_a_copier   = _DEFAULT_TEXT_EXERCICE_;
    int index_a_copier          = 0;
};

#endif // TRAINING_H
