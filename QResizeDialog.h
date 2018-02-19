#ifndef QRESIZEDIALOG_H
#define QRESIZEDIALOG_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QComboBox;
class QLineEdit;
QT_END_NAMESPACE

namespace Ui {
class QResizeDialog;
}

class QResizeDialog : public QWidget
{
    Q_OBJECT

public:
    explicit QResizeDialog(QWidget *parent = 0);
    ~QResizeDialog();

private slots:
    void onComboActivated(int);
    void onOpenImageFile();
    void onSelectResourcePath();

private:
    void loadComboBox(bool = false);
    bool loadFile(const QString &);
    void SaveScaledImages(const int, const int);
    int  ValidateResPath(QString) const;

    Ui::QResizeDialog*   ui;
    QLabel* m_imageLabel;
    QString m_fileName;
    QString m_resPath;
};

#endif // QRESIZEDIALOG_H
