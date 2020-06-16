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
	setCentralWidget(showWidget);//��֮����Ϊ���Ĳ���
	/*�����������˵����������ĺ���*/
	createActions();
	createMenus();
	createToolBar();
	if (img.load("yhyl.jpg")) {
		/*��imageLabel�����з���ͼ��*/
		showWidget->getImageLabel()->setPixmap(QPixmap::fromImage(img));
	}
}

/*����(Action)��ʵ��*/
void ImageProcessor::createActions() {
	//"��"����
	openFileAction = new QAction(QIcon("img/open.jpg"), "��", this);
	openFileAction->setShortcut(tr("Ctrl+O"));
	openFileAction->setStatusTip("��һ���ļ�");
	connect(openFileAction, SIGNAL(triggered()), this, SLOT(showOpenFile()));
	//"�½�"����
	newFileAction = new QAction(QIcon("img/new.jpg"), "�½�", this);
	newFileAction->setShortcut(tr("Ctrl+N"));
	newFileAction->setStatusTip("�½�һ���ļ�");
	connect(newFileAction, SIGNAL(triggered()), this, SLOT(showNewFile()));
	//"�˳�"����
	exitAction = new QAction(QIcon("img/exit.jpg"), "�˳�", this);
	exitAction->setShortcut(tr("Ctrl+Q"));
	exitAction->setStatusTip("�˳�����");
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
	//"����"����
	copyAction = new QAction(QIcon("img/copy.jpg"), "����", this);
	copyAction->setShortcut(tr("Ctrl+C"));
	copyAction->setStatusTip("�����ļ�");
	connect(copyAction, SIGNAL(triggered()), showWidget->getText(), SLOT(copy()));
	//"����"����
	cutAction = new QAction(QIcon("img/cut.jpg"), "����", this);
	cutAction->setShortcut(tr("Ctrl+T"));
	cutAction->setStatusTip("�����ļ�");
	connect(cutAction, SIGNAL(triggered()), showWidget->getText(), SLOT(cut()));
	//"ճ��"����
	pasteAction = new QAction(QIcon("img/paste.jpg"), "ճ��", this);
	pasteAction->setShortcut(tr("Ctrl+V"));
	pasteAction->setStatusTip("ճ���ļ�");
	connect(pasteAction, SIGNAL(triggered()), showWidget->getText(), SLOT(paste()));
	//"����"����
	aboutAction = new QAction(QIcon("img/about.jpg"), "����", this);
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(QApplication::aboutQt()));
	//"��ӡ�ı�"����
	printTextAction = new QAction(QIcon("img/printText.jpg"), "��ӡ�ı�", this);
	printTextAction->setStatusTip("��һ���ı�");
	connect(printTextAction, SIGNAL(triggered()), this, SLOT(showPrintText()));
	//"��ӡͼ��"����
	printImageAction = new QAction(QIcon("img/printImage.jpg"), "��ӡͼƬ", this);
	printImageAction->setStatusTip("��һ��ͼƬ");
	connect(printImageAction, SIGNAL(triggered()), this, SLOT(showPrintImage()));
	//"�Ŵ�"����
	zoomInAction = new QAction(QIcon("img/zoomin.jpg"), "�Ŵ�", this);
	zoomInAction->setStatusTip("�Ŵ�ͼƬ");
	connect(zoomInAction, SIGNAL(triggered()), this, SLOT(showZoomin()));
	//"��С"����
	zoomOutAction = new QAction(QIcon("img/zoomout.jpg"), "��С", this);
	zoomOutAction->setStatusTip("��СͼƬ");
	connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(showZoomout()));
	//ʵ����ת
	//��ת90��
	rotate90Action = new QAction(QIcon("img/rotate90.jpg"), "��ת90��", this);
	rotate90Action->setStatusTip("��ͼƬ��ת90��");
	//��ת180��
	rotate180Action = new QAction(QIcon("img/rotate180.jpg"), "��ת180��", this);
	rotate180Action->setStatusTip("��ͼƬ��ת180��");
	//��ת270��
	rotate270Action = new QAction(QIcon("img/rotate270.jpg"), "��ת270��", this);
	rotate270Action->setStatusTip("��ͼƬ��ת270��");
	//ʵ��ͼ��ľ���
	//������
	mirrorVerticalAction = new QAction(QIcon("img/mirrorVertical.jpg"), "������", this);
	mirrorVerticalAction->setStatusTip("������");
	//������
	mirrorHorizontalAction = new QAction(QIcon("img/mirrorHorizontal.jpg"), "������", this);
	mirrorHorizontalAction->setStatusTip("������");
	//ʵ�ֳ����ͻָ�����
	//�����ͻָ�
	undoAction = new QAction(QIcon("img/undo.jpg"), "����", this);
	connect(undoAction, SIGNAL(triggered()), showWidget->getText(), SLOT(undo()));
	redoAction = new QAction(QIcon("img/redo.jpg"), "����", this);
	connect(redoAction, SIGNAL(triggered()), showWidget->getText(), SLOT(redo()));
}

void ImageProcessor::createMenus() {
	//�ļ��˵�
	fileMenu = menuBar()->addMenu("�ļ�");
	fileMenu->addAction(openFileAction);
	fileMenu->addAction(newFileAction);
	fileMenu->addAction(printTextAction);
	fileMenu->addAction(printImageAction);
	fileMenu->addSeparator();//�ָ���
	fileMenu->addAction(exitAction);
	//���Ų˵�
	zoomMenu = menuBar()->addMenu("�༭");
	zoomMenu->addAction(copyAction);
	zoomMenu->addAction(cutAction);
	zoomMenu->addAction(pasteAction);
	zoomMenu->addAction(aboutAction);
	zoomMenu->addSeparator();
	zoomMenu->addAction(zoomInAction);
	zoomMenu->addAction(zoomOutAction);
	//��ת�˵�
	rotateMenu = menuBar()->addMenu("��ת");
	rotateMenu->addAction(rotate90Action);
	rotateMenu->addAction(rotate180Action);
	rotateMenu->addAction(rotate270Action);
	//����˵�
	mirrorMenu = menuBar()->addMenu("����");
	mirrorMenu->addAction(mirrorHorizontalAction);
	mirrorMenu->addAction(mirrorVerticalAction);
}

void ImageProcessor::createToolBar() {
	//�ļ�������
	fileToolBar = addToolBar("�ļ�");
	fileToolBar->addAction(openFileAction);
	fileToolBar->addAction(newFileAction);
	fileToolBar->addAction(printTextAction);
	fileToolBar->addAction(printImageAction);
	//�༭������
	zoomToolBar = addToolBar("�༭");
	zoomToolBar->addAction(copyAction);
	zoomToolBar->addAction(cutAction);
	zoomToolBar->addAction(pasteAction);
	zoomToolBar->addAction(aboutAction);
	zoomToolBar->addSeparator();
	zoomToolBar->addAction(zoomInAction);
	zoomToolBar->addAction(zoomOutAction);
	//��ת������
	rotateToolBar = addToolBar("��ת");
	rotateToolBar->addAction(rotate90Action);
	rotateToolBar->addAction(rotate180Action);
	rotateToolBar->addAction(rotate270Action);
	//����������������
	doToolBar = addToolBar("����|����");
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
			qDebug() << "��һ��";
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
	QPrintDialog printDialog(&printer, this);                   //����һ��QPrintDialog���󣬲���ΪQPrinter����
	if (printDialog.exec()) {                                   //�ж��û��Ƿ񵥻�����ӡ����ť
		QTextDocument* doc = showWidget->getText()->document(); //��ȡQTextEdit������ĵ�
		doc->print(&printer);                                   //��ӡ
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