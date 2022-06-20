#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(0));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    // проверка ввода данных
    if ((ui->Xbeg->text().toDouble() == 0) and (ui->Xend->text().toDouble() == 0)) {
        QMessageBox::warning(this, "Ошибка!","Интервал равен 0!");
    }

    else if ( ((ui->Xbeg->text().toDouble() == false) and (ui->Xbeg->text() != "0"))
              or ((ui->Xend->text().toDouble() == false) and (ui->Xend->text() != "0")) or ( (ui->A->text().toDouble() == false) and (ui->A->text() != "0")) ) {
        QMessageBox::warning(this, "Ошибка!","Ошибка ввода!");
    }

    else if (ui->Xbeg->text().toDouble() < -99 or ui->Xbeg->text().toDouble() > 99) {
        QMessageBox::warning(this, "Ошибка!","Число введенное в первую колонку больше/меньше 99!");
    }

    else if (ui->Xend->text().toDouble() < -99 or ui->Xend->text().toDouble() > 99) {
        QMessageBox::warning(this, "Ошибка!","Число введенное во вторую колонку меньше 99!");
    }

    else if ( (ui->Xbeg->text().toDouble() >= ui->Xend->text().toInt()) or (ui->Xend->text().toDouble() <= ui->Xbeg->text().toDouble() )) {
        QMessageBox::warning(this, "Ошибка!","Некорректный интервал!");
    }

    else if ( (ui->A->text().toDouble() < -99) or (ui->A->text().toDouble() > 99)) {
        QMessageBox::warning(this, "Ошибка!","Введенное число 'a' < или > 99!");
    }

    else {
        // функция кнопки

        // записываем значения полученные с поля ввода в переменные
        a = ui->A->text().toDouble();
        Xbeg = ui->Xbeg->text().toDouble(); // начало X
        Xend = ui->Xend->text().toDouble(); // конец X
        Step = 0.1; // шаг

        N = (Xend - Xbeg) / Step + 2; //Вычисляем количество точек, которые будем отрисовывать

        QVector<double> x(N), y(N); //Массивы координат точек


        z = 0.1*((double)(rand()%10)/(double)10+(double)(rand()%10)); // вещественное число в диапозоне от 0 до 1


        int i = 0;
        for (double X = Xbeg; X <= Xend; X += Step) {
          x[i] = X;
          y[i] = a * sin(pow(X,3)) + z; //Формула нашей функции
          i++;
        }

        ui->widget->clearGraphs(); // очищаем графики
        ui->widget->addGraph(); // добавляем новый
        ui->widget->graph(0)->setData(x, y); // говорим, что отрисовать нужно график по нашим двум массивам x и y

        //Подписываем оси Ox и Oy
        ui->widget->xAxis->setLabel("x");
        ui->widget->yAxis->setLabel("y");

        //Установим область, которая будет показываться на графике
        ui->widget->xAxis->setRange(Xbeg, Xend); //Для оси Ox



        double minY = y[0], maxY = y[0];
        for (int i = 1; i < N; i++) {
          if (y[i] < minY) minY = y[i];
          if (y[i] > maxY) maxY = y[i];
        }
        ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy


        // перерисуем график на нашем widget
        ui->widget->replot();

        x.clear();
        y.clear();

    }




}

