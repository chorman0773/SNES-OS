#ifndef __stdio_h_2018_04_20_11_39
#define __stdio_h_2018_04_20_11_39

#ifdef __cplusplus
extern "C"{
#endif

#define EOF (-1)
#define BUFSIZ 512
    
#define _IOFBUFF 1
#define _IOLBUFF 2
#define _IONBUFF 0
#define FOPEN_MAX 128
#define FILENAME_MAX 65536
#define TMP_MAX 256
#define L_tmpnam 512
#define SEEK_CURR 1
#define SEEK_END -1
#define SEEK_SET 0
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
typedef uint64_t pos_t;

struct _iobuff{
    int fd;
    uint64_t filePos;
    unsigned short mode;
    unsigned short status;
    int buffAmm;
    unsigned char* buffer;
};
typedef _iobuff FILE;

extern FILE* const stdin;
extern FILE* const stdout;
extern FILE* const stderr;
FILE* fopen(const char*,const char*);
FILE* freopen(const char*,const char*,FILE*);
void fflush(FILE*);
void fclose(FILE*);
bool ferror(FILE*);
bool feof(FILE*);
void fwrite(const void*,size_t,size_t,FILE*);
int fread(void*,size_t,size_t,FILE*);
void fcloseall();
void clearerror(FILE*);

int fsetpos(FILE*,pos_t*);
size_t ftell(FILE*);

int remove(const char*);
int rename(const char*,const char*);

void setbuff(FILE*,char*);
void setvbuff(FILE*,char*,int,size_t);

void rewind(FILE*);



FILE* tmpfile();
char* tmpname(char*);

int vprintf(const char*,va_list);
int vfprintf(FILE*,const char*,va_list);
int vsprintf(char*,const char*,va_list);

void printf(const char*,...);
void fprintf(FILE*,const char*,...);
void sprintf(FILE*,const char*,...);

int scanf(const char*,...); 
int fscanf(FILE*,const char*,...);
int sscanf(char*,const char*,...);

int getc(FILE*);
int fgets(FILE*,int,char*);
char* gets(char*);
int getchar();
int ungetc(int,FILE*);

int putchar(int);
int putc(int,FILE*);
int puts(const char*);

void perror(const char*);




#ifdef __cplusplus
};
#endif
#endif
