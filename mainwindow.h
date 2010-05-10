#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QScreen;
class QKeyboardView;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void UpdateMenu();

public slots:
    void fileScreenshot();
    void helpAboutQt();
    void emulatorFrame();
    void emulatorRun();
    void emulatorReset();
    void emulatorFloppy0();
    void emulatorFloppy1();
    void emulatorFloppy2();
    void emulatorFloppy3();
    void emulatorCartridge1();
    void emulatorCartridge2();
    void emulatorHardDrive1();
    void emulatorHardDrive2();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QScreen *m_screen;
    QKeyboardView *m_keyboard;

    void emulatorCartridge(int slot);
    void emulatorHardDrive(int slot);
    void emulatorFloppy(int slot);
};

#endif // MAINWINDOW_H
