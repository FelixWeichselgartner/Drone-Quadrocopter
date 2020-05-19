#include "Arduino.h"
#include "drone_config.h"
#include "LiPo.hpp"
#include "debug.h"

/**
 * @brief  table for volt/percentage of lipo cells.
 * @note   first is 0%, last value is 100%, 5% steps in between
 * @retval None
 */
const int MV[21] = {
    3270, 3610, 3690, 3710, 3730, 3750,
    3770, 3790, 3800, 3820, 3840, 3850,
    3870, 3910, 3950, 3980, 4020, 4080,
    4110, 4150, 4200};

LiPo::LiPo(int t_v_ref_mv, int t_res) {
    setReference(t_v_ref_mv, t_res);
    init();
}

void LiPo::init() {
    for (int i = 0; i < 21; i++) {
        m_lookup_table[i].percentageLoaded = i * 5;
        m_lookup_table[i].currentVoltage = MV[i];
    }

    for (int i = 0; i < 4; i++) {
        m_lookup_table[i].state = false;
    }

    for (int i = 4; i < 21 - 4; i++) {
        m_lookup_table[i].state = true;
    }
}

void LiPo::refresh() {
    if (refreshCounter % refreshInterval != 0) {
        // only refresh every refreshInterval th time.
        refreshCounter++;
        return;
    }

    int codeWord = 0, n = 20;
    for (int i = 0; i < n; i++) {
        codeWord += analogRead(LIPO_FB);
    }
    codeWord /= n;

    #if DEBUG
    /*if (Serial) {
        Serial.print("CW: ");
        Serial.println(codeWord);
    }*/
    #endif
    
    // calculate the current voltage 
    currentVoltage_mV = (long long) (codeWord * this->voltageDividerDenominator / this->voltageDividerNominator) * this->referenceVoltage / this->referenceCW;

    int t_x = 0, i = 0;
    int t_delta_down, t_delta_up;

    while (currentVoltage_mV > m_lookup_table[i + 1].currentVoltage) {
        t_x++;
        i++;

        if (t_x == 20) {
            break;
        }
    }

    if (t_x != 20 && currentVoltage_mV > m_lookup_table[0].currentVoltage) {
        t_delta_down = currentVoltage_mV - m_lookup_table[t_x].currentVoltage;
        t_delta_up = m_lookup_table[t_x + 1].currentVoltage - currentVoltage_mV;

        if (t_delta_up < t_delta_down) {
            t_x++;
        }
    }

    percentageLoaded = m_lookup_table[t_x].percentageLoaded;
    state = m_lookup_table[t_x].state;
    refreshCounter++;
}

bool LiPo::getState() {
    refresh();
    return state;
}

int LiPo::getCurrentVoltage() {
    refresh();
    return currentVoltage_mV;
}

int LiPo::getPercentageLoaded() {
    refresh();
    return percentageLoaded;
}

void LiPo::setReference(int t_v_ref_mv, int t_res) {
    this->referenceVoltage = t_v_ref_mv;
    this->referenceCW = 1;
    for (int i = 0; i < t_res; i++) {
        this->referenceCW *= 2;
    }
}
