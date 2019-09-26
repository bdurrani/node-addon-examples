#ifndef PRIMITIVE_H
#define PRIMITIVE_H

class Primitive{
    public:
        ~Primitive();
        Primitive(int data);
        void Doit();

    private:
        int m_data;

};

#endif