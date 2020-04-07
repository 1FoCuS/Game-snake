#include "snake.h"

Snake::Snake(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color:black;");
    create_button_start();

    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;

    resize(B_WIDTH, B_HEIGHT);
    loadImages();

    connect(button_start, &QPushButton::clicked, this, &Snake::initGame);
}

void Snake::loadImages()
{
    apple.load("apple.png");
    dot.load("dot.png");
    head_snake.load("head.png");
}

void Snake::initGame()
{
    if (button_start!=nullptr) delete button_start;
    dots = 3;
    for (int z = 0; z < dots; z++)
    {
        x[z] = 50 - z * 10;
        y[z] = 50;
    }

    locateApple();

    timerId = startTimer(DELAY);
}

void Snake::checkApple()
{

    if ((x[0] == apple_x) && (y[0] == apple_y))
    {
        dots++;
        locateApple();
    }
}

void Snake::move()
{
    for (int z = dots; z > 0; z--)
    {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    if (leftDirection)
    {
        x[0] -= DOT_SIZE;
    }

    if (rightDirection)
    {
        x[0] += DOT_SIZE;
    }

    if (upDirection)
    {
        y[0] -= DOT_SIZE;
    }

    if (downDirection)
    {
        y[0] += DOT_SIZE;
    }
}

void Snake::checkCollision()
{
    for (int z = dots; z > 0; z--)
    {
        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z]))
        {
            inGame = false;
        }
    }

    if (y[0] >= B_HEIGHT)
    {
        inGame = false;
    }

    if (y[0] < 0)
    {
        inGame = false;
    }

    if (x[0] >= B_WIDTH)
    {
        inGame = false;
    }

    if (x[0] < 0)
    {
        inGame = false;
    }

    if(!inGame)
    {
        killTimer(timerId);
    }
}

void Snake::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    doDrawing();
}

void Snake::doDrawing()
{
    QPainter qp(this);
    if (inGame)
    {
        qp.drawImage(apple_x, apple_y, apple);
        for (int z = 0; z < dots; z++)
        {
            if (z == 0)
            {
                qp.drawImage(x[z], y[z], head_snake);
            } else
            {
                qp.drawImage(x[z], y[z], dot);
            }
        }

    } else
    {
        gameOver(qp);
    }
}

void Snake::gameOver(QPainter &qp)
{
    QString message = "GAME OVER";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    qp.setPen(QColor(Qt::white));
    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);

//    button_start = new QPushButton("start", this);
//    button_start->setGeometry(50, 40, 75, 30);
//    connect(button_start, &QPushButton::clicked, this, &Snake::initGame);
}

void Snake::locateApple()
{
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS;
    apple_x = (r * DOT_SIZE);

    r = qrand() % RAND_POS;
    apple_y = (r * DOT_SIZE);
}

void Snake::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    if (inGame)
    {
        checkApple();
        checkCollision();
        move();
    }

    repaint();
}

void Snake::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();

    if ((key == Qt::Key_Left) && (!rightDirection))
    {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Right) && (!leftDirection))
    {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Up) && (!downDirection))
    {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((key == Qt::Key_Down) && (!upDirection))
    {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    QWidget::keyPressEvent(e);
}

void Snake::create_button_start()
{
    button_start = new QPushButton("START GAME", this);
    button_start->setStyleSheet("background-color: rgb(111,128,105);");
    button_start->setGeometry(B_WIDTH/2-50, B_HEIGHT/2-25, 100, 50);
}
