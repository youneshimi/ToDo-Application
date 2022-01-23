#include "app.h"

#include<QPixmap>
#include "iomanager.h"
#include "createfile.h"
#include"newTask.h"
#include <QHeaderView>

app::app()
{
    // This is the default path, but if it does not exist, you can change it into the program
    path = "/Users/Younes Imane /database.txt";
    QWidget *widget = new QWidget;
    setCentralWidget(widget);


    // Filters
    QHBoxLayout *filtersLayout = new QHBoxLayout;
    createFilters(filtersLayout);
    //filtersLayout->setContentsMargins();

    setWindowTitle("My To-do List");
    setMinimumSize(480, 320);
    resize(580, 480);

    //Table
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




    //creating actions
    createActions();

    //creating Menu
    createMenus();
    //creating toolbar
    createtoolBar();

}



void app::createActions()
{
    // add task
    QPixmap AddIcon("://add.png");
    AddTask=new QAction(AddIcon,"&Add Task",this);
    AddTask->setShortcut(tr("Ctrl+N"));
    if(IOManager::exists(path) == false){
        AddTask->setEnabled(false);
    }
  connect(AddTask, &QAction::triggered, this,&app::addTask);
    //create file
    QPixmap CreateIcon("://create.png");
    CreateFile = new QAction(CreateIcon,"&Create &File",this);
    CreateFile->setShortcut(tr("Ctrl+E"));
     connect(CreateFile, &QAction::triggered, this, &app::Newfile);


    // Exit
    //lui choisir une icone
     QPixmap ExitIcon("://exit.png");
    //lui choisir un nom
     Exit=new QAction(ExitIcon,"&Exit",this);
    //lui choisir un reccoursi
     Exit->setShortcut(tr("Ctrl+Q"));
      connect(Exit,&QAction::triggered,this,&app::close);
// option
    //change file
    QPixmap ChangeIcon("://change.png");
    ChangeFile=new QAction(ChangeIcon,"Change &File",this);
    ChangeFile->setShortcut(tr("Ctrl+R"));
    connect(ChangeFile, &QAction::triggered, this, &app::changeFile);


 //Help

     QPixmap AboutQtIcon("://info qt.png");
     AboutQt= new QAction(AboutQtIcon,"&AboutQt",this);
      connect(AboutQt,&QAction::triggered,this,&app::infoAbout);
}
void app::createMenus()
{
    //file
    File = menuBar()->addMenu("&File");
    File->addAction(AddTask);
    File->addAction(CreateFile);
    File->addAction(Exit);

    //edit

    Option= menuBar()->addMenu("&Option");
    Option->addAction(ChangeFile);

    //help

    Help = menuBar()->addMenu("&Help");
    Help->addAction(AboutQt);


}
void app::createtoolBar()
{
    auto tool1=addToolBar("File");
//cree une toolbar
    tool1->addAction(CreateFile);

//cree une autre tool Bar
    auto tool2=addToolBar("Option");
    tool2->addAction(ChangeFile);
//cree une autre tool bar
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

    //inserting data
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
        // Set the checkbox as not editable and check it if necessary
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

    int julian = t.tm_yday;  // Jan 1 = 1, Jan 2 = 2, etc...
    int dow = t.tm_wday;     // Sun = 0, Mon = 1, etc...
    int dowJan1 = mauxdate->tm_wday;   // find out first of year's day
    int weekNum = ((julian + 6) / 7);   // probably better.  CHECK THIS LINE. (See comments.)
    if (dow < dowJan1){                 // adjust for being after Saturday of week #1
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





