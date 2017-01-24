/* This file is part of PKSV
> MIT License
> Copyright (c) 2016/17 Bernardo Giordano
>
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all
> copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
> SOFTWARE. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <3ds.h>
#include "http.h"
#include "graphic.h"

Result downloadFile(char* url, char* path) {
    httpcInit(0);
    httpcContext context;
    u32 statuscode = 0;
    u32 contentsize = 0;
    u8 *buf;

    if (httpcOpenContext(&context, HTTPC_METHOD_GET, url, 0)) {
        infoDisp("Failed to open http context!");
        return -1;
    }

    if (httpcAddRequestHeaderField(&context, "User-Agent", "PKSV")) {
        infoDisp("Failed to add a request header field!");
        return -1;
    }
	
    if (httpcSetSSLOpt(&context, SSLCOPT_DisableVerify)) {
        infoDisp("Failed to set SSLOpt!");
        return -1;
    }
	
	httpcAddRequestHeaderField(&context, "Connection", "Keep-Alive");

    if (httpcBeginRequest(&context)) {
        infoDisp("Failed to begin a http request!");
        return -1;
    }

    if (httpcGetResponseStatusCode(&context, &statuscode)) {
        infoDisp("Failed to receive a status code!");
        httpcCloseContext(&context);
        return -1;
    }

    if (statuscode != 200) {
        if (statuscode >= 300 && statuscode < 400) {
            char newUrl[1024];
            if (httpcGetResponseHeader(&context, (char*)"Location", newUrl, 1024)) {
                infoDisp("Redirection failed!");
                return -1;
            }
            httpcCloseContext(&context);
            downloadFile(newUrl, path);
            return -1;
        } else {
            infoDisp("Redirection failed!");
            httpcCloseContext(&context);
            return -1;
        }
    }

    if (httpcGetDownloadSizeState(&context, NULL, &contentsize)) {
        infoDisp("Failed to receive download size!");
        httpcCloseContext(&context);
        return -1;
    }

    buf = (u8*)malloc(contentsize);
    if (buf == NULL) {
		free(buf);
        infoDisp("Failed to alloc memory!");
        return -1;
    }
    memset(buf, 0, contentsize);

    if (httpcDownloadData(&context, buf, contentsize, NULL)) {
        free(buf);
        infoDisp("Failed to download file!");
        httpcCloseContext(&context);
        return -1;
    }

    remove(path);
    FILE *fptr = fopen(path, "wb");
    fwrite(buf, 1, contentsize, fptr);
    fclose(fptr);
    free(buf);

    httpcCloseContext(&context);
    httpcExit();
    return 0;
}