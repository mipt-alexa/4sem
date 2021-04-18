#include <ctime>
#include <cmath>
#include <iostream>
#include <list>
#include <random>
#include <SFML/Graphics.hpp>
#include <vector>


using namespace sf; // это надо убрать

// надо свое пр-во имен
// надо разбиение на файлы
// во всем коде надо проверить форматирование и code style

//// глобальные константы остались
const float W =  static_cast< float > (VideoMode::getDesktopMode().width);
const float H = static_cast< float > (VideoMode::getDesktopMode().height);


const float deg_to_rad = 0.017453f;


class Animation
{
private:
    float m_frame{}, m_speed{};

    std::vector<IntRect> m_frames;

public:
    Sprite m_sprite; // public?

    Animation() = default; // мы пишем = default, но он вообще нужен?

    Animation(Texture& t, float x, float y, float w, float h, int count, float Speed):
            m_frame(0), m_speed(Speed)
    {// списки инициализации?

        for (int i = 0; i < count; i++)
            m_frames.emplace_back(x + static_cast< float >(i) * w, y, w, h);

        m_sprite.setTexture(t);
        m_sprite.setOrigin(w / 2, h / 2);
        m_sprite.setTextureRect(m_frames[0]);
    }

    void update()
    {
        m_frame += m_speed;

        auto n = m_frames.size();

        if (m_frame >= n) {
            m_frame -= n;
        }

        if (n > 0) {
            m_sprite.setTextureRect(m_frames[static_cast<int> (m_frame)]);  // приведение плохое ???
        }
    }

public:
    bool finished() const
    {
        return m_frame + m_speed >= m_frames.size();
    }

};


class Entity
{
private:


public:

    Animation m_anim; // все публичное, непорядок
    float m_x, m_y, m_dx{}, m_dy{}, m_r = 1, m_angle = 0;
    bool m_alive = true;

    Entity(Animation& a, float X, float Y, float Angle, float radius):
            m_anim(a), m_x(X), m_y(Y), m_angle(Angle), m_r(radius), m_alive(true) {}


    // можно применить идиому NVI, или шаблонный метод для гибкости #TODO update template&??
//    virtual void update() {}; // = default


    float x() const{
        return m_x;
    }

    float y() const{
        return m_y;
    }

    float r() const{
        return m_r;
    }

    float angle() const{
        return m_angle;
    }


    void draw(RenderWindow& app)
    {
        m_anim.m_sprite.setPosition(m_x, m_y);

        m_anim.m_sprite.setRotation(m_angle + 90);

        app.draw(m_anim.m_sprite);

    }

    virtual ~Entity() = default;
};


class Asteroid : public Entity
{
public:

    Asteroid(Animation& a, float X, float Y, float Angle, float radius) : Entity(a, X, Y, Angle, radius)
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution< int > uid(-4, 4);

        m_dx = uid(gen);
        m_dy = uid(gen);

    }

    ~Asteroid() override = default;

    void update()
    {
        m_x += m_dx;
        m_y += m_dy;

        if (m_x > W) m_x = 0;  if (m_x < 0) m_x = W;
        if (m_y > H) m_y = 0;  if (m_y < 0) m_y = H;

    }

};


class Bullet : public Entity
{
private:
    float m_speed;

public:
    Bullet(Animation& a, float X, float Y, float Angle, float radius) : Entity(a, X, Y, Angle, radius)
    {
        m_speed = 6;
    }

    void  update()
    {
        m_dx = std::cos(m_angle * deg_to_rad) * m_speed;
        m_dy = std::sin(m_angle * deg_to_rad) * m_speed;


        m_x += m_dx;
        m_y += m_dy;

        if (m_x > W || m_x < 0 || m_y > H || m_y < 0) m_alive = false;
    }

};


class Player : public Entity
{
public:
    bool m_thrust{}; // публичные данные
    int m_lives;
    int m_score;

    Player(Animation& a, float X, float Y, float Angle, float radius) : Entity(a, X, Y, Angle, radius)
    {
        m_lives = 3;
        m_score = 0;
    }

    bool is_alive() const {
        return (m_lives > 0);
    }

    void score_increase() {
        m_score++;
    }

    void new_start(){
        m_x = W/2;
        m_y = H/2;

        m_dx = 0;
        m_dy = 0;
        m_lives--;
    }

    void update()
    {
        if (m_thrust)
        {
            m_dx += static_cast< float > (std::cos(m_angle * deg_to_rad) * 0.2);
            m_dy += static_cast< float > (std::sin(m_angle * deg_to_rad) * 0.2);
        }
        else
        {
            m_dx *= slowing_rate;
            m_dy *= slowing_rate;
        }

        float speed = std::sqrt(m_dx * m_dx + m_dy * m_dy);
        if (speed > maxSpeed)
        {
            m_dx *= maxSpeed / speed;
            m_dy *= maxSpeed / speed;
        }

        m_x += m_dx;
        m_y += m_dy;

        if (m_x > W) m_x = 0; if (m_x < 0) m_x = W;
        if (m_y > H) m_y = 0; if (m_y < 0) m_y = H;
    }


private:

    const float maxSpeed = 15;
    const float slowing_rate = 0.99;

};


class Explosion : public Entity{
public:
    Explosion(Animation& a, float X, float Y, float Angle = 0, float radius = 0) : Entity(a, X, Y, Angle, radius)
    {}

    void update() {}
};


template<class A, class B>
bool collided(std::shared_ptr< A > a, std::shared_ptr< B > b)
{
    return (b->m_x - a->m_x) * (b->m_x - a->m_x) +
           (b->m_y - a->m_y) * (b->m_y - a->m_y) <
           (a->m_r + b->m_r) * (a->m_r + b->m_r);
}


template<class A>
void update(std::vector< std::shared_ptr< A > >& vec, RenderWindow& app){
    for (int i = 0; i < vec.size(); i++) {

        vec[i]->update();
        vec[i]->m_anim.update();

        if (!vec[i]->m_alive){
            vec.erase(vec.cbegin()+i);
        }else {
            vec[i]->draw(app);
        }
    }

}



class Game{
public:
    static void run(){
        Font font; // +
        if (!font.loadFromFile("../hw11/Font/ITCBLKAD.ttf")) // +
        {
            std::cerr << "error...\n";
        }

        Text text; // +
        text.setFont(font); // +
        text.setCharacterSize(40); // +
        text.setFillColor(sf::Color::Red); // +

        RenderWindow app(VideoMode(static_cast< int >(W), static_cast< int >(H)), "Asteroids!");
        app.setFramerateLimit(60);

        Texture t1, t2, t3, t4, t5, t6, t7;
        t1.loadFromFile("../hw11/images/spaceship.png");
        t2.loadFromFile("../hw11/images/background.jpg");
        t3.loadFromFile("../hw11/images/explosions/type_C.png");
        t4.loadFromFile("../hw11/images/rock.png");
        t5.loadFromFile("../hw11/images/fire_blue.png");
        t6.loadFromFile("../hw11/images/rock_small.png");
        t7.loadFromFile("../hw11/images/explosions/type_B.png");

        t1.setSmooth(true);
        t2.setSmooth(true);

        Sprite background(t2);

        Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
        Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
        Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
        Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
        Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
        Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
        Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);


        std::vector< std::shared_ptr< Asteroid > > asteroids;
        std::vector< std::shared_ptr< Bullet > > bullets;
        std::vector< std::shared_ptr< Explosion > > explosions;


        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution< int > rand_angle(0, 359);
        std::uniform_int_distribution< int > rand_y(0, H);
        std::uniform_int_distribution< int > rand_x(0, W);


        for (int i = 0; i < 5; i++)
        {
            std::shared_ptr< Asteroid > a1 (new Asteroid(sRock, rand_x(gen), rand_y(gen), rand_angle(gen), 25));
            asteroids.push_back(std::move(a1));

        }

        std::shared_ptr< Player > player ( new Player(sPlayer, W / 2, H / 2, 0, 20));


        int counter_for_asteroids = 0;

        /////main loop/////
        while (app.isOpen() && player->is_alive())
        {
            Event event{};
            while (app.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    app.close();

                if (event.type == Event::KeyPressed)
                    if (event.key.code == Keyboard::Space)
                    {
                        std::shared_ptr< Bullet > b (new Bullet(sBullet, player->m_x, player->m_y, player->m_angle, 10));

                        bullets.push_back(std::move(b));
                    }
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)) player->m_angle += 3;
            if (Keyboard::isKeyPressed(Keyboard::Left)) player->m_angle -= 3;
            if (Keyboard::isKeyPressed(Keyboard::Up)) {

                player->m_thrust = true;
                player->m_anim = sPlayer_go;
            }
            else{

                player->m_thrust = false;
                player->m_anim = sPlayer;
            }


            // collisions
            for (const auto& a : asteroids) {

                for (const auto& b : bullets) {  // a bullet destroys an asteroid
                    if (collided(a, b)) {

                        a->m_alive = false;
                        b->m_alive = false;

                        std::shared_ptr< Explosion > e1 (new Explosion(sExplosion, a->m_x, a->m_y));

                        explosions.push_back(std::move(e1));

                        player->score_increase();

                    }
                }

                //  an asteroid destroys the player
                if (collided(a, player)) {
                    a->m_alive = false;

                    std::shared_ptr< Explosion > e2 (new Explosion(sExplosion_ship, player->m_x, player->m_y));

                    explosions.push_back(std::move(e2));

                    player->collided();

                }
            }


            for (const auto& e : explosions) {

                if (e->m_anim.finished()){
                    e->m_alive = false;
                }

            }

            counter_for_asteroids++;

            if (counter_for_asteroids % 100 == 0)
            {
                std::shared_ptr< Asteroid > a1 (new Asteroid(sRock, 0, rand_y(gen), rand_angle(gen), 25));
                asteroids.push_back(std::move(a1));
            }


            //////draw//////
            app.draw(background);

            text.setString("Score: " + std::to_string(player->m_score) + "\nLives: " + std::to_string(player->m_lives));
            app.draw(text);

            player->update();
            player->m_anim.update();

            player->draw(app);

            update(explosions, app);
            update(bullets, app);
            update(asteroids, app);


            app.display();
        }

    }
};


int main()
{

    Game a;

    Game::run();

    return 0;
}
