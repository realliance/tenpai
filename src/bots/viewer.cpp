#include "bots/viewer.h"
#include "support/matchkeeper.h"

#include <iostream>
#include <memory>

#include "event.h"
#include "piecetype.h"
#include "winds.h"

using Mahjong::Event;
using Support::MatchKeeper;

auto Viewer::Name() -> std::string {
  return controller->Name();
}

auto Viewer::GameStart(int playerID) -> void {
  controller->GameStart(playerID);
}

auto Viewer::RoundStart(std::vector<Mahjong::Piece> hand, Mahjong::Wind seatWind, Mahjong::Wind prevalentWind) -> void {
  controller->RoundStart(hand, seatWind, prevalentWind);
}

auto Viewer::ReceiveEvent(Mahjong::Event e) -> void {
  controller->ReceiveEvent(e);

  if (e.type == Event::PointDiff) {
    scores[e.player] += e.piece;
  }

  if (e.type == Event::End) {
    MatchKeeper::getInstance().RecordScores(scores);
  }
}

auto Viewer::RetrieveDecision() -> Mahjong::Event {
  return controller->RetrieveDecision();
}
