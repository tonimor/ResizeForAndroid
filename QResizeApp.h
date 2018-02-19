#ifndef QRESIZEAPP_H
#define QRESIZEAPP_H

#include <QObject>
#include <QApplication>
#include <QStack>

class QResizeApp : public QApplication
{
public:

    static const QString m_appName;
    static const QString m_orgName;
    static const QString m_domName;

    QResizeApp(int argc, char **argv);
    ~QResizeApp();

    void    setResourcePath(QString);

    QStack<QString>& getStack(){ return m_stack; }

private:

    QStack<QString> m_stack;

    void loadRegistryData();
    void saveRegistryData();
};

#endif // QRESIZEAPP_H
