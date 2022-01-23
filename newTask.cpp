#include "newTask.h"
#include "ui_newTask.h"

newTask::newTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newTask)
{
    ui->setupUi(this);

    ui->date->setDisplayFormat("yyyy/MM/dd");

    QDate date = QDate::currentDate();
    ui->date->setDate(date);

    ui->slide->setRange(0, 100);
    ui->slide->setSingleStep(5);

    ui->save->setEnabled(false);
    ui->delete_2->setVisible(false);

    this->NewTask = true;
}

void newTask::setPath(string path)
{
    this->path = path;
}

void newTask::setData(string duedate, string title, string percent, string description)
{
    this->oldDuedate = duedate;
    this->oldTitle = title;
    this->oldPercent = percent;
    this->oldDescription = description;
    string *sdate = IOManager::split(duedate, '/');
    QDate *sd = new QDate(stoi(sdate[0]), stoi(sdate[1]), stoi(sdate[2]));
    ui->date->setDate(*sd);
    ui->title->setText(QString::fromStdString(title));
    ui->slide->setValue(stoi(percent));
    ui->description->setPlainText(QString::fromStdString(description));
    this->NewTask = false;
    ui->save->setText("Modify");
    ui->delete_2->setVisible(true);
}

newTask::~newTask()
{
    delete ui;
}


void newTask::on_slide_valueChanged(int value)
{
    ui->percent->setText(QString::fromStdString(to_string(value)+"% Compl."));
    checkFields();
}


void newTask::checkFields(){
    string sdatepicker(ui->date->text().toUtf8().constData());
    string stitle(ui->title->text().toUtf8().constData());
    string spercent(ui->percent->text().toUtf8().constData());
    spercent = spercent.substr(0, spercent.find('%'));
    string sdescr(ui->description->toPlainText().toUtf8().constData());

    //We check all fields are completed
    if(sdatepicker.length()!=10 || stitle.length()==0 || spercent.length()==0 || sdescr.length()==0){
        ui->save->setEnabled(false);
    }else{
        ui->save->setEnabled(true);
    }
}
void newTask::on_description_textChanged()
{
    checkFields();
}

void newTask::on_title_textChanged(const QString &arg1)
{
    checkFields();
}

void newTask::on_date_userDateChanged(const QDate &date)
{
    checkFields();
}

void newTask::on_save_clicked()
{
    vector<string*> lines = IOManager::readFile(path);
    unsigned int i;
    string sdatepicker(ui->date->text().toUtf8().constData());
    string stitle(ui->title->text().toUtf8().constData());
    string spercent(ui->percent->text().toUtf8().constData());
    spercent = spercent.substr(0, spercent.find('%'));
    string sdescr(ui->description->toPlainText().toUtf8().constData());
    string s = "";

    if(NewTask){
        for(i=0; i<lines.size(); i++){
            s+=lines.at(i)[0]+";"+lines.at(i)[1]+";"+lines.at(i)[2]+";"+lines.at(i)[3]+"\n";
        }
        s += sdatepicker+";"+stitle+";"+spercent+";"+sdescr;
    }else{
        for(i=0; i<lines.size(); i++){
            if(lines.at(i)[0].compare(oldDuedate) == 0 && lines.at(i)[1].compare(oldTitle) == 0 &&
                    lines.at(i)[2].compare(oldPercent) == 0 && lines.at(i)[3].compare(oldDescription) == 0){
                s += sdatepicker+";"+stitle+";"+spercent+";"+sdescr+"\n";
            }else{
                s+=lines.at(i)[0]+";"+lines.at(i)[1]+";"+lines.at(i)[2]+";"+lines.at(i)[3]+"\n";
            }
        }
    }
    IOManager::writeFile(path, s);
    lines.clear();
    origin->filter();
    this->close();
}

void newTask::on_cancel_clicked()
{
    this->close();
}

void newTask::on_delete_2_clicked()
{
    vector<string*> lines = IOManager::readFile(path);
    unsigned int i;

    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Delete task", "Are you sure you want to permanently delete this task?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::No) {
          return;
      }

    string s = "";

    for(i=0; i<lines.size(); i++){
        if(!(lines.at(i)[0].compare(oldDuedate) == 0 && lines.at(i)[1].compare(oldTitle) == 0 &&
                lines.at(i)[2].compare(oldPercent) == 0 && lines.at(i)[3].compare(oldDescription) == 0)){
            s+=lines.at(i)[0]+";"+lines.at(i)[1]+";"+lines.at(i)[2]+";"+lines.at(i)[3]+"\n";
        }
    }

    IOManager::writeFile(path, s);
    lines.clear();
    origin->filter();
    this->close();
}


