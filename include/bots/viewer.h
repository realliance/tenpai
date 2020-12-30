#pragma once
#include <event.h>
#include <piecetype.h>
#include <playercontroller.h>
#include <winds.h>
#include <controllermanager.h>

#include <cstddef>
#include <string>
#include <vector>

using Mahjong::newControllerInst;
using Mahjong::PlayerController;

/**
 * Viewer Bot. 
 * This controller acts as a layer on top of another player controller in order to output events and match information to cout
 */
class Viewer : public Mahjong::PlayerController {
  public:
    Viewer(newControllerInst c, std::vector<std::string> playerL) : controller(c()), playerList(playerL) {
      scores.resize(4);
    };
    auto Name() -> std::string override;
    auto GameStart(int _playerID) -> void override;
    auto RoundStart(std::vector<Mahjong::Piece> hand, Mahjong::Wind seatWind, Mahjong::Wind prevalentWind) -> void override;
    auto ReceiveEvent(Mahjong::Event e) -> void override;
    auto RetrieveDecision() -> Mahjong::Event override;
  private:
    std::vector<Mahjong::Piece> hand;
    std::vector<std::string> playerList;
    size_t n = 0;
    Mahjong::Event lastEvent;
    PlayerController* controller;
    std::vector<uint16_t> scores;
};
