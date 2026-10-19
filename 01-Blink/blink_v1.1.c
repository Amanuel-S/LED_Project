/*
 * ============================================================
 * Project       : LED_Project
 * File          : blink.c
 * Author        : Amanuel Shibre
 * Date Created  : [2026-10-16]
 * Version       : 1.1.0
 *
 * Description:
 *     This is version of the blinker blinks the SOS in morse code 10 times.
 *
 * Dependencies:
 *     #include <gpiod.h>
 *     #include <stdio.h>
 *     #include <unistd.h>
 *
 * Input:
 *     N/A
 *
 * Output:
 *     LED light blinks on and off
 *
 * Notes:
 *     For the hardware set-up we have the gpio17 (the physical pin 11) connected to the pred board which we made 
 *     a simple circuit with a resistor and light then connected the end of the circuit to the ground of the 
 *     raspberry pi (physical pin 9)
 *
 * ============================================================
 */

#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

#define CHIP_PATH   "/dev/gpiochip0"   // change to gpiochip4 on a Pi 5 
#define LED_OFFSET  17                 //GPIO17 = physical pin 11 */

int main(void)
{
    struct gpiod_chip *chip = NULL;
    struct gpiod_line_settings *settings = NULL;
    struct gpiod_line_config *line_cfg = NULL;
    struct gpiod_request_config *req_cfg = NULL;
    struct gpiod_line_request *request = NULL;
    unsigned int offset = LED_OFFSET;
    int ret = 1;

    chip = gpiod_chip_open(CHIP_PATH);
    if (!chip) {
        perror("open chip");
        return 1;
    }

    /* Describe how we want the pin configured: output, starting low */
    settings = gpiod_line_settings_new();
    if (!settings) goto cleanup;
    gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_OUTPUT);
    gpiod_line_settings_set_output_value(settings, GPIOD_LINE_VALUE_INACTIVE);

    /* Apply those settings to our pin */
    line_cfg = gpiod_line_config_new();
    if (!line_cfg) goto cleanup;
    if (gpiod_line_config_add_line_settings(line_cfg, &offset, 1, settings) < 0) {
        perror("add line settings");
        goto cleanup;
    }

    /* Give our request a name (shows up in `gpioinfo`) */
    req_cfg = gpiod_request_config_new();
    if (!req_cfg) goto cleanup;
    gpiod_request_config_set_consumer(req_cfg, "blink");

    /* Claim the pin */
    request = gpiod_chip_request_lines(chip, req_cfg, line_cfg);
    if (!request) {
        perror("request lines");
        goto cleanup;
    }

    for (int i = 0; i < 10; i++) {

        //S
        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_ACTIVE);
        usleep(50000);
        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_INACTIVE);
        usleep(80000);

        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_ACTIVE);
        usleep(50000);
        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_INACTIVE);
        usleep(80000);

        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_ACTIVE);
        usleep(50000);
        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_INACTIVE);
        usleep(80000);
        
       

        //O

        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_ACTIVE);
        sleep(1);
        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_INACTIVE);
        usleep(80000);

        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_ACTIVE);
        sleep(1);
        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_INACTIVE);
        usleep(80000);

        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_ACTIVE);
        sleep(1);
        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_INACTIVE);
        usleep(80000);


        //S
        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_ACTIVE);
        usleep(50000);
        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_INACTIVE);
        usleep(80000);

        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_ACTIVE);
        usleep(50000);
        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_INACTIVE);
        usleep(80000);

        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_ACTIVE);
        usleep(50000);
        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_INACTIVE);
        sleep(2);
    }
    

    ret = 0;

cleanup:
    if (request)  gpiod_line_request_release(request);
    if (req_cfg)  gpiod_request_config_free(req_cfg);
    if (line_cfg) gpiod_line_config_free(line_cfg);
    if (settings) gpiod_line_settings_free(settings);
    if (chip)     gpiod_chip_close(chip);
    return ret;
}

