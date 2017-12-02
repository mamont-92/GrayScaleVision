#include "RasterImageProvider.h"
#include <QPixmap>
#include <QPainter>
#include <QFontMetrics>
#include "GlobalContext.h"

RasterImageProvider::RasterImageProvider() : QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

QPixmap RasterImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{

    QString number = id;
    int ind=number.indexOf("_");
    if(ind >=1)
        number.truncate(ind);
    QImage img = GlobalContext::instance().filterManager()->images(number.toInt());
    if(img.isNull()){
        int width = 100;
        int height = 50;

        if (size)
            *size = QSize(width, height);
        QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                       requestedSize.height() > 0 ? requestedSize.height() : height);
        pixmap.fill("red");

        QPainter painter(&pixmap);
        painter.setFont(QFont("Arial", 8, QFont::Bold));

        QFontMetrics fm(painter.font());
        QRect fontRect = fm.boundingRect(number);

        fontRect.moveCenter(pixmap.rect().center());
        painter.drawText(fontRect, Qt::AlignCenter, number);
        return pixmap;
    }
    else{
        return QPixmap::fromImage(img);
    }
}
