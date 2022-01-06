#include "ButtonManager.h"
#include <cstring>

ButtonManager::ButtonManager(
    const std::array<uint8_t, 4>& buttonPins,
    const std::array<uint8_t, 3>& buttonControlPins,
    ChangeCheckPin changeCheckPin,
    IsOnFunc isOnFunc,
    ChangeKeyFunc changeKey
):
    m_buttonPins(buttonPins),
    m_buttonControlPins(buttonControlPins),
    m_keyConfig(),
    m_changeCheckPin(changeCheckPin),
    m_isOnFunc(isOnFunc),
    m_changeKey(changeKey)
{
}

void ButtonManager::checkButtonState() {
    auto nextState = m_state;
    uint8_t number = 0;

    for (const uint8_t& c: m_buttonControlPins) {
        m_changeCheckPin(c);
        for (const uint8_t& b: m_buttonPins) {
            nextState.setIsPushed(number, m_isOnFunc(b));
            ++number;
        }
    }

    if (nextState != m_state) {
        m_changeKey(m_keyConfig.keyForButtonState(nextState));
        m_state = nextState;
    }
}

void ButtonManager::setKeyConfig(const KeyConfig& keyConfig) {
    m_keyConfig = keyConfig;
}
