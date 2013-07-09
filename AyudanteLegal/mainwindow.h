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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollBar>
#include <QLineEdit>
#include <QStackedLayout>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void scaleImage(double factor);
    QLabel* label;
    double scaleFactor;
    void GenerarMenu();
    void GenerarConexiones();
    void CargaImagen();
    void CargaTextBox();
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

public slots:
    void CargaPlanilla();
    void ZoomIn();
    void ZoomOut();
    
private:
    //ui
    Ui::MainWindow *ui;
    //Menu
    QMenu* Archivo;
    QMenu* ArchivoNuevo;
    QList<QAction*>* ArchivoNuevoLista;
    QAction* ArchivoAbrir;
    QAction* ArchivoImprimir;
    QAction* ArchivoGuardar;
    QAction* ArchivoGuardarComo;

    QMenu* Ver;
    QAction* VerZoomIn;
    QAction* VerZoomOut;
    QAction* VerHoja;
    QAction* VerPagina;
    QAction* VerEdicion;

    QMenu* Edicion;
    QAction* EdicionCopiar;
    QAction* EdicionCortar;
    QAction* EdicionPegar;

    QMenu* Formato;
    QMenu* FormatoFuente;
    QList<QAction*>* FormatoFuenteLista;
    QAction* FormatoBase;
    QAction* FormatoMinimo;
    //misc
    QPixmap* pic;

};

#endif // MAINWINDOW_H
