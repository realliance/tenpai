#include "bots/templatebot.h"

#include <memory>

#include "event.h"
#include "piecetype.h"
#include "winds.h"

auto TemplateBot::Name() -> std::string {
  return "TemplateBot";
}

auto TemplateBot::GameStart(int /*playerID*/) -> void {}

auto TemplateBot::RoundStart(std::vector<Mahjong::Piece> _hand, Mahjong::Wind /*seatWind*/, Mahjong::Wind /*prevalentWind*/) -> void {
  // Resets AI at beginning of round to new hand
  hand = _hand;
  lastEvent.type = Mahjong::Event::Discard;
}

auto TemplateBot::ReceiveEvent(Mahjong::Event e) -> void {
  // Choose the highest priority decision
  if (e.decision) {
    if (e.type <= lastEvent.type) {
      lastEvent = e;
    }
  } 
  if (e.type == Mahjong::Event::Discard) {
    hand.emplace_back(e.piece);
  }
}

auto TemplateBot::RetrieveDecision() -> Mahjong::Event {
  if (lastEvent.type == Mahjong::Event::Discard) {
    lastEvent.piece = hand[n].toUint8_t();
    n = (n + 1) % hand.size();
  }
  Mahjong::Event e = lastEvent;
  lastEvent.type = Mahjong::Event::Discard;  // lowest """priority""" event type
  return e;
}
