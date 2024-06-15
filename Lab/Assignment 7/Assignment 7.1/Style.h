#pragma once

class Style {

    private:

        char color[10];
        bool isFilled;

    public:

        Style(const char* col = "white", bool fill = true);
        ~Style();

        void print();

        void setColor(const char*);
        void setFilled(bool);

};