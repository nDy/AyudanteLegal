#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dirent.h"
#include "stdio.h"
#include "QLabel"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//Menu
    QMenu* Archivo;
        QMenu* ArchivoNuevo;
            QList<QAction*> ArchivoNuevoLista;
        QAction* ArchivoAbrir;
        QAction* ArchivoImprimir;
        QAction* ArchivoGuardar;
        QAction* ArchivoGuardarComo;

    QMenu* Ver;
        QAction* VerZoom;
        QAction* VerHoja;
        QAction* VerPagina;
        QAction* VerEdicion;

    QMenu* Edicion;
        QAction* EdicionCopiar;
        QAction* EdicionCortar;
        QAction* EdicionPegar;

    QMenu* Formato;
        QMenu* FormatoFuente;
            QList<QAction*> FormatoFuenteLista;
        QAction* FormatoBase;
        QAction* FormatoMinimo;

//Menu Archivo


    Archivo = new QMenu;
    Archivo->setTitle("Archivo");

    ArchivoNuevo = new QMenu;
    ArchivoNuevo->setTitle("Nuevo");

    //Carga de planillas
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("../AyudanteLegal/Planillas")) != NULL) {
      //Lee Los nombres de las formas
      while ((ent = readdir (dir)) != NULL) {
          printf ("Carpeta: %s\n", ent->d_name);
          DIR *formadir;
          struct dirent *formaent;
          if ((formadir = opendir (ent->d_name)) != NULL) {
            //Lee componentes de la forma
            while ((formaent = readdir (dir)) != NULL) {
                 if(formaent->d_name[0]!='.'){
                     printf ("      Carpeta %s\n", formaent->d_name);
                     QAction* aux;
                     static QString* file;
                     file = new QString();
                     file->append("../AyudanteLegal/Planillas/");
                     file->append(formaent->d_name);
                     file->append("/");
                     aux = new QAction(ArchivoNuevo);
                     aux->setText(formaent->d_name);
                     printf ("%s\n", file->toStdString().c_str());
                     aux->setObjectName(*file);
                     ArchivoNuevo->addAction(aux);
                 }
            }
          }
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("");
    }

    QList<QAction*>::iterator j;
    for (j = ArchivoNuevo->actions().begin(); j != ArchivoNuevo->actions().end(); ++j) {
        QObject::connect((*j), SIGNAL(triggered()),
                         this, SLOT(CargaPlanilla()));
    }

    Archivo->addMenu(ArchivoNuevo);

    ArchivoAbrir = new QAction(Archivo);
    ArchivoAbrir->setText("Abrir");
    Archivo->addAction(ArchivoAbrir);

    ArchivoGuardar = new QAction(Archivo);
    ArchivoGuardar->setText("Guardar");
    Archivo->addAction(ArchivoGuardar);

    ArchivoGuardarComo = new QAction(Archivo);
    ArchivoGuardarComo->setText("Guardar Como");
    Archivo->addAction(ArchivoGuardarComo);

//Menu Ver
    Ver = new QMenu;
    Ver->setTitle("Ver");

    VerEdicion = new QAction(Ver);
    VerEdicion->setText("Vista de Edicion");
    Ver->addAction(VerEdicion);

    VerHoja = new QAction(Ver);
    VerHoja->setText("Vista de Hoja");
    Ver->addAction(VerHoja);

    VerPagina = new QAction(Ver);
    VerPagina->setText("Vista de Pagina");
    Ver->addAction(VerPagina);

    VerZoom = new QAction(Ver);
    VerZoom->setText("Vista de Edicion");
    Ver->addAction(VerZoom);

//Menu Edicion
    Edicion = new QMenu;
    Edicion->setTitle("Edicion");

//Menu Formato
    Formato = new QMenu;
    Formato->setTitle("Formato");

    ui->menuBar->addMenu(Archivo);
    ui->menuBar->addMenu(Ver);
    ui->menuBar->addMenu(Edicion);
    ui->menuBar->addMenu(Formato);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CargaPlanilla()
{
    QObject* action = sender();
     if(action)
     {
        QString ruta = action->objectName();
        printf ("string de ruta: %s\n", ruta.toStdString().c_str());
        QString aux;
        aux.append(ruta);
        aux.append("Imagen.png");
        printf ("string auxiliar: %s\n", aux.toStdString().c_str());
        QLabel* label;
        label = new QLabel(ui->centralWidget);
        QPixmap* pic;
        pic = new QPixmap(aux);
        QLayout *vbl = ui->centralWidget->layout();
        vbl->addWidget(label);
        label->setPixmap(*pic);
     }

}
