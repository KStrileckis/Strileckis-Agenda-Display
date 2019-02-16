#ifndef datapackHead
#define datapackHead
#include "D:\D Documents\Educational Projects\Agenda Display\Strileckis Agenda Display\include\DataPack.h"
#include <stdlib.h>
#endif // datapackHead


DataPack::DataPack(char* agenda)
{
            std::cout<<("constructor");
    //ctor
    this->agenda = agenda;
    createFillWidthAndHeight();
}

DataPack::~DataPack()
{
    //dtor
}

//Precondition - this.agenda has a value
//Postcondition - this.horizontalSize is set
void DataPack::createFillWidthAndHeight()
{
    //Prevent invalid sessions from crashing program
    if(this->agenda[0] != '~'){
        std::cout<<"Session invalid";
        this->charPeriod = (char*)" ";
        this->period = 0;
        this->periodTitle = (char*)"Invalid Session";
        this->agenda = (char*)"";
        this->horizontalSize =  9*15;
        this->verticalHeight = 18*4;
        return;
    }
    //Handle valid sessions
    int width = 0;
    int i=0, j=0, lines=0;

    //Get period (second character)
    this->charPeriod = (char*)malloc(1);
    this->charPeriod[0] = this->agenda[1];
    this->period = (int)charPeriod[0];

    //Get Period title (third onwards character)
    this->periodTitle = (char*)malloc(15);
    int s = 0;
    for(int chRun=2; this->agenda[chRun] != '\n'; ++chRun){//Go through rest of line
        periodTitle[s++] = this->agenda[chRun];
    }
    periodTitle[s++] = '\0';

    //Remove the first line from agenda
    this->agenda++;
    this->agenda = (this->agenda+s+1);
    //std::cout<<this->agenda;

    //Count lines and characters per line
    while(this->agenda[i] != '\0'){
        j++;
        if(this->agenda[i] == '\n'){
            lines++;
            if(j > width){
                width = j;
            }
            j=0;
        }
        i++;
    }
    width++;
    lines++;

    //Add bullet point


    //Set sizes
    ++width *= 9;
    lines *= 18;
    this->horizontalSize = width;
    this->verticalHeight = lines;
    cout<<this->verticalHeight;
}






//Accessors
int DataPack::getHeight(){return this->verticalHeight;}
int DataPack::getWidth(){return this->horizontalSize;}
int DataPack::getPeriod(){return this->period;}
char* DataPack::getCharPeriod(){
    return this->charPeriod;
    }
char* DataPack::getPeriodTitle(){
    return this->periodTitle;
    }
char* DataPack::getAgenda(){return this->agenda;}

