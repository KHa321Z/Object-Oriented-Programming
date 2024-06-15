#include <iostream>
#include "CDDrive.h"

CDDrive::CDDrive(const char* manu, int sp) : speed(sp), aCompactDisc(0) {

    for (int i = 0; ; i++) {

        this->manufacturer[i] = manu[i];

        if (manu[i] == '\0')
            break;

    }

    std::cout << "CDDrive() called" << std::endl;

}

CDDrive::~CDDrive() {

    std::cout << "~CDDrive() called" << std::endl;

}

void CDDrive::Play() {

    if (this->aCompactDisc) {

        std::cout << "Title: " << this->aCompactDisc->getTitle();
        std::cout << std::endl;
        std::cout << "Capacity: " << this->aCompactDisc->getCapacity();
        std::cout << std::endl;
    
    } else 
        std::cout << "Please insert a Disc." << std::endl;

}

void CDDrive::InsertCD(CompactDisc* aDisc) {

    this->aCompactDisc = aDisc;

}

CompactDisc* CDDrive::EjectCD() {

    CompactDisc* temp = this->aCompactDisc;
    this->aCompactDisc = 0;

    return temp;

}