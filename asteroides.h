
#include <chrono>


/*
Objetivos :
    Generar asteroides basado en multiples condiciones
    -deben ser aleatorio en posición y pixmap (los pixmas actuales son temporales y deben ser modificados)
        por otros que tengan más paleta de color con la escena.
    -debe estar sobrecargado para el evento final (cuando el personaje se debe morir si o sí)
        NOTA : fase experimental del final del juego , 1 nivel.
            BUGS : se debe corregir la visualización y el punto de choque.
                   Dimensiones , y aceleración o tiempo de caida además del pixmap.
*/

class asteroides :public QObject , public QGraphicsRectItem
{
    Q_OBJECT

private:
    // ---------- Atributos privados de la clase -------------------
    QMediaPlayer *sonido;
    QPixmap *meteoros;
    QTimer *timer;

    signed short int anguloRotacion , factorCaida;
    bool fuegoAves , cuerpoRotando, animado ;
    //Animacion de los Meteoros
    qreal ancho, alto, frame , limite;

    // ---------- Metodos privados de la clase ------------------------
    void generarAspecto();
    void animarMeteoro();

public:
    asteroides(bool sound=true); // defecto
    asteroides(short int n); // animado
    asteroides(qreal x, qreal y); // aves (minibombs)

    ~asteroides();

    //Animacion de los meteoros
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private slots:
    void moverAsteroide();

};

#endif // ASTEROIDES_H
