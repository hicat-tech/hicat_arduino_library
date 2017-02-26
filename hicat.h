

#ifndef _HICAT_H_
#define _HICAT_H_

#include <Arduino.h>

class HiCat
{
public:
    HiCat();
    int begin(void);

    /**
     * Take a picture
     *
     * @param file_name     picture name
     * @return 0 - OK, otherwise - error code
     */
    int snapshot(const char *file_name);

    /**
     * Start to record a video which is saved at /www/mmc/video/
     *
     * @return 0 - OK, otherwise - error code
     */
    int record();

    /**
     * Stop to record a video
     *
     * @return 0 - OK, otherwise - error code
     */
    int stop_recording();

    /**
     * Set camera format
     *
     * @param resolution    0 - 1280*720, 2 - 640*480, 1 - 320*240
     * @param rotation      0 - no rotation, 1 - 180 degree rotation
     * @param fps           frame per secord from 1 to 25
     * @return 0 - OK, otherwise - error code
     */
    int set_camera(int resolution, int rotation, int fps);

    /**
     * Set Wi-Fi mode
     *
     * @param mode  0 - AP mode, 1 - Station mode
     * @param ssid  SSID
     * @param password  password
     * @return 0 - OK, otherwise - error code
     */
    int set_wifi(int mode, const char *ssid, const char *password);

    /**
     * Run a shell command
     *
     * @param command   shell command
     * @return 0 - OK, otherwise - error code
     */
    int run(const char *command);

private:
    void prepare_web_command();
    int read_result();
};

extern HiCat hicat;


#endif // _HICAT_H_
