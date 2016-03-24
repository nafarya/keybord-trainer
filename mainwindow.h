#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void clearUI();
    void genNextChar();
    void updateUI();
    void stop();
};

#endif // MAINWINDOW_H
