#include <iostream>
#include "CompactDisc.h"

CompactDisc::CompactDisc(const char* tit, int cap) : capacity(cap) {

    for (int i = 0; ; i++) {

        this->title[i] = tit[i];

        if (tit[i] == '\0')
            break;

    }

    std::cout << "CompactDisc() called" << std::endl;

}

CompactDisc::~CompactDisc() {

    std::cout << "~CompactDisc() called" << std::endl;

}

int CompactDisc::getCapacity() {

    return this->capacity;

}

char* CompactDisc::getTitle() {

    return this->title;

}

void CompactDisc::setCapacity(int cap) {

    this->capacity = cap;

}

void CompactDisc::setTitle(const char* tit) {

    for (int i = 0; ; i++) {

        this->title[i] = tit[i];

        if (tit[i] == '\0')
            break;

    }

}