#pragma once

#ifndef XPWEBM__ENEMY_H_
#define XPWEBM__ENEMY_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <utility>
#include <cstdlib>

#define SCALE_FAC 10.f

struct enemy_data_t {
  sf::Color c;
  int ah;
  int ap;
  int min;
  int max;
};

struct enemy_t : public sf::RectangleShape {
  int addHealth;
  int addPoints;
  sf::Vector2f accel;
  enemy_t(enemy_data_t in, sf::Vector2f a, sf::Vector2f p) {
    float size_ = (rand() % in.max + in.min + 1) / SCALE_FAC;
    accel = a;
    addHealth = in.ah;
    addPoints = in.ap;
    this->setPosition(p);
    this->setSize(sf::Vector2f(100, 100));
    this->setScale(size_, size_);
    this->setFillColor(in.c);
  }

};

#endif //XPWEBM__ENEMY_H_
