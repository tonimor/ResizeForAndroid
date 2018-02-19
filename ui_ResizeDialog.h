/********************************************************************************
** Form generated from reading UI file 'ResizeDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESIZEDIALOG_H
#define UI_RESIZEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QResizeDialog
{
public:
    QLabel *img_label;
    QPushButton *load_image_button;
    QPushButton *path_button;
    QComboBox *paht_combo;

    void setupUi(QWidget *QResizeDialog)
    {
        if (QResizeDialog->objectName().isEmpty())
            QResizeDialog->setObjectName(QStringLiteral("QResizeDialog"));
        QResizeDialog->resize(339, 260);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QResizeDialog->sizePolicy().hasHeightForWidth());
        QResizeDialog->setSizePolicy(sizePolicy);
        QResizeDialog->setAutoFillBackground(false);
        img_label = new QLabel(QResizeDialog);
        img_label->setObjectName(QStringLiteral("img_label"));
        img_label->setGeometry(QRect(110, 10, 120, 120));
        img_label->setLayoutDirection(Qt::LeftToRight);
        img_label->setAutoFillBackground(false);
        img_label->setFrameShape(QFrame::NoFrame);
        img_label->setPixmap(QPixmap(QString::fromUtf8(":/Images/default.png")));
        img_label->setScaledContents(true);
        img_label->setAlignment(Qt::AlignCenter);
        load_image_button = new QPushButton(QResizeDialog);
        load_image_button->setObjectName(QStringLiteral("load_image_button"));
        load_image_button->setGeometry(QRect(100, 150, 141, 41));
        path_button = new QPushButton(QResizeDialog);
        path_button->setObjectName(QStringLiteral("path_button"));
        path_button->setGeometry(QRect(10, 230, 51, 23));
        path_button->setFlat(false);
        paht_combo = new QComboBox(QResizeDialog);
        paht_combo->setObjectName(QStringLiteral("paht_combo"));
        paht_combo->setGeometry(QRect(70, 230, 259, 22));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(paht_combo->sizePolicy().hasHeightForWidth());
        paht_combo->setSizePolicy(sizePolicy1);
        paht_combo->setMaximumSize(QSize(16777215, 16777215));
        paht_combo->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        paht_combo->setMinimumContentsLength(0);
        paht_combo->setFrame(true);

        retranslateUi(QResizeDialog);

        QMetaObject::connectSlotsByName(QResizeDialog);
    } // setupUi

    void retranslateUi(QWidget *QResizeDialog)
    {
        QResizeDialog->setWindowTitle(QApplication::translate("QResizeDialog", "ResizeDialog", 0));
        img_label->setText(QString());
        load_image_button->setText(QApplication::translate("QResizeDialog", "Select Image...", 0));
        path_button->setText(QApplication::translate("QResizeDialog", "Path", 0));
    } // retranslateUi

};

namespace Ui {
    class QResizeDialog: public Ui_QResizeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESIZEDIALOG_H
