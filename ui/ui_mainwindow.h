/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *s_mainWindowGridLayout;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QTreeView *hierarchyView;
    QGroupBox *s_drawGB;
    QGridLayout *gridLayout_2;
    QCheckBox *m_wireframe;
    QPushButton *select;
    QPushButton *deselect;
    QLabel *label;
    QTableWidget *tableWidget;
    QLineEdit *loadGeoInput;
    QListView *fileExplorer;
    QPushButton *loadGeo;
    QLabel *label_2;
    QLineEdit *m_selectLine;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        s_mainWindowGridLayout = new QGridLayout(centralwidget);
        s_mainWindowGridLayout->setObjectName(QStringLiteral("s_mainWindowGridLayout"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        s_mainWindowGridLayout->addItem(horizontalSpacer_6, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        s_mainWindowGridLayout->addItem(horizontalSpacer_5, 0, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        s_mainWindowGridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        s_mainWindowGridLayout->addItem(horizontalSpacer, 0, 4, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(20);
        sizePolicy.setVerticalStretch(20);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(20, 20));
        groupBox->setMaximumSize(QSize(200, 900));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        hierarchyView = new QTreeView(groupBox);
        hierarchyView->setObjectName(QStringLiteral("hierarchyView"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(hierarchyView->sizePolicy().hasHeightForWidth());
        hierarchyView->setSizePolicy(sizePolicy1);
        hierarchyView->setMaximumSize(QSize(300, 900));

        gridLayout_4->addWidget(hierarchyView, 0, 0, 1, 1);


        s_mainWindowGridLayout->addWidget(groupBox, 2, 0, 1, 1);

        s_drawGB = new QGroupBox(centralwidget);
        s_drawGB->setObjectName(QStringLiteral("s_drawGB"));
        gridLayout_2 = new QGridLayout(s_drawGB);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        m_wireframe = new QCheckBox(s_drawGB);
        m_wireframe->setObjectName(QStringLiteral("m_wireframe"));
        m_wireframe->setEnabled(true);
        m_wireframe->setTristate(false);

        gridLayout_2->addWidget(m_wireframe, 5, 1, 1, 1);

        select = new QPushButton(s_drawGB);
        select->setObjectName(QStringLiteral("select"));

        gridLayout_2->addWidget(select, 2, 1, 1, 1);

        deselect = new QPushButton(s_drawGB);
        deselect->setObjectName(QStringLiteral("deselect"));

        gridLayout_2->addWidget(deselect, 3, 1, 1, 1);

        label = new QLabel(s_drawGB);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 10, 1, 1, 1);

        tableWidget = new QTableWidget(s_drawGB);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem14);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy2);
        tableWidget->setMinimumSize(QSize(200, 120));
        tableWidget->setMaximumSize(QSize(220, 200));
        tableWidget->setAutoFillBackground(false);
        tableWidget->setInputMethodHints(Qt::ImhDigitsOnly);
        tableWidget->setDragEnabled(true);
        tableWidget->horizontalHeader()->setDefaultSectionSize(67);

        gridLayout_2->addWidget(tableWidget, 11, 1, 1, 1);

        loadGeoInput = new QLineEdit(s_drawGB);
        loadGeoInput->setObjectName(QStringLiteral("loadGeoInput"));

        gridLayout_2->addWidget(loadGeoInput, 13, 1, 1, 1);

        fileExplorer = new QListView(s_drawGB);
        fileExplorer->setObjectName(QStringLiteral("fileExplorer"));

        gridLayout_2->addWidget(fileExplorer, 15, 1, 1, 1);

        loadGeo = new QPushButton(s_drawGB);
        loadGeo->setObjectName(QStringLiteral("loadGeo"));

        gridLayout_2->addWidget(loadGeo, 14, 1, 1, 1);

        label_2 = new QLabel(s_drawGB);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 12, 1, 1, 1);

        m_selectLine = new QLineEdit(s_drawGB);
        m_selectLine->setObjectName(QStringLiteral("m_selectLine"));

        gridLayout_2->addWidget(m_selectLine, 1, 1, 1, 1);


        s_mainWindowGridLayout->addWidget(s_drawGB, 2, 5, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Template", Q_NULLPTR));
        groupBox->setTitle(QString());
        s_drawGB->setTitle(QString());
        m_wireframe->setText(QApplication::translate("MainWindow", "Wireframe", Q_NULLPTR));
        select->setText(QApplication::translate("MainWindow", "Select", Q_NULLPTR));
        deselect->setText(QApplication::translate("MainWindow", "Deselect", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Add transformations:", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "T", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "R", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "S", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(0, 0);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "0.0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(0, 1);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "0.0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(0, 2);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "0.0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(1, 0);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "0.0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(1, 1);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "0.0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(1, 2);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "0.0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(2, 0);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "1.0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(2, 1);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "1.0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(2, 2);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "1.0", Q_NULLPTR));
        tableWidget->setSortingEnabled(__sortingEnabled);

        loadGeo->setText(QApplication::translate("MainWindow", "Load", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Load file:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
