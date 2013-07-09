/**********************************************************************************
 *                                                                                *
 *    This file is part of AyudanteLegal.                                         *
 *    AyudanteLegal is free software: you can redistribute it and/or modify       *
 *    it under the terms of the GNU General Public License as published by        *
 *    the Free Software Foundation, either version 3 of the License, or           *
 *    (at your option) any later version.                                         *
 *                                                                                *
 *    AyudanteLegal is distributed in the hope that it will be useful,            *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 *    GNU General Public License for more details.                                *
 *                                                                                *
 *    Source Code written by nDy (Andres Rangel)                                  *
 *    Contact info:                                                               *
 *    Email: nDy.Work@gmail.com      GitHub Repository: https://github.com/nDy    *
 *                                                                                *
 *    Copyright:                                                                  *
 *               nDySoft© (2013)                                                  *
 *                                                                                *
 **********************************************************************************/

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

    //NewFileConections
    QList<QAction*>::iterator j;
    for (j = ArchivoNuevo->actions().begin(); j != ArchivoNuevo->actions().end(); ++j) {
        QObject::connect((*j), SIGNAL(triggered()),
                         this, SLOT(CargaPlanilla()));
    }

    //ResizeTextConections

    //ZoomConections
    connect(VerZoomIn, SIGNAL(triggered()), this, SLOT(ZoomIn()));
    connect(VerZoomOut, SIGNAL(triggered()), this, SLOT(ZoomOut()));
    connect(ArchivoImprimir, SIGNAL(triggered()), this, SLOT(Imprimir()));


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
            DIR *formadir;
            struct dirent *formaent;
            if ((formadir = opendir (ent->d_name)) != NULL) {
                //Lee componentes de la forma
                while ((formaent = readdir (dir)) != NULL) {
                    if(formaent->d_name[0]!='.'){
                        QAction* aux;
                        static QString* file;
                        file = new QString();
                        file->append("../AyudanteLegal/Planillas/");
                        file->append(formaent->d_name);
                        file->append("/");
                        aux = new QAction(ArchivoNuevo);
                        aux->setText(formaent->d_name);
                        aux->setObjectName(*file);
                        ArchivoNuevo->addAction(aux);
                    }
                }
            }
        }
        closedir (dir);
    } else {
        //No se puede abrir el directorio
        perror ("No se puede abrir el directorio");
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

    ArchivoImprimir = new QAction(Archivo);
    ArchivoImprimir->setText("Imprimir");
    Archivo->addAction(ArchivoImprimir);

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
    EdicionCopiar = new QAction(Edicion);
    EdicionCopiar->setText("Copiar");
    Edicion->addAction(EdicionCopiar);
    EdicionCortar = new QAction(Edicion);
    EdicionCortar->setText("Cortar");
    Edicion->addAction(EdicionCortar);
    EdicionPegar = new QAction(Edicion);
    EdicionPegar->setText("Pegar");
    Edicion->addAction(EdicionPegar);

    //Menu Formato
    Formato = new QMenu;
    Formato->setTitle("Formato");
    FormatoBase = new QAction(Formato);
    FormatoBase->setText("Base");
    Formato->addAction(FormatoBase);
    FormatoFuente = new QMenu(Formato);
    FormatoFuente->setTitle("Fuente");
    Formato->addMenu(FormatoFuente);
    FormatoMinimo = new QAction(Formato);
    FormatoMinimo->setText("Minimo");
    Formato->addAction(FormatoMinimo);


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

void MainWindow::CargaImagen()
{
    QObject* action = sender();
    if(action)
    {
        QString ruta = action->objectName();
        QString aux;
        aux.append(ruta);
        aux.append("Imagen.png");
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

void MainWindow::CargaTextBox()
{
    QObject* action = sender();
    if(action)
    {
        QString ruta = action->objectName();
        QString aux;
        aux.append(ruta);
        aux.append("Mapa.txt");
        QFile file(aux);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        file.readLine();
        int Xo,Yo,Xf,Yf;

        CuadrosDeTexto = new QList<QLineEdit*>;
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
            CuadrosDeTexto->append(cuadro);
        }

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

void MainWindow::Imprimir()
{
    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer, this);

    if (dialog->exec() != QDialog::Accepted)
        return;

    QPainter painter;

    //dibujar texto en el painter

    painter.begin(&printer);


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
