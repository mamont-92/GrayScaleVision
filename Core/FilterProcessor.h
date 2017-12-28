#ifndef FilterProcessor_H
#define FilterProcessor_H

#include <QObject>
#include <QtCore>
#include <QHash>
#include <QMultiHash>
#include <QVariant>
#include <QImage>
#include <QMutex>
#include <QSet>
#include <QFutureWatcher>

#include "AbstractFilter.h"

struct Connection
{
    int targetFilter;
    int targetSlot;
    int currentSlot;

    Connection(int _targetFilter, int _targetSlot,int _currentSlot):
        targetFilter(_targetFilter), targetSlot(_targetSlot), currentSlot(_currentSlot) {}
};

struct FilterParams{
    int filterNumber;
    QVariant parameter;
    FilterParams(const int & _filterNumber= -1, const QVariant & _parameter = QVariant()):
        filterNumber(_filterNumber), parameter(_parameter) {}
};

namespace FilterProcessorComands{
    class ICommand;
    class CommandCallBackAcceptor;
}

class FilterProcessor : public QObject {
    Q_OBJECT
public:
    FilterProcessor(QObject *parent=Q_NULLPTR);
    ~FilterProcessor();

    void execute(FilterProcessorComands::ICommand * command);

    QVariant availableFilters();
    QVariant availableRasterModes();

    QImage images(int filterNumber);
signals:
    void imageRastered(int number);
    void paramsChanged(const FilterParams & params);
private:
    void addFilter(int num, QString type);
    void removeFilter(int num);
    void connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn);
    void setParameterValueForFilter(int filterNumber, QString paramName, QVariant value);
    void setRasterMode(QString mode);

    void updateNonActualFilters();
    void removeAllConnections(int filterNumber);
    void removeConnectionsForFilterInSlot(int filterNumber, int slot);
    void updateAllConnectionsForFilters();
    //void updateFromFilter(int number);
    void rasterAllImages();
    void setImageForFilter(int filterNumber, QImage img);
    void updateFilterSet(QSet<int> filterSet);

    QSet<int> allDependentNodes(int startNode);

    QMutex m_imageMutex;
    QMultiHash<int, Connection> m_outConnections, m_inConnections;
    QHash<int, AbstractFilter * > m_filters;
    QHash<int, QImage> m_images;
    QString m_rasterMode;
    QHash<QString, QVariant> m_nonAplliedParams;
    QFutureWatcher<void> m_updateWatcher;
    FilterProcessorComands::CommandCallBackAcceptor * m_commandAcceptor;
    QSet<int> m_needUpdatingFilters;
};

#endif // FilterProcessor_H
