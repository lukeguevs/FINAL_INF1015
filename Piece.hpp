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

    class Piece : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString symbol MEMBER symbol)
    public:
        enum class Type { PAWN, ROOK, KING, QUEEN, KNIGHT, BISHOP };
        enum class Color { WHITE, BLACK };

        Piece(Type type, Color color, const QString& unicode);

        Type getType() const;
        Color getColor() const;
        virtual QString getSymbol() const = 0;

    protected:
        Type type;
        Color color;
        QString symbol; // Unicode character

        /*White King : \u2654
        White Queen : \u2655
        White Rook : \u2656
        White Bishop : \u2657
        White Knight : \u2658
        White Pawn : \u2659
        Black King : \u265A
        Black Queen : \u265B
        Black Rook : \u265C
        Black Bishop : \u265D
        Black Knight : \u265E
        Black Pawn : \u265F*/
    };

}