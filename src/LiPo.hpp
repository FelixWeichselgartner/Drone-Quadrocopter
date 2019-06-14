#ifndef LIPO_HPP_
#define LIPO_HPP_

namespace LiPo {

struct tuple {
	int per;
	int mV;
	bool state;
};

class LiPo {
	
public:

	LiPo(int, int);

	bool getState(int, int&, int&);
	void setReference(int, int);

private:

	struct tuple m_lookup_table[21];
	int m_v_ref_mv;
	int m_cw_ref = 1;

	void init();
};

}

#endif