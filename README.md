# ToDoList-QT

Le projet consiste à créer Une application qui guerre vos taches en C++ / Qt creator

## Objectif :

 créer une application pour gérer vos tâches. Il devrait avoir toutes les fonctionnalités de l'application principale telle que les menus, les actions et la barre d'outils. L'application doit stocker une archive de toutes les tâches en attente et terminées .


## Cas d'utilisation : 

> * Un utilisateur devrait pouvoir fermer l'application bien sûr
> * Une application Todo ne peut être utile que si elle offre la possibilité de créer de nouvelles tâches 
> * La vue du widget principal doit être divisée en trois zones 
> * Chaque catégorie doit être affichée avec une icône personnalisée 
> * L'utilisateur peut afficher hide/showles vues en attente et terminées
> * Enfin, les tâches saisies dans votre application doivent rester dans l'application lors d'une utilisation future



# les fichiers d'entête :
## iomanager.h
```ts
#ifndef IOMANAGER_H
#define IOMANAGER_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class IOManager
{
public:
    IOManager();
    static vector<string*> readFile(string path);
    static void createFile(string path);
    static void writeFile(string path, string);
    static string* split(string l, char regex);
    static bool exists(string path);
};


#endif // IOMANAGER_H
```

## createfile.h

```ts
#ifndef CREATEFILE_H
#define CREATEFILE_H

#include <QDialog>
#include <string>
#include "iomanager.h"
#include "app.h"
using namespace std;

namespace Ui {
class createfile;
}

class createfile : public QDialog
{
    Q_OBJECT

public:
    explicit createfile(QWidget *parent = nullptr);
    inline void setOrigin(app *origin){ this->origin = origin; }
    ~createfile();

private slots:

    void on_cancel_clicked();

    void on_folder_textChanged(const QString &arg1);

    void on_create_clicked();

    void on_select_clicked();

    void on_name_textChanged(const QString &arg1);


private:
    Ui::createfile *ui;
    void checkFields();
    void updateOutputLabel();
    app *origin;
};

#endif // CREATEFILE_H
```











## App.cpp
```ts
#include "app.h"

#include<QPixmap>
#include "iomanager.h"
#include "createfile.h"
#include"newTask.h"
#include <QHeaderView>

app::app()
{
   
    path = "/Users/Younes Imane /database.txt";
    QWidget *widget = new QWidget;
    setCentralWidget(widget);


    
    QHBoxLayout *filtersLayout = new QHBoxLayout;
    createFilters(filtersLayout);

    setWindowTitle("My To-do List");
    setMinimumSize(480, 320);
    resize(580, 480);

    table = new QTableWidget(this);
    initializeTable();

    QVBoxLayout *layout = new QVBoxLayout;
    layout -> setMargin(8);
    layout -> addLayout(filtersLayout);
    layout -> addWidget(table);
    layout -> setStretch(0, 0);
    layout -> setStretch(1, 0);
    layout -> setStretch(2, 1);

    widget -> setLayout(layout);




    createActions();

    createMenus();
    createtoolBar();

}



void app::createActions()
{
    QPixmap AddIcon("://add.png");
    AddTask=new QAction(AddIcon,"&Add Task",this);
    AddTask->setShortcut(tr("Ctrl+N"));
    if(IOManager::exists(path) == false){
        AddTask->setEnabled(false);
    }
  connect(AddTask, &QAction::triggered, this,&app::addTask);
   
    QPixmap CreateIcon("://create.png");
    CreateFile = new QAction(CreateIcon,"&Create &File",this);
    CreateFile->setShortcut(tr("Ctrl+E"));
     connect(CreateFile, &QAction::triggered, this, &app::Newfile);


   
     QPixmap ExitIcon("://exit.png");

     Exit=new QAction(ExitIcon,"&Exit",this);
     Exit->setShortcut(tr("Ctrl+Q"));
      connect(Exit,&QAction::triggered,this,&app::close);
    
    QPixmap ChangeIcon("://change.png");
    ChangeFile=new QAction(ChangeIcon,"Change &File",this);
    ChangeFile->setShortcut(tr("Ctrl+R"));
    connect(ChangeFile, &QAction::triggered, this, &app::changeFile);



     QPixmap AboutQtIcon("://info qt.png");
     AboutQt= new QAction(AboutQtIcon,"&AboutQt",this);
      connect(AboutQt,&QAction::triggered,this,&app::infoAbout);
}
void app::createMenus()
{
    File = menuBar()->addMenu("&File");
    File->addAction(AddTask);
    File->addAction(CreateFile);
    File->addAction(Exit);


    Option= menuBar()->addMenu("&Option");
    Option->addAction(ChangeFile);


    Help = menuBar()->addMenu("&Help");
    Help->addAction(AboutQt);


}
void app::createtoolBar()
{
    auto tool1=addToolBar("File");
    tool1->addAction(CreateFile);


    auto tool2=addToolBar("Option");
    tool2->addAction(ChangeFile);
    auto tool3=addToolBar("File");
    tool3->addAction(Exit);
}
void app::infoAbout()
{
     QMessageBox ::aboutQt(this,"about QT");

}


void app::createFilters(QHBoxLayout *layout)
{
    all = new QRadioButton;
    today = new QRadioButton;
    thisweek = new QRadioButton;
    pending = new QRadioButton;
    lcompleted = new QCheckBox;

    all->setText(tr("&All"));
    all->setChecked(true);
    today->setText(tr("&Today"));
    thisweek->setText(tr("&This Week"));
    pending->setText(tr("&Pending"));
    lcompleted->setText(tr("&Not Completed"));

    connect(all,SIGNAL(clicked()),this,SLOT(filter()));
    connect(today,SIGNAL(clicked()),this,SLOT(filter()));
    connect(thisweek,SIGNAL(clicked()),this,SLOT(filter()));
    connect(pending,SIGNAL(clicked()),this,SLOT(filter()));
    connect(lcompleted,SIGNAL(clicked()),this,SLOT(filter()));

    QHBoxLayout *Layoutk = new QHBoxLayout;
    Layoutk -> setAlignment(Qt::AlignRight);
    Layoutk -> addWidget(lcompleted);

    layout->addWidget(all);
    layout->addWidget(today);
    layout->addWidget(thisweek);
    layout->addWidget(pending);
    layout->addLayout(Layoutk);

    layout -> setStretch(0, 0);
    layout -> setStretch(1, 0);
    layout -> setStretch(2, 0);
    layout -> setStretch(3, 0);
    layout -> setStretch(4, 1);

}
void app::initializeTable()
{
    table -> setColumnCount(5);
    tableHeader << "Finished" << "DueDate" << "Title" << "% Complete" << "Description";
    table -> setHorizontalHeaderLabels(tableHeader);
    table -> horizontalHeader()->setStretchLastSection(true);
    table -> verticalHeader() -> setVisible(false);
    table -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    table -> setSelectionBehavior(QAbstractItemView::SelectRows);
    table -> setSelectionMode(QAbstractItemView::SingleSelection);
    table -> setStyleSheet("QTableView {selection-background-color: #E0F7FA; selection-color: #000000;}");

    updateTable(IOManager::readFile(path));

    connect( table, SIGNAL( cellDoubleClicked (int, int) ), this, SLOT( cellSelected( int, int ) ) );
}


void app::addTask()
{
    newTask a;
    a.setModal(true);
    a.setPath(path);
    a.setOrigin(this);
    a.exec();
}
void app::Newfile()
{
    createfile a;
    a.setModal(true);
    a.setOrigin(this);
    a.exec();
}
void app::changeFile()
{
    QFileDialog a(this);
    a.setFileMode(QFileDialog::ExistingFile);
    a.setNameFilter(tr("Text (*.txt)"));
    a.setViewMode(QFileDialog::List);

    QStringList fileNames;
    if (a.exec()){
        fileNames = a.selectedFiles();
        this->path = ((QString)fileNames.at(0)).toUtf8().constData();
        this->filter();
    }

    AddTask->setEnabled(true);
}
void app::close()
{
    exit(0);
}

void app::cellSelected(int nRow, int nCol)
{
    newTask a;
    a.setModal(true);
    a.setData(table->item(nRow, 1)->text().toUtf8().constData(), table->item(nRow, 2)->text().toUtf8().constData(), table->item(nRow, 3)->text().toUtf8().constData(), table->item(nRow, 4)->text().toUtf8().constData());
    a.setPath(path);
    a.setOrigin(this);
    a.exec();
}

void app::updateTable(vector<string*> data){
    table -> clearContents();
    table -> setRowCount(data.size());
    unsigned int i;
    for(i=0; i<data.size(); i++){
        QCheckBox *qcb = new QCheckBox;
        qcb->setStyleSheet(QStringLiteral("QCheckBox::indicator {subcontrol-position: center;}"));
        qcb->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        qcb->setFocusPolicy(Qt::NoFocus);
        qcb -> setChecked(stoi(data.at(i)[2]) == 100);

        table -> setAlternatingRowColors(true);
        table -> setCellWidget(i, 0, qcb);
        QTableWidgetItem *qdd = new QTableWidgetItem(QString::fromStdString(data.at(i)[0]));
        qdd -> setTextAlignment(Qt::AlignCenter);
        table -> setItem(i, 1, qdd);
        table -> setItem(i, 2, new QTableWidgetItem(QString::fromStdString(data.at(i)[1])));
        QTableWidgetItem *qtwi = new QTableWidgetItem(QString::fromStdString(data.at(i)[2]));
        qtwi -> setTextAlignment(Qt::AlignCenter);
        table -> setItem(i, 3, qtwi);
        table -> setItem(i, 4, new QTableWidgetItem(QString::fromStdString(data.at(i)[3])));
    }
}


void app::filter()
{
    vector<string*> data = IOManager::readFile(path);
    bool completed = lcompleted->isChecked();

    time_t now = time(0);
    tm cur = *gmtime(&now);

    unsigned int i;
    for(i=0; i<data.size(); i++){
        int year = stoi(IOManager::split(data.at(i)[0], '/')[0]);
        int month = stoi(IOManager::split(data.at(i)[0], '/')[1]);
        int day = stoi(IOManager::split(data.at(i)[0], '/')[2]);

        if(completed){
            if(stoi(data.at(i)[2]) == 100){
                data.erase(data.begin()+i);
                i--;
                continue;
            }
        }

        if(today->isChecked()){
            if(cur.tm_year+1900 != year || cur.tm_mon+1 != month || cur.tm_mday != day){
                data.erase(data.begin()+i);
                i--;
            }
        }else if(thisweek->isChecked()){
            time_t auxd = time(0);
            tm *auxdate = gmtime(&auxd);
            auxdate->tm_mday = day;
            auxdate->tm_mon = month - 1;
            auxdate->tm_year = year - 1900;
            auxd = mktime(auxdate);
            auxdate =  gmtime(&auxd);
            tm cp = *auxdate;

            if(getWeekNumber(cur) != getWeekNumber(cp) || cur.tm_year != cp.tm_year){
                data.erase(data.begin()+i);
                i--;
            }
        }else if(pending->isChecked()){
            if(cur.tm_year+1900 > year || (cur.tm_year+1900 == year && cur.tm_mon+1 < month) || (cur.tm_year+1900 == year && cur.tm_mon+1 == month && cur.tm_mday <= day)){
                data.erase(data.begin()+i);
                i--;
             }
      }
  }
    updateTable(data);
}


int app::getWeekNumber(tm t)
{
    time_t nnow = time(0);
    tm *mauxdate = gmtime(&nnow);
    mauxdate->tm_mday = 0;
    mauxdate->tm_mon = 0;
    mauxdate->tm_year = mauxdate->tm_year;
    nnow = mktime(mauxdate);
    mauxdate =  gmtime(&nnow);

    int julian = t.tm_yday;  
    int dow = t.tm_wday;     
    int dowJan1 = mauxdate->tm_wday;   
    int weekNum = ((julian + 6) / 7);   
    if (dow < dowJan1){                 
        ++weekNum;
    }
    return weekNum;
}


app::~app()
{
 delete ui;
 delete table;
delete AddTask;
delete CreateFile;
delete ChangeFile;
delete Exit;
delete About;
delete AboutQt;
 delete all;
 delete today;
delete thisweek;
delete lcompleted;

}
```
 le chemin par défaut, mais s'il n'existe pas, vous pouvez le changer dans le programme : 
