#pragma once

#include "../../../vendor/SDL2/include/SDL.h"

namespace Tabby {
using GamepadAxis = int32_t;
using GamepadButtons = uint32_t;

namespace Gamepad {
    enum : GamepadAxis {
        GAMEPAD_AXIS_LEFT_X = 0, // Gamepad left stick X axis
        GAMEPAD_AXIS_LEFT_Y = 1, // Gamepad left stick Y axis
        GAMEPAD_AXIS_RIGHT_X = 2, // Gamepad right stick X axis
        GAMEPAD_AXIS_RIGHT_Y = 3, // Gamepad right stick Y axis
        GAMEPAD_AXIS_LEFT_TRIGGER = 4, // Gamepad back trigger left, pressure level: [1..-1]
        GAMEPAD_AXIS_RIGHT_TRIGGER = 5 // Gamepad back trigger right, pressure level: [1..-1]
    };

    enum : GamepadButtons {
        GAMEPAD_BUTTON_RIGHT_FACE_UP = SDL_CONTROLLER_BUTTON_Y,
        GAMEPAD_BUTTON_RIGHT_FACE_RIGHT = SDL_CONTROLLER_BUTTON_B,
        GAMEPAD_BUTTON_RIGHT_FACE_DOWN = SDL_CONTROLLER_BUTTON_A,
        GAMEPAD_BUTTON_RIGHT_FACE_LEFT = SDL_CONTROLLER_BUTTON_X,

        GAMEPAD_BUTTON_LEFT_TRIGGER_1 = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
        GAMEPAD_BUTTON_RIGHT_TRIGGER_1 = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,

        GAMEPAD_BUTTON_MIDDLE_LEFT = SDL_CONTROLLER_BUTTON_BACK,
        GAMEPAD_BUTTON_MIDDLE = SDL_CONTROLLER_BUTTON_GUIDE,
        GAMEPAD_BUTTON_MIDDLE_RIGHT = SDL_CONTROLLER_BUTTON_START,

        GAMEPAD_BUTTON_LEFT_FACE_UP = SDL_CONTROLLER_BUTTON_DPAD_UP,
        GAMEPAD_BUTTON_LEFT_FACE_RIGHT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
        GAMEPAD_BUTTON_LEFT_FACE_DOWN = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
        GAMEPAD_BUTTON_LEFT_FACE_LEFT = SDL_CONTROLLER_BUTTON_DPAD_LEFT,

        GAMEPAD_BUTTON_LEFT_THUMB = SDL_CONTROLLER_BUTTON_LEFTSTICK,
        GAMEPAD_BUTTON_RIGHT_THUMB = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
    };
}
}
