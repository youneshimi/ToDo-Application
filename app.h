#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include<QAction>
#include<QMenu>
#include<QMenuBar>
#include<QToolBar>
#include<QMessageBox>
#include <QCheckBox>
#include <QTableWidget>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <QFileDialog>

using namespace std;

namespace Ui {
class app;
}

class app : public QMainWindow
{
    Q_OBJECT

public:
    explicit app();
    inline void setPath(string path){ this->path = path; }
    ~app();

private:
    Ui::app *ui;
    //file
    QMenu *File;
    QAction *AddTask;
    QAction *CreateFile;
    QAction   *Exit;
    //option
    QMenu *Option;
    QAction *ChangeFile;
    //help
    QMenu *Help;
    QAction *About;
    QAction *AboutQt;
    void createFilters(QHBoxLayout *layout);
    void initializeTable();
    int getWeekNumber(tm t);
    void updateTable(vector<string*> data);
    string path;
    QRadioButton *all;
    QRadioButton *today;
    QRadioButton *thisweek;
    QRadioButton *pending;
    QCheckBox *lcompleted;
    QTableWidget *table;
    QStringList tableHeader;


protected:
  void   createActions();
  void  createMenus();
  void  createtoolBar();
private slots:
  void infoAbout();
  void addTask();
  void changeFile();
  void Newfile();
  void close();
  void cellSelected(int nRow, int nCol);

public slots:
  void filter();
};
#endif // APP_H