```ts
app::app()
{
   
    path = "/Users/Younes Imane /database.txt";
    QWidget *widget = new QWidget;
    setCentralWidget(widget);
```
Filters : 
```ts
QHBoxLayout *filtersLayout = new QHBoxLayout;
    createFilters(filtersLayout);
```
créer un fichier : 
```ts
    QPixmap CreateIcon("://create.png");
    CreateFile = new QAction(CreateIcon,"&Create &File",this);
    CreateFile->setShortcut(tr("Ctrl+E"));
     connect(CreateFile, &QAction::triggered, this, &app::Newfile);
 ```
 
Création Menu :
```ts
    createMenus();
 ```
Création d'une barre d'outils : 
```ts
    createtoolBar();
 ```
ajuster pour être après le samedi de la semaine : 
```ts
    if (dow < dowJan1){                 
        ++weekNum;
    }
 ```
 insertion de données : 
 ```ts
updateTable(IOManager::readFile(path));
 ```
Définissez la case à cocher comme non modifiable et cochez-la si nécessaire
 ```ts
qcb->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        qcb->setFocusPolicy(Qt::NoFocus);
        qcb -> setChecked(stoi(data.at(i)[2]) == 100);
```
Crée une autre tool Bar :
 ```ts
    auto tool2=addToolBar("Option");
    tool2->addAction(ChangeFile);
    auto tool3=addToolBar("File");
    tool3->addAction(Exit);
```
Option
 ```ts
    QPixmap ChangeIcon("://change.png");
    ChangeFile=new QAction(ChangeIcon,"Change &File",this);
    ChangeFile->setShortcut(tr("Ctrl+R"));
    connect(ChangeFile, &QAction::triggered, this, &app::changeFile);
```
## Main.cpp
 ```ts
#include "app.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    app w;
    w.show();

    return a.exec();
}
```
## Capture démonstrative :
 > createfile.ui : 
![createfile](https://user-images.githubusercontent.com/96379214/150688438-a5dbab76-f4d9-4422-a12e-6ccef035fe55.png)


> newTask.ui : 
 ![newTask](https://user-images.githubusercontent.com/96379214/150688532-3cf550e5-6c5c-487f-9340-0059f2ca45ba.png)

