

#ifndef _HICAT_H_
#define _HICAT_H_

class HiCat
{
    HiCat();
    int init(void);
    int tack_picture(const char *file_name);
    int start_capture(const char *file_name);
    int stop_capture();
}


#endif // _HICAT_H_
