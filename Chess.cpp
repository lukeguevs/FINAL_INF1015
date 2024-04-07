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

    QDir dir(":/Chess/");
    QStringList filters;
    filters << "*.png";
    dir.setNameFilters(filters);
    QStringList pieceFiles = dir.entryList();

    for (const QString& file : pieceFiles) {
        QString pieceName = file.left(file.lastIndexOf("."));
        pieceImagePaths[pieceName] = ":/Chess/" + file;
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
    if (event->button() == Qt::LeftButton) {
        
        int row = event->y() / squareSize;
        int col = event->x() / squareSize;
        
    }
}

void Chess::drawChessboard(QPainter* painter)
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

void Chess::drawPieces(QPainter* painter)
{
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row == 0 || row == 7) && (col % 7 == 0)) {
                QString pieceName = (row == 0) ? "Rook-Black" : "Rook-White";
                QPixmap pieceImage(pieceImagePaths[pieceName]);
                painter->drawPixmap(squares[row * 8 + col], pieceImage);
            }
        }
    }
}


Chess::~Chess()
{}
