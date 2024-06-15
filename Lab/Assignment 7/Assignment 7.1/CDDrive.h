#pragma once
#include "CompactDisc.h"

class CDDrive {

    private:

        char manufacturer[20];
        int speed;
        CompactDisc* aCompactDisc;

    public:

        CDDrive(const char*, int);
        ~CDDrive();

        void Play();
        void InsertCD(CompactDisc*);
        CompactDisc* EjectCD();

};