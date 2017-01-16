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
        uint16_t messageIndex = 0;
        uint16_t cycleCounter = 0;
        FakeLedControl &ledControl;
        std::string message;
        const PyFont* pf = nullptr;
};
