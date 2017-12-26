#ifndef FilterProcessor_H
#define FilterProcessor_H

#include <QObject>
#include <QtCore>
#include <QHash>
#include <QMultiHash>
#include <QVariant>
#include <QImage>
#include <QMutex>

#include "AbstractFilter.h"

struct Connection
{
    int targetFilter;
    int targetSlot;
    int currentSlot;

    Connection(int _targetFilter, int _targetSlot,int _currentSlot):
        targetFilter(_targetFilter), targetSlot(_targetSlot), currentSlot(_currentSlot) {}
};

class FilterProcessor : public QObject {
    Q_OBJECT
public:
    FilterProcessor(QObject *parent=Q_NULLPTR);

    void addFilter(int num, QString type);
    void removeFilter(int num);
    void connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn);
    void setParameterValueForFilter(int filterNumber, QString paramName, QVariant value);

    QVariant availableFilters();
    QVariant filterParamsInfo(int filterNumber);
    QVariant availableRasterModes();

    void updateAllFilters();
    QImage images(int filterNumber);
signals:
    void imageRastered(int number);
private:
    void removeAllConnections(int filterNumber);
    void removeConnectionsForFilterInSlot(int filterNumber, int slot);
    void updateAllConnectionsForFilters();

    QMutex m_imageMutex;
    QMultiHash<int, Connection> m_outConnections, m_inConnections;
    QHash<int, AbstractFilter * > m_filters;
    QHash<int, QImage> m_images;
};

#endif // FilterProcessor_H
