#include <iostream>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;
/**
 * Use g++ as the source compiler
 * keep source code in folder along with files in input_files folder
 *      program.txt -> input file
 *      optab.txt -> opcode file
 *
 * run the folloing command:
 * g++ 190101070_Assign01.cpp
 *
 * then execute ./a
 *
 * Four new files will be created:
 * 1. intermediate.txt
 * 2. symtab.txt
 * 3. length.txt
 * 4. output.txt
 *
 *
 */

map<char, int> hex_to_dec{
    {'0', 0},
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'A', 10},
    {'B', 11},
    {'C', 12},
    {'D', 13},
    {'E', 14},
    {'F', 15},
};

map<int, char> dec_to_hex{
    {0, '0'},
    {1, '1'},
    {2, '2'},
    {3, '3'},
    {4, '4'},
    {5, '5'},
    {6, '6'},
    {7, '7'},
    {8, '8'},
    {9, '9'},
    {10, 'A'},
    {11, 'B'},
    {12, 'C'},
    {13, 'D'},
    {14, 'E'},
    {15, 'F'},
};
class Hex
{
public:
    string hex_val;
    int dec_val;

    Hex(int dec_val)
    {
        this->dec_val = dec_val;
        string hex;
        int i = 0;
    }
};

string get_hex_value(int n)
{
    string h;
    int i = 0;

    if (!n)
    {
        h = "0";
    }
    else
    {
        for (int j = n; j != 0; j = j / 16)
        {
            int tmp = 0;
            tmp = j % 16;
            if (tmp < 10)
            {
                h += (char)(tmp + 48);
            }
            else
            {
                h += (char)(tmp + 55);
            }
        }
    }
    reverse(h.begin(), h.end());
    return h;
}

int get_dec_value(string s)
{
    int n = s.size() - 1;
    int val = 0;
    int count = 0;
    for (int i = n; i >= 0; i--)
    {
        int tmp = hex_to_dec[s[i]];
        val = val + tmp * ((int)pow(16, count));
        count++;
    }

    return val;
}

string add_hex(string a, string b)
{
    if (a.size() < b.size())
        add_hex(b, a);

    int n = a.size();
    int m = b.size();

    string val = "";

    int carry = 0;
    int i;
    int j;

    for (i = n - 1, j = m - 1; j >= 0; i--, j--)
    {
        int sum = hex_to_dec[a[i]] + hex_to_dec[b[j]] + carry;
        char to_add = dec_to_hex[sum % 16];
        val.push_back(to_add);
        carry = sum / 16;
    }

    while (i >= 0)
    {
        int sum = hex_to_dec[a[i]] + carry;
        char to_add = dec_to_hex[sum % 16];
        val.push_back(to_add);
        carry = sum / 16;
        i--;
    }

    if (carry)
    {
        val.push_back(dec_to_hex[carry]);
    }

    reverse(val.begin(), val.end());
    return val;
}

void remove_backspaces(string &s)
{
    while (s.back() == ' ')
    {
        s.pop_back();
    }
    return;
}

map<string, int> read_opcode_table()
{
    fstream opcode_table;
    opcode_table.open("optab.txt", ios::in);

    string line;
    map<string, int> opcode_table_map;

    opcode_table.seekg(0, ios::beg);
    while (!opcode_table.eof())
    {
        getline(opcode_table, line);
        string num = line.substr(line.size() - 2, 2);
        string code = "";
        for (int i = 0; i < line.size() && line[i] != ' ' && line[i] != '\t'; i++)
        {
            code += line[i];
            i++;
        }
        pair<string, int> to_insert(code, stoi(num));
        opcode_table_map.insert(to_insert);
    }
    return opcode_table_map;
}

class Instruction
{
public:
    string label;
    string opcode;
    string operand;

    Instruction(string label = "", string opcode = "", string operand = "")
    {
        this->label = label;
        this->opcode = opcode;
        this->operand = operand;
    }

    bool is_comment()
    {
        return (label == ".");
    }

    bool has_label()
    {
        return (label != "");
    }
};

bool isComment(string label)
{
    if (label[0] == '.' || label[0] == ';')
        return true;
    else
        return false;
}

void clear_space(string &s, string &t, string &u)
{
    remove_backspaces(s);
    remove_backspaces(t);
    remove_backspaces(u);
}

void get_data(string &line, string &label, string &opcode, string &operand)
{
    label = line.substr(0, 10);
    opcode = line.substr(10, 10);
    operand = line.substr(20);
    clear_space(label, opcode, operand);
}

string optable(string code)
{
    if (code == "ADD")
        return "18";
    if (code == "AND")
        return "40";
    if (code == "COMP")
        return "28";
    if (code == "DIV")
        return "24";
    if (code == "J")
        return "3C";
    if (code == "JEQ")
        return "30";
    if (code == "JGT")
        return "34";
    if (code == "JLT")
        return "38";
    if (code == "JSUB")
        return "48";
    if (code == "LDA")
        return "00";
    if (code == "LDCH")
        return "50";
    if (code == "LDL")
        return "08";
    if (code == "LDX")
        return "04";
    if (code == "MUL")
        return "20";
    if (code == "OR")
        return "44";
    if (code == "RD")
        return "D8";
    if (code == "RSUB")
        return "4C";
    if (code == "STA")
        return "0C";
    if (code == "STCH")
        return "54";
    if (code == "STL")
        return "14";
    if (code == "STX")
        return "10";
    if (code == "SUB")
        return "1C";
    if (code == "TD")
        return "E0";
    if (code == "TIX")
        return "2C";
    if (code == "WD")
        return "DC";
}

int optable_int(string code)
{
    if (code == "ADD")
        return get_dec_value("18");
    if (code == "AND")
        return get_dec_value("40");
    if (code == "COMP")
        return get_dec_value("28");
    if (code == "DIV")
        return get_dec_value("24");
    if (code == "J")
        return get_dec_value("3C");
    if (code == "JEQ")
        return get_dec_value("30");
    if (code == "JGT")
        return get_dec_value("34");
    if (code == "JLT")
        return get_dec_value("38");
    if (code == "JSUB")
        return get_dec_value("48");
    if (code == "LDA")
        return get_dec_value("00");
    if (code == "LDCH")
        return get_dec_value("50");
    if (code == "LDL")
        return get_dec_value("08");
    if (code == "LDX")
        return get_dec_value("04");
    if (code == "MUL")
        return get_dec_value("20");
    if (code == "OR")
        return get_dec_value("44");
    if (code == "RD")
        return get_dec_value("D8");
    if (code == "RSUB")
        return get_dec_value("4C");
    if (code == "STA")
        return get_dec_value("0C");
    if (code == "STCH")
        return get_dec_value("54");
    if (code == "STL")
        return get_dec_value("14");
    if (code == "STX")
        return get_dec_value("10");
    if (code == "SUB")
        return get_dec_value("1C");
    if (code == "TD")
        return get_dec_value("E0");
    if (code == "TIX")
        return get_dec_value("2C");
    if (code == "WD")
        return get_dec_value("DC");
}
void pass1()
{
    string line;
    string label;
    string opcode;
    string operand;
    string locctr;
    bool flag = false;
    string begin;
    fstream input_program;
    fstream symbol_table;
    fstream intermediate_file;
    fstream opcode_table;

    input_program.open("program.txt", ios::in);
    if (input_program)
    {
        opcode_table.open("optab.txt", ios::in);
        if (opcode_table)
        {
            symbol_table.open("symtab.txt", ios::trunc | ios::out | ios::in);
            intermediate_file.open("intermediate.txt", ios::out);

            getline(input_program, line);
            get_data(line, label, opcode, operand);

            if (opcode != "START")
            {
                locctr = "0";
            }
            else
            {
                locctr = operand;
                begin = locctr;
                intermediate_file << locctr;
                string write_line = "\t" + label + "\t" + opcode + "\t" + operand;
                intermediate_file << write_line << "\n";
            }

            while (!input_program.eof())
            {
                getline(input_program, line);
                if (line == "." || line == ";")
                    continue;
                get_data(line, label, opcode, operand);

                int cnt = (label.size() > 0) + (opcode.size() > 0) + (operand.size() > 0);

                if (!isComment(label))
                {
                    if (cnt == 3)
                    {
                        fstream tempory_symbol_table;
                        tempory_symbol_table.open("symtab.txt", ios::in);
                        while (!tempory_symbol_table.eof())
                        {
                            flag = false;
                            string symbol;
                            int address;
                            getline(tempory_symbol_table, line);
                            symbol = line.substr(0, 10);
                            remove_backspaces(symbol);
                            if (label == symbol)
                            {
                                flag = true;
                                cout << "Error: Duplicate Symbol\n";
                                return;
                            }
                        }
                        tempory_symbol_table.close();
                        if (!flag)
                        {
                            symbol_table << label << "\t" << locctr << "\n";
                            intermediate_file << locctr;
                            string write_line = "\t" + label + "\t" + opcode + "\t" + operand;
                            intermediate_file << write_line << "\n";
                        }
                    }
                    else if (cnt == 1)
                    {
                        intermediate_file << locctr;
                        string write_line = "\t\t" + opcode;
                        intermediate_file << write_line << "\n";
                    }
                    else
                    {
                        intermediate_file << locctr;
                        string write_line = "\t\t" + opcode + "\t" + operand;
                        intermediate_file << write_line << "\n";
                    }

                    opcode_table.seekg(0, ios::beg);
                    while (!opcode_table.eof())
                    {
                        getline(opcode_table, line);
                        string op_no = line.substr(line.length() - 2, 2);
                        string code = "";
                        for (int i = 0; i < line.size() && line[i] != ' ' && line[i] != '\t'; i++)
                        {
                            code += line[i];
                            i++;
                        }

                        bool breakloop = false;

                        if (opcode == code)
                        {
                            locctr = add_hex(locctr, "3");
                            flag = false;
                            breakloop = true;
                        }
                        else if (opcode == "BYTE" || opcode == "byte")
                        {
                            int l = operand.size() - 3;
                            if (operand[0] != 'C' && operand[0] != 'X')
                            {
                                locctr = add_hex("1", locctr);
                                flag = false;
                                breakloop = true;
                            }
                            else if (opcode == "BYTE" && operand[0] == 'C')
                            {
                                locctr = add_hex(locctr, get_hex_value(l));
                                flag = false;
                                breakloop = true;
                            }
                            else if (opcode == "BYTE" && operand[0] == 'X')
                            {
                                locctr = add_hex(locctr, get_hex_value((l + 1) / 2));
                                flag = false;
                                breakloop = true;
                            }
                            else
                            {
                                flag = true;
                            }
                        }
                        else if (opcode == "RESB" || opcode == "resb")
                        {
                            int ressize = stoi(operand);
                            string h = get_hex_value(ressize);
                            locctr = add_hex(locctr, h);
                            flag = false;
                            breakloop = true;
                        }
                        else if (opcode == "RESW" || opcode == "resb")
                        {
                            int ressize = stoi(operand);
                            string h = get_hex_value(ressize);
                            string t = add_hex(h, h);
                            t = add_hex(t, h);
                            locctr = add_hex(t, locctr);
                            flag = false;
                            breakloop = true;
                        }

                        else if (opcode == "WORD" || opcode == "word")
                        {
                            locctr = add_hex(locctr, "3");
                            flag = false;
                            breakloop = true;
                        }

                        if (breakloop)
                            break;
                        if (flag)
                        {
                            cout << opcode << " Not present in optab" << endl;
                            return;
                        }
                    }
                }

                if (opcode == "END")
                    break;
            }

            fstream program_length;
            program_length.open("length.txt", ios::out);
            int l = get_dec_value(locctr) - get_dec_value(begin);
            program_length << get_hex_value(l);
            input_program.close();
            intermediate_file.close();
            symbol_table.close();
            opcode_table.close();
            program_length.close();

            return;
        }
        else
        {
            cout << "optab is missing\n";
            return;
        }
    }
    else
    {
        cout << "Source File Not Found\n";
        return;
    }
}

void pass2()
{
    fstream symbol_table, intermediate_file, opcode_table, output_file, program_length;
    string begin, line, target = "0";
    int j = 0;
    long int bseek, aseek;
    int ntxt = 0;

    opcode_table.open("optab.txt", ios::in);

    if (opcode_table)
    {
        symbol_table.open("symtab.txt", ios::in);
        if (symbol_table)
        {
            intermediate_file.open("intermediate.txt", ios::in);
            if (intermediate_file)
            {
                program_length.open("length.txt", ios::in);
                if (program_length)
                {
                    output_file.open("output.txt", ios::out);

                    string locctr, label, opcode, operand;
                    string num_opcode = "";
                    intermediate_file >> locctr >> label >> opcode >> operand;

                    if (opcode == "START")
                    {
                        begin = operand;
                        string length;
                        program_length >> length;
                        output_file << "H^" << label;
                        for (int i = label.size(); i < 6; ++i)
                        {
                            output_file << " ";
                        }
                        output_file << "^00" << begin << "^00" << length;
                        output_file << "\nT^00" << begin << "^00^";
                        bseek = output_file.tellg();
                    }

                    getline(intermediate_file, line);
                    int cnt = 0;

                    while (!intermediate_file.eof())
                    {

                        getline(intermediate_file, line);
                        istringstream ss(line);
                        label = "";
                        locctr = "";
                        opcode = "";
                        operand = "";
                        ss >> locctr >> label >> opcode >> operand;
                        int ct = (locctr.length() > 0) + (label.length() > 0) + (opcode.length() > 0) + (operand.length() > 0);

                        if (ct == 2)
                        {
                            opcode = label;
                            label = "";
                        }

                        else if (ct == 3)
                        {
                            operand = opcode;
                            opcode = label;
                            label = "";
                        }

                        if (ntxt || cnt >= 60 || opcode == "RESB" || opcode == "RESW" || opcode == "END")
                        {
                            aseek = output_file.tellg();
                            output_file.seekg(-(aseek - bseek) - 3L, ios::cur);
                            int record_len = cnt / 2;
                            if (record_len < 16)
                                output_file << "0" << get_hex_value(record_len) << "^";
                            else
                                output_file << get_hex_value(record_len) << "^";

                            output_file.seekg(0, ios::end);

                            if (opcode == "END")
                            {
                                break;
                            }
                            ntxt = 1;
                            if (opcode != "RESW" && opcode != "RESB" && ntxt)
                            {
                                output_file << "\nT^00" << locctr << "^00^";
                                ntxt = 0;
                            }

                            bseek = output_file.tellg();
                            cnt = 0;
                        }

                        opcode_table.seekg(0, ios::beg);
                        int op_status = 0;

                        while (!opcode_table.eof())
                        {
                            string code, op_no;
                            opcode_table >> code >> op_no;

                            if (code == opcode)
                            {
                                num_opcode = op_no;
                                op_status = 1;
                                break;
                            }
                        }

                        j = operand.length();
                        if (op_status == 1 && operand[j - 1] == 'X' && operand[j - 2] == ',')
                        {

                            j = operand.length();
                            operand = operand.substr(0, j - 2);
                            symbol_table.seekg(0, ios::beg);
                            string symbol;
                            string address;
                            while (!symbol_table.eof())
                            {
                                symbol_table >> symbol >> address;
                                if (symbol == operand)
                                {
                                    target = address;
                                    target = add_hex(target, "8000");
                                    break;
                                }
                            }
                            output_file << num_opcode;
                            for (int i = target.length(); i < 4; ++i)
                                output_file << " ";
                            output_file << target << "^";
                            cnt += 6;
                            continue;
                        }

                        else if (op_status == 1 && opcode != "RSUB")
                        {

                            symbol_table.seekg(0, ios::beg);
                            string symbol;
                            string address;
                            while (!symbol_table.eof())
                            {
                                symbol_table >> symbol >> address;
                                if (symbol == operand)
                                {
                                    target = address;
                                    break;
                                }
                            }
                            output_file << num_opcode;
                            for (int i = target.length(); i < 4; ++i)
                                output_file << " ";
                            output_file << target << "^";
                            cnt += 6;
                            continue;
                        }

                        else if (op_status == 1 && opcode == "RSUB")
                        {
                            output_file << num_opcode << "0000^";
                            cnt += 6;
                            continue;
                        }

                        else
                        {

                            if (opcode == "BYTE" || opcode == "byte")
                            {

                                string ascii;

                                if (operand[0] == 'C')
                                {
                                    for (int i = 2; i < operand.length() - 1; ++i)
                                    {
                                        ascii += get_hex_value((int)operand[i]);
                                    }
                                    output_file << ascii << "^";
                                    cnt += operand.length() - 3;
                                }

                                else if (operand[0] == 'X')
                                {

                                    for (int i = 2; i < operand.length() - 1; ++i)
                                    {
                                        output_file << operand[i];
                                    }
                                    output_file << "^";
                                    cnt += operand.length() - 3;
                                }
                            }

                            else if (opcode == "WORD" || opcode == "word")
                            {
                                string hex = get_hex_value(stoi(operand));
                                int len = hex.length();
                                for (int i = len; i < 6; ++i)
                                {
                                    output_file << "0";
                                }
                                output_file << hex << "^";
                                cnt += 6;
                                continue;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }

                    output_file << "\nE^00" << begin;

                    intermediate_file.close();
                    symbol_table.close();
                    opcode_table.close();
                    output_file.close();
                    program_length.close();

                    return;
                }
                else
                {
                    return;
                }
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
    else
    {
        return;
    }
}

int main()
{
    pass1();
    pass2();
    return 0;
}