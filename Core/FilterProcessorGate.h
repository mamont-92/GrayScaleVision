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
    //Q_INVOKABLE QVariant filterParamsInfo(int filterNumber);
    Q_INVOKABLE QVariant availableRasterModes();
    Q_INVOKABLE void setRasterMode(QString mode);


signals:
    void imageRastered(int number);
    void paramsChanged(QVariant params);
private:
    FilterProcessor * m_filterProcessor;
};

#endif // FilterProcessorGATE_H
