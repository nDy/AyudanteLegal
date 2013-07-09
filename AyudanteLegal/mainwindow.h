#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollBar>

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
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void GenerarMenu();
    void GenerarConexiones();
public slots:
    void CargaPlanilla();
    void ZoomIn();
    void ZoomOut();
    
private:
            QPixmap* pic;
    Ui::MainWindow *ui;
    //Menu
        QMenu* Archivo;
            QMenu* ArchivoNuevo;
                QList<QAction*> ArchivoNuevoLista;
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
                QList<QAction*> FormatoFuenteLista;
            QAction* FormatoBase;
            QAction* FormatoMinimo;
};

#endif // MAINWINDOW_H
