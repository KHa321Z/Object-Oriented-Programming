#pragma once

class CompactDisc {

    private:

        char title[20];
        int capacity;

    public:

        CompactDisc(const char* tit = "cd1", int cap = 0);
        ~CompactDisc();

        char* getTitle();
        int getCapacity();

        void setTitle(const char*);
        void setCapacity(int);

};