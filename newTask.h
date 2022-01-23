#ifndef NEWTASK_H
#define NEWTASK_H

#include <QDialog>
#include <string>
#include <vector>
#include <QMessageBox>
#include "iomanager.h"
#include "app.h"

using namespace std;

namespace Ui {
class newTask;
}

class newTask : public QDialog
{
    Q_OBJECT

public:
    explicit newTask(QWidget *parent = 0);
    void setData(string duedate, string title, string percent, string description);
    void setPath(string path);
    inline void setOrigin(app *origin){ this->origin = origin; }
    string oldDuedate;
    string oldTitle;
    string oldPercent;
    string oldDescription;
    ~newTask();

private slots:
    void on_slide_valueChanged(int value);
    void on_description_textChanged();
    void on_title_textChanged(const QString &arg1);
    void on_date_userDateChanged(const QDate &date);
    void on_save_clicked();
    void on_cancel_clicked();

     void on_delete_2_clicked();

private:
    void checkFields();
    Ui::newTask *ui;
    bool NewTask;
    string path;
    app  *origin;
};

#endif // NEWTASK_H
