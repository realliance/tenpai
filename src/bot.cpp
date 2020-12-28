
#include "gentlemanbot.h"

#include "gametablesdk/network.h"

using GametableSDK::Network::connectToMatch;

int main() {
  GentlemanBot bot;
  connectToMatch(bot, "http://vps.chrismiller.xyz:8080");

  return 0;
}
