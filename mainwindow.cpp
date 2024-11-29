#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButtonPush_clicked() {
    QString patient = ui->patientInput->text();
    if (!patient.isEmpty()) {
        returnedPatientStack.push(patient);
        ui->patientInput->clear();
        updateStackDisplay();
        updateStatusLabel("name of patient added to recently returned stack.");
    }
}

void MainWindow::on_pushButtonPop_clicked() {
    if (!returnedPatientStack.isEmpty()) {
        returnedPatientStack.pop();
        updateStackDisplay();
        updateStatusLabel("Processed patients from the stack.");
    } else {
        updateStatusLabel("Stack is empty!");
    }
}

void MainWindow::on_pushButtonPeekStack_clicked() {
    if (!returnedPatientStack.isEmpty()) {
        updateStatusLabel("Top patient in stack: " + returnedPatientStack.top());
    } else {
        updateStatusLabel("Stack is empty!");
    }
}

void MainWindow::on_pushButtonEnqueue_clicked() {
    QString patient = ui->reservationInput->text();
    if (!patient.isEmpty()) {
        reservationsQueue.enqueue(patient);
        ui->reservationInput->clear();
        updateQueueDisplay();
        updateStatusLabel("patient added to reservations queue.");
    }
}

void MainWindow::on_pushButtonDequeue_clicked() {
    if (!reservationsQueue.isEmpty()) {
        reservationsQueue.dequeue();
        updateQueueDisplay();
        updateStatusLabel("Processed front reservation.");
    } else {
        updateStatusLabel("Queue is empty!");
    }
}

void MainWindow::on_pushButtonPeekQueue_clicked() {
    if (!reservationsQueue.isEmpty()) {
        updateStatusLabel("Front reservation in queue: " + reservationsQueue.head());
    } else {
        updateStatusLabel("Queue is empty!");
    }
}

void MainWindow::updateStackDisplay() {
    ui->stackListWidget->clear();
    for (const auto &patient : returnedPatientStack) {
        ui->stackListWidget->addItem(patient);
    }
}

void MainWindow::updateQueueDisplay() {
    ui->queueListWidget->clear();
    for (const auto &book : reservationsQueue) {
        ui->queueListWidget->addItem(book);
    }
}

void MainWindow::updateStatusLabel(const QString &message) {
    ui->statusLabel->setText(message);
}
