#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include "include/DataPack.h"
#include "include/httprip.h"
#include "switchboard.h"
#include <iomanip>
#include <ctime>
#include <chrono>
#include <unistd.h>

char* getLines();
char* getPeriodAgenda();
char* getCurrentAgenda();
int getDay();
int getMonth();
std::string* split_up(string, char, string[]);
void update(HWND );

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*TODO: Get output every six minutes*/
DataPack ag(getLines());
char* fullDatabase;

//Boolean checks if combination to close has been pressed
bool isClosable;


/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    //isClosable
    isClosable = false;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           WS_EX_TOPMOST,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Strileckis Agenda Display"),       /* Title Text */
           WS_VISIBLE, /* window with no X*/
           0,       /* start in top left corner of screen */
           0,       /* start in top left corner of screen */
           35+ag.getWidth(),                 /* The program's width */
           200,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    FreeConsole();


    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


HWND periodWindow, titleWindow, agendaWindow;

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            update(hwnd);
            if(ag.getAgenda()[0] == '0'){
                std::cout<<"Crash gracefully";
                Sleep(1500);
                DestroyWindow(hwnd);
            }
            break;
        //Rich Edit box
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
     /*   case WM_CLOSE:
            if(isClosable){
                DestroyWindow(hwnd);
            }
            else{
                cout<<"no";
            }
            break;*/
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
        update(hwnd);
    }

    return 0;
}

void update(HWND hwnd){
    //Period heading
    periodWindow = CreateWindowEx(0, TEXT("STATIC"), TEXT(ag.getCharPeriod()),
                WS_VISIBLE | WS_CHILD,
                10, 10, 7, 16,
                hwnd, (HMENU) NULL, NULL, NULL);
    titleWindow = CreateWindowEx(0, TEXT("STATIC"), TEXT(ag.getPeriodTitle()),
                WS_VISIBLE | WS_CHILD,
                18, 10, 120, 16,
                hwnd, (HMENU) NULL, NULL, NULL);
    //Agenda
    agendaWindow = CreateWindowEx(0, TEXT("STATIC"), TEXT(ag.getAgenda()),
                WS_VISIBLE | WS_CHILD,
                25, 28, ag.getWidth(), ag.getHeight(),
                hwnd, (HMENU) NULL, NULL, NULL);
}

char* strToCharStar(std::string str){
    char* newStr = (char*)malloc(str.length() + 1);
    int i=0;
    for(char c : str){
        newStr[i++] = c;
    }
    newStr[i] = '\0';

    return newStr;
}

char* getPeriodAgenda(){
   /* std::tm time_in = { 0, 0, 0, // second, minute, hour
      9, 10, 2016 - 1900 }; // 1-based day, 0-based month, year since 1900*/
     time_t rawtime;
    time (&rawtime);
     //std::time_t time_temp = std::mktime(&rawtime);

     const std::tm * time_out = std::localtime(&rawtime);

  //Sunday == 0, Monday == 1, and so on ...
    //std::cout<<"\t~"<< time_out->tm_hour <<std::endl;
    string location = ".txt";
    location = periodSwitchboard(time_out->tm_wday,     //Period
                                 time_out->tm_hour,
                                 time_out->tm_min)
                                 + location;
    location = switchboard(time_out->tm_wday)+location; //Day MTWRF
    location = switchboard(getDay())+location;          //Day #
    location = switchboard(getMonth())+location;        //Month
    std::cout<<endl<<location<<endl;
    location = "http://kevinstrileckis.com/agendas/" + location;
    ripHTTP(strToCharStar(location));
    return ripAgenda();
}

int getDay(){
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    /*std::cout << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday
         << "\n";*/
    return now->tm_mday;
}
int getMonth(){
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    /*std::cout << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday
         << "\n";*/
    return (now->tm_mon + 1);
}

char* getLines(){
    std::cout<<("getLines");
    //return  "1output\noutput\ncrazycrazycrazy\nhey\nhey\nhey\nhey\nhey\n\nHey\0";
    //Rip from online
    //ripHTTP("http://www.kevinstrileckis.com/");
    //Rip from local drive
    return getPeriodAgenda();
}

std::string* split_up(string str, char token, string storage[]){
    int tokenCount = 0;
    for(int i=0; str[i] != '\0'; ++i){
        if(str[i] == token){
            tokenCount++;
        }
    }
    for(int i=0, j=0, c=0; str[i] != '\0'; ++i){
        if(str[i] == token){
            j++;
        }
        else{
            storage[j][c++] = str[i];
        }
    }

    return storage;
}
