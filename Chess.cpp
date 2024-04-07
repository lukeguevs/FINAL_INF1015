//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#include "Chess.h"

Chess::Chess(QWidget* parent) : QWidget(parent)
{
    m_board = new ChessBoard(this);
}

void Chess::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    // Optionally, you can handle additional painting in the Chess class
    // For example, drawing player information, game status, etc.
}
