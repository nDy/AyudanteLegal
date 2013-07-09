#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dirent.h"
#include "stdio.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scaleFactor = 1.0;

    this->GenerarMenu();

    this->GenerarConexiones();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GenerarConexiones(){

    QList<QAction*>::iterator j;
    for (j = ArchivoNuevo->actions().begin(); j != ArchivoNuevo->actions().end(); ++j) {
        QObject::connect((*j), SIGNAL(triggered()),
                         this, SLOT(CargaPlanilla()));
    }


    connect(VerZoomIn, SIGNAL(triggered()), this, SLOT(ZoomIn()));
    connect(VerZoomOut, SIGNAL(triggered()), this, SLOT(ZoomOut()));

}

void MainWindow::GenerarMenu(){
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

        VerZoomIn = new QAction(Ver);
        VerZoomIn->setText("ZoomIn");
        Ver->addAction(VerZoomIn);

        VerZoomOut = new QAction(Ver);
        VerZoomOut->setText("ZoomOut");
        Ver->addAction(VerZoomOut);

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

void MainWindow::CargaPlanilla()
{
    CargaImagen();
    CargaTextBox();
}

void MainWindow::CargaTextBox()
{
    QObject* action = sender();
     if(action)
     {
         QString ruta = action->objectName();
         printf ("string de ruta: %s\n", ruta.toStdString().c_str());
         QString aux;
         aux.append(ruta);
         aux.append("Mapa.txt");
         QFile file(aux);
         if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;

         file.readLine();
         int Xo,Yo,Xf,Yf;

            while (!file.atEnd()) {
                QString linea = file.readLine();
                //parseline
                Xo=linea.section('|',0,0).toInt();
                Yo=linea.section('|',1,1).toInt();
                Xf=linea.section('|',2,2).toInt();
                Yf=linea.section('|',3,3).toInt();
                //feedtolinegeometry
                QLineEdit* cuadro;
                cuadro = new QLineEdit(label);
                cuadro->setGeometry(Xo,Yo,Xf-Xo,Yf-Yo);
                cuadro->setStyleSheet("QLineEdit{background: white;}");
                cuadro->raise();
            }



     }
}


void MainWindow::CargaImagen()
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
         label = new QLabel;
         pic = new QPixmap(aux);
         label->setPixmap(*pic);

         QWidget* w;
         w = new QWidget();
         ui->scrollArea->setWidget(w);
         QVBoxLayout* lay;
         lay = new QVBoxLayout();
         w->setLayout(lay);
         w->layout()->addWidget(label);

        scaleImage(0.343289086);
     }

}


void MainWindow::ZoomIn()
{
        scaleImage(1.25);
}
void MainWindow::ZoomOut()
{
        scaleImage(0.75);
}

void MainWindow::scaleImage(double factor){
    scaleFactor *= factor;
    label->setPixmap(pic->scaled(pic->width()*scaleFactor,pic->height()*scaleFactor));

    adjustScrollBar(ui->scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui->scrollArea->verticalScrollBar(), factor);

}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
