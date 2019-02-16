#ifndef SWITCHBOARD
#define SWITCHBOARD
#include <iostream>
#include <stdlib.h>
#include "switchboard.h"

char switchboard(int number){
    switch(number){
    case 0:
        return '0';
    case 1:
        return '1';
    case 2:
        return '2';
    case 3:
        return '3';
    case 4:
        return '4';
    case 5:
        return '5';
    case 6:
        return '6';
    case 7:
        return '7';
    case 8:
        return '8';
    case 9:
        return '9';
    case 10:
        return 'A';
    case 11:
        return 'B';
    case 12:
        return 'C';
    case 13:
        return 'D';
    case 14:
        return 'E';
    case 15:
        return 'F';
    case 16:
        return 'G';
    case 17:
        return 'H';
    case 18:
        return 'I';
    case 19:
        return 'J';
    case 20:
        return 'K';
    case 21:
        return 'L';
    case 22:
        return 'M';
    case 23:
        return 'N';
    case 24:
        return 'O';
    case 25:
        return 'P';
    case 26:
        return 'Q';
    case 27:
        return 'R';
    case 28:
        return 'S';
    case 29:
        return 'T';
    case 30:
        return 'U';
    case 31:
        return 'V';
    case 32:
        return 'W';
    case 33:
        return 'X';
    case 34:
        return 'Y';
    case 35:
        return 'Z';
    case 36:
        return '@';
    case 37:
        return '#';
    case 38:
        return '$';
    case 39:
        return '%';
    case 40:
        return '^';
    case 41:
        return '&';
    case 42:
        return '*';
    default:
        return '0';
    }
}


char periodSwitchboard(int dayOfWeek, int hour, int minute){
    //1Monday   2Tues   3Wed    4Thurs  5Fri
    std::cout<<"\t~"<<dayOfWeek<<"\t"<<hour<<"\t"<<minute<<std::endl;

    //Straight seven
    if(dayOfWeek == 1 || dayOfWeek == 2 || dayOfWeek == 5){
        return straightSeven(hour, minute);
    }
    //Even day
    if(dayOfWeek == 3){
        return evenDay(hour, minute);
    }
    if(dayOfWeek == 4){
        return oddDay(hour, minute);
    }

    //First period -- default
    return '1';
}



char straightSeven(int hour, int minute){
    if(hour == 7){
        std::cout<<"Hour = 7";
        return '1';
    }
    if(hour == 8){
        if(minute <= 54){
            return '2';
        }
        else{
            return '3';
        }
    }
    if(hour == 9){
        return '3';
    }
    if(hour == 10){
        if(minute <= 54){
            return '4';
        }
        else{
            return '5';
        }
    }
    if(hour == 11){
        if(minute <= 49){
            return '5';
        }
        else{
            return '5';//lunch
        }
    }
    if(hour == 12){
        if(minute >= 26){
            return '6';
        }
    }
    if(hour == 13){
        if(minute <= 14){
            return '6';
        }
        else{
            return '7';
        }
    }

    //7 is default
    return '7';
}

char evenDay(int hour, int minute){
    if(hour == 7){
        return '2';
    }
    if(hour == 8){
        if(minute <= 40){
            return '2';
        }
        else{
            return '4';
        }
    }
    if(hour == 9){
        return '4';
    }
    if(hour == 10){
        return '4';//4 and advisement and lunch
    }
    if(hour == 11){
        if(minute >= 41){
            return '6';
        }
        else{
            return '4';
        }
    }

    //6 is default
    return '6';
}

char oddDay(int hour, int minute){
    std::cout<<"odd day\t~"<<hour<<"\t"<<minute<<std::endl;
    if(hour == 7){
        return '1';
    }
    if(hour == 8){
        if(minute <= 40){
            return '1';
        }
        else{
            return '3';
        }
    }
    if(hour == 9){
        return '3';
    }
    if(hour == 10){
        if(minute <= 25){
            return '3';
        }
        else{
            return '5';
        }
    }
    if(hour == 11){
        return '5';
    }
    if(hour == 12){
        if(minute < 39){
            return '5';
        }
        else{
            return '7';
        }
    }

    //7 is default
    return '7';
}

/*char* strToCharStar(std::string str){
    char* newStr = (char*)malloc(str.length() + 1);
    int i=0;
    for(char c : str){
        newStr[i++] = c;
    }
    newStr[i] = '\0';

    return newStr;
}
*/
#endif
