#include "../../common/Sound.h"
#include "FastLED.h"
#include "toneAC.h"
#include "utils.h"

class BoardSound final : public Sound {
protected:
    virtual void play_note(uint16_t freq, uint8_t duration) override;
};
