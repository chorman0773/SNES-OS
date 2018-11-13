#ifndef __dir_h_2018_05_04_14_26
#define __dir_h_2018_05_04_14_26


typedef struct{
	path* parent;
	path* sibling;
	path* firstChild;
	const char* lname;
	bool isDir;
}path;


typedef struct{
	int ownerUid;
	int ownerGid;
	unsigned short permissions;
	long updateTimeSeconds;
	int updateTimeNanos;
	path* basePath;
}pathinfo;


void mountDevice(path*,path*);
void mountDirectory(path*,path*);
void unmount(path*);
path* mkdir(path*,const char*);
path* createFile(path*,const char*);
void rm(path*);
void link(path*,path*);

bool exists(path*);
bool isDir(path*);
bool isFile(path*);

path* getAbsolutePath(const char*);
path* getChildPath(path*,const char*);
const char* getPathname(path*);
path* getWorkingDirectory();
path* getProgramDirectory();
path* getRelativePath(const char*);

path* getFsRoot();

int listPaths(path*,path**);

pathinfo* getPathInfo(path*);

int openFD(path*,int);

#endif
