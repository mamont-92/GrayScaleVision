#ifndef FILTERMANAGERBACKENDGATE_H
#define FILTERMANAGERBACKENDGATE_H


#include <QObject>
#include <QString>
#include <QVariant>
class FilterManagerBackend;

class FilterManagerBackendGate : public QObject
{
    Q_OBJECT

public:
    explicit FilterManagerBackendGate(QObject *parent = nullptr);

    Q_INVOKABLE void addFilter(int num, QString type);
    Q_INVOKABLE void removeFilter(int num);
    Q_INVOKABLE void connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn);
    Q_INVOKABLE void setParameterValueForFilter(int filterNumber, QString paramName, QVariant value);

    Q_INVOKABLE QVariant filterCreationTemplate();
    Q_INVOKABLE QVariant filterParamsInfo(int filterNumber);

signals:
    void imageRastered(int number);
private:
    FilterManagerBackend * m_filterManager;
};

#endif // FILTERMANAGERBACKENDGATE_H
