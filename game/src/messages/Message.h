#include "../utilities/vector2d.h"

enum class Action{
        pointer_left,
        pointer_right,
        pointer_up,
        pointer_down,
        main_action,
        extra_action,
        quit,
        null
    };

template <typename T>
struct Message{
    T info;
};