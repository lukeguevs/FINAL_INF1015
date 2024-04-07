//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//�cole Polytechnique de Montr�al
//Projet Final de INF1015


#pragma once

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include <QMouseEvent>
//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//�cole Polytechnique de Montr�al
//Projet Final de INF1015

#include "ui_Chess.h"

#include <QDir>

class Chess : public QMainWindow
{
    Q_OBJECT

public:
    Chess(QWidget *parent = nullptr);
    ~Chess();
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void drawChessboard(QPainter* painter);
    void drawPieces(QPainter* painter);


private:
    int squareSize;
    // Store image file paths for each piece
    QMap<QString, QString> pieceImagePaths;
    QVector<QRect> squares;
    Ui::ChessClass ui;
};
