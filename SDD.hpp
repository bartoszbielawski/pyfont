#include <vector>
#include "pyfont.h"
// Scrolling Display Driver (SDD)
// Class for the state machine that handles the scrolling of the
// text on the screens

class FakeLedControl;

class SDD
{
    public:
        SDD(FakeLedControl &ledControl);
        ~SDD() {}

        bool tick();
        void renderString(const std::string &message, const PyFont& font);

        void refreshDisplay();

    private:
        std::vector<uint8_t> buffer;
        enum class STATE
        {
            START,
            MIDDLE,
            END
        };

        STATE state = STATE::START;

        FakeLedControl &ledControl;
        const static int columnIncrement = 2;
        size_t           startColumn = 0;

        const static int endDelay = 5;
        int              delayCounter = 0;
        int              physicalDisplayLen;
};
