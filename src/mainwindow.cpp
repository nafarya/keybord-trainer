#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <QTextStream>
#include <QTimer>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList items;
    for (int d : durations) {
        items << QString::number(d);
    }
    ui->comboBox->addItems(items);
    timer = new QTimer(this);
    connect(ui->buttonStart, SIGNAL(clicked(bool)), this, SLOT(start()));
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(ui->changeLangButton, SIGNAL(clicked(bool)), this, SLOT(changeLanguage()));
    getStat();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::update()
{
    std::cout << secondsRemaining << std::endl;
    secondsRemaining--;
    ui->lcdTimeRemaining->display(secondsRemaining);
    if (secondsRemaining <= 0) {
        stop();
    }
}

void MainWindow::stop()
{
    timer->stop();
    ui->buttonStart->setEnabled(true);
    ui->comboBox->setEnabled(true);
    updateTop();


}

void MainWindow::updateTop()
{
    QFile file("statistics.txt");

    if (!file.open(QFile::WriteOnly|QFile::Truncate))
         ui->label_3->setText(QString::number(points));


    QTextStream out(&file);



    switch(durations[ui->comboBox->currentIndex()]) {

    case 15:
        if (points > ui->label_3->text().toInt())
            ui->label_3->setText(QString::number(points));
            inputData[0] = QString::number(points);
        break;
    case 30:
        if (points > ui->label_4->text().toInt())
            ui->label_4->setText(QString::number(points));
            inputData[1] = QString::number(points);
        break;
    case 45:
        if (points > ui->label_5->text().toInt())
            ui->label_5->setText(QString::number(points));
            inputData[2] = QString::number(points);
        break;

    }
    out << inputData[0] << "\n";
    out << inputData[1] << "\n";
    out << inputData[2];


}

void MainWindow::getStat()
{
    QFile file("/home/dan/GameLab4/statistics.txt");
    if (!file.exists()) {
        ui->label_3->setText(QString("FUCK YOU"));
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        ui->label_3->setText(QString("FUCK YOU"));

    QTextStream in(&file);
    int ind = 0;
    while (!in.atEnd()) {
        inputData[ind++] = in.readLine();
    }

    ui->label_3->setText(inputData[0]);
    ui->label_4->setText(inputData[1]);
    ui->label_5->setText(inputData[2]);
    file.close();
}

void MainWindow::changeLanguage()
{
    QTranslator translator;
    if (curLang == "en") {
        translator.load("arrowpad_ru", ":/translations/");
        QApplication::instance()->installTranslator(&translator);
        ui->retranslateUi(this);
        curLang = "ru";
        ui->changeLangButton->setText("РУС");
    } else {
        translator.load("arrowpad_en", ":/translations/");
        QApplication::instance()->installTranslator(&translator);
        ui->retranslateUi(this);
        ui->changeLangButton->setText("EN");
        curLang = "en";

    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!timer->isActive())
    {
        return;
    }
    QString text = event->text();
    if (text.length() == 1)
    {
        QChar c = text[0];
        if (c == currentChar) {
            points++;
            genNextChar();
            updateUI();
        } else {
             if (points > 0)
                points--;
             updateUI();
        }
    }
}

void MainWindow::start()
{
    clearUI();
    genNextChar();
    ui->labelCurChar->setText(QString(currentChar));
    ui->buttonStart->setEnabled(false);
    ui->comboBox->setEnabled(false);
    secondsRemaining = durations[ui->comboBox->currentIndex()];
    ui->lcdTimeRemaining->display(secondsRemaining);
    timer->start(1000);
}

void MainWindow::clearUI()
{
    ui->labelCurChar->clear();
    ui->lcdPoints->display(0);
    points = 0;
}

void MainWindow::genNextChar()
{
    int r = qrand() % 3;
    switch (r) {
    case 0:
        currentChar = QChar('a' + qrand() % 26);
        break;
    case 1:
        currentChar = QChar('A' + qrand() % 26);
        break;
    default:
        currentChar = QChar('0' + qrand() % 10);
    }
}

void MainWindow::updateUI()
{
    ui->labelCurChar->setText(QString(currentChar));
    ui->lcdPoints->display(points);
}
