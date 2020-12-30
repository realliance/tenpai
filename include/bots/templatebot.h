#pragma once
#include <event.h>
#include <piecetype.h>
#include <playercontroller.h>
#include <winds.h>

#include <cstddef>
#include <string>
#include <vector>

/**
 * Template Bot. A mirror of libmahjong's Angry Discardo Bot
 * Original Author: Alice Hartley <github.com/HartleyAHartley>
 */
class TemplateBot : public Mahjong::PlayerController {
  public:
    auto Name() -> std::string override;
    auto GameStart(int _playerID) -> void override;
    auto RoundStart(std::vector<Mahjong::Piece> hand, Mahjong::Wind seatWind, Mahjong::Wind prevalentWind) -> void override;
    auto ReceiveEvent(Mahjong::Event e) -> void override;
    auto RetrieveDecision() -> Mahjong::Event override;

  private:
    std::vector<Mahjong::Piece> hand;
    size_t n = 0;
    Mahjong::Event lastEvent;
};
