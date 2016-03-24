#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(ui->buttonStart, SIGNAL(clicked(bool)), this, SLOT(start()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::update()
{
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
    ui->spinBoxTime->setEnabled(true);
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
            return;
        }
    }
}

void MainWindow::start()
{
    clearUI();
    genNextChar();
    ui->labelCurChar->setText(QString(currentChar));
    ui->buttonStart->setEnabled(false);
    ui->spinBoxTime->setEnabled(false);
    secondsRemaining = ui->spinBoxTime->value();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
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
