#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTime>
#include <QPushButton>

class Snake : public QWidget
{
    //Q_OBJECT
public:
    Snake(QWidget *parent = nullptr);
    virtual ~Snake() {};
private slots:
         void initGame();
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
private:
    QPushButton *button_start = nullptr;

    QImage dot;
    QImage head_snake;
    QImage apple;

    static const int B_WIDTH    = 500;  //< size playground
    static const int B_HEIGHT   = 500;
    static const int DOT_SIZE   = 10;   //< size apple and snake parts
    static const int ALL_DOTS   = (B_WIDTH*B_HEIGHT) / (DOT_SIZE*DOT_SIZE);
    static const int RAND_POS   = 29;   //< for random
    static const int DELAY      = 140;  //< game speed

    int timerId;
    int dots;
    int apple_x;
    int apple_y;

    int x[ALL_DOTS];    //< position oll parts snake
    int y[ALL_DOTS];

    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;
    bool inGame;

    void loadImages();

    void locateApple();
    void checkApple();
    void checkCollision();
    void move();
    void doDrawing();
    void gameOver(QPainter &);

    void create_button_start();
};
#endif // SNAKE_H
