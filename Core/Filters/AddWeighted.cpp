#include "AddWeighted.h"
#include <QDebug>

AddWeighted::AddWeighted() : AbstractFilter()
{
    qDebug() << "Constructor Add Weighted";
    registerInSlot("scr1", 0);
    registerInSlot("scr2", 1);
    registerOutSlot("res", 0);
}


void AddWeighted::update()
{
    qDebug() << "Add Weighted::update";
}
