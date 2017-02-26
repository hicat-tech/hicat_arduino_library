
#include "hicat.h"

HiCat hicat;

HiCat::HiCat()
{
    
}

int HiCat::begin()
{
    Serial.begin(115200);
    Serial1.begin(115200);
}

int HiCat::snapshot(const char *file_name)
{
    prepare_web_command();
    Serial1.print("snapshot?dir=/www/mmc/&name=");
    Serial1.print(file_name);
    Serial1.print("\"\n");

    return read_result();
}

int HiCat::record()
{
    prepare_web_command();
    Serial1.print("record?save=1\"\n");

    return read_result();
}

int HiCat::stop_recording()
{
    prepare_web_command();
    Serial1.print("record?save=0\"\n");

    return read_result();
}


int HiCat::set_camera(int resolution, int rotation, int fps)
{
    prepare_web_command();
    Serial1.print("setCamera?resolve=");
    Serial1.print(resolution);
    Serial1.print("&rotate=");
    Serial1.print(rotation);
    Serial1.print("&fps=");
    Serial1.print(fps);
    Serial1.print("\"\n");

    return read_result();
}

int HiCat::set_wifi(int mode, const char *ssid, const char *password)
{
    prepare_web_command();
    if (mode) {
        Serial1.print("stationMode");
    } else {
        Serial1.print("apMode");
    }
    Serial1.print("?ssid=");
    Serial1.print(ssid);
    Serial1.print("?password=");
    Serial1.print(password);
    Serial1.print("\"\n");

    return read_result();
}

int HiCat::run(const char *command)
{
    Serial1.print(command);
    Serial1.print('\n');

    return read_result();
}

void HiCat::prepare_web_command()
{
    Serial1.print('\x03');
    Serial1.print("curl \"http://127.0.0.1/hicat/");
}

int HiCat::read_result()
{
    delay(1000);
    while (Serial1.available()) {
        Serial1.read();
    }
    Serial1.print('echo $?\n');

    int timeout = 10000;
    while (!Serial1.available() && timeout) { timeout--; }
    return Serial1.read() - '0';
}

void serialEventRun()
{
    while (Serial1.available() && Serial.availableForWrite()) {
        Serial.write((char)Serial1.read());
    }

    while (Serial.available() && Serial1.availableForWrite()) {
        Serial1.write((char)Serial.read());
    }
}