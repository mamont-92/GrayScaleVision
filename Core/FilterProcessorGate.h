#ifndef FilterProcessorGATE_H
#define FilterProcessorGATE_H


#include <QObject>
#include <QString>
#include <QVariant>
class FilterProcessor;

class FilterProcessorGate : public QObject
{
    Q_OBJECT

public:
    explicit FilterProcessorGate(QObject *parent = nullptr);

    Q_INVOKABLE void addFilter(int num, QString type);
    Q_INVOKABLE void removeFilter(int num);
    Q_INVOKABLE void connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn);
    Q_INVOKABLE void setParameterValueForFilter(int filterNumber, QString paramName, QVariant value);

    Q_INVOKABLE QVariant availableFilters();
    Q_INVOKABLE QVariant filterParamsInfo(int filterNumber);

signals:
    void imageRastered(int number);
private:
    FilterProcessor * m_filterManager;
};

#endif // FilterProcessorGATE_H
