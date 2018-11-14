/*
 * path.c
 *
 *  Created on: Nov 13, 2018
 *      Author: chorm
 */

#include "path.h"
#include <stdlib.h>
#include <string.h>

struct path_cache{
	const char* absName;
	path* target;
	struct path_cache* next;
	struct path_cache* prev;
};

typedef struct path_cache path_cache;

path_cache head = {"/",NULL,NULL,NULL};
path_cache* current = &head;
struct path{
	path_cache* cache_entry;
	path* parent;
	const char* name;
	uint16_t refCount;
};

path* getFSRoot(){
	static path root = {&head,NULL,"",1};
	static bool init = true;
	if(init){
		head.target = root;
		init = false;
	}
	return &root;
}

path* getProgramDirectory(){
	const char* name;
	syscall(0xF1,6,&name);
	path* p = getAbsolutePath(strdup(name));
	path* parent = p->parent;
	pathDup(parent);
	pathFree(p);
	return parent;
}

path* getWorkingDirectory(){
	const char* name;
	syscall(23,"pwd",&name);
	return getAbsolutePath(strdup(name));
}

path* pathNew(){
	path* p = (path*)malloc(sizeof(path));
	p->cache_entry = NULL;
	p->name = NULL;
	p->parent = NULL;
	p->refCount = 1;
	return p;
}

void pathFree(path* p){
	if(!p)
		return;
	p->refCount--;
	if(!p->refCount){
		path_cache* pc = p->cache_entry;
		if(pc){
			if(pc==current)
				current = pc->prev;
			pc->prev->next = pc->next;
			pc->next->prev = pc->prev;
			free(pc);
		}
		pathFree(p->parent);
		if(p->name)
			free(p->name);
		free(p);
	}
}

void pathDup(path* p){
	p->refCount++;
}

path* getAbsolutePath(const char* name){
	const char* nEnd = name+strlen(name);
	path_cache* c = &head;
	if(*name!='/')
		return NULL;
	for(;c&&strcmp(c->absName,name);c=c->next);
	if(c){
		path* p = c->target;

	}else{
		while(--nEnd!=name&&*nEnd!='/');
		path* p = pathNew();
		p->name = strdup(nEnd);
		char* name = strndup(name,nEnd-name);
		p->parent = getAbsolutePath(name);
		p->parent->refCount++;
		free(name);
		path_cache* cache_ent = malloc(sizeof(path_cache));
		cache_ent->target = p;
		p->cache_entry = cache_ent;
		cache_ent->absName = name;
		cache_ent->prev = current;
		cache_ent->next = NULL;
		current->next = cache_ent;
		current = cache_ent;
	}
}



void pathListFree(path_list* list){
	if(list!=list->head)
		list = list->head;
	while(list!=NULL){
		path_list* tmp = list->next;
		pathFree(list->path);
		free(list);
		list = tmp;
	}
}

path_list* getChildren(path* p){
	char** names;
	uint16_t nCount;
	path_list* ret;
	path_list* current;
	if(!p||!isDirectory(p))
		return NULL;
	syscall(0x10C,1,&nCount);
	syscall(0x10C,0,&names);
	ret = malloc(sizeof(path_list));

}
