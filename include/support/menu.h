#pragma once

#include <iostream>
#include <any>
#include <string>
#include <variant>
#include <vector>
#include <type_traits>
#include <optional>
#include <sstream>
#include <limits>
#include <cctype>

/**
 * Simple C++17 Menu System
 * based on https://www.bfilipek.com/2018/07/menu-cpp17-example.html
 */

namespace Support {
  namespace Input {
    std::optional<std::string> getline(std::istream&, const std::string& = "");
    std::string getline(const std::string& = "", const std::string& = "");
    std::string getbotselection(const std::string& = "Select Bot");

    inline std::string trim(const std::string& s) {
      constexpr char whitespace[] = " \t\n\r";
      const size_t first = s.find_first_not_of(whitespace);

      return (first != std::string::npos) ? s.substr(first, (s.find_last_not_of(whitespace) - first + 1)) : std::string {};
    };

    template<typename T = int>
    bool startsWithDigit(const std::string& s) {
      if (s.empty()) {
        return false;
      }

      if (std::isdigit(s.front())) {
        return true;
      }

      return (((std::is_signed<T>::value 
          && (s.front() == '-')) || (s.front() == '+'))
          && ((s.size() > 1) && std::isdigit(s[1])));
    };

    template<typename T = int>
    std::optional<T> stonum(const std::string& st) {
      const auto s = trim(st);
      bool ok = startsWithDigit<T>(s);

      auto v = T {};

      if (ok) {
        std::istringstream ss(s);
        ss >> v;
        ok = (ss.peek() == EOF);
      }

      return ok ? v : std::optional<T> {};
    };

    template<typename T = std::string>
    std::optional<T> getdata(std::istream& is) {
      auto i = T {};
      const bool b = (is >> i) && std::isspace(is.peek());

      for (is.clear(); is && !std::isspace(is.peek()); is.ignore());
      return b ? i : std::optional<T> {};
    };

    template<typename T = int>
    auto getnum(std::istream& is, bool wholeline = true) {
      if (wholeline) {
        const auto o = getline(is);
        return o.has_value() ? stonum<T>(*o) : std::optional<T> {};
      }

      return getdata<T>(is);
    };

    template <typename T = int>
    auto getnum(const std::string& prm = "", T nmin = std::numeric_limits<T>::lowest(), T nmax = std::numeric_limits<T>::max(), bool wholeline = true) {
      const auto showdefs = [nmin, nmax]() {
        std::cout << " (";

        if (nmin != std::numeric_limits<T>::lowest() || std::is_unsigned<T>::value)
          std::cout << nmin;

        std::cout << " - ";

        if (nmax != std::numeric_limits<T>::max())
          std::cout << nmax;

        std::cout << ")";
      };

      std::optional<T> o;

      do {
        std::cout << prm;

        if ((nmin != std::numeric_limits<T>::lowest()) || (nmax != std::numeric_limits<T>::max()))
          showdefs();

        std::cout << " : ";
        o = getnum<T>(std::cin, wholeline);
      } while ((!o.has_value() || (((*o < nmin) || (*o > nmax)))) && (std::cout << "Invalid input" << std::endl));

      return *o;
    };
  };

  using Params = std::vector<std::variant<size_t, int, double, char, std::string>>;

  class Menu {
    private:
      using itemFunc = void(*)(std::any& param);

      struct MenuItem {
        std::string name;
        std::variant<itemFunc, Menu*> func;
      };

      using menuItems = std::vector<MenuItem>;

    public:
      Menu (const std::string& _title, const menuItems& _items) : title(_title), items(_items) {}

      void menu(std::any& param) {
        menu(*this, param);
      }

    private:
      struct Visitor {
        Visitor(std::any& _param) : param(_param) {}
        
        void operator()(itemFunc f) { f(param); }
        void operator()(Menu* menu) { Menu::menu(*menu, param); }

        private:
          std::any& param;
      };

      static void menu(const Menu& m, std::any& param) {
        const static auto show = [](const Menu& mu) {
          std::ostringstream oss;
          const auto nom = mu.items.size();

          oss << '\n' << mu.title << "\n\n";

          for (size_t i = 0U; i < nom; ++i) {
            oss << i + 1 << ")  " << mu.items[i].name << '\n';
          }

          oss << "0)  Exit menu\n\nEnter menu option number";
          return Input::getnum<size_t>(oss.str(), 0, nom);
        };

        auto opt = show(m);
        std::visit(Visitor(param), m.items[opt - 1].func);
      }

      std::string title;
      menuItems items;
  };
}
