#include "RasterImageProvider.h"
#include <QPixmap>
#include <QPainter>
#include <QFontMetrics>
#include "GlobalContext.h"

RasterImageProvider::RasterImageProvider() : QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

QPixmap genEmptyPixmap()
{
    QPixmap pixmap(QSize(200,200));
    pixmap.fill("gray");

    QPainter painter(&pixmap);
    painter.setFont(QFont("Arial", 16, QFont::Bold));

    QString str ="Empty Image";

    QFontMetrics fm(painter.font());
    QRect fontRect = fm.boundingRect(str);

    fontRect.moveCenter(pixmap.rect().center());
    painter.drawText(fontRect, Qt::AlignCenter, str);

    return pixmap;
}

QPixmap RasterImageProvider::emptyPixmap(){
    static QPixmap _emptyPixmap = genEmptyPixmap();
    return _emptyPixmap;
}

QPixmap RasterImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QString number = id;
    int ind=number.indexOf("_");
    if(ind >=1)
        number.truncate(ind);
    QImage img = GlobalContext::instance().filterManager()->images(number.toInt());
    if(img.isNull()){
        return emptyPixmap();
    }
    else{
        return QPixmap::fromImage(img);
    }
}
