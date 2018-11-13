#include <os/gfxenv.h>

#include "../../../../SNES-OS/os/fs/path.h"
#include "../../../../SNES-OS/os/socket.h"
#include "../../../../SNES-OS/os/syscalls.h"
#include "../../../../SNES-OS/os/terminals.h"

const devno_t tmpfsDev = 0x102;
const char rootDir[] = "/";
const char tmpfsDir[] = "/tmp";
const char tmpfsDevicePath[] = "/dev/sys/fs/tmp";

void initTmpFs(){
    path* tmpfsDevice = getAbsolutePath(tmpfsDevicePath);
    path* tmpfsPath = getAbsolutePath(tmpfsDir);
    mountDevice(tmpfsDevice,tmpfsPath);
}