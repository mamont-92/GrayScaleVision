#include "Inversion.h"
#include <QDebug>

Inversion::Inversion() : AbstractFilter()
{
    qDebug() << "Constructor Inversion";
    registerInSlot("scr", 0);
    registerOutSlot("res", 0);
}

void Inversion::update()
{
    qDebug() << "Inversion::update";
}
