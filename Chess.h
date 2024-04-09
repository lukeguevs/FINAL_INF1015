//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#include <QMainWindow>
#include "ChessBoard.hpp"
#include "ChessPieceWidget.hpp"

using namespace board;

class Chess : public QMainWindow
{
    Q_OBJECT
public:
    explicit Chess(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    ChessBoard* chessboard;
    ChessPieceWidget* chessPieceWidget;
};