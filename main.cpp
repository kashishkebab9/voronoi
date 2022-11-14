#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <algorithm>

bool circ_comp(const sf::CircleShape a, const sf::CircleShape b) {
  return a.getPosition().x < b.getPosition().x;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(2000, 2000), "Voronoi");
    std::vector<sf::CircleShape> point_set_vec;
    float point_size = 10.f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
              std::cout << "Pressed!" << std::endl;
              // we want to take the x, y position of the mouse click and draw a permanent point there:
              sf::CircleShape point(point_size);
              float point_pos_x = static_cast<float>(sf::Mouse::getPosition(window).x);
              float point_pos_y = static_cast<float>(sf::Mouse::getPosition(window).y);
              sf::Vector2f point_pos;
              point_pos.x = point_pos_x;
              point_pos.y = point_pos_y;
              point.setFillColor(sf::Color::Black);
              point.setPosition(point_pos);
              point_set_vec.push_back(point);

              // we need to take this vector of points and order it by the x value of each point 
              sort(point_set_vec.begin(), point_set_vec.end(), circ_comp);

              //we need to separate the sets into subsets of left and right


            }

        }

        window.clear(sf::Color::White);
        for (auto point: point_set_vec) {
          window.draw(point);

        }
        if (point_set_vec.size() > 2) {
          auto mid = point_set_vec.size()/2;

          sf::RectangleShape line(sf::Vector2f(5.f, 2000.f));
          line.setPosition(sf::Vector2f(point_set_vec[mid].getPosition().x + point_size/2, 0));
          line.setFillColor(sf::Color::Black);
          sf::CircleShape mid_point(20.f);
          mid_point.setPosition(sf::Vector2f(point_set_vec[mid].getPosition().x- point_size, point_set_vec[mid].getPosition().y- point_size));
          mid_point.setFillColor(sf::Color::Green);
          window.draw(mid_point);
          window.draw(line);

        }
        window.display();
    }

    return 0;
}
