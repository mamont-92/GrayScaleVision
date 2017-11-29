#include "RasterImageProvider.h"
#include <QPixmap>
#include <QPainter>
#include <QFontMetrics>

RasterImageProvider::RasterImageProvider() : QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

QPixmap RasterImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = 100;
    int height = 50;

    if (size)
        *size = QSize(width, height);
    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);
    pixmap.fill("yellow");

    QPainter painter(&pixmap);
    painter.setFont(QFont("Arial", 8, QFont::Bold));

    QFontMetrics fm(painter.font());
    QRect fontRect = fm.boundingRect(id);

    fontRect.moveCenter(pixmap.rect().center());
    painter.drawText(fontRect, Qt::AlignCenter, id);

    return pixmap;
}
