//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#include <QWidget>
#include <QVector>
#include <QMap>
#include <QRect>
#include <QPainter>
#include <QMouseEvent>
#include <QDir>

class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoard(QWidget* parent = nullptr);

    void setSquareSize(int size);
    void setPieceImage(const QString& pieceName, const QPixmap& image);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    int squareSize;
    QVector<QRect> squares;
    QMap<QString, QPixmap> pieceImages;

    void drawChessboard(QPainter* painter);
    void drawPieces(QPainter* painter);
};

