#ifndef DATAPACK_H
#define DATAPACK_H
#include <iostream>
using namespace std;

class DataPack
{
    public:
        DataPack(char* s);
        virtual ~DataPack();
        int getHeight();
        int getWidth();
        int getPeriod();
        char* getCharPeriod();
        char* getAgenda();
        char* getPeriodTitle();
    protected:
    private:
        char* agenda;
        int verticalHeight;
        int horizontalSize;
        int period;
        char* charPeriod;
        char* periodTitle;
        void createFillWidthAndHeight();
};

#endif // DATAPACK_H
