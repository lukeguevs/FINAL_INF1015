//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#include "ChessBoard.hpp"

ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent), squareSize(50)
{
    // Create the squares for an 8x8 chessboard
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            squares.append(QRect(col * squareSize, row * squareSize, squareSize, squareSize));
        }
    }

    // Load piece images
    QDir dir(":/images/Chess/");
    QStringList filters;
    filters << "*.png";
    dir.setNameFilters(filters);
    QStringList pieceFiles = dir.entryList();

    for (const QString& file : pieceFiles) {
        QString pieceName = file.left(file.lastIndexOf("."));
        QPixmap pieceImage(":/images/Chess/" + file);
        pieceImages[pieceName] = pieceImage;
    }
}

void ChessBoard::setSquareSize(int size)
{
    squareSize = size;
}

void ChessBoard::setPieceImage(const QString& pieceName, const QPixmap& image)
{
    pieceImages[pieceName] = image;
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

void ChessBoard::drawPieces(QPainter* painter)
{

}
