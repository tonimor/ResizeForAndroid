#ifndef QWAITCURSOR_H
#define QWAITCURSOR_H

#include <QObject>

class QWaitCursor : public QObject
{
    Q_OBJECT

public:
    explicit QWaitCursor(QObject *parent = 0);
    ~QWaitCursor();

    void restore();

signals:

public slots:
};

#endif // QWAITCURSOR_H
