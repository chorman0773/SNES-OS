#ifndef __syscalls_h_2018_06_06_10_18
#define __syscalls_h_2018_06_06_10_18

#ifdef __cplusplus
extern "C"{
#endif

#define PROC_Read 0x01
#define PROC_Write 0x02
#define PROC_Exec 0x10

#define MODE_Distinct 0x01
#define MODE_Shared 0x00
#define MODE_COW 0x02

#define FMODE_READ 0x01
#define FMODE_WRITE 0x02
#define FMODE_APPEND 0x04
#define FMODE_RW 0x03
#define FMODE_RAPP 0x05

#define FD_STDIN 0
#define FD_STDOUT 1
#define FD_STDERR 2

#define FD_NONE -1
  
#define F_LOCK 0
#define F_ULOCK 1
#define F_TEST 2
#define F_TLOCK 3
  
#define SEEK_SET 0
#define SEEK_CURR 1
#define SEEK_END 2
  
typedef int off_t;

typedef int fd_t;

typedef unsigned short pid_t;
typedef unsigned short uid_t;
typedef unsigned short gid_t;

typedef void noreturn_t;


/*
  Maps a given pointer into some memory.
  If the pointer is not given (set to NULL), mmap will attempt to find some memory availble to the process that will not conflict
  with other regions. If The pointer is already mapped, the region will be resized or have permissions changed.
  The last argument is a file-descriptor. the value -1 indicates that no file-descriptor is to be assigned to the memory,
  and some new physical memory is allocated (the same occurs if MODE_Distinct is passed).
  If the file descriptor is open to the file /dev/null, or a symbolic link to that file, then the returned pointer is
  NULL. If memory cannot be allocated for the function, for example, the pointer is invalid, 
  assigned to a reserved memory region, or not given and the process cannot find a large enough unused region of memory,
  or Physical Memory allocation would occur (either directly without passing a file descriptor or with MODE_Distinct, or
  as a possible side effect (IE. mapping memory with MODE_COW)), and the underlying memory control unit cannot guarentee
  enough physical memory then the returned pointer is NULL.
  If the given file descriptor is not readable by the current user, or is allocated with PROC_Write, using MODE_Shared (default),
  and the file descriptor is not writeable by the current user, then program raises an Access Violation.
  If the given file descriptor is not -1 and is invalid, then the function returns NULL.
*/
void* mmap(void*,size_t,unsigned char,unsigned char,fd_t,unsigned long long);
/*
  Releases a mapped region of memory.
  If the region of memory is not mapped or is reserved this function has no effect.
*/
void mumap(void*);

/*
  Opens a file with the given name and the given mode.
  If the function cannot open the given file with the given int chown(mode as the current user, the function returns -1.
*/
fd_t open(const char*,int)

/*
  Reads from a file descriptor into a given memory region.
  The function will return either the number of bytes read or -1 to indicate that reading failed.
*/
fd_t read(int,void*,size_t);

/*
  Writes to a file descriptor from a given memory region.
  The function will return the number of bytes written, or -1 to indicate that writing failed.
*/
int write(fd_t,void*,size_t);

/*
  Closes a given file descriptor. If the file descriptor is invalid or not open then the function has no effect.
  Closing stdin, stdout, and stderr also have no effect.
*/
void close(fd_t);

/*
  Creates a file descriptor to a temporary file and opens it in Read/Write mode.
  The file will cease to exist when the process is deallocated.
*/
fd_t openTemporary();

/*
  Forks the current process into a new child process.
  The function will return the id of the new child process in the parent process, or return 0 in the child.
  If fork cannot execute, it will return 0 and errno is set.
*/
pid_t fork();
pid_t vfork();

/*
  Detachs the current process from any controlling shell.
  This function applies as though by the following code:
  if(fork())
    _exit(2); 
  This function can be useful for GUI programs, or programs that don't require user input or user output.
*/
void detach();

/*
  Exits the process with full cleanup but without calling exit handlers.
*/
noreturn_t _exit(int)__attribute__((noreturn));

fd_t dup(fd_t);
fd_t dup2(fd_t,fd_t);

int pipe(fd_t[2]);
  
int lockf(fd_t,int,off_t);
  
off_t lseek(fd_t,off_t,int);

int link(const char*,const char*);
int symlink(const char*,const char*);
  
unsigned int sleep(unsigned int seconds);
  
void sync();

int chdir(const char*);
int chroot(const char*);

int chown(const char*,uid_t,gid_t);
int lchown(const char*,uid_t,gid_t);
  
pid_t getppid();
pid_t getpid();
pid_t getpgid();
pid_t getpgrp();
/*
  Obtains the User Id of the User executing the program.
  Note that this function may lose information. If the program is executed via sudo the uid is 0 (for root).
*/
uid_t getuid();
gid_t getgid();

  
int unlink(const char*);
int rmdir(const char*);
  
int execl(const char*,...);
int execle(const char*,...);
int execv(const char*,const char* const argv[]);
int execve(const char*,const char* const argv[],const char*const envp[]);
#ifdef __cplusplus
};
#endif

#endif
