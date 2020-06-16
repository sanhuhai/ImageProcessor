#include "ImageProcessor.h"

ImageProcessor::ImageProcessor(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	display();
}

void ImageProcessor::display() {
	setWindowTitle("Easy Word");
	showWidget = new ShowWidget(this);
	setCentralWidget(showWidget);//将之设置为中心部件
	/*创建动作、菜单、工具栏的函数*/
	createActions();
	createMenus();
	createToolBar();
	if (img.load("yhyl.jpg")) {
		/*在imageLabel对象中放置图像*/
		showWidget->getImageLabel()->setPixmap(QPixmap::fromImage(img));
	}
}

/*动作(Action)的实现*/
void ImageProcessor::createActions() {
	//"打开"动作
	openFileAction = new QAction(QIcon("img/open.jpg"), "打开", this);
	openFileAction->setShortcut(tr("Ctrl+O"));
	openFileAction->setStatusTip("打开一个文件");
	connect(openFileAction, SIGNAL(triggered()), this, SLOT(showOpenFile()));
	//"新建"动作
	newFileAction = new QAction(QIcon("img/new.jpg"), "新建", this);
	newFileAction->setShortcut(tr("Ctrl+N"));
	newFileAction->setStatusTip("新建一个文件");
	connect(newFileAction, SIGNAL(triggered()), this, SLOT(showNewFile()));
	//"退出"动作
	exitAction = new QAction(QIcon("img/exit.jpg"), "退出", this);
	exitAction->setShortcut(tr("Ctrl+Q"));
	exitAction->setStatusTip("退出程序");
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
	//"复制"动作
	copyAction = new QAction(QIcon("img/copy.jpg"), "复制", this);
	copyAction->setShortcut(tr("Ctrl+C"));
	copyAction->setStatusTip("复制文件");
	connect(copyAction, SIGNAL(triggered()), showWidget->getText(), SLOT(copy()));
	//"剪切"动作
	cutAction = new QAction(QIcon("img/cut.jpg"), "剪切", this);
	cutAction->setShortcut(tr("Ctrl+T"));
	cutAction->setStatusTip("剪切文件");
	connect(cutAction, SIGNAL(triggered()), showWidget->getText(), SLOT(cut()));
	//"粘贴"动作
	pasteAction = new QAction(QIcon("img/paste.jpg"), "粘贴", this);
	pasteAction->setShortcut(tr("Ctrl+V"));
	pasteAction->setStatusTip("粘贴文件");
	connect(pasteAction, SIGNAL(triggered()), showWidget->getText(), SLOT(paste()));
	//"关于"动作
	aboutAction = new QAction(QIcon("img/about.jpg"), "关于", this);
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(QApplication::aboutQt()));
	//"打印文本"动作
	printTextAction = new QAction(QIcon("img/printText.jpg"), "打印文本", this);
	printTextAction->setStatusTip("打开一个文本");
	connect(printTextAction, SIGNAL(triggered()), this, SLOT(showPrintText()));
	//"打印图像"动作
	printImageAction = new QAction(QIcon("img/printImage.jpg"), "打印图片", this);
	printImageAction->setStatusTip("打开一张图片");
	connect(printImageAction, SIGNAL(triggered()), this, SLOT(showPrintImage()));
	//"放大"动作
	zoomInAction = new QAction(QIcon("img/zoomin.jpg"), "放大", this);
	zoomInAction->setStatusTip("放大图片");
	connect(zoomInAction, SIGNAL(triggered()), this, SLOT(showZoomin()));
	//"缩小"动作
	zoomOutAction = new QAction(QIcon("img/zoomout.jpg"), "缩小", this);
	zoomOutAction->setStatusTip("缩小图片");
	connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(showZoomout()));
	//实现旋转
	//旋转90度
	rotate90Action = new QAction(QIcon("img/rotate90.jpg"), "旋转90度", this);
	rotate90Action->setStatusTip("将图片旋转90度");
	//旋转180度
	rotate180Action = new QAction(QIcon("img/rotate180.jpg"), "旋转180度", this);
	rotate180Action->setStatusTip("将图片旋转180度");
	//旋转270度
	rotate270Action = new QAction(QIcon("img/rotate270.jpg"), "旋转270度", this);
	rotate270Action->setStatusTip("将图片旋转270度");
	//实现图像的镜像
	//纵向镜像
	mirrorVerticalAction = new QAction(QIcon("img/mirrorVertical.jpg"), "纵向镜像", this);
	mirrorVerticalAction->setStatusTip("纵向镜像");
	//横向镜像
	mirrorHorizontalAction = new QAction(QIcon("img/mirrorHorizontal.jpg"), "横向镜像", this);
	mirrorHorizontalAction->setStatusTip("横向镜像");
	//实现撤销和恢复动作
	//撤销和恢复
	undoAction = new QAction(QIcon("img/undo.jpg"), "撤销", this);
	connect(undoAction, SIGNAL(triggered()), showWidget->getText(), SLOT(undo()));
	redoAction = new QAction(QIcon("img/redo.jpg"), "重做", this);
	connect(redoAction, SIGNAL(triggered()), showWidget->getText(), SLOT(redo()));
}

void ImageProcessor::createMenus() {
	//文件菜单
	fileMenu = menuBar()->addMenu("文件");
	fileMenu->addAction(openFileAction);
	fileMenu->addAction(newFileAction);
	fileMenu->addAction(printTextAction);
	fileMenu->addAction(printImageAction);
	fileMenu->addSeparator();//分隔符
	fileMenu->addAction(exitAction);
	//缩放菜单
	zoomMenu = menuBar()->addMenu("编辑");
	zoomMenu->addAction(copyAction);
	zoomMenu->addAction(cutAction);
	zoomMenu->addAction(pasteAction);
	zoomMenu->addAction(aboutAction);
	zoomMenu->addSeparator();
	zoomMenu->addAction(zoomInAction);
	zoomMenu->addAction(zoomOutAction);
	//旋转菜单
	rotateMenu = menuBar()->addMenu("旋转");
	rotateMenu->addAction(rotate90Action);
	rotateMenu->addAction(rotate180Action);
	rotateMenu->addAction(rotate270Action);
	//镜像菜单
	mirrorMenu = menuBar()->addMenu("镜像");
	mirrorMenu->addAction(mirrorHorizontalAction);
	mirrorMenu->addAction(mirrorVerticalAction);
}

void ImageProcessor::createToolBar() {
	//文件工具条
	fileToolBar = addToolBar("文件");
	fileToolBar->addAction(openFileAction);
	fileToolBar->addAction(newFileAction);
	fileToolBar->addAction(printTextAction);
	fileToolBar->addAction(printImageAction);
	//编辑工具条
	zoomToolBar = addToolBar("编辑");
	zoomToolBar->addAction(copyAction);
	zoomToolBar->addAction(cutAction);
	zoomToolBar->addAction(pasteAction);
	zoomToolBar->addAction(aboutAction);
	zoomToolBar->addSeparator();
	zoomToolBar->addAction(zoomInAction);
	zoomToolBar->addAction(zoomOutAction);
	//旋转工具条
	rotateToolBar = addToolBar("旋转");
	rotateToolBar->addAction(rotate90Action);
	rotateToolBar->addAction(rotate180Action);
	rotateToolBar->addAction(rotate270Action);
	//撤销和重做工具条
	doToolBar = addToolBar("撤销|重做");
	doToolBar->addAction(undoAction);
	doToolBar->addAction(redoAction);
}

void ImageProcessor::loadFile(QString filename) {
	qDebug() << filename.data();
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream textStream(&file);
		while (!textStream.atEnd()) {
			showWidget->getText()->append(textStream.readLine());
			qDebug() << "读一行";
		}
		qDebug() << endl;
	}
}

void ImageProcessor::mergeFormat(QTextCharFormat textCharFormat) {

}

void ImageProcessor::showNewFile() {
	ImageProcessor* newImageProcessor = new ImageProcessor;
	newImageProcessor->show();
}

void ImageProcessor::showOpenFile() {
	fileName = QFileDialog::getOpenFileName(this);
	if (!fileName.isEmpty()) {
		if (showWidget->getText()->document()->isEmpty()) {
			loadFile(fileName);
		}
		else {
			ImageProcessor* newImageProcessor = new ImageProcessor;
			newImageProcessor->show();
			newImageProcessor->loadFile(fileName);
		}
	}
}

void ImageProcessor::showPrintText() {
	QPrinter printer;
	QPrintDialog printDialog(&printer, this);                   //创建一个QPrintDialog对象，参数为QPrinter对象
	if (printDialog.exec()) {                                   //判断用户是否单击“打印”按钮
		QTextDocument* doc = showWidget->getText()->document(); //获取QTextEdit对象的文档
		doc->print(&printer);                                   //打印
	}
}

void ImageProcessor::showPrintImage() {
	QPrinter printer;
	QPrintDialog printDialog(&printer, this);
	if (printDialog.exec()) {
		QPainter painter(&printer);
		QRect rect = painter.viewport();
		QSize size = img.size();
		size.scale(rect.size(), Qt::KeepAspectRatio);
		painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
		painter.setWindow(img.rect());
		painter.drawImage(0, 0, img);
	}
}

void ImageProcessor::showZoomin() {
	if (img.isNull()) return;
	QMatrix matrix;
	matrix.scale(2, 2);
	img = img.transformed(matrix);
	showWidget->getImageLabel()->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::showZoomout() {
	if (img.isNull()) return;
	QMatrix matrix;
	matrix.scale(0.5, 0.5);
	img = img.transformed(matrix);
	showWidget->getImageLabel()->setPixmap(QPixmap::fromImage(img));
}