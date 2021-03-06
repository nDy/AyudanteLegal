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
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scaleFactor = 1.0;

    this->GenerarMenu();

    this->GenerarConexiones();

    this->DocumentoGuardado = false;
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

    //ZoomConections
    connect(VerZoomIn, SIGNAL(triggered()), this, SLOT(ZoomIn()));
    connect(VerZoomOut, SIGNAL(triggered()), this, SLOT(ZoomOut()));

    //FileConections
    connect(ArchivoImprimir, SIGNAL(triggered()), this, SLOT(Imprimir()));
    connect(ArchivoAbrir, SIGNAL(triggered()), this, SLOT(Abrir()));
    connect(ArchivoGuardar, SIGNAL(triggered()), this, SLOT(Guardar()));
    connect(ArchivoGuardarComo, SIGNAL(triggered()), this, SLOT(GuardarComo()));


}

void MainWindow::GenerarMenu(){
    //Menu Archivo
    Archivo = new QMenu;
    Archivo->setTitle("Archivo");

    ArchivoNuevo = new QMenu;
    ArchivoNuevo->setTitle("Nuevo");

    //Carga de planillas

    QDir Dir;
    QString path;
    path = Dir.homePath();
    path.append("/Planillas");
    Dir.setPath(path);

    QFileInfoList list = Dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName().size()>2){
            QAction* aux;
            static QString* file;
            file = new QString();
            file->append("../AyudanteLegal/Planillas/");
            file->append(fileInfo.fileName());
            file->append("/");
            aux = new QAction(ArchivoNuevo);
            aux->setText(fileInfo.fileName());
            aux->setObjectName(*file);
            ArchivoNuevo->addAction(aux);
        }
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

    DocumentoGuardado = false;
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
        Pic = new QPixmap(aux);
        RutaPic = new QString();
        RutaPic->append(aux);
        label->setPixmap(*Pic);

        QWidget* w;
        w = new QWidget();
        ui->scrollArea->setWidget(w);
        QVBoxLayout* lay;
        lay = new QVBoxLayout();
        w->setLayout(lay);
        w->layout()->addWidget(label);

        scaleImage(0.323);
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

        int Xo,Yo,Xf,Yf;

        CuadrosDeTexto = new QList<QLineEdit*>;
        while (!file.atEnd()) {
            QString linea = file.readLine();
            //parseline
            if (linea.at(0)!='#'&&!linea.isEmpty()){
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
                QFont* BaseFont;
                BaseFont = new QFont("Times", 15);
                cuadro->setFont(*BaseFont);
                CuadrosDeTexto->append(cuadro);
            }
        }
        file.close();
    }

    //ResizeTextConections
    QList<QLineEdit*>::iterator j;
    for (j = CuadrosDeTexto->begin(); j != CuadrosDeTexto->end(); ++j) {
        QObject::connect((*j), SIGNAL(textChanged(QString)),
                         this, SLOT(AjustarTexto()));
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
    QPrinter* printer;
    printer = new QPrinter(QPrinter::PrinterMode::ScreenResolution);
    QPrintDialog *dialog = new QPrintDialog(*&printer, this);

    if (dialog->exec() != QDialog::Accepted)
        return;

    QPainter painter;

    painter.begin(*&printer);

    //dibujar texto en el painter
    QList<QLineEdit*>::iterator j;
    for (j = CuadrosDeTexto->begin(); j != CuadrosDeTexto->end(); ++j) {
        painter.setFont((*j)->font());
        painter.drawText((*j)->geometry().x(),(*j)->geometry().y()+(*j)->height()/2,(*j)->text());
    }

    painter.end();

}

void MainWindow::Abrir()
{
    QString filename = QFileDialog::getOpenFileName(this);

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text)){
        //desechar cabeza de imagen
        file.readLine();
        //cargar imagen
        QString ruta;
        ruta.append(file.readLine());
        //desechar cabeza de cajas de texto
        file.readLine();
        //Cargar cajas de texto
        //cerrar archivo
        file.close();
    }

}


void MainWindow::Guardar()
{
    if(!DocumentoGuardado){
        GuardarComo();
        DocumentoGuardado = true;
    }

}

void MainWindow::GuardarComo()
{
    QString nombre;
    nombre = QFileDialog::getSaveFileName(this, tr("Save File"),
                                          "/home/untitled.LegalMap",
                                          tr("Legal Map File (*.LegalMap)"));

    QFile file(nombre);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
        printf ("Open file failed\n");

    }

    QTextStream out(&file);

    //imagen
    out<<"IMGDATA="<<"\n";
    out<<RutaPic->toStdString().c_str()<<"\n";
    //separador
    out<<"FILEDATA="<<"\n";
    //data
    QList<QLineEdit*>::iterator j;
    for (j = CuadrosDeTexto->begin(); j != CuadrosDeTexto->end(); ++j) {
        out << (*j)->text()<<"|"<<(*j)->geometry().x()<<"|"<<(*j)->geometry().y()<<"|"<<(*j)->height()<<"|"<<(*j)->width() << "\n";
    }
    file.close();
}

void MainWindow::AjustarTexto()
{
    QObject* action = sender();
    if(action)
    {
        QFont font;
        font = ((QLineEdit*)action)->font();
        QString str;
        str = ((QLineEdit*)action)->text();

        QFontMetrics fm(font);

        int width=fm.width(str);

        if ((width >= ((QLineEdit*)action)->width())){
            if(font.pointSize()<=(0.20)){
                ((QLineEdit*)action)->backspace();
            }else{
                qreal aux;
                aux = font.pointSize()-(0.15);
                font.setPointSize(aux);
                ((QLineEdit*)action)->setFont(font);
            }

            QFontMetrics auxfm(font);
            width=auxfm.width(str);
        }

    }
}

void MainWindow::scaleImage(double factor){
    scaleFactor *= factor;
    label->setPixmap(Pic->scaled(Pic->width()*scaleFactor,Pic->height()*scaleFactor));

    adjustScrollBar(ui->scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui->scrollArea->verticalScrollBar(), factor);

}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
