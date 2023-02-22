#include "log.h"

#include "ansiCodes/AnsiCodes.h"

using namespace log;

Handler log::i = Handler();
Handler log::w = Handler(AnsiCodes::Yellow, AnsiCodes::Reset);
Handler log::e = Handler(AnsiCodes::Red, AnsiCodes::Reset);

std::string log::endl = AnsiCodes::Reset + "\n";
std::string log::endm = AnsiCodes::Reset + "\n\n";
std::string log::entity = "@";