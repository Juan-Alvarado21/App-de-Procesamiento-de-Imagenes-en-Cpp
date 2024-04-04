#include "imageinfowindow.h"
#include "src/Transformations/transformaciones.h"
#include "ui_imageinfowindow.h"

using namespace std;

ImageInfoWindow::ImageInfoWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::ImageInfoWindow) {

  ui->setupUi(this);
  // Setteamos el logo
  setWindowIcon(QIcon("/home/juan/computer_vision/Analizador/Analizador_imagen/"
                      "docs/img/racoonized_logo.png"));
  // Declaramos las Gráficas en el Widget
  graphTotal = ui->CustomPlot->addGraph();
  graphRed = ui->CustomPlot->addGraph();
  graphGreen = ui->CustomPlot->addGraph();
  graphBlue = ui->CustomPlot->addGraph();

  graphTotal->setName("Plano de Gris");
  graphRed->setName("Canal R");
  graphGreen->setName("Canal G");
  graphBlue->setName("Canal B");

  // Asignación de color a la gráfica
  // El histograma total con color naranja y transparencia
  graphTotal->setPen(
      QPen(QColor(50, 50, 50, 200))); // Color Gris con algo de transparencia
  graphTotal->setBrush(QColor(
      50, 50, 50, 50)); // Pincel con el mismo color pero más transparencia

  // El histograma del canal rojo
  graphRed->setPen(QPen(QColor(255, 0, 0, 200))); // Rojo
  graphRed->setBrush(QColor(
      255, 0, 0, 50)); // Pincel con el mismo color pero más transparencia

  // El histograma del canal verde
  graphGreen->setPen(QPen(QColor(0, 255, 0, 200))); // Verde
  graphGreen->setBrush(QColor(
      0, 255, 0, 50)); // Pincel con el mismo color pero más transparencia

  // El histograma del canal azul
  graphBlue->setPen(QPen(QColor(0, 0, 255, 200))); // Azul
  graphBlue->setBrush(QColor(
      0, 0, 255, 50)); // Pincel con el mismo color pero más transparencia

  // Configuración de los ejes
  ui->CustomPlot->xAxis->setLabel("Valor de color");
  ui->CustomPlot->yAxis->setLabel("Frecuencia de Pixeles");
  ui->CustomPlot->xAxis->setRange(0, 255);
  ui->CustomPlot->yAxis->setRange(0, 7000);

  // Ajuste del Estilo de cuadricula y ejes
  ui->CustomPlot->xAxis->grid()->setPen(
      QPen(QColor(0, 0, 0, 25), 1, Qt::DotLine));
  ui->CustomPlot->yAxis->grid()->setPen(
      QPen(QColor(0, 0, 0, 25), 1, Qt::DotLine));
  ui->CustomPlot->xAxis->grid()->setSubGridPen(
      QPen(QColor(0, 0, 0, 25), 1, Qt::DotLine));
  ui->CustomPlot->yAxis->grid()->setSubGridPen(
      QPen(QColor(0, 0, 0, 25), 1, Qt::DotLine));
  ui->CustomPlot->xAxis->grid()->setSubGridVisible(true);
  ui->CustomPlot->yAxis->grid()->setSubGridVisible(true);

  // Propiedades del texto
  ui->CustomPlot->legend->setVisible(true);
  ui->CustomPlot->legend->setBrush(QColor(255, 255, 255, 150));
  ui->CustomPlot->axisRect()->insetLayout()->setInsetAlignment(
      0, Qt::AlignTop | Qt::AlignRight);

  // Refrescar el gráfico
  ui->CustomPlot->replot();

  setWindowTitle("Información de la imagen");
}

ImageInfoWindow::~ImageInfoWindow() { delete ui; }

// Método para actualizar la información a mostrarse en el Label de la ventana
// modal

void ImageInfoWindow::setImageInfo(QString img_output) {
  QImage image(img_output);

  if (!image.isNull()) {
    QString infoText;

    // Información del archivo usando QFileInfo
    QFileInfo fileInfo(img_output);

    // Nombre del archivo
    infoText += "Nombre del archivo: " + fileInfo.fileName() + "\n";
    // Ruta completa del archivo
    infoText += "Ruta del archivo: " + fileInfo.absoluteFilePath() + "\n";
    // Tamaño del archivo en bytes
    QFile file(img_output);
    if (file.open(QIODevice::ReadOnly)) {
      qint64 size = file.size(); // Tamaño en bytes
      infoText += "Tamaño del archivo: " + QString::number(size) + " bytes\n";
      file.close();
    }

    // Tamaño de la imagen
    infoText += "Tamaño de imagen: " + QString::number(image.width()) + "x" +
                QString::number(image.height()) + " píxeles\n";
    // Profundidad de color
    infoText +=
        "Profundidad de color: " + QString::number(image.depth()) + " bits\n";
    // Formato de la imagen
    infoText += "Formato: " + fileInfo.suffix() + "\n";
    // Canal alfa
    bool hasAlphaChannel = image.hasAlphaChannel();
    infoText += "Canal alfa (transparencia): " +
                QString(hasAlphaChannel ? "Sí" : "No") + "\n";

    // Densidad de píxeles por pulgada (DPI)
    qreal xDPI =
        image.dotsPerMeterX() != 0 ? image.dotsPerMeterX() * 0.0254 : 0;
    qreal yDPI =
        image.dotsPerMeterY() != 0 ? image.dotsPerMeterY() * 0.0254 : 0;
    infoText += "Densidad de píxeles (DPI): X: " + QString::number(xDPI) +
                ", Y: " + QString::number(yDPI) + "\n";

    // Actualizar el QLabel con la información de la imagen
    ui->imageInfoLabel->setText(infoText);

    // Generar Histograma
    GenerarHistograma(img_output);
    GenerarColorScatterPlot(img_output);

  } else {
    // Manejo del caso en que la imagen no se pueda cargar
    QMessageBox::warning(this, tr("Abrir imagen"),
                         tr("El archivo no se pudo leer:(  ."));
  }
}

// Método para visualizar bitmap

pxl **ImageInfoWindow::procesar_bitmap(QString img_path) {
  QImage image(img_path);
  if (image.isNull()) {
    QMessageBox::warning(nullptr, tr("Abrir imagen"),
                         tr("El archivo no se pudo leer :(."));
    return nullptr; // Retorna nullptr si la imagen no se pudo cargar
  }

  const int width = image.width();
  const int height = image.height();

  if (width == 0 || height == 0) {
    qDebug() << "La imagen está vacía.";
    return nullptr;
  }

  // Asignación dinámica de memoria para el mapa de bits
  pxl **bitmap = new pxl *[width];
  for (int i = 0; i < width; ++i) {
    bitmap[i] = new pxl[height];
  }

  // Recuperar el color y pasarlo a la estructura rgb
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      QRgb pixelColor = image.pixel(i, j);
      bitmap[i][j] = {qRed(pixelColor), qGreen(pixelColor), qBlue(pixelColor)};
      // qDebug() << "(" << bitmap[i][j].r << "," << bitmap[i][j].g << "," <<
      // bitmap[i][j].b << "), ";
    }
    qDebug() << "\n";
  }

  return bitmap;
}

// Generar y settear el histograma de una imagen

void ImageInfoWindow::GenerarHistograma(QString img_path) {

  QImage image(img_path);
  Transformaciones transformacion;
  pxl **map = procesar_bitmap(img_path);

  QVector<QVector<int>> histogramas(4, QVector<int>(256, 0));
  QVector<double> x(256), yTotal(256), yRed(256), yGreen(256), yBlue(256);

  for (int i = 0; i < image.height(); i++) {
    for (int j = 0; j < image.width(); j++) {
      int gris = ((map[j][i].r + map[j][i].g + map[j][i].b) / 3); // Histograma
                                                                  // 0
      int rojo = map[j][i].r;  // Histograma 1
      int verde = map[j][i].g; // Histograma 2
      int azul = map[j][i].b;  // Histograma 3

      histogramas[0][gris]++;
      histogramas[1][rojo]++;
      histogramas[2][azul]++;
      histogramas[3][verde]++;
    }
  }

  // Llenamos los vectores de datos para cada histograma y el de valores x
  for (int i = 0; i < 256; ++i) {
    x[i] = i; // Los valores de intensidad de x son siempre de 0 a 255
    yTotal[i] = histogramas[0][i];
    yRed[i] = histogramas[1][i];
    yGreen[i] = histogramas[2][i];
    yBlue[i] = histogramas[3][i];
  }

  // Seteamos los datos en las gráficas de QCustomPlot
  graphTotal->setData(x, yTotal);
  graphRed->setData(x, yRed);
  graphGreen->setData(x, yGreen);
  graphBlue->setData(x, yBlue);

  // Finalmente, llamamos a replot para actualizar el gráfico
  ui->CustomPlot->replot();

  // Limpieza de memoria para el mapa de bits
  for (int i = 0; i < image.width(); i++) {
    delete[] map[i]; // Liberar cada array de pxl
  }
  delete[] map; // Liberar el array de punteros
}

void ImageInfoWindow::GenerarColorScatterPlot(QString img_path) {
  QImage image(img_path);

  // Crear un nuevo gráfico para los puntos de dispersión
  QCPGraph *colorScatter = ui->ScatterPlot->addGraph();
  colorScatter->setLineStyle(QCPGraph::lsNone); // Sin líneas, solo puntos
  colorScatter->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 4)); // Estilo de los puntos
  colorScatter->setPen(QPen(
      QColor(255, 150, 0, 200))); // Color naranja con algo de transparencia
  colorScatter->setBrush(QColor(
      255, 150, 0, 50)); // Pincel con el mismo color pero más transparencia

  QVector<double> x, y;
  QVector<QColor> colors;

  for (int i = 0; i < image.height(); ++i) {
    for (int j = 0; j < image.width(); ++j) {
      QColor color = image.pixelColor(j, i);

      // Añadir coordenadas y colores a los vectores
      x.append(color.red());
      y.append(color.green());
      colors.append(color); // Utilizaremos este color más adelante
    }
  }

  colorScatter->setData(x, y);

  // Configurar el eje X y Y
  ui->ScatterPlot->xAxis->setLabel("Niveles de Rojo");
  ui->ScatterPlot->yAxis->setLabel("Niveles de Verde");

  // Ajustar los rangos de los ejes
  ui->ScatterPlot->xAxis->setRange(0, 255);
  ui->ScatterPlot->yAxis->setRange(0, 255);

  // Actualizar el gráfico
  ui->ScatterPlot->replot();
}
