//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//�cole Polytechnique de Montr�al
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

    // Load piece image paths
    QDir dir(":/Images/");
    QStringList filters;
    filters << "*.png";
    dir.setNameFilters(filters);
    QStringList pieceFiles = dir.entryList();

    for (const QString& file : pieceFiles) {
        QString pieceName = file.left(file.lastIndexOf("."));
        pieceImagePaths[pieceName] = ":/pieces/" + file;
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


Chess::~Chess()
{}
