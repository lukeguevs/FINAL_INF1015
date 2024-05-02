//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#pragma once
#include <unordered_map>
#include <QWidget>
#include <QVector>
#include <QMap>
#include <QRect>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <QDir>
#include "ChessPieceWidget.hpp"
#include "King.hpp"
#include "Piece.hpp"
#include "Tour.hpp"
#include "Knight.hpp"
#include "RAII.hpp"

namespace board {

    class ChessBoard : public QWidget
    {
        Q_OBJECT
    public:
        ChessBoard(QWidget* parent);
        ~ChessBoard();
        ChessBoard();

        void setSquareSize(int size);
        int squareSize;
        QVector<QRect> squares;
        QMap<QString, QPixmap> pieceImages;
        ChessPieceWidget* chessPieceWidget;
        QPushButton* buttons[8][8];
        Piece::Color getCaseColor(int posX, int posY);
        void isCheck();
        void findPieces();
        
    protected:
        
        void paintEvent(QPaintEvent* event) override;
        //void mousePressEvent(QMouseEvent* event) override;
    private:
        vector<Piece> piecesBoard;
        bool isDisplay_ = false;
        Piece::Color turnColor_ = Piece::Color::WHITE;
    public slots:
        void addPieceSlot(Piece& piece, int posX, int posY);
        void drawChessboard(QPainter* painter);
        void displayPossibleMoves(Piece& piece, int posX, int posY);
    };

}