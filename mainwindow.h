#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void start();
    void update();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    int points;
    int secondsRemaining;
    QTimer *timer;
    QChar currentChar;

    QList<int> durations = {15, 30, 45};
    QString inputData[3];

    void clearUI();
    void genNextChar();
    void updateUI();
    void stop();
    void updateTop();
    void getStat();

};

#endif // MAINWINDOW_H
