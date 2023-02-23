#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define PIN_PWM (13)

#define PIN_SW_P (0)
#define PIN_SW_M (4)

namespace {
enum {
    PwmLevelMax = 500,
};

int16_t lvl = 0;

bool sw_state_p = 0;
bool sw_state_m = 0;

void init_sw()
{
    gpio_init(PIN_SW_P);
    gpio_init(PIN_SW_M);

    gpio_set_dir(PIN_SW_P, false);
    gpio_set_dir(PIN_SW_M, false);

    gpio_set_pulls(PIN_SW_P, true, false);
    gpio_set_pulls(PIN_SW_M, true, false);
}

void process_sw()
{
    auto p = !gpio_get(PIN_SW_P);
    auto m = !gpio_get(PIN_SW_M);
    if (!sw_state_p && p) {
        lvl += 50;
        if (PwmLevelMax < lvl) {
            lvl = PwmLevelMax;
        }
    }
    if (!sw_state_m && m) {
        lvl -= 50;
        if (lvl < 0) {
            lvl = 0;
        }
    }
    sw_state_p = p;
    sw_state_m = m;
}
} // namespace

int main()
{
    stdio_init_all();

    puts("Hello, world!");

    sleep_ms(100);

    gpio_set_function(PIN_PWM, GPIO_FUNC_PWM);

    auto slice = pwm_gpio_to_slice_num(PIN_PWM);
    auto c = pwm_get_default_config();
    auto ch = pwm_gpio_to_channel(PIN_PWM);
    pwm_config_set_clkdiv(&c, 63);
    pwm_config_set_wrap(&c, PwmLevelMax);
    // pwm_set_wrap(slice, 1000);
    pwm_init(slice, &c, false);
    pwm_set_chan_level(slice, ch, lvl);
    // start pwm
    pwm_set_enabled(slice, true);

    init_sw();

    while (true) {
        sleep_ms(50);
        process_sw();
        pwm_set_chan_level(slice, ch, lvl);
    }

    return 0;
}
