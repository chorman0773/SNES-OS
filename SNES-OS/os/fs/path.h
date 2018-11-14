#ifndef __dir_h_2018_05_04_14_26
#define __dir_h_2018_05_04_14_26

#include <stdbool.h>

typedef struct path path;


typedef struct{
	int ownerUid;
	int ownerGid;
	unsigned short permissions;
	long long updateTimeSeconds;
	unsigned int updateTimeNanos;
	path* basePath;
}pathinfo;

typedef struct path_list{
	path* path;
	struct path_list* next;
	struct path_list* head;
}path_list;

/*
 * Allocates a new path.
 * The path has a refcount of 1
 */
path* pathNew();

/*
 * Frees a path if only one instance exists, otherwise decrements its refcount
 */
void pathFree(path*);

/**
 * Frees the given path list, and any contained paths that would be orphaned
 */
void pathListFree(path_list*);

/*
 * Indicates that multiple places will share the given path by incrementing its refcount
 */
void pathDup(path*);

void mount(path*,path*,...);
void unmount(path*);
void mkdir(path*);
void createFile(path*);
void rm(path*);
void link(path*,path*);
void symlink(path*,path*);

bool exists(path*);
bool isDir(path*);
bool isFile(path*);

path* getAbsolutePath(const char*);
path* getChildPath(path*,const char*);
char* getPathname(path*);
path* getWorkingDirectory();
path* getProgramDirectory();
path* getRelativePath(const char*);

path* getFsRoot();

path_list* getChildren(path*);

pathinfo getPathInfo(path*);

int openFD(path*,int);

#endif
