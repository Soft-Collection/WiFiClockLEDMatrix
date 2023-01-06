#ifndef ClockLEDMatrixDisplay_h
#define ClockLEDMatrixDisplay_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "Config.h"
#include "Period.h"

class ClockLEDMatrixDisplay
{
public:
	ClockLEDMatrixDisplay();
	virtual ~ClockLEDMatrixDisplay();
	void Init();
	void Check();
	void DisplayTime(int8_t hour, int8_t minute, int8_t day, int8_t month, bool showPoints);
	void DisplayNotUpdated();
private:
	static void OnPeriodExpiredStaticScroll(void* instance);
	void OnPeriodExpiredScroll();	
	static void OnPeriodExpiredStaticChange(void* instance);
	void OnPeriodExpiredChange();	
private:
    Period* mPeriodScroll;
    Period* mPeriodChange;
	Adafruit_NeoMatrix* mMatrix;
	uint16_t mColors[5];
	String mStringToDisplay;
	char mTime[16];
	char mDate[16];
	bool mShowTime;
	bool mIsWaiting;
};

#endif //ClockLEDMatrixDisplay_h