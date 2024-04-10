//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include "ChessPieceWidget.hpp"
#include "Chess.h"

using namespace board;

Chess::Chess(QWidget* parent) : QMainWindow(parent)
{
    chessboard = new ChessBoard(this);
    setCentralWidget(chessboard); // Set the chessboard as the central widget of the main window

    // Create a ChessPieceWidget
    chessPieceWidget = new ChessPieceWidget(this);

    // Add the pieces widget to the main window
    QWidget* container = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(container);
    layout->addWidget(chessboard);
    layout->addWidget(chessPieceWidget);
    layout->setContentsMargins(0, 0, 0, 0); // Remove any margins around the layout
    container->setLayout(layout); // Set the layout on the container
    setCentralWidget(container);
}

Chess::~Chess() {
   delete chessboard;
  delete chessPieceWidget;
}

void Chess::paintEvent(QPaintEvent* event)
{
    QMainWindow::paintEvent(event); 

}