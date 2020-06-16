#include "showWidget.h"

ShowWidget::ShowWidget(QWidget* parent /* = 0 */):QWidget(parent) {
	display();
}

void ShowWidget::display() {
	imageLabel = new QLabel;
	imageLabel->setScaledContents(true);
	text = new QTextEdit;
	mainLayout = new QHBoxLayout(this);
	mainLayout->addWidget(imageLabel);
	mainLayout->addWidget(text);
}

QLabel* ShowWidget::getImageLabel() {
	return imageLabel;
}

QTextEdit* ShowWidget::getText() {
	return text;
}