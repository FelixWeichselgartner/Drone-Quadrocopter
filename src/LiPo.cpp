#include "Arduino.h"
#include "drone_config.h"
#include "LiPo.hpp"

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
        m_lookup_table[i].per = i * 5;
        m_lookup_table[i].mV = MV[i];
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
        return;
    }

    int codeWord = analogRead(LIPO_FB);
    // calculate the current voltage 
    currentVoltage_mV = codeWord * this->referenceVoltage * this->voltageDividerDenominator / this->voltageDividerNominator;

    int t_x = 0, i = 0;
    int t_delta_down, t_delta_up;

    while (currentVoltage_mV > m_lookup_table[i + 1].mV) {
        t_x++;
        i++;

        if (t_x == 20) {
            break;
        }
    }

    if (t_x != 20 && currentVoltage_mV > m_lookup_table[0].mV) {
        t_delta_down = currentVoltage_mV - m_lookup_table[t_x].mV;
        t_delta_up = m_lookup_table[t_x + 1].mV - currentVoltage_mV;

        if (t_delta_up < t_delta_down) {
            t_x++;
        }
    }

    percentageLoaded = m_lookup_table[t_x].per;
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

void LiPo::setReference(int t_v_ref_mv, int t_res)
{
    m_v_ref_mv = t_v_ref_mv;
    for (int i = 0; i < t_res; i++)
    {
        m_cw_ref *= 2;
    }
}

//#define EXAMPLE

#ifdef EXAMPLE

#include <iostream>
using namespace std;

using namespace LiPo;

int main()
{
    // U_ref = 3V3
    // ADC resolution = 10 bits
    class LiPo lipo(3300, 10);

    // current lipo cw
    int myCurrentCw = 4020 * 1024 / 3300 / 2;
    int myCurrent_mV;

    // battery percentage
    int percentageLoaded;
    bool state;
    int currentVoltage_mV = myCurrentCw * 3300 * 2 / 1;


    // calculate the current voltage 
    int currentVoltage_mV = myCurrentCw * this->referenceVoltage * this->voltageDividerDenominator / this->voltageDividerNominator;

    int t_x = 0, i = 0;
    int t_delta_down, t_delta_up;

    while (currentVoltage_mV > m_lookup_table[i + 1].mV)
    {
        t_x++;
        i++;

        if (t_x == 20)
        {
            break;
        }
    }

    if (t_x != 20 && currentVoltage_mV > m_lookup_table[0].mV)
    {
        t_delta_down = currentVoltage_mV - m_lookup_table[t_x].mV;
        t_delta_up = m_lookup_table[t_x + 1].mV - currentVoltage_mV;

        if (t_delta_up < t_delta_down)
        {
            t_x++;
        }
    }

    percentageLoaded = m_lookup_table[t_x].per;
    state = m_lookup_table[t_x].state;

    cout << "Percentage loaded: " << percentageLoaded << endl;
    cout << "voltage: " << 

    return 0;
}

#endif