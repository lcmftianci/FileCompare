#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QFileDialog>
#include <QStringListModel>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));
    connect(ui->listView_2,SIGNAL(clicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showClick(QModelIndex index)
{
    QString strTemp;
    strTemp = index.data().toString();

    QMessageBox msg;
    msg.setText(strTemp);
    msg.exec();


}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "click push btn";
    //QMessageBox msgBox;
    //msgBox.setText("The document has been modified.");
    //msgBox.exec();

//    QString runPath = QCoreApplication::applicationDirPath();
//    QString exeName = "FileCompare.exe";
//    QString exePath = QString("%1/%2").arg(runPath).arg(exeName);
//    QFile bfilePath(exePath);
//    if(!bfilePath.exists()){
//        qDebug() << "path:" << exePath << "not has";
//           return;
//    }
//    QString filePath = "file:///" + exePath;
//    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
//    ui->lineEdit->setText(filePath);

    QString dir = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("open path"), QDir::currentPath()));
    if(!dir.isEmpty()){
        ui->lineEdit->setText(dir);
    }

    //遍历文件夹
    QStringList sl = getFileList(dir);

    //插入所有文件
    for(int i = 0; i< sl.size();++i)
    {
        QString tmp = sl.at(i);
        qDebug()<<"tmp ="<< tmp;
    }

    //ui->listView->setViewMode(QListView::IconMode);
    //ui->listView->setMovement(QListView::Static);
    //ui->listView->setIconSize(QSize(100,100));
    //ui->listView->setGridSize(QSize(150,130));
    //ui->listView->setGeometry(0,0,480,272);
    //ui->listView->setResizeMode(QListView::Adjust);
    QStringListModel *Model;
    QStandardItemModel *ItemModel;
    ItemModel = new QStandardItemModel(this);
    for(int i = 0; i < sl.size(); i++)
    {
          QString string = static_cast<QString>(sl.at(i));
          QString strIconPath = QDir::currentPath();
          strIconPath += "/stylesheet/radio_selected.png";
          QStandardItem *item = new QStandardItem(string);
          //QStandardItem *item = new QStandardItem(QIcon(strIconPath), string);
          ItemModel->appendRow(item);
    }
    ui->listView->setModel(ItemModel);
    //ui->listView->setFixedSize(200,300);
}

QStringList MainWindow::getFileList(const QString &dir_path)
{
    QStringList get_files;
    QDir dir(dir_path);
    if(!dir.exists())
    {
        qDebug() << "it is not true dir_path";
    }
    QFileInfoList info_list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    for(int i= 0 ; i< info_list.count(); i++)
    {
        QFileInfo info = info_list.at(i);
        if(info.isDir())
        {
            QString sub_dir  = info.absoluteFilePath();
            get_files.append(sub_dir);
            /*递归*/
            QStringList get_next_files = getFileList(sub_dir);

            get_files.append(get_next_files);
        }else
        {
            QString file_name = info.absoluteFilePath();
            get_files.append(file_name);
        }
    }

    return get_files;
}


void MainWindow::on_pushButton_2_clicked()
{
    QString dir = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("open path"), QDir::currentPath()));
    if(!dir.isEmpty()){
        ui->lineEdit_2->setText(dir);
    }

    //遍历文件夹
    QStringList sl = getFileList(dir);

    //插入所有文件
    for(int i = 0; i< sl.size();++i)
    {
        QString tmp = sl.at(i);
        qDebug()<<"tmp ="<< tmp;
    }

    QStringListModel *Model;
    QStandardItemModel *ItemModel;
    ItemModel = new QStandardItemModel(this);
    for(int i = 0; i < sl.size(); i++)
    {
          QString string = static_cast<QString>(sl.at(i));
          QStandardItem *item = new QStandardItem(string);
          ItemModel->appendRow(item);
    }
    ui->listView_2->setModel(ItemModel);
}
