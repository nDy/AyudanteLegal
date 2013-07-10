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
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QFileDialog>
#include <QTextStream>

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
    void Imprimir();
    void Abrir();
    void Guardar();
    void GuardarComo();
    
private:
    //ui
    Ui::MainWindow *ui = nullptr;
    //Menu
    QMenu* Archivo = nullptr;
    QMenu* ArchivoNuevo = nullptr;
    QList<QAction*>* ArchivoNuevoLista = nullptr;
    QAction* ArchivoAbrir = nullptr;
    QAction* ArchivoImprimir = nullptr;
    QAction* ArchivoGuardar = nullptr;
    QAction* ArchivoGuardarComo = nullptr;

    QMenu* Ver = nullptr;
    QAction* VerZoomIn = nullptr;
    QAction* VerZoomOut = nullptr;
    QAction* VerHoja = nullptr;
    QAction* VerPagina = nullptr;
    QAction* VerEdicion = nullptr;

    QMenu* Edicion = nullptr;
    QAction* EdicionCopiar = nullptr;
    QAction* EdicionCortar = nullptr;
    QAction* EdicionPegar = nullptr;

    QMenu* Formato = nullptr;
    QMenu* FormatoFuente = nullptr;
    QList<QAction*>* FormatoFuenteLista = nullptr;
    QAction* FormatoBase = nullptr;
    QAction* FormatoMinimo = nullptr;
    //misc
    QPixmap* Pic = nullptr;
    QString* RutaPic = nullptr;
    QList<QLineEdit*>* CuadrosDeTexto = nullptr;
    bool DocumentoGuardado;

};

#endif // MAINWINDOW_H
