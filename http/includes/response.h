#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include"global.h"

struct BasicResponse{
  size_t len;
  char state[stateLen];
};
struct AdditionalResponse{
  size_t len;
  char state[dflen];
};
struct FinalResponse{
  size_t len;
  char *data;
};
struct FileInfo{
  size_t len;
  int chunked;
  char type[dftypelen];
  char *fpath;
};

struct BasicResponse* responseFirstLine(int scode,char* description);
struct AdditionalResponse* initResponse(char* key,char* value);
void addResponse(struct FinalResponse* res,struct AdditionalResponse* ar);
void addBasicResponse(struct FinalResponse* res,struct BasicResponse* br);
void addTail(struct FinalResponse* res);
#endif