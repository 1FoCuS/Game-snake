#ifndef SNAKE_H
#define SNAKE_H

#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTime>
#include <QPushButton>
#include <array>

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
    QPushButton *button_exit = nullptr;

    QImage dot;
    QImage head_snake;
    QImage apple;

    static constexpr int B_WIDTH    = 500;  //< size playground
    static constexpr int B_HEIGHT   = 500;
    static constexpr int DOT_SIZE   = 10;   //< size apple and snake parts
    static constexpr int ALL_DOTS   = (B_WIDTH*B_HEIGHT) / (DOT_SIZE*DOT_SIZE);
    static constexpr int RAND_POS   = 29;   //< for random
    static constexpr int DELAY      = 140;  //< game speed

    int timerId;
    int dots;

    std::array<int, ALL_DOTS> x;    //< position all parts snake
    std::array<int, ALL_DOTS> y;
    int apple_x;
    int apple_y;


    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;
    bool inGame = false;
    bool is_defeat = false;

    void loadImages();

    void locate_new_apple();
    void checkApple();
    void checkCollision();
    void move();
    void drawing_playground();
    void gameOver(QPainter &);

    void create_button_start();
    void create_button_exit();
};
#endif // SNAKE_H
