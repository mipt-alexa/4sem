#include <ctime>
#include <cmath>
#include <iostream>
#include <list>
#include <random>
#include <SFML/Graphics.hpp>
#include <vector>



const float deg_to_rad = 0.017453f;


class Animation {
private:
    float m_frame{}, m_speed{};

    std::vector<sf::IntRect> m_frames;

public:
    sf::Sprite m_sprite;

    Animation() = default;

    Animation(sf::Texture &t, float x, float y, float w, float h, int count, float Speed) :
            m_frame(0), m_speed(Speed) {
        for (int i = 0; i < count; i++)
            m_frames.emplace_back(x + static_cast< float >(i) * w, y, w, h);

        m_sprite.setTexture(t);
        m_sprite.setOrigin(w / 2, h / 2);
        m_sprite.setTextureRect(m_frames[0]);
    }

    void update() {
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
    bool finished() const {
        return m_frame + m_speed >= m_frames.size();
    }

};


class Entity {
protected:

    float m_x, m_y, m_dx{}, m_dy{}, m_r = 1, m_angle = 0;

    bool m_alive;

public:

    Animation m_anim;

    Entity(Animation &a, float X, float Y, float Angle, float radius) :
            m_anim(a), m_x(X), m_y(Y), m_angle(Angle), m_r(radius), m_alive(true) {}


    float x() const {
        return m_x;
    }

    float y() const {
        return m_y;
    }

    float r() const {
        return m_r;
    }

    float angle() const {
        return m_angle;
    }

    bool alive() const {
        return m_alive;
    }

    void kill() {
        m_alive = false;
    }

    void draw(sf::RenderWindow &app) {
        m_anim.m_sprite.setPosition(m_x, m_y);

        m_anim.m_sprite.setRotation(m_angle + 90);

        app.draw(m_anim.m_sprite);

    }

    virtual ~Entity() = default;
};


class Asteroid : public Entity {
public:

    Asteroid(Animation &a, float X, float Y, float Angle, float radius) : Entity(a, X, Y, Angle, radius) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> uid(-4, 4);

        m_dx = uid(gen);
        m_dy = uid(gen);

    }

    void update(const float W, const float H) {
        m_x += m_dx;
        m_y += m_dy;

        if (m_x > W) m_x = 0;
        if (m_x < 0) m_x = W;
        if (m_y > H) m_y = 0;
        if (m_y < 0) m_y = H;

        m_anim.update();


    }

};


class Bullet : public Entity {
private:
    float m_speed;

public:
    Bullet(Animation &a, float X, float Y, float Angle, float radius) : Entity(a, X, Y, Angle, radius) {
        m_speed = 6;
    }

    void update(const float W, const float H) {
        m_dx = std::cos(m_angle * deg_to_rad) * m_speed;
        m_dy = std::sin(m_angle * deg_to_rad) * m_speed;


        m_x += m_dx;
        m_y += m_dy;

        if (m_x > W || m_x < 0 || m_y > H || m_y < 0) {
            m_alive = false;
        }else {
            m_anim.update();
        }

    }

};


class Player : public Entity {
private:
    int m_lives;

    int m_score;

    const float maxSpeed = 15;

    const float slowing_rate = 0.99;

    const float angle_change = 3;

public:

    bool m_thrust{};

    Player(Animation &a, float X, float Y, float Angle, float radius) : Entity(a, X, Y, Angle, radius) {
        m_lives = 3;
        m_score = 0;
    }

    int lives() const {
        return m_lives;
    }

    int score() const {
        return m_score;
    }

    void score_increase() {
        m_score++;
    }

    void turn(bool direction) {

        if (direction) {
            m_angle += angle_change;
        } else {
            m_angle -= angle_change;
        }
    }

    void new_start(const float W, const float H) {
        m_x = W / 2;
        m_y = H / 2;

        m_dx = 0;
        m_dy = 0;
        m_lives--;
    }

    void update(const float W, const float H) {
        if (m_thrust) {
            m_dx += static_cast< float > (std::cos(m_angle * deg_to_rad) * 0.2);
            m_dy += static_cast< float > (std::sin(m_angle * deg_to_rad) * 0.2);
        } else {
            m_dx *= slowing_rate;
            m_dy *= slowing_rate;
        }

        float speed = std::sqrt(m_dx * m_dx + m_dy * m_dy);
        if (speed > maxSpeed) {
            m_dx *= maxSpeed / speed;
            m_dy *= maxSpeed / speed;
        }

        m_x += m_dx;
        m_y += m_dy;

        if (m_x > W) m_x = 0;
        if (m_x < 0) m_x = W;
        if (m_y > H) m_y = 0;
        if (m_y < 0) m_y = H;

        m_anim.update();

    }

};


class Explosion : public Entity {
public:
    Explosion(Animation &a, float X, float Y, float Angle = 0, float radius = 0) : Entity(a, X, Y, Angle, radius) {}

    void update(const float W, const float H) {
        m_anim.update();

    }
};


template<class A, class B>
bool collided(std::shared_ptr<A> a, std::shared_ptr<B> b) {
    return (b->x() - a->x()) * (b->x() - a->x()) +
           (b->y() - a->y()) * (b->y() - a->y()) <
           (a->r() + b->r()) * (a->r() + b->r());
}


