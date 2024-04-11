//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#include "ChessBoard.hpp"
using namespace std;
using namespace chess;

namespace board {

    ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent), squareSize(50)
    {
        // Create the squares for an 8x8 chessboard
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                squares.append(QRect(col * squareSize, row * squareSize, squareSize, squareSize));

                buttons[row][col] = new QPushButton(this);
                buttons[row][col]->setGeometry(col * squareSize, row * squareSize, squareSize, squareSize);
                buttons[row][col]->setFlat(true);
                buttons[row][col]->setVisible(true);
            }
        }

        // Set a fixed size for the widget
        setFixedSize(8 * squareSize, 8 * squareSize);

    }

    void ChessBoard::setSquareSize(int size)
    {
        squareSize = size;
    }


    void ChessBoard::paintEvent(QPaintEvent* event)
    {
        Q_UNUSED(event);
        QPainter painter(this);
        drawChessboard(&painter);
    }

    void ChessBoard::drawChessboard(QPainter* painter)
    {
        QColor lightColor(209, 139, 71);
        QColor darkColor(255, 206, 158);

        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if ((row + col) % 2 == 0) {
                    painter->setBrush(lightColor);
                }
                else {
                    painter->setBrush(darkColor);
                }
                painter->drawRect(squares[row * 8 + col]);
            }
        }
    }

    ChessBoard::~ChessBoard() {
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                delete buttons[row][col];
            }
        }
    }

    void ChessBoard::addPieceSlot(const Piece& pieceName)
    {
        addPiece(pieceName);
    }

}