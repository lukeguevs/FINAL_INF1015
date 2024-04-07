//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015



#include <QWidget>
#include "ChessBoard.hpp"

class Chess : public QWidget
{
    Q_OBJECT
public:
    explicit Chess(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    ChessBoard* m_board;
};