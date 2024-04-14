// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"
#include "vector"

bool isNum(char c) {
  return (c >= '0' && c <= '9');
}
int getPriority(char operation) {
  switch (operation) {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;

    default: return -1;
  }
}

std::vector<std::string> toTokenArray(std::string s) {
  std::vector<std::string> result;
  std::string buf = "";
  for (int i = 0; i < s.length(); i++) {
    if (!isNum(s[i])) {
      if (!buf.empty()) {
        result.push_back(buf);
      }
      std::string temp = "";
      result.push_back(temp + s[i]);
      buf = "";
    } else {
      buf += s[i];
    }
  }
  result.push_back(buf);

  return result;
}
std::string infx2pstfx(std::string inf) {
  std::vector<std::string> arr = toTokenArray(inf);
  TStack<std::string, 300> stek;
  std::string result;
  for (auto i : arr) {
    if (isNum(i[0])) {
      result += i;
      result += ' ';
      continue;
    }
    if (i[0] == ')') {
      while (stek.get() != "(") {
        result += stek.pop();
        result += ' ';
      }
      stek.pop();
      continue;
    }

    // Если знак операции т.е всё кроме цифры
    if (!isNum(i[0])) {
      if (stek.isEmpty()
          || i[0] == '('
          || (getPriority(i[0]) > getPriority(stek.get()[0]))) {
        stek.push(i);
      } else {
        while (!stek.isEmpty() &&
        getPriority(i[0]) <= getPriority(stek.get()[0])) {
          result += stek.pop();
          result += ' ';
        }
        stek.push(i);
      }
      continue;
    }
  }

  // Конец строки
  while (!stek.isEmpty()) {
    result += stek.pop();
    result += ' ';
  }
  while (result[result.length() - 1] == ' ') {
    result.pop_back();
  }
  return result;
}

int doMath(int num1, int num2, char operation) {
  switch (operation) {
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case '*': return num1 * num2;
    default: return num1 / num2;
  }
}

int eval(std::string pref) {
  std::string temp;
  TStack<int, 300> stek;
  for (int i = 0; i < pref.length(); i++) {
    if (isNum(pref[i])) {
      temp += pref[i];
      continue;
    }
    if (pref[i] == ' ') {
      if (temp.empty()) {
        continue;
      }
      stek.push(std::stoi(temp));
      temp = "";
      continue;
    }

    if (!isNum(pref[i])) {
      int num1 = stek.pop();
      int num2 = stek.pop();
      int result = doMath(num2, num1, pref[i]);
      stek.push(result);
    }
  }
  return stek.get();
}
