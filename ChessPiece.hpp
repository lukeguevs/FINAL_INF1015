//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015


#pragma once
#include <QObject>
#include <QWidget>
#include <QPixmap>

class ChessPiece : public QObject {

	Q_OBJECT;

public:
    ChessPiece(QObject* parent = nullptr);
    QPixmap pixmap() const;
    void setPixmap(const QPixmap& pixmap);
    void setPosition(const QPoint& position);
    QPoint position() const;

private:
    QPixmap m_pixmap;
    QPoint m_position;

};
