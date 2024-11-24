#include <iostream>
using namespace std;

int digit_length(string digit);
int binary_to_decimal(string digit, int length);
int octal_to_decimal(string digit, int length);
int hexa_to_decimal(string digit, int length);
int decimal_string_to_decimal(string digit, int length);
string decimal_to_binary(int decimal);
string decimal_to_octal(int decimal);
string decimal_to_hexa(int decimal);
string encrypt_message(string message, int base);
string decrypt_message(string encrypted, int base);
int get_base();

int main()
{
    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Number System Conversion\n";
        cout << "2. Encrypt a Message\n";
        cout << "3. Decrypt a Message\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string digit;
            int b;
            int decimal = 0;
            cout << "Enter the digit: ";
            cin >> digit;
            b = get_base();
            int length = digit_length(digit);

            if (b == 2)
            {
                decimal = binary_to_decimal(digit, length);
            }
            else if (b == 8)
            {
                decimal = octal_to_decimal(digit, length);
            }
            else if (b == 16)
            {
                decimal = hexa_to_decimal(digit, length);
            }
            else if (b == 10)
            {
                decimal = decimal_string_to_decimal(digit, length);
            }
            else
            {
                cout << "Invalid base!" << endl;
                continue;
            }
            cout << "Decimal number: " << decimal << endl;

            if (b != 2)
            {
                string binary = decimal_to_binary(decimal);
                cout << "Binary number: " << binary << endl;
            }
            if (b != 8)
            {
                string octal = decimal_to_octal(decimal);
                cout << "Octal number: " << octal << endl;
            }
            if (b != 16)
            {
                string hexa = decimal_to_hexa(decimal);
                cout << "Hexadecimal number: " << hexa << endl;
            }
        }
        else if (choice == 2)
        {
            cin.ignore(); // Clear the input buffer
            string message;
            cout << "Enter the message to encrypt: ";
            getline(cin, message);
            int base = get_base();

            if (base == 2 || base == 8 || base == 16)
            {
                string encrypted = encrypt_message(message, base);
                cout << "Encrypted message: " << encrypted << endl;
            }
            else
            {
                cout << "Invalid base for encryption!" << endl;
            }
        }
        else if (choice == 3)
        {
            cin.ignore(); // Clear the input buffer
            string encrypted;
            cout << "Enter the encrypted message: ";
            getline(cin, encrypted);
            int base = get_base();

            if (base == 2 || base == 8 || base == 16)
            {
                string decrypted = decrypt_message(encrypted, base);
                cout << "Decrypted message: " << decrypted << endl;
            }
            else
            {
                cout << "Invalid base for decryption!" << endl;
            }
        }
        else if (choice == 4)
        {
            cout << "Exiting the program." << endl;
        }
        else
        {
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}

int get_base()
{
    int b;
    cout << "Enter the value of base: ";
    cin >> b;
    return b;
}

int digit_length(string digit)
{
    int length = 0;
    for (int i = 0; digit[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}

int binary_to_decimal(string digit, int length)
{
    int decimal = 0;
    int base = 1;
    for (int i = length - 1; i >= 0; i--)
    {
        if (digit[i] == '1')
        {
            decimal = decimal + base;
        }
        base = base * 2;
    }
    return decimal;
}

int octal_to_decimal(string digit, int length)
{
    int decimal = 0;
    int base = 1;
    for (int i = length - 1; i >= 0; i--)
    {
        int n = digit[i] - '0';
        decimal = decimal + n * base;
        base = base * 8;
    }
    return decimal;
}

int hexa_to_decimal(string digit, int length)
{
    int decimal = 0;
    int base = 1;
    for (int i = length - 1; i >= 0; i--)
    {
        int value = 0;

        if (digit[i] >= '0' && digit[i] <= '9')
        {
            value = digit[i] - '0';
        }
        else if (digit[i] >= 'A' && digit[i] <= 'F')
        {
            value = digit[i] - 'A' + 10;
        }
        else if (digit[i] >= 'a' && digit[i] <= 'f')
        {
            value = digit[i] - 'a' + 10;
        }
        decimal = decimal + value * base;
        base = base * 16;
    }
    return decimal;
}

int decimal_string_to_decimal(string digit, int length)
{
    int decimal = 0;
    int base = 1;
    for (int i = length - 1; i >= 0; i--)
    {
        int n = digit[i] - '0';
        decimal = decimal + n * base;
        base = base * 10;
    }
    return decimal;
}

string decimal_to_binary(int decimal)
{
    if (decimal == 0)
    {
        return "0";
    }
    string binary = "";
    while (decimal > 0)
    {
        int rem = decimal % 2;
        binary = char(rem + '0') + binary;
        decimal = decimal / 2;
    }
    return binary;
}

string decimal_to_octal(int decimal)
{
    if (decimal == 0)
    {
        return "0";
    }
    string octal = "";
    while (decimal > 0)
    {
        int rem = decimal % 8;
        octal = char(rem + '0') + octal;
        decimal = decimal / 8;
    }
    return octal;
}

string decimal_to_hexa(int decimal)
{
    if (decimal == 0)
    {
        return "0";
    }
    string hexa = "";
    while (decimal > 0)
    {
        int rem = decimal % 16;
        if (rem < 10)
        {
            hexa = char(rem + '0') + hexa;
        }
        else
        {
            hexa = char(rem - 10 + 'A') + hexa;
        }
        decimal = decimal / 16;
    }
    return hexa;
}

string encrypt_message(string message, int base)
{
    string encrypted = "";
    for (int i = 0; message[i] != '\0'; i++)
    {
        int ascii_value = int(message[i]);
        string converted = "";

        if (base == 2)
        {
            converted = decimal_to_binary(ascii_value);
            // Pad to 8 bits for consistency
            while (converted.length() < 8)
            {
                converted = '0' + converted;
            }
        }
        else if (base == 8)
        {
            converted = decimal_to_octal(ascii_value);
        }
        else if (base == 16)
        {
            converted = decimal_to_hexa(ascii_value);
        }

        encrypted = encrypted + converted + " ";
    }
    return encrypted;
}

string decrypt_message(string encrypted, int base)
{
    string decrypted = "";
    string value = "";
    for (int i = 0; encrypted[i] != '\0'; i++)
    {
        if (encrypted[i] != ' ')
        {
            value = value + encrypted[i];
        }
        else
        {
            int length = digit_length(value);
            int decimal_value = 0;

            if (base == 2)
            {
                decimal_value = binary_to_decimal(value, length);
            }
            else if (base == 8)
            {
                decimal_value = octal_to_decimal(value, length);
            }
            else if (base == 16)
            {
                decimal_value = hexa_to_decimal(value, length);
            }

            char character = char(decimal_value);
            decrypted = decrypted + character;
            value = "";
        }
    }
    // Handle the last value if there's no trailing space
    if (value != "")
    {
        int length = digit_length(value);
        int decimal_value = 0;

        if (base == 2)
        {
            decimal_value = binary_to_decimal(value, length);
        }
        else if (base == 8)
        {
            decimal_value = octal_to_decimal(value, length);
        }
        else if (base == 16)
        {
            decimal_value = hexa_to_decimal(value, length);
        }

        char character = char(decimal_value);
        decrypted = decrypted + character;
    }
    return decrypted;
}
