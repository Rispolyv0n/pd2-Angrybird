/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QLabel *label_score;
    QLabel *label_exit;
    QLabel *label_restart;
    QLabel *label_go;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(960, 540);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(960, 540));
        MainWindow->setMaximumSize(QSize(960, 540));
        MainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 961, 541));
        graphicsView->setStyleSheet(QStringLiteral("background-image: url(:/image/43X58PIC5u8_1024.jpg);"));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        label_score = new QLabel(centralWidget);
        label_score->setObjectName(QStringLiteral("label_score"));
        label_score->setEnabled(false);
        label_score->setGeometry(QRect(680, 20, 261, 61));
        QFont font;
        font.setFamily(QStringLiteral("Imprint MT Shadow"));
        font.setPointSize(18);
        label_score->setFont(font);
        label_score->setStyleSheet(QStringLiteral("color: rgb(244, 244, 244);"));
        label_score->setAlignment(Qt::AlignCenter);
        label_score->setTextInteractionFlags(Qt::NoTextInteraction);
        label_exit = new QLabel(centralWidget);
        label_exit->setObjectName(QStringLiteral("label_exit"));
        label_exit->setEnabled(false);
        label_exit->setGeometry(QRect(80, 470, 60, 60));
        label_exit->setStyleSheet(QStringLiteral("image: url(:/image/exit.png);"));
        label_exit->setFrameShadow(QFrame::Plain);
        label_exit->setTextInteractionFlags(Qt::NoTextInteraction);
        label_restart = new QLabel(centralWidget);
        label_restart->setObjectName(QStringLiteral("label_restart"));
        label_restart->setGeometry(QRect(10, 470, 60, 60));
        label_restart->setStyleSheet(QStringLiteral("image: url(:/image/restart.png);"));
        label_restart->setTextInteractionFlags(Qt::NoTextInteraction);
        label_go = new QLabel(centralWidget);
        label_go->setObjectName(QStringLiteral("label_go"));
        label_go->setGeometry(QRect(40, 300, 58, 161));
        label_go->setStyleSheet(QStringLiteral("image: url(:/image/shooter.png);"));
        label_go->setTextInteractionFlags(Qt::NoTextInteraction);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_score->setText(QString());
        label_exit->setText(QString());
        label_restart->setText(QString());
        label_go->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
