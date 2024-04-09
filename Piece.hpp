//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015


#pragma once
#include <QObject>
#include <QWidget>
#include <QPixmap>

namespace chess {

    class Piece
    {
    public:
        enum class Type { Pawn, Rook, Knight, Bishop, Queen, King };
        enum class Color { White, Black };

        Piece(Type type, Color color);
        virtual ~Piece();

        Type getType() const;
        Color getColor() const;
        virtual QString getName() const = 0;

    protected:
        Type type;
        Color color;
    };

}