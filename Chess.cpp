//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#pragma once
#include <QWidget>
#include "Chess.h"


Chess::Chess(QWidget* parent) : QMainWindow(parent)
{
    chessboard = new ChessBoard(this);
    setCentralWidget(chessboard); // Set the chessboard as the central widget of the main window
}

void Chess::paintEvent(QPaintEvent* event)
{
    QMainWindow::paintEvent(event); // Call base class paintEvent
    // Optionally, you can handle additional painting in the Chess class
    // For example, drawing player information, game status, etc.
}