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
    /*各项菜单栏*/
    QMenu* fileMenu, * zoomMenu, * mirrorMenu, * rotateMenu;
    QImage img;
    QString fileName;
    ShowWidget* showWidget;
    /*文件菜单项*/
    QAction* openFileAction, * newFileAction, * printTextAction, * printImageAction, * exitAction;
    /*编辑菜单栏*/
    QAction* copyAction, * cutAction, * zoomInAction, * zoomOutAction, * pasteAction, * aboutAction;
    /*旋转菜单栏*/
    QAction* rotate90Action, * rotate180Action, * rotate270Action;
    /*镜像菜单项*/
    QAction* mirrorVerticalAction, * mirrorHorizontalAction, * undoAction, * redoAction;
    /*工具栏*/
    QToolBar* fileToolBar, * zoomToolBar, * rotateToolBar, * mirrorToolBar, * doToolBar;
};
