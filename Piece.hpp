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
#include <vector>
using namespace std;


namespace chess {

    class Piece
    {
    public:
        enum class Type {ROOK, KING, KNIGHT};
        enum class Color { WHITE, BLACK };
        
        Piece(Type type, Color color);
        Type getType() const;
        Color getColor() const;
        char32_t getUnicode() const ;
        void setColor(Color newColor);
        void setType(Type newType);
        void setUnicode(char32_t newUnicode);
        vector<pair<int, int>> getPossibleMoves(int positionY, int positionX,Type type) const;
        ~Piece();
    protected:
        Type type;
        Color color;
        char32_t unicode;
    };

}