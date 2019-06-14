#include "LiPo.hpp"

const int MV[21] = {
    3270, 3610, 3690, 3710, 3730, 3750, 
    3770, 3790, 3800, 3820, 3840, 3850, 
    3870, 3910, 3950, 3980, 4020, 4080, 
    4110, 4150, 4200
};

LiPo::LiPo::LiPo(int t_v_ref_mv, int t_res) {
    setReference(t_v_ref_mv, t_res);
    init();
}

void LiPo::LiPo::init() {
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

bool LiPo::LiPo::getState(int t_cw_lipo, int& t_lipo_mV, int& t_per) {
    // 2 * because of voltage divider
    int t_mV = t_cw_lipo * m_v_ref_mv * 2 / m_cw_ref;
    int t_x = 0, i = 0;
    int t_delta_down, t_delta_up;

    while (t_mV > m_lookup_table[i + 1].mV) {
        t_x++;
        i++;

        if (t_x == 20) {
            break;
        }
    }

    if (t_x != 20 && t_mV > m_lookup_table[0].mV) {
        t_delta_down = t_mV - m_lookup_table[t_x].mV;
        t_delta_up = m_lookup_table[t_x + 1].mV - t_mV;

        if (t_delta_up < t_delta_down) {
            t_x++;
        }
    }

    t_lipo_mV = t_mV;
	t_per = m_lookup_table[t_x].per;
	return m_lookup_table[t_x].state;
}

void LiPo::LiPo::setReference(int t_v_ref_mv, int t_res) {
    m_v_ref_mv = t_v_ref_mv;
    for (int i = 0; i < t_res; i++) {
        m_cw_ref *= 2;
    }
}

//#define EXAMPLE

#ifdef EXAMPLE

#include <iostream>
using namespace std;

using namespace LiPo;

int main() {
    // U_ref = 3V3
    // ADC resolution = 10 bits
    class LiPo lipo(3300, 10);

    // current lipo cw
    int myCurrentCw = 4020 * 1024 / 3300 / 2;
    int myCurrent_mV;

    // battery percentage
    int percentage;

    if (lipo.getState(myCurrentCw, myCurrent_mV, percentage)) {
        cout << "good battery state: V = " << myCurrent_mV 
            << "mV == " << percentage << "%" << endl;
    } else {
        cout << "bad battery state: Cw = " << myCurrent_mV
            << "mV == " << percentage << "%" << endl;
    }
    
    return 0;
}

#endif