//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015


#pragma once

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include "ui_Chess.h"

class Chess : public QMainWindow
{
    Q_OBJECT

public:
    Chess(QWidget *parent = nullptr);
    ~Chess();
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void drawChessboard(QPainter* painter);


private:
    int squareSize;
    QVector<QRect> squares;
    Ui::ChessClass ui;
};
