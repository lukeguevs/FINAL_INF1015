//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015


#pragma once

#include "Piece.hpp"
namespace chess {

    class Piece {
    public:
        enum class Type { King, Queen, Rook, Bishop, Knight, Pawn };
        enum class Color { White, Black };

        Piece(Type type, Color color, const QString& unicode)
            : type(type), color(color), pieceUnicode(unicode) {}

        QString getPieceUnicode() const {
            return pieceUnicode;
        }

        Type getType() const {
            return type;
        }

        Color getColor() const {
            return color;
        }

    private:
        Type type;
        Color color;
        QString pieceUnicode;

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
