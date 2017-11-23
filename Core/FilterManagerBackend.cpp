#include "FilterManagerBackend.h"
#include <QDebug>

FilterManagerBackend::FilterManagerBackend(QObject *parent) : QObject(parent), m_userName("macho")
{
    qDebug() << "constructor";
}

QString FilterManagerBackend::userName()
{
    return m_userName;
}

void FilterManagerBackend::setUserName(const QString &userName)
{
    if (userName == m_userName)
        return;

    m_userName = userName;
    emit userNameChanged();
}
