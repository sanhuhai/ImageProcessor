#pragma once

#include <QtWidgets/QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>
#include <QFileDialog>
#include <QDebug>
#include <QTextDocument>
#include <QTextStream>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include "showWidget.h"
#include "ui_ImageProcessor.h"
#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif // WIN32


class ImageProcessor : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = Q_NULLPTR);
    void display();
    void createActions();
    void createMenus();
    void createToolBar();
    void loadFile(QString filename);
    void mergeFormat(QTextCharFormat textCharFormat);

protected slots:
    

private slots:
    void showNewFile();
    void showOpenFile();
    void showPrintText();
    void showPrintImage();
    void showZoomin();
    void showZoomout();
private:
    Ui::ImageProcessorClass ui;
    /*����˵���*/
    QMenu* fileMenu, * zoomMenu, * mirrorMenu, * rotateMenu;
    QImage img;
    QString fileName;
    ShowWidget* showWidget;
    /*�ļ��˵���*/
    QAction* openFileAction, * newFileAction, * printTextAction, * printImageAction, * exitAction;
    /*�༭�˵���*/
    QAction* copyAction, * cutAction, * zoomInAction, * zoomOutAction, * pasteAction, * aboutAction;
    /*��ת�˵���*/
    QAction* rotate90Action, * rotate180Action, * rotate270Action;
    /*����˵���*/
    QAction* mirrorVerticalAction, * mirrorHorizontalAction, * undoAction, * redoAction;
    /*������*/
    QToolBar* fileToolBar, * zoomToolBar, * rotateToolBar, * mirrorToolBar, * doToolBar;
};
