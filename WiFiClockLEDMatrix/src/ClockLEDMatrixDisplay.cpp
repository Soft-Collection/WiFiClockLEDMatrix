#include "ClockLEDMatrixDisplay.h"

ClockLEDMatrixDisplay::ClockLEDMatrixDisplay()
{
    // MATRIX DECLARATION:
    // Parameter 1 = width of NeoPixel matrix
    // Parameter 2 = height of matrix
    // Parameter 3 = pin number (most are valid)
    // Parameter 4 = matrix layout flags, add together as needed:
    //   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
    //     Position of the FIRST LED in the matrix; pick two, e.g.
    //     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
    //   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
    //     rows or in vertical columns, respectively; pick one or the other.
    //   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
    //     in the same order, or alternate lines reverse direction; pick one.
    //   See example below for these values in action.
    // Parameter 5 = pixel type flags, add together as needed:
    //   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
    //   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
    //   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
    //   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
    //   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
    // Example for NeoPixel Shield.  In this application we'd like to use it
    // as a 5x8 tall matrix, with the USB port positioned at the top of the
    // Arduino.  When held that way, the first pixel is at the top right, and
    // lines are arranged in columns, progressive order.  The shield uses
    // 800 KHz (v2) pixels that expect GRB color data.
    mMatrix = new Adafruit_NeoMatrix(32, 8, MATRIX_PIN,
      NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
      NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
      NEO_GRB            + NEO_KHZ800);
    //---------------------------------------------  
    mColors[0] = mMatrix->Color(255, 0, 0);
    mColors[1] = mMatrix->Color(0, 255, 0);
    mColors[2] = mMatrix->Color(0, 0, 255);
    mColors[3] = mMatrix->Color(255, 255, 0);
    mColors[4] = mMatrix->Color(255, 255, 255);
    //---------------------------------------------  
    mPeriodScroll = new Period(this, 30, false);
    mPeriodChange = new Period(this, 5000, false);
    //---------------------------------------------  
    mShowTime = true;
    mIsWaiting = false;
}
ClockLEDMatrixDisplay::~ClockLEDMatrixDisplay()
{
}
void ClockLEDMatrixDisplay::Init()
{
    mMatrix->begin();
    mMatrix->setTextWrap(false);
    mMatrix->setBrightness(10);
    mMatrix->setTextColor(mColors[0]);
    mPeriodScroll->AddOnPeriodExpiredHandler(ClockLEDMatrixDisplay::OnPeriodExpiredStaticScroll);    
    mPeriodChange->AddOnPeriodExpiredHandler(ClockLEDMatrixDisplay::OnPeriodExpiredStaticChange);    
}
void ClockLEDMatrixDisplay::Check()
{
    mPeriodScroll->Check(millis());
    mPeriodChange->Check(millis());
}
void ClockLEDMatrixDisplay::DisplayTime(int8_t hour, int8_t minute, int8_t day, int8_t month, bool showPoints)
{
    mPeriodScroll->Reset();
    sprintf(mTime, "%02d%c%02d", hour, (showPoints) ? ':' : ' ', minute);
    sprintf(mDate, "%02d/%02d", day, month);
    if (mShowTime)
    {
        mStringToDisplay = String(mTime);
    }
    else
    {
        mStringToDisplay = String(mDate);
    }
}
void ClockLEDMatrixDisplay::DisplayNotUpdated()
{
    mPeriodScroll->Reset();
    mStringToDisplay = String(".....");
}
void ClockLEDMatrixDisplay::OnPeriodExpiredStaticScroll(void* instance)
{
 	ClockLEDMatrixDisplay* clmd = (ClockLEDMatrixDisplay*)instance;
	if (clmd != NULL) clmd->OnPeriodExpiredScroll();
}
void ClockLEDMatrixDisplay::OnPeriodExpiredScroll()
{
    mPeriodScroll->Reset();
    static int matrixWidth = mMatrix->width();
    static int colorIdx = 0;
    mMatrix->fillScreen(0);
    mMatrix->setCursor(matrixWidth, 0);
    mMatrix->print(mStringToDisplay);
    int columnsInString = mStringToDisplay.length() * 5;
    if (!mIsWaiting)
    {
        if(--matrixWidth < -columnsInString) 
        {
            matrixWidth = mMatrix->width();
            if (++colorIdx >= 5) colorIdx = 0;
            mMatrix->setTextColor(mColors[colorIdx]);
            mShowTime = !mShowTime;
        }
        if (matrixWidth == 2)
        {
            mIsWaiting = true;
            mPeriodChange->Reset();
        }
    }
    mMatrix->show();
}
void ClockLEDMatrixDisplay::OnPeriodExpiredStaticChange(void* instance)
{
    ClockLEDMatrixDisplay* clmd = (ClockLEDMatrixDisplay*)instance;
	  if (clmd != NULL) clmd->OnPeriodExpiredChange();
}
void ClockLEDMatrixDisplay::OnPeriodExpiredChange()
{
    mIsWaiting = false;
}