#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>


class Stack {
    std::vector<int> buf;
    int sp = -1;
public:
    explicit Stack(int size) : buf(size, 0) {}

    void push(int n) {
        if(sp + 1 >= buf.size()) {
            throw std::runtime_error("Stack overflow");
        }
        buf[++sp] = n;
    }
    int pop() {
        const int n = buf[sp];
        sp--;
        return n;
    }
    [[nodiscard]] int top() const {
        return buf[sp];
    }
};


int main(int argc, char *argv[]) {

    std::ifstream f(argv[1]);
    if (!f.is_open()) {
        std::cerr << "Error opening the file!";
        return 1;
    }
    std::string s;
    std::vector<std::string> program_lines;
    while (getline(f, s)) { program_lines.push_back(s); }
    f.close();

    for (unsigned int i = 1 ; i < program_lines.size(); ++i) {
        if ( program_lines.at(i).empty() ) {
            program_lines.erase(program_lines.begin() + i);
            --i;
        }
    }


    std::vector<std::string> program;
    int token_counter = 0;
    std::map<std::string, int> label_tracker;

    for (std::string &line : program_lines) {
        std::vector<std::string> parts;
        std::stringstream ss(line);
        std::string t;
        char del = ' ';
        while (getline(ss, t, del)) { parts.push_back(t); }
        std::string opcode = parts[0];

        if (opcode.empty()) { continue; }
        if (opcode.ends_with(":")) {
            std::string newopcode = opcode.substr(0, opcode.length() - 1);
            label_tracker[newopcode] = token_counter;
            continue;
        }

        program.emplace_back(opcode);
        token_counter++;

        if (opcode == "push") {
            std::string snumber = parts[1];
            program.emplace_back(snumber);
            token_counter++;
        } else if (opcode == "write") {
            std::vector<std::string> newparts = {parts.begin() + 1, parts.end()};
            std::string string_literal;
            for (size_t i = 0; i < newparts.size(); ++i) {
                string_literal += (i ? " " : "");
                string_literal += newparts[i];
            }
            program.emplace_back(string_literal);
            token_counter++;
        } else if (opcode == "goto(=0)") {
            const std::string& label = parts[1];
            program.emplace_back(label);
            token_counter++;
        } else if (opcode == "goto(>0)") {
            const std::string& label = parts[1];
            program.emplace_back(label);
            token_counter++;
        } else if (opcode == "goto(>0)") {
            const std::string& label = parts[1];
            program.emplace_back(label);
            token_counter++;
        }
    }

    /*
     * interpret program
     */

    int pc = 0;
    Stack stack(256);

    while (program[pc] != "return") {
        const std::string& op = program[pc];
        pc++;

        if (op == "push") {
            int number = std::stoi(program[pc]);
            pc++;
            stack.push(number);
        } else if (op == "pop") {
            stack.pop();
        } else if (op == "abs") {
            int a = stack.pop();
            if (a < 0) { stack.push(-a); }
            else { stack.push(a); }
        } else if (op == "dup") {
            int a = stack.pop();
            stack.push(a);
            stack.push(a);
        } else if (op == "swap") {
            int a = stack.pop();
            int b = stack.pop();
            stack.push(a);
            stack.push(b);
        } else if (op == "over") {
            int a = stack.pop();
            int b = stack.pop();
            stack.push(b);
            stack.push(a);
            stack.push(b);
        } else if (op == "rot") {
            int a = stack.pop();
            int b = stack.pop();
            int c = stack.pop();
            stack.push(b);
            stack.push(a);
            stack.push(c);
        } else if (op == "add") {
            int a = stack.pop();
            int b = stack.pop();
            stack.push(b + a);
        } else if (op == "sub") {
            int a = stack.pop();
            int b = stack.pop();
            stack.push(b - a);
        } else if (op == "mul") {
            int a = stack.pop();
            int b = stack.pop();
            stack.push(b * a);
        } else if (op == "div") {
            int a = stack.pop();
            int b = stack.pop();
            stack.push(b / a);
        } else if (op == "mod") {
            int a = stack.pop();
            int b = stack.pop();
            stack.push(b % a);
        } else if (op == "write") {
            const std::string& string_literal = program[pc];
            pc++;
            std::cout << string_literal << std::endl;
        } else if (op == "read") {
            int number;
            std::cin >> number;
            stack.push(number);
        } else if (op == "goto(=0)") {
            int number = stack.top();
            if (number == 0) { pc = label_tracker[program[pc]]; }
            else { pc++; }
        } else if (op == "goto(>0)") {
            int number = stack.top();
            if (number > 0) { pc = label_tracker[program[pc]]; }
            else { pc++; }
        } else if (op == "goto(<0)") {
            int number = stack.top();
            if (number < 0) { pc = label_tracker[program[pc]]; }
            else { pc++; }
        } else if (op == "top") {
            int number = stack.top();
            std::cout << number << std::endl;
        }
    }

    return 0;
}
