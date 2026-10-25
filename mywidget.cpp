#include "mywidget.h"
#include "ui_mywidget.h"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>

QString mFilename = "C:/ContactBook/myfile.csv";

void Write(QString Filename, QString str)
{
    QFile mFile(Filename);
    if (!mFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "could not open file for write";
        return;
    }
    QTextStream out(&mFile);
    out << str;
    mFile.flush();
    mFile.close();
}

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    QStringList ColTotle;
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(0);
    ColTotle << "學號" << "班級" << "姓名" << "電話";
    ui->tableWidget->setHorizontalHeaderLabels(ColTotle);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    QTableWidgetItem *inputRow1, *inputRow2, *inputRow3, *inputRow4;
    inputRow1 = new QTableWidgetItem(ui->lineEdit->text());
    inputRow2 = new QTableWidgetItem(ui->lineEdit_2->text());
    inputRow3 = new QTableWidgetItem(ui->lineEdit_3->text());
    inputRow4 = new QTableWidgetItem(ui->lineEdit_4->text());

    int currentRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(currentRow);

    ui->tableWidget->setItem(currentRow, 0, inputRow1);
    ui->tableWidget->setItem(currentRow, 1, inputRow2);
    ui->tableWidget->setItem(currentRow, 2, inputRow3);
    ui->tableWidget->setItem(currentRow, 3, inputRow4);
}

void MyWidget::on_pushButton_2_clicked()
{
    QString saveFile = "";
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            if (ui->tableWidget->item(i, j)) {
                saveFile += ui->tableWidget->item(i, j)->text();
            }
            if (j < ui->tableWidget->columnCount() - 1) {
                saveFile += ",";
            }
        }
        saveFile += "\n";
    }
    Write(mFilename, saveFile);
}
void MyWidget::on_pushButton_4_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "選擇檔案", "", "CSV 檔案 (*.csv)");
    if (filePath.isEmpty()) {
        return;
    }

    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return;
    }

    ui->tableWidget->setRowCount(0);

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) {
            continue;
        }

        QStringList fields = line.split(",");
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        for (int col = 0; col < fields.size() && col < 4; col++) {
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(fields[col]));
        }
    }
    file.close();
}

