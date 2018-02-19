#include <QtWidgets>
#include <QFileInfo>
#include "QResizeDialog.h"
#include "QResizeApp.h"
#include "QWaitCursor.h"
#include "ui_ResizeDialog.h"

#define PIX_MDPI    48
#define PIX_HDPI    72
#define PIX_XHDPI   96
#define PIX_XXHDPI  144

#define NOT_FOUND_ERROR_MDPI    0b0001
#define NOT_FOUND_ERROR_HDPI    0b0010
#define NOT_FOUND_ERROR_XHDPI   0b0100
#define NOT_FOUND_ERROR_XXHDPI  0b1000

QResizeDialog::QResizeDialog(QWidget *parent) :
    QWidget(parent), ui(new Ui::QResizeDialog)
{
    ui->setupUi(this);

    setWindowTitle(tr("ResizeForAndroid"));
    setFixedSize(width(), height());

    m_imageLabel = ui->img_label;
    m_imageLabel->setBackgroundRole(QPalette::Base);
    m_imageLabel->setSizePolicy(
        QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_imageLabel->setScaledContents(true);

    QComboBox *myCombo = ui->paht_combo;
    connect(myCombo, SIGNAL(activated(int)), this, SLOT(onComboActivated(int)));
    loadComboBox(true);

    QPushButton *myButton = ui->load_image_button;
    connect(myButton, SIGNAL(clicked()), this, SLOT(onOpenImageFile()));

    myButton = ui->path_button;
    connect(myButton, SIGNAL(clicked()), this, SLOT(onSelectResourcePath()));
}

void QResizeDialog::loadComboBox(bool i_addEmpty)
{
    QComboBox *myCombo = ui->paht_combo;
    myCombo->clear();
    myCombo->setInsertPolicy(QComboBox::InsertAtTop);

    QResizeApp* app = static_cast<QResizeApp *>(QApplication::instance());
    QStack<QString>& stack = app->getStack();
    QVectorIterator<QString> iter(stack);
    while(iter.hasNext())
    {
        QString resPath = iter.next();
        myCombo->insertItem(0, resPath);
        myCombo->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        myCombo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    }
    if(i_addEmpty)
        myCombo->insertItem(0, "");
    myCombo->setCurrentIndex(0);
}

QResizeDialog::~QResizeDialog()
{
    delete ui;
}

void QResizeDialog::onComboActivated(int i_index)
{
   QComboBox *myCombo = ui->paht_combo;
   m_resPath = myCombo->itemText(i_index);
}

void QResizeDialog::onSelectResourcePath()
{
    QString path = QFileDialog::getExistingDirectory(
        this, tr("Open Directory"), QDir::currentPath(),
         QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(path.isEmpty())
        return;

    const int validate = ValidateResPath(path);
    if(validate != 0)
    {
        QString message = "Incorrect Path:\n" + path;
        message += "\n\nDoes not exist resource folders\n";
        if((validate & NOT_FOUND_ERROR_MDPI) == NOT_FOUND_ERROR_MDPI)
            message += "drawable-mdpi\n";
        if((validate & NOT_FOUND_ERROR_HDPI) == NOT_FOUND_ERROR_HDPI)
            message += "drawable-hdpi\n";
        if((validate & NOT_FOUND_ERROR_XHDPI) == NOT_FOUND_ERROR_XHDPI)
            message += "drawable-xhdpi\n";
        if((validate & NOT_FOUND_ERROR_XXHDPI) == NOT_FOUND_ERROR_XXHDPI)
            message += "drawable-xxhdpi\n";

        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.exec();
        path = "";
    }

    m_resPath = path;

    if(m_resPath.isEmpty() == false)
    {
        QResizeApp* app = static_cast<QResizeApp *>(QApplication::instance());
        app->setResourcePath(m_resPath);
    }

    loadComboBox(m_resPath.isEmpty());
}

void QResizeDialog::onOpenImageFile()
{
    QWaitCursor waitcursor;

    if(m_resPath.isEmpty())
    {
        waitcursor.restore();
        QMessageBox msgBox;
        msgBox.setText("You must select resource path !");
        msgBox.exec();
        return;
    }

    QStringList mimeTypeFilters;
    foreach(const QByteArray &mimeTypeName, QImageReader::supportedMimeTypes())
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    const QStringList picturesLocations =
        QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);

    QFileDialog dialog(this, tr("Open File"),
        picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.first());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");

    int result = dialog.exec();
    activateWindow();
    if(result == QDialog::Accepted)
        loadFile(dialog.selectedFiles().first());

    // give me some breath !!!!
    QCoreApplication::processEvents();

    if(m_fileName.isEmpty())
        return;

    SaveScaledImages(PIX_MDPI, PIX_MDPI);
    SaveScaledImages(PIX_HDPI, PIX_HDPI);
    SaveScaledImages(PIX_XHDPI, PIX_XHDPI);
    SaveScaledImages(PIX_XXHDPI, PIX_XXHDPI);

    waitcursor.restore();

    QMessageBox msgBox;
    QString text = m_fileName + "\n\nDone !!!     ";
    msgBox.setText(text);
    msgBox.exec();
    m_fileName = "";
}

bool QResizeDialog::loadFile(const QString &fileName)
{
    QWaitCursor waitcursor;

    QImage image(fileName);

    m_fileName.clear();
    if (image.isNull())
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
            tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
        setWindowFilePath(QString());
        m_imageLabel->setPixmap(QPixmap());
        m_imageLabel->adjustSize();
        return false;
    }

    QPixmap pixmap = QPixmap::fromImage(image);

    // get label dimensions
    const int width  = m_imageLabel->width();
    const int height = m_imageLabel->height();
    m_imageLabel->setPixmap(
        pixmap.scaled(width, height, Qt::KeepAspectRatio));

    setWindowFilePath(fileName);
    m_fileName = fileName;
    return true;
}

void QResizeDialog::SaveScaledImages(const int i_width, const int i_height)
{
    if(m_fileName.isEmpty() == false)
    {
        QImage img(m_fileName);
        QPixmap pixmap = pixmap.fromImage(img.scaled(
            i_width, i_height,
            //Qt::IgnoreAspectRatio,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation));

        // Save File
        QFileInfo   fInfo(m_fileName);
        QString     fname = fInfo.fileName();
        QString     ftype = fInfo.completeSuffix();
        QString     fpath = m_resPath + "/";
        if(i_width == PIX_MDPI && i_height == PIX_MDPI /*drawable-mdpi*/)
            fpath += "drawable-mdpi/" + fname;
        else if(i_width == PIX_HDPI && i_height == PIX_HDPI /*drawable-hdpi*/)
            fpath += "drawable-hdpi/" + fname;
        else if(i_width == PIX_XHDPI && i_height == PIX_XHDPI /*drawable-xhdpi*/)
            fpath += "drawable-xhdpi/" + fname;
        else if(i_width == PIX_XXHDPI && i_height == PIX_XXHDPI /*drawable-xxhdpi*/)
            fpath += "drawable-xxhdpi/" + fname;
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Resolución Incorrecta !");
            msgBox.exec();
            return;
        }

        // ...Save Now !
        QFile file(fpath);
        file.open(QIODevice::WriteOnly);
        const char* ctype = ftype.toStdString().c_str();
        pixmap.save(&file, ctype, 100);
        file.close();
    }
}

int QResizeDialog::ValidateResPath(QString i_resPath) const
{
    QFileInfo   fInfo(i_resPath);
    if(fInfo.exists() == false)
        return -1;

    int result = 0;

    QString dir;
    dir = i_resPath + "/drawable-mdpi/";
    fInfo.setFile(dir);
    if(fInfo.exists() == false)
        result |= NOT_FOUND_ERROR_MDPI;

    dir = i_resPath + "/drawable-hdpi/";
    fInfo.setFile(dir);
    if(fInfo.exists() == false)
        result |= NOT_FOUND_ERROR_HDPI;

    dir = i_resPath + "/drawable-xhdpi/";
    fInfo.setFile(dir);
    if(fInfo.exists() == false)
        result |= NOT_FOUND_ERROR_XHDPI;

    dir = i_resPath + "/drawable-xxhdpi/";
    fInfo.setFile(dir);
    if(fInfo.exists() == false)
        result |= NOT_FOUND_ERROR_XXHDPI;

    return result;
}
