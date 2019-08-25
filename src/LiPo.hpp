#ifndef LIPO_HPP_
#define LIPO_HPP_

struct tuple {
	int percentageLoaded; //ex. 70 = 70% loaded
	int currentVoltage;   //current output voltage of the lipo
	bool state;			  //false = empty, true = full
};

/**
 * @brief Used to retreive the battery charging state and wether it is empty or not.
 * @note   
 * @retval None
 */
class LiPo {
    
public:
	LiPo(int, int);

	bool getState();
	int getPercentageLoaded();
	int getCurrentVoltage();
	void setReference(int, int);

private:
	/**
	 * @brief  updates the current voltage and calculates percentageLoaded and state.
	 * @note   updates only every refresh_interval th step. Returns the old values otherwise
	 * @retval None
	 */
	void refresh();
	struct tuple m_lookup_table[21];
	//only actually refreshes every 6th call
	unsigned int refreshInterval = 6;
	unsigned int refreshCounter;
	int referenceVoltage;
	int currentVoltage_mV;
	int percentageLoaded;
	bool state;

	// percentage of voltage used e.G nominator=1, denominator=2 = 1/2 of the voltage is used.
	int voltageDividerNominator = 1;
	int voltageDividerDenominator = 2;

	void init();
};

#endif