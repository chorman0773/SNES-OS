#include <os/gfxenv.h>
#include <os/syscalls.h>
#include <os/terminals.h>
#include <os/socket.h>
#include <os/fs/path.h>


const devno_t procfsDev = 0x101;
const char rootDir[] = "/";
const char procfsMountDir[] = "/proc";
const char procfsDevicePath[] = "/dev/sys/fs/procfs";
const char procfsSelfSymlink[] = "/proc/self";
const pid_t procfsOwnerPid = 0;//root
const gid_t procfsOwnerGid = 0;//root
extern const char* const procSelfTarget;


const permissions_t procfsPermissions = 0700;//owner:rwx
const permissions_t procfsDirPermissions = 0700;//owner: create, rename, delete 

const char procfsMem[] = "mem";
const char procfsFD[] = "fd";
const char procfsChildren[] = "children";
const char procfsInfo[] = "info";

void initProcFs(){
    path* procfsDevice = getAbsolutePath(procfsDevicePath);
    path* procfsMount = getAbsolutePath(procfsMountDir);
    mountDevice(procfsDevice,procfsMount);
}

path* getProcSelfPath(){
    return getAbsolutePath(procSelfTarget);
}
