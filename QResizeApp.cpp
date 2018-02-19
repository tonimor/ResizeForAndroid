#include <QSettings>
#include <QFileInfo>
#include "QResizeApp.h"

const QString QResizeApp::m_appName = "ResizeForAndroid";
const QString QResizeApp::m_orgName = "QAMS";
const QString QResizeApp::m_domName = "qams.net";

QResizeApp::QResizeApp(int argc, char **argv ) : QApplication(argc, argv)
{
    setOrganizationName(QResizeApp::m_orgName);
    setApplicationName(QResizeApp::m_appName);
    setOrganizationDomain(QResizeApp::m_domName);
    loadRegistryData();
}

QResizeApp::~QResizeApp()
{
    saveRegistryData();
}

void QResizeApp::setResourcePath(QString i_path)
{
    if(i_path.isEmpty())
        return;

    QFileInfo fInfo(i_path);
    if(fInfo.exists() == false)
        return;

    if(m_stack.contains(i_path))
        return;

    if(m_stack.count() == 10)
        m_stack.removeFirst();

    m_stack.push(i_path);
}

void QResizeApp::loadRegistryData()
{
    QSettings settings(QResizeApp::m_orgName, QResizeApp::m_appName);

    const int maxEntrys = 10;
    for(int iIndex = 0; iIndex < maxEntrys; iIndex++)
    {
        QString entry = QString("%1%2").arg("resPath", QString::number(iIndex));

        const int defaultValue = 123;
        QVariant qv = settings.value(entry, defaultValue);
        if(qv.toInt() == defaultValue)
            continue; // entryName not exists !!!!

        QString resPath = qv.toString();
        QFileInfo fInfo(resPath);
        if(fInfo.exists())
            m_stack.push(resPath);
    }
}

void QResizeApp::saveRegistryData()
{
    QSettings settings(QResizeApp::m_orgName, QResizeApp::m_appName);
    settings.clear();

    int iIndex = 0;
    QVectorIterator<QString> iter(m_stack);
    while(iter.hasNext())
    {
        QString entry = QString("%1%2").arg("resPath", QString::number(iIndex));
        QString value = iter.next();
        settings.setValue(entry, value);
        iIndex++;
    }
}
