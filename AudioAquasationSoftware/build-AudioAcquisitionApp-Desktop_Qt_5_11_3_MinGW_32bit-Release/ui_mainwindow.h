/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *statusLabel;
    QFrame *frame;
    QComboBox *serialPortComboBox;
    QPushButton *recordButton;
    QPushButton *stopButton;
    QPushButton *saveButton;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QGraphicsView *waveformGraphicsView;
    QLabel *QStatusBar1;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1143, 387);
        MainWindow->setStyleSheet(QLatin1String("background-color: rgb(145, 145, 145);\n"
"background-color: rgb(255, 255, 255);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        statusLabel = new QLabel(centralWidget);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setGeometry(QRect(0, 320, 271, 16));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(-10, 0, 1161, 51));
        frame->setStyleSheet(QStringLiteral("background-color: rgb(179, 230, 255);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        serialPortComboBox = new QComboBox(frame);
        serialPortComboBox->setObjectName(QStringLiteral("serialPortComboBox"));
        serialPortComboBox->setGeometry(QRect(20, 10, 91, 22));
        serialPortComboBox->setStyleSheet(QLatin1String("background-color: rgb(0, 153, 230);\n"
"color: rgb(255, 255, 255);"));
        recordButton = new QPushButton(frame);
        recordButton->setObjectName(QStringLiteral("recordButton"));
        recordButton->setGeometry(QRect(120, 10, 81, 23));
        recordButton->setStyleSheet(QLatin1String("background-color: rgb(0, 153, 230);\n"
"color: rgb(255, 255, 255);\n"
""));
        stopButton = new QPushButton(frame);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setGeometry(QRect(210, 10, 91, 23));
        stopButton->setStyleSheet(QLatin1String("background-color: rgb(0, 153, 230);\n"
"color: rgb(255, 255, 255);"));
        saveButton = new QPushButton(frame);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(310, 10, 91, 23));
        saveButton->setStyleSheet(QLatin1String("background-color: rgb(0, 153, 230);\n"
"color: rgb(255, 255, 255);"));
        zoomInButton = new QPushButton(frame);
        zoomInButton->setObjectName(QStringLiteral("zoomInButton"));
        zoomInButton->setGeometry(QRect(410, 10, 91, 23));
        zoomInButton->setStyleSheet(QLatin1String("background-color: rgb(0, 153, 230);\n"
"color: rgb(255, 255, 255);"));
        zoomOutButton = new QPushButton(frame);
        zoomOutButton->setObjectName(QStringLiteral("zoomOutButton"));
        zoomOutButton->setGeometry(QRect(520, 10, 91, 23));
        zoomOutButton->setStyleSheet(QLatin1String("background-color: rgb(0, 153, 230);\n"
"color: rgb(255, 255, 255);"));
        waveformGraphicsView = new QGraphicsView(centralWidget);
        waveformGraphicsView->setObjectName(QStringLiteral("waveformGraphicsView"));
        waveformGraphicsView->setGeometry(QRect(0, 51, 1151, 261));
        QStatusBar1 = new QLabel(centralWidget);
        QStatusBar1->setObjectName(QStringLiteral("QStatusBar1"));
        QStatusBar1->setGeometry(QRect(1090, 320, 47, 13));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1143, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        statusLabel->setText(QString());
        recordButton->setText(QApplication::translate("MainWindow", "Record", nullptr));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        saveButton->setText(QApplication::translate("MainWindow", "Save ", nullptr));
        zoomInButton->setText(QApplication::translate("MainWindow", "Zoom In", nullptr));
        zoomOutButton->setText(QApplication::translate("MainWindow", "Zoom Out", nullptr));
        QStatusBar1->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
