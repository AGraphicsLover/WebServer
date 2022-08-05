#include"request.h"

char* headers[typenums] = {"Connection: ","Accept: ","Content-Length: ","Content-Type: ","Transfer-Encoding: "};

int requestFirstline(struct Request* req,char* ptr,size_t len)
{
	char *tmp = strstr(ptr," ");
	if(tmp==NULL||(tmp-ptr)>=8) 
		return -1;
	memcpy(req->method,ptr,tmp-ptr);
	len -= (tmp-ptr+1);
	ptr = tmp+1;
	tmp = strstr(ptr," ");
	if(tmp==NULL) 
		return -1;
	memcpy(req->URL,ptr,tmp-ptr);
	req->URLlen = tmp-ptr;
	len -= (tmp-ptr+1);
	ptr = tmp+1;
	memcpy(req->version,ptr,len);
	return 0;
}

struct Request* phaser(size_t len,char* buffer)
{
	char* ptr = buffer;
	int slen;

	struct Request* rst = (struct Request*)malloc(sizeof(struct Request));
	memset(rst,0,sizeof(struct Request));
	slen = headlize(ptr);
	if(slen<=3){free(rst);return NULL;}
	if(requestFirstline(rst,ptr,slen)==-1){  //如果接收到不支持的请求则释放并返回NULL
		free(rst);
		return NULL;
	}
	ptr = ptr+slen+2;
	while((slen=headlize(ptr))>0){  //循环处理头部
		if(headhandler(rst,slen,ptr)==false){
			free(rst);
			return NULL;
		}
		ptr = ptr+slen+2;
	}
	return rst;
}

int headlize(char* ptr)  //分行
{
	int rst = 0;
	char* tmp = strstr(ptr,rn);
	if(tmp==NULL) return -1;
	rst = tmp - ptr;
	return rst;
}

int headhandler(struct Request* req,size_t slen,char* ptr)  //处理头部
{
	if(memcmp(ptr,headers[0],12)==0) 
		memcpy(req->connection,ptr+12,slen-12);
	else if(memcmp(ptr,headers[1],8)==0) 
		memcpy(req->accept,ptr+8,slen-8);
	else if(memcmp(ptr,headers[2],16)==0) 
		memcpy(req->contentLength,ptr+16,slen-16);
	else if(memcmp(ptr,headers[3],14)==0) 
		memcpy(req->contentType,ptr+14,slen-14);
	else if(memcmp(ptr,headers[4],19)==0) 
		memcpy(req->Encoding,ptr+19,slen-19);
	return true;
}
