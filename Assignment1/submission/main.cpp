#include <iostream>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

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
        while (n != 0)
        {
            int tmp = 0;
            tmp = n % 16;
            if (tmp < 10)
            {
                h += (char)(tmp + 48);
            }
            else
            {
                h += (char)(tmp + 55);
            }
            i++;
            n = n / 16;
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
    while (n >= 0)
    {
        int tmp = hex_to_dec[s[n]];
        n--;
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

int pass1()
{
    string line, label, opcode, operand;
    string locctr;
    int flag = 0;
    string start;
    fstream f_prog, f_symtab, f_inter, f_optab;

    f_prog.open("program.txt", ios::in);
    if (!f_prog)
    {
        cout << "Source File Not Found\n";
        return 0;
    }

    f_optab.open("optab.txt", ios::in);
    if (!f_optab)
    {
        cout << "optab is missing\n";
        return 0;
    }

    f_symtab.open("symtab.txt", ios::trunc | ios::out | ios::in);
    f_inter.open("intermediate.txt", ios::out);

    getline(f_prog, line);
    label = line.substr(0, 10);
    opcode = line.substr(10, 10);
    operand = line.substr(20);
    remove_backspaces(label);
    remove_backspaces(opcode);
    remove_backspaces(operand);

    if (opcode == "START")
    {
        locctr = operand;
        start = locctr;
        f_inter << locctr;
        string write_line = "\t" + label + "\t" + opcode + "\t" + operand;
        f_inter << write_line << "\n";
    }
    else
    {
        locctr = "0";
    }

    while (!f_prog.eof())
    {
        getline(f_prog, line);
        if (line == "." || line == ";")
            continue;
        label = line.substr(0, 10);
        opcode = line.substr(10, 10);
        operand = line.substr(20);
        remove_backspaces(label);
        remove_backspaces(opcode);
        remove_backspaces(operand);

        int count = (label.size() > 0) + (opcode.size() > 0) + (operand.size() > 0);

        if (label[0] != '.' && label[0] != ';')
        {
            if (count == 1)
            {
                f_inter << locctr;
                string write_line = "\t\t" + opcode;
                f_inter << write_line << "\n";
            }
            else if (count == 2)
            {
                f_inter << locctr;
                string write_line = "\t\t" + opcode + "\t" + operand;
                f_inter << write_line << "\n";
            }
            else if (count == 3)
            {
                fstream temp_f;
                temp_f.open("symtab.txt", ios::in);
                while (!temp_f.eof())
                {
                    flag = 0;
                    string symbol;
                    int address;
                    getline(temp_f, line);
                    symbol = line.substr(0, 10);
                    remove_backspaces(symbol);
                    if (label == symbol)
                    {
                        flag = 1;
                        cout << "Error: Duplicate Symbol\n";
                        return 0;
                    }
                }
                temp_f.close();
                if (flag == 0)
                {
                    f_symtab << label << "\t" << locctr << "\n";
                    f_inter << locctr;
                    string write_line = "\t" + label + "\t" + opcode + "\t" + operand;
                    f_inter << write_line << "\n";
                }
            }

            f_optab.seekg(0, ios::beg);
            while (!f_optab.eof())
            {
                getline(f_optab, line);
                string op_no = line.substr(line.length() - 2, 2);
                string code = "";
                int i = 0;
                while (line[i] != ' ' && line[i] != '\t')
                {
                    code += line[i];
                    i++;
                }

                if (opcode == code)
                {
                    locctr = add_hex(locctr, "3");
                    flag = 0;
                    break;
                }
                else if (opcode == "WORD" || opcode == "word")
                {
                    locctr = add_hex(locctr, "3");
                    flag = 0;
                    break;
                }
                else if (opcode == "RESW" || opcode == "resb")
                {
                    int ressize = stoi(operand);
                    string h = get_hex_value(ressize);
                    string t = add_hex(h, h);
                    t = add_hex(t, h);
                    locctr = add_hex(t, locctr);
                    flag = 0;
                    break;
                }
                else if (opcode == "RESB" || opcode == "resb")
                {
                    int ressize = stoi(operand);
                    string h = get_hex_value(ressize);
                    locctr = add_hex(locctr, h);
                    flag = 0;
                    break;
                }
                else if (opcode == "BYTE" || opcode == "byte")
                {
                    int l = operand.size() - 3;
                    if (operand[0] != 'C' && operand[0] != 'X')
                    {
                        locctr = add_hex("1", locctr);
                        flag = 0;
                        break;
                    }
                    else if (opcode == "BYTE" && operand[0] == 'C')
                    {
                        locctr = add_hex(locctr, get_hex_value(l));
                        flag = 0;
                        break;
                    }
                    else if (opcode == "BYTE" && operand[0] == 'X')
                    {
                        locctr = add_hex(locctr, get_hex_value((l + 1) / 2));
                        flag = 0;
                        break;
                    }
                    else
                    {
                        flag = 1;
                    }
                }

                if (flag == 1)
                {
                    cout << opcode << " Not present in optab" << endl;
                    return 0;
                }
            }
        }

        if (opcode == "END")
            break;
    }

    fstream f_length;
    f_length.open("length.txt", ios::out);
    int l = get_dec_value(locctr) - get_dec_value(start);
    f_length << get_hex_value(l);
    f_prog.close();
    f_inter.close();
    f_symtab.close();
    f_optab.close();
    f_length.close();

    return 1;
}

int pass2()
{
    fstream f_symtab, f_inter, f_optab, f_obj, f_length;
    string start;
    string line;
    string target = "0";
    int j = 0;
    long bseek;
    long aseek;
    int newtxt = 0;

    f_optab.open("optab.txt", ios::in);
    if (!f_optab)
    {
        cout << "optab is missing" << endl;
        return 0;
    }
    f_symtab.open("symtab.txt", ios::in);
    if (!f_symtab)
    {
        cout << "symtab is missing";
        return 0;
    }
    f_inter.open("intermediate.txt", ios::in);
    if (!f_inter)
    {
        cout << "intermediate file is missing" << endl;
        return 0;
    }
    f_length.open("length.txt", ios::in);
    if (!f_length)
    {
        cout << "length.txt missing" << endl;
        return 0;
    }
    f_obj.open("object_program.txt", ios::out);

    string locctr, label, opcode, operand;
    string opcode_no = "";
    f_inter >> locctr >> label >> opcode >> operand;

    if (opcode == "START")
    {
        start = operand;
        string length;
        f_length >> length;
        f_obj << "H^" << label;
        for (int i = label.size(); i < 6; ++i)
        {
            f_obj << " ";
        }
        f_obj << "^00" << start << "^00" << length;
        f_obj << "\nT^00" << start << "^00^";
        bseek = f_obj.tellg();
    }

    getline(f_inter, line);
    int cnt = 0;

    while (!f_inter.eof())
    {
        getline(f_inter, line);
        istringstream ss(line);
        label = "";
        locctr = "";
        opcode = "";
        operand = "";

        ss >> locctr >> label >> opcode >> operand;

        int count = (locctr.length() > 0) + (label.length() > 0) + (opcode.length() > 0) + (operand.length() > 0);

        if (count == 2)
        {
            opcode = label;
            label = "";
        }
        else if (count == 3)
        {
            operand = opcode;
            opcode = label;
            label = "";
        }

        if (newtxt || cnt >= 60 || opcode == "RESB" || opcode == "RESW" || opcode == "END")
        {
            aseek = f_obj.tellg();
            f_obj.seekg(-(aseek - bseek) - 3L, ios::cur);
            int record_len = cnt / 2;

            if (record_len < 16)
                f_obj << "0" << get_hex_value(record_len) << "^";
            else
                f_obj << get_hex_value(record_len) << "^";

            f_obj.seekg(0, ios::end);

            if (opcode == "END")
            {
                break;
            }
            newtxt = 1;

            if (opcode != "RESW" && opcode != "RESB" && newtxt)
            {
                f_obj << "\nT^00" << locctr << "^00^";
                newtxt = 0;
            }

            bseek = f_obj.tellg();
            cnt = 0;
        }

        f_optab.seekg(0, ios::beg);
        int op_st = 0;
        while (!f_optab.eof())
        {
            string code, num;
            f_optab >> code >> num;

            if (code == opcode)
            {
                opcode_no = num;
                op_st = 1;
                break;
            }
        }

        j = operand.size();

        if (op_st == 1 && operand[j - 1] == 'X' && operand[j - 2] == ',')
        {
            j = operand.size();
            operand = operand.substr(0, j - 2);
            f_symtab.seekg(0, ios::beg);
            string sym;
            string adr;
            while (!f_symtab.eof())
            {
                f_symtab >> sym >> adr;
                if (sym == operand)
                {
                    target = adr;
                    target = add_hex(target, "8000");
                    break;
                }
            }
            f_obj << opcode_no;
            for (int k = target.size(); k < 4; k++)
                f_obj << " ";
            cnt += 6;
            continue;
        }
        else if (op_st = 1 && opcode != "RSUB")
        {
            f_symtab.seekg(0, ios::beg);
            string sym;
            string adr;
            while (!f_symtab.eof())
            {
                f_symtab >> sym >> adr;
                if (sym == operand)
                {
                    target = adr;
                    break;
                }
            }
            f_obj << opcode_no;
            for (int k = target.size(); k < 4; k++)
                f_obj << " ";
            f_obj << target << "^";
            cnt += 6;
            continue;
        }
        else if (op_st == 1 && opcode == "RSUB")
        {
            f_obj << opcode_no << "0000^";
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
                    for (int k = 2; k < operand.size() - 1; ++k)
                    {
                        ascii += get_hex_value((int)operand[k]);
                    }
                    f_obj << ascii << "^";
                    cnt += operand.size() - 3;
                }
                else if (operand[0] == 'X')
                {
                    for (int k = 2; k < operand.size() - 1; ++k)
                    {
                        f_obj << operand[k];
                    }
                    f_obj << "^";
                    cnt += operand.length() - 3;
                }
            }
            else if (opcode == "WORD" || opcode == "word")
            {
                string h = get_hex_value(stoi(operand));
                int l = h.size();

                for (int k = l; k < 6; k++)
                {
                    f_obj << "0";
                }
                f_obj << h << "^";
                cnt += 6;
                continue;
            }
            else
            {
                continue;
            }
        }
    }

    f_obj << "\nE^00" << start;
    f_inter.close();
    f_symtab.close();
    f_optab.close();
    f_obj.close();
    f_length.close();

    cout << "\nEnding pass 2" << endl;
    return 1;
}

int main()
{
    pass1();
    pass2();
    return 0;
}