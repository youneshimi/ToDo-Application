#include "createfile.h"
#include "ui_createfile.h"

createfile::createfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createfile)
{
    ui->setupUi(this);
    ui->folder->setReadOnly(true);
    ui->create->setEnabled(false);
}

createfile::~createfile()
{
    delete ui;
}

void createfile::on_cancel_clicked()
{
this->close();
}


void createfile::on_folder_textChanged(const QString &arg1)
{
    updateOutputLabel();
    checkFields();
}


void createfile::on_name_textChanged(const QString &arg1)
{
    updateOutputLabel();
    checkFields();
}



void createfile::on_create_clicked()
{
    string sfolder(ui->folder->text().toUtf8().constData());
    string stitle(ui->name->text().toUtf8().constData());
    origin->setPath(sfolder + QString(QDir::separator()).toUtf8().constData() + stitle + ".txt");
    origin->filter();
    this->close();

}


void createfile::on_select_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory"), NULL, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->folder->setText(dir);
}
void createfile::updateOutputLabel(){
    string sfolder(ui->folder->text().toUtf8().constData());
    string stitle(ui->name->text().toUtf8().constData());
    QString outputstringlbl = QString::fromStdString(sfolder + QString(QDir::separator()).toUtf8().constData() + stitle + ".txt");
    ui->ko->setText(outputstringlbl);
}


void createfile::checkFields(){
    string sfolder(ui->folder->text().toUtf8().constData());
    string stitle(ui->name->text().toUtf8().constData());

    if(sfolder.length()>0 && stitle.length()>0){
        ui->create->setEnabled(true);
    }else{
        ui->create->setEnabled(false);
    }
}


