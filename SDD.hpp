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

    private:
        std::vector<uint8_t> buffer;
        enum class STATE
        {
            STANDBY,
            ONGOING
        };
        STATE state = STATE::STANDBY;
        uint8_t messageIndex = 0;
        FakeLedControl &ledControl;
};
