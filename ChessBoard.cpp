//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#include "ChessBoard.hpp"
using namespace std;

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

    void ChessBoard::mousePressEvent(QMouseEvent* event)
    {
        // Handle mouse click event (e.g., piece selection)
        // You can add your logic here
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

    void ChessBoard::addPiece(const QString& selectedPieceName)
    {

        // Get the mouse position on the board
        QPoint mousePos = mapFromGlobal(QCursor::pos());

        // Calculate the row and column of the square where the piece should be added
        int row = mousePos.y() / squareSize;
        int col = mousePos.x() / squareSize;

        // Add the piece to the board
        if (row >= 0 && row < 8 && col >= 0 && col < 8) {

            // Draw the piece on the board
            QPainter painter(this);
            painter.drawPixmap(squares[row * 8 + col], pieceImages[selectedPieceName]);

            // Update the board display
            update();
        }

    }
    ChessBoard::~ChessBoard() {
        delete buttons;
    }

    void ChessBoard::addPieceSlot(const QString& pieceName)
    {
        addPiece(pieceName);
    }

}