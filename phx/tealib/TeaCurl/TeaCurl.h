
#ifndef __TEA_CURL_H
#define __TEA_CURL_H

#include <string>
#include <cstring>
#include <stdlib.h>
#include <curl/curl.h>

class TeaCurl
{
public:
	TeaCurl(std::string url);
	void exec();
	CURL *getCurlResource();
	std::string getBody();
	std::string getError();
	std::string getResponseHeader();
	CURLcode getInfo(CURLINFO infoOpt, void *ptr);
	long getHttpCode();
	CURLcode getRes();
	void close();
	void setOpt(CURLoption opt, const void *val);
	void setProxy(std::string, std::string);
	~TeaCurl();
protected:
private:
	
	CURL *ch;
	CURLcode res;

	int closed = 0;
	long httpCode;
	long responseHeaderSize;
	
	std::string out;
	std::string url;
	std::string error;
	std::string responseHeader;

	void setUp();
	void cleanUp();
	static size_t __teaCurlWriteFunc(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif
