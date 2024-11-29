#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QQueue>
#include <QListWidget>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonPush_clicked();
    void on_pushButtonPop_clicked();
    void on_pushButtonPeekStack_clicked();
    void on_pushButtonEnqueue_clicked();
    void on_pushButtonDequeue_clicked();
    void on_pushButtonPeekQueue_clicked();

private:
    Ui::MainWindow *ui;
    QStack<QString> returnedPatientStack;
    QQueue<QString> reservationsQueue;
    void updateStackDisplay();
    void updateQueueDisplay();
    void updateStatusLabel(const QString &message);
};

#endif // MAINWINDOW_H
