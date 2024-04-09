//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#include "ChessBoard.hpp"

namespace board {

    ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent), squareSize(50)
    {
        // Create the squares for an 8x8 chessboard
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                squares.append(QRect(col * squareSize, row * squareSize, squareSize, squareSize));
            }
        }

        // Set a fixed size for the widget
        setFixedSize(8 * squareSize, 8 * squareSize);

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

        connect(pieceWidget, &ChessPieceWidget::addPiece, this, &ChessBoard::addPiece);
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
        drawPieces(&painter);
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

    void ChessBoard::addPiece()
    {
        // Get the selected piece name from the ChessPieceWidget
        QString selectedPieceName = pieceWidget->getSelectedPieceName();

        // Get the mouse position on the board
        QPoint mousePos = mapFromGlobal(QCursor::pos());

        // Calculate the row and column of the square where the piece should be added
        int row = mousePos.y() / squareSize;
        int col = mousePos.x() / squareSize;

        // Add the piece to the board
        if (row >= 0 && row < 8 && col >= 0 && col < 8 && !pieceImages.contains(selectedPieceName)) {
            pieceImages[selectedPieceName] = QPixmap();
            update();
        }
    }

    void ChessBoard::setPieceImage(const QString& pieceName, const QPixmap& image)
    {
        pieceImages[pieceName] = image;
    }

}