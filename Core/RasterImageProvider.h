#ifndef RASTERIMAGEPROVIDER_H
#define RASTERIMAGEPROVIDER_H

//#include <QQuickItem>
#include <QQuickImageProvider>

class RasterImageProvider: public QQuickImageProvider
{
public:
    RasterImageProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
private:
    static QPixmap emptyPixmap();
};

#endif // RASTERIMAGEPROVIDER_H
