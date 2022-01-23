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
