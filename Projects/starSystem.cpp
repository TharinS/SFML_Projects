#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

const int WIDTH = 800;
const int HEIGHT = 600;
const int CONCENTRATION_RADIUS = 20;
const int BELT_RADIUS_MIN = 40;
const int BELT_RADIUS_MAX = 300;
const int NUM_BELTS = 50;
const float STAR_DENSITY = 0.51f;

int p[256];

float fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float lerp(float t, float a, float b) {
    return a + t * (b - a);
}

float grad(int hash, float x, float y) {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : h == 12 || h == 14 ? x
                                             : 0;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float perline_noise(float x, float y) {
    int X = (int)std::floor(x) & 255;
    int Y = (int)std::floor(y) & 255;
    x -= std::floor(x);
    y -= std::floor(y);
    float u = fade(x);
    float v = fade(y);
    int A = p[X] + Y;
    int AA = p[A], AB = p[A + 1];
    int B = p[X + 1] + Y;
    int BA = p[B], BB = p[B + 1];
    return lerp(v, lerp(u, grad(p[AA], x, y), grad(p[BA], x - 1, y)),
                lerp(u, grad(p[AB], x, y - 1),
                     grad(p[BB], x - 1, y - 1)));
}

float perlinNoise(float x, float y) {
    float total = 0;
    float p = 0.5f;
    float freq = 1.0f / 32;
    float amp = 1.0f;
    for (int i = 0; i < 4; ++i) {
        total += perline_noise(x * freq, y * freq) * amp;
        amp *= p;
        freq *= 2;
    }
    return total;
}

void initPerlin() {
    for (int i = 0; i < 256; ++i) {
        p[i] = i;
    }
    for (int i = 255; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(p[i], p[j]);
    }
    for (int i = 0; i < 256; ++i) {
        p[256 + i] = p[i];
    }
}

float noise(float x, float y) {
    return perlinNoise(x, y);
}

sf::Color getRandomColor() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    return sf::Color(dis(gen), dis(gen), dis(gen));
}

int main() {
    initPerlin();

    // create window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Starfield");

    // create image and texture
    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);
    sf::Texture texture;
    texture.loadFromImage(image);

    // create sprite
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // seed random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // calculate center of array
    int centerX = WIDTH / 2;
    int centerY = HEIGHT / 2;

    // set color of pixels near center to white
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            float distance = std::sqrt(std::pow(x - centerX, 2) + std::pow(y - centerY, 2));
            if (distance < CONCENTRATION_RADIUS) {
                image.setPixel(x, y, getRandomColor());
            }
        }
    }

    // create belt of stars
    for (int i = 0; i < NUM_BELTS; ++i) {
        int radius = std::uniform_int_distribution<int>(BELT_RADIUS_MIN, BELT_RADIUS_MAX)(gen);

        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                float distance = std::sqrt(std::pow(x - centerX, 2) + std::pow(y - centerY, 2));
                if (std::abs(distance - radius) < 1.0f) {
                    if (std::uniform_real_distribution<float>(0.0f, 1.0f)(gen) < STAR_DENSITY * (1.0f - std::abs(distance - radius) / radius)) {
                        image.setPixel(x, y, getRandomColor());
                    }
                }
            }
        }
    }

    // update texture and display sprite
    texture.update(image);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
