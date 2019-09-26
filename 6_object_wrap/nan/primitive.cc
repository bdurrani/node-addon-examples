#include <stdio.h>
#include "primitive.h" 

Primitive::Primitive(int data): m_data(data){}

Primitive::~Primitive(){
    printf("primitive destructor\n");
}

void Primitive::Doit(){
    printf("data %d\n", m_data);
}