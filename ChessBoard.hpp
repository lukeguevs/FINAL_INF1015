//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#pragma once
#include <QWidget>
#include <QVector>
#include <QMap>
#include <QRect>
#include <QPainter>
#include <QMouseEvent>
#include <QDir>
#include "ChessPieceWidget.hpp"
#include "Piece.cpp"
#include "Rook.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Pawn.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"


using 

namespace board {

    class ChessBoard : public QWidget
    {
        Q_OBJECT
    public:
        ChessBoard(QWidget* parent);
        ~ChessBoard();

        void setSquareSize(int size);
        void addPiece(const QString& pieceName);
        int squareSize;
        QVector<QRect> squares;
        ChessPieceWidget* chessPieceWidget;
        QPushButton* buttons[8][8];
        void addPieces();


    protected:
        void paintEvent(QPaintEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;

    public slots:
        void addPieceSlot(const chess::Piece& pieceName);
        void drawChessboard(QPainter* painter);
    };

}