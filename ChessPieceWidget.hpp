//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>

class ChessPieceWidget : public QWidget
{
    Q_OBJECT

public:
    ChessPieceWidget(QWidget* parent = nullptr);

public slots:
    void addPiece();

    void removePiece();
};