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
    vector<pair<int, int>> getPossibleMoves() const;
    void setPossibleMoves(int positionY, int positionX, Type type);
    void setPossibleMoves(const vector<pair<int, int>>& possibleMoves);
    void addPossibleMove(int posX, int posY);
    void clearPossibleMoves();
    ~Piece();
protected:
    Type type;
    Color color;
    char32_t unicode;
    vector<pair<int, int>> possibleMoves;
};

