#ifndef HTTPRIPPER
#define HTTPRIPPER

#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

#include <winsock.h>
#include <shellapi.h>
#include <mmsystem.h>

#define HTTP_USER_AGENT "httprip"
#define BUFFER_SIZE 512

void usage(void);
void die(const char *message);

const char http[] = "HTTP";

int ripHTTP(char* requesturl)
{
    int argc = 3;
    HANDLE file;
    //SECURITY_ATTRIBUTES sa;
    HINTERNET handle_Internet;
    HINTERNET url;
    char *outputfile = NULL;
    char *buf = NULL;
    DWORD bytesread;
    DWORD byteswritten;
    int k;
    int usestdout = 0;

    if (argc == 2)
        // user wants data directed to stdout
        usestdout = 1;
    else if (argc != 3)
        usage();


    if (!usestdout)
        outputfile = (char*)"out.agenda";

    // validate protocol -- first 4 alphas should be http, case insensitive
    for (k = 0; k < 4; k++)
        if (requesturl[k] != http[k] &&	requesturl[k] != (char)(http[k] + 32))
            die("Invalid url");

    if (!usestdout)
    {
        file = CreateFile(outputfile,
        GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
        if (file == INVALID_HANDLE_VALUE)
            die("CreateFile()");
    }

    printf("Opening connection...\n");
    //InternetOpen is the first WinInet function called by an application.
    handle_Internet = InternetOpen(
                            HTTP_USER_AGENT,  //this file (which rips http)
                            INTERNET_OPEN_TYPE_PRECONFIG, //checks registry for configuration (proxy/direct)
                            NULL, //proxy servers allowed
                            NULL, //host names to rout through
                            0); //kind of Internet flag
    if (handle_Internet == NULL)
        die("InternetOpen()");

    printf("Requesting url...\n");
    url = InternetOpenUrl(handle_Internet, //handler
                          requesturl, //url
                          NULL, //Headers to be sent
                          0, //length of additional headers
                          INTERNET_FLAG_RAW_DATA, //find as raw HTML
                          //INTERNET_FLAG_PRAGMA_NOCACHE, //old flag--I don't know what this does
                          0);//value returned to any callback functions
    if (url == NULL)
        die("InternetOpenUrl()");

    buf = (char*)malloc(BUFFER_SIZE + 1);
    if (buf == NULL)
        die("Unable to allocate memory for receive buffer");

    printf("Saving file");
    while (InternetReadFile(url, buf, BUFFER_SIZE, &bytesread))
    {
        if (bytesread == 0)
            break;
        if (!usestdout)
        {
            WriteFile(file, buf, bytesread, &byteswritten, NULL);
            putchar('.');
        }
        else
            //fwrite( const void *buffer, size_t size, size_t count, FILE *stream );
            fwrite(buf, bytesread, 1, stdout);
    }
    putchar('\n');

    free(buf);
    InternetCloseHandle(url);
    InternetCloseHandle(handle_Internet);
    CloseHandle(file);

    printf("Done.\n");

    return 0;
}

char* ripAgenda(){
    std::ifstream ifp("out.agenda");
    std::string buffer = "";
    char c;
    if(ifp.good()){
        ifp.get(c);
        if(c == '~'){
            printf("input good");
            buffer += c;
        }
        else{
            printf("invalid agenda file");
            return (char *)"Invalid session";
        }
    }
    else{
        printf("input is not good");
        return (char *)"Invalid session";
    }
    while(ifp.get(c)){
        buffer += c;
    }
    ifp.close();
    //printf("%s %d", buffer.c_str(), buffer.length());
    int x=buffer.length();
    char* value = (char*)malloc(x);
    int i=0;
    for(; i<x; ++i){
        value[i] = buffer[i];
    }
    value[i] = '\0';

    //After using the file, destroy it.
    int report = remove("out.agenda");

    return value;
}

/*
void usage(void)
{
    fprintf(stderr, "http rip - Chad Osgood\n\nusage: httprip url filename\n");
    exit(EXIT_FAILURE);
}

void die(const char *message)
{
    fprintf(stderr, "%s", message);
    exit(EXIT_FAILURE);
}

*/
#endif // HTTPRIPPER
