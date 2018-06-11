#include <os/gfxenv.h>
#include <os/syscalls.h>
#include <os/terminals.h>
#include <os/socket.h>
#include <os/fs/path.h>

const devno_t tmpfsDev = 0x102;
const char rootDir[] = "/";
const char tmpfsDir[] = "/tmp";
const char tmpfsDevicePath[] = "/dev/sys/fs/tmp";

void initTmpFs(){
    path* tmpfsDevice = getAbsolutePath(tmpfsDevicePath);
    path* tmpfsPath = getAbsolutePath(tmpfsDir);
    mountDevice(tmpfsDevice,tmpfsPath);
}