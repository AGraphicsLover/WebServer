#include"response.h"

struct BasicResponse* responseFirstLine(int scode,char* description)  //response第一行
{
  struct BasicResponse* rst = (struct BasicResponse*)malloc(sizeof(struct BasicResponse));
  sprintf(rst->state,"HTTP/1.1 %d %s\r\n",scode,description);
  rst->len = strlen(rst->state);
  return rst;
}

struct AdditionalResponse* initResponse(char* key,char* value)  //初始化回应
{
    struct AdditionalResponse* rst = (struct AdditionalResponse*)malloc(sizeof(struct AdditionalResponse));
    sprintf(rst->state,"%s: %s\r\n",key,value);
    rst->len = strlen(rst->state);
    return rst;
}

void addResponse(struct FinalResponse* res,struct AdditionalResponse* ar)  //添加回应信息
{
    char* tmp = res->data+res->len;
    memcpy(tmp,ar->state,ar->len);
    res->len = res->len+ar->len;
    free(ar);
}

void addBasicResponse(struct FinalResponse* res,struct BasicResponse* br)  //添加基本回应信息
{
    memcpy(res->data,br->state,br->len);
    res->len = br->len;
    free(br);
}

void addTail(struct FinalResponse* res)  //添加回应尾部
{
    memcpy(res->data+res->len,"\r\n",2);
    res->len = res->len+2;
}