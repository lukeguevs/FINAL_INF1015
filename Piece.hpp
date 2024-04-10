//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015


#pragma once
#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QDir>

namespace chess {

    class Piece
    {
    public:
        enum class Type { PAWN, ROOK, KING, QUEEN, KNIGHT, BISHOP };
        enum class Color { WHITE, BLACK };

        Piece(Type type, Color color);
        void setPieceImage(const QPixmap& image);
        Type getType() const;
        Color getColor() const;
        virtual QString getName() const = 0;

    protected:
        QPixmap pieceImage;
        QMap<QString, QPixmap> pieceImages;
        Type type;
        Color color;
    };

}