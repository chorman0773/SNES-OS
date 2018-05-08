#ifndef __setup_devfs_2018_05_07_19_15
#define __setup_devfs_2018_05_07_19_15
#include <os/fs/path.h>

void initDevFs(path**,unsigned int(**)(unsigned long long,unsigned char*,unsigned int),void(**)(unsinged long long, unsigned const char*,unsigned int));

#endif
