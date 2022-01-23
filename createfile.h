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
