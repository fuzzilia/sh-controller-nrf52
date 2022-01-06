#ifndef FUZZILIA_BUTTON_MANAGER_H
#define FUZZILIA_BUTTON_MANAGER_H

#include <stdint.h>
#include <array>

#include "ButtonState.h"
#include "Key.h"
#include "KeyConfig.h"

typedef void (* ChangeCheckPin)(uint8_t pin);
typedef bool (* IsOnFunc)(uint8_t pin);
typedef void (* ChangeKeyFunc)(Key key);

/**
 * ボタンの状態を読み取り、いつ何のキーコードを送信するかをコントロールするクラスです。
 */
class ButtonManager {
    std::array<uint8_t, 4> m_buttonPins;
    std::array<uint8_t, 3> m_buttonControlPins;
    size_t m_buttonPinSize;
    KeyConfig m_keyConfig;
    ChangeCheckPin m_changeCheckPin;
    IsOnFunc m_isOnFunc;
    ChangeKeyFunc m_changeKey;
    ButtonState m_state;

public:
    ButtonManager(const std::array<uint8_t, 4>& buttonPins, const std::array<uint8_t, 3>& buttonControlPins, ChangeCheckPin changeCheckPin, IsOnFunc isOnFunc, ChangeKeyFunc changeKey);
    void checkButtonState();
    void setKeyConfig(const KeyConfig&);
};

#endif // FUZZILIA_BUTTON_MANAGER_H