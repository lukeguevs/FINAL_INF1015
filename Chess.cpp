//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015


#include "Chess.h"

Chess::Chess(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    squareSize = 50;

    // Create the squares
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            squares.append(QRect(col * squareSize, row * squareSize, squareSize, squareSize));
        }
    }

}

void Chess::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    drawChessboard(&painter);
}

void Chess::mousePressEvent(QMouseEvent *event)
{
    // Handle mouse clicks
    if (event->button() == Qt::LeftButton) {
        // Calculate the square clicked
        int row = event->y() / squareSize;
        int col = event->x() / squareSize;
        // Perform action based on the square clicked
        // For example, you can move pieces here
    }
}

void Chess::drawChessboard(QPainter* painter)
{
    // Draw the chessboard
    QColor lightColor(209, 139, 71); // Light brown color
    QColor darkColor(255, 206, 158); // Dark brown color

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


Chess::~Chess()
{}
