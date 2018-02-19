
#include <QApplication>
#include "QWaitcursor.h"

QWaitCursor::QWaitCursor(QObject *parent) : QObject(parent)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QCoreApplication::processEvents();
}

QWaitCursor::~QWaitCursor()
{
    QApplication::restoreOverrideCursor();
}

void QWaitCursor::restore()
{
    QApplication::restoreOverrideCursor();
}