template<class A>
void update(std::vector<std::shared_ptr<A> > &vec, sf::RenderWindow &app, float W, float H) {
    for (int i = 0; i < vec.size(); i++) {

        vec[i]->update(W, H);

        if (!vec[i]->alive()) {
            vec.erase(vec.cbegin() + i);
        } else {
            vec[i]->draw(app);
        }
    }

}


class Game {

private:

    const float W = static_cast< float > (sf::VideoMode::getDesktopMode().width);
    const float H = static_cast< float > (sf::VideoMode::getDesktopMode().height);

    int counter_for_asteroids;

    std::vector<std::shared_ptr<Asteroid> > asteroids;
    std::vector<std::shared_ptr<Bullet> > bullets;
    std::vector<std::shared_ptr<Explosion> > explosions;

    std::shared_ptr< Player > player;

    sf::Text text;
    sf::Font font;

    sf::Sprite background;

    sf::RenderWindow app;

    Animation sExplosion;

public:

    Game() : app(sf::VideoMode(static_cast< int >(W), static_cast< int >(H)), "Asteroids")

    {
        counter_for_asteroids = 0;

        app.setFramerateLimit(60);

        if (!font.loadFromFile("../hw11/Font/ITCBLKAD.ttf")) // +
        {
            std::cerr << "error...\n";
        }

        text.setFont(font); // +
        text.setCharacterSize(40); // +
        text.setFillColor(sf::Color::Red); // +

        sf::Texture t3;

        t3.loadFromFile("../hw11/images/explosions/type_C.png");

        sExplosion = Animation(t3, 0, 0, 256, 256, 48, 0.5);

    };


    void draw(){
        app.draw(background);

        text.setString("Score: " + std::to_string(player->score()) + "\nLives: " + std::to_string(player->lives()));
        app.draw(text);

        player->update(W, H);

        player->draw(app);

        update(explosions, app, W, H);
        update(bullets, app, W, H);
        update(asteroids, app, W, H);

        app.display();
    }


    void run() {

        sf::Texture t1, t2, t3, t4, t5, t6, t7;

        t1.loadFromFile("../hw11/images/spaceship.png");
        t2.loadFromFile("../hw11/images/background.jpg");
        t3.loadFromFile("../hw11/images/explosions/type_C.png");
        t4.loadFromFile("../hw11/images/rock.png");
        t5.loadFromFile("../hw11/images/fire_blue.png");
        t6.loadFromFile("../hw11/images/rock_small.png");
        t7.loadFromFile("../hw11/images/explosions/type_B.png");

        t1.setSmooth(true);
        t2.setSmooth(true);

        background = sf::Sprite(t2);

//        Animation  sExplosion (t3, 0, 0, 256, 256, 48, 0.5);

    Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
    Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
    Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
    Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
    Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
    Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);


        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> rand_angle(0, 359);
        std::uniform_int_distribution<int> rand_y(0, H);
        std::uniform_int_distribution<int> rand_x(0, W);


        for (int i = 0; i < 5; i++) {
            std::shared_ptr<Asteroid> a1(new Asteroid(sRock, rand_x(gen), rand_y(gen), rand_angle(gen), 25));
            asteroids.push_back(std::move(a1));

        }

        player = std::make_shared< Player > ( sPlayer, W / 2, H / 2, 0, 20);

        /////main loop/////
        while (app.isOpen() && player->alive()) {
            sf::Event event{};
            while (app.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    app.close();

                if (event.type == sf::Event::KeyPressed)
                    if (event.key.code == sf::Keyboard::Space) {
                        std::shared_ptr<Bullet> b(new Bullet(sBullet, player->x(), player->y(), player->angle(), 10));

                        bullets.push_back(std::move(b));
                    }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player->turn(true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                player->turn(false);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

                player->m_thrust = true;
                player->m_anim = sPlayer_go;
            } else {

                player->m_thrust = false;
                player->m_anim = sPlayer;
            }


            // collisions
            for (const auto &a : asteroids) {

                for (const auto &b : bullets) {  // a bullet destroys an asteroid
                    if (collided(a, b)) {

                        a->kill();
                        b->kill();

                        std::shared_ptr<Explosion> e1(new Explosion(sExplosion, a->x(), a->y()));

                        explosions.push_back(std::move(e1));

                        player->score_increase();

                    }
                }

                //  an asteroid destroys the player
                if (collided(a, player)) {

                    a->kill();

//                    a->m_alive = false;

                    std::shared_ptr<Explosion> e2(new Explosion(sExplosion_ship, player->x(), player->y()));

                    explosions.push_back(std::move(e2));

                    player->new_start(W, H);

                }
            }


            for (const auto &e : explosions) {

                if (e->m_anim.finished()) {

                    e->kill();

                }
            }

            counter_for_asteroids++;

            if (counter_for_asteroids % 100 == 0) {
                std::shared_ptr<Asteroid> a1(new Asteroid(sRock, 0, rand_y(gen), rand_angle(gen), 25));
                asteroids.push_back(std::move(a1));
            }


            if (player->lives() == 0){
                player->kill();
            }

            draw();
        }

    }
};



int main() {

    Game a;

    a.run();

    return 0;
}