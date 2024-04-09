//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>

class ChessPieceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChessPieceWidget(QWidget* parent = nullptr);
public slots:
    void addPiece();
    void removePiece();
signals:
    void addPieceSignal(const QString& pieceName);
    void removePieceFromBoard(const QString& pieceName);
private:
    QListWidget* listWidget;

};