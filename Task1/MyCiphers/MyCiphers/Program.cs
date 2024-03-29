using System;
using System.IO;
using System.Reflection.PortableExecutable;
using System.Text;

/*Console.WriteLine("======\nZigZag\n======\n\n1) Encrypt\n2) Decrypt\n");
                        ConsoleKeyInfo zigMode = Console.ReadKey();
                        if (zigMode.Key == ConsoleKey.D1)
                        {
                            Console.Clear();
                            Console.WriteLine("Shifring");
                            zigWorking = false;
                        }
                        else if (zigMode.Key == ConsoleKey.D2)
                        {
                            Console.Clear();
                            Console.WriteLine("De(tut)shifring");
                            zigWorking = false;
                        }
                        else
                        {
                            Console.Clear();
                            Console.WriteLine("No.");
                        }
*/
public class Ciphers
{
    //ZigZag
    public static void ZigZag(int blockLen, int height)
    {
        string inputFileName = "message.txt";
        string outputFileName = "enmessages.txt";
        if (blockLen == 0)
        {
            blockLen = inputFileName.Length;
        }
        StreamReader sr = new StreamReader(inputFileName);
        using (StreamWriter sw = new StreamWriter(outputFileName, true))
        {
            while (!sr.EndOfStream)
            {
                char[] buffer = new char[blockLen];
                int charsRead = sr.ReadBlock(buffer, 0, blockLen);

                if (charsRead > 0)
                {
                    string block = new string(buffer, 0, charsRead);
                    string encryptedBlock = EncryptZigZag(block, height);
                    sw.WriteLine(encryptedBlock);
                }
            }
        }

        Console.WriteLine("Encryption completed.");
        
    }

    public static string EncryptZigZag(string input, int height)
    {
        int len = input.Length;
        StringBuilder result = new StringBuilder(len);

        for (int i = 0; i < height; i++)
        {
            for (int j = i; j < len; j += (height - 1) * 2)
            {
                result.Append(input[j]);
                int k = j + (height - i - 1) * 2;
                if (i != 0 && i != height - 1 && k < len)
                    result.Append(input[k]);
            }
        }

        return result.ToString();
    }

    //=========================
    //Caesar
public static void Caesar(int blockLen, int step) 
    {
        string inputFileName = "message.txt";
        string outputFileName = "enmessages.txt";
        string alphabetFileName = "alphabet.txt";
        if (blockLen == 0)
        {
            blockLen = inputFileName.Length;
        }
        StreamReader ar = new StreamReader(alphabetFileName);
        string line = ar.ReadToEnd();
        char[] alphabet = line.ToCharArray();
        

        //char[] alphabet  = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'];
        StreamReader sr = new StreamReader(inputFileName);
        using (StreamWriter sw = new StreamWriter(outputFileName, true))
        {
            while (!sr.EndOfStream)
            {
                char[] buffer = new char[blockLen];
                int charsRead = sr.ReadBlock(buffer, 0, blockLen);

                if (charsRead > 0)
                {
                    string block = new string(buffer, 0, charsRead);
                    string encryptedBlock = EncryptCaesar(block, step, alphabet);
                    sw.WriteLine(encryptedBlock);
                }
            }
        }

        Console.WriteLine("Encryption completed.");
    }
    static string EncryptCaesar(string input, int step, char[] alphabet)
    {
        StringBuilder result = new StringBuilder(input.Length);

        foreach (char c in input)
        {
            if (char.IsLetter(c))
            {
                char shiftedChar = ShiftChar(c, step, alphabet);
                result.Append(shiftedChar);
            }
            
        }

        return result.ToString();
    }

    static char ShiftChar(char c, int step, char[] alphabet)
    {
        int index = (c - alphabet[0] + step) % alphabet.Length;
        if (index < 0)
        {
            index += alphabet.Length;
        }
        return alphabet[index];
    }
    //=========================
    //=========================
    //Vigenere
    
    public static void Main(string[] args)
    {
        bool isWorking = true;
        while (isWorking)
        {
            Console.WriteLine("_Choose the cipher_\n===================\n1)ZigZag\n2)Caesar\n3)Vigenere\n\nExit");
            ConsoleKeyInfo cipherMode = Console.ReadKey();
            Console.Clear();
            switch (cipherMode.Key)
            {
                case ConsoleKey.D1:
                    //ZigZag start
                    bool zigWorking = true;
                    while (zigWorking)
                    {
                        Console.WriteLine("======\nZigZag\n======\n\n1)Encrypt\n2)Decrypt\n");
                        ConsoleKeyInfo zigMode = Console.ReadKey();
                        // Шифруємо
                        if (zigMode.Key == ConsoleKey.D1)
                        {
                            Console.Clear();
                            Console.WriteLine("Input Block Length\n");
                            int blockLen = Convert.ToInt32(Console.ReadLine());
                            Console.Clear();
                            Console.WriteLine("Input Fence Height\n");
                            int height = Convert.ToInt32(Console.ReadLine());
                            Console.Clear();
                            ZigZag(blockLen,height);
                            zigWorking = false;
                        }
                        // Дешифруємо
                        else if (zigMode.Key == ConsoleKey.D2)
                        {
                            Console.Clear();
                            Console.WriteLine("Input Block Length\n");
                            int blockLen = Convert.ToInt32(Console.ReadLine());
                            Console.Clear();
                            Console.WriteLine("Input Fence Height\n");
                            int height = Convert.ToInt32(Console.ReadLine());
                            Console.Clear();
                            //ZigZagDecryption(blockLen, height);
                            Console.WriteLine(":(");
                            zigWorking = false;
                        }
                        // Нічьо не робимо
                        else
                        {
                            Console.Clear();
                            Console.WriteLine("No.");
                        }
                    }
                    isWorking = false;
                    break;
                case ConsoleKey.D2:
                    //Caesar start
                    bool casWorking = true;
                    while (casWorking)
                    {
                        Console.WriteLine("======\nCaesar\n======\n\n1)Encrypt\n2)Decrypt\n");
                        ConsoleKeyInfo casMode = Console.ReadKey();
                        // Шифруємо
                        if (casMode.Key == ConsoleKey.D1)
                        {
                            Console.Clear();
                            Console.WriteLine("Input Block Length\n");
                            int blockLen = Convert.ToInt32(Console.ReadLine());
                            Console.Clear();
                            Console.WriteLine("Input Caesar Step\n");
                            int step = Convert.ToInt32(Console.ReadLine());
                            Console.Clear();
                            Caesar(blockLen,step);
                            casWorking = false;
                        }
                        // Дешифруємо
                        else if (casMode.Key == ConsoleKey.D2)
                        {
                            Console.Clear();
                            Console.WriteLine("De(tut)shifring");
                            casWorking = false;
                        }
                        // Нічьо не робимо
                        else
                        {
                            Console.Clear();
                            Console.WriteLine("No.");
                        }
                    }
                    isWorking = false;
                    break;
                case ConsoleKey.D3:
                    //Vigenere start
                    bool vigWorking = true;
                    while (vigWorking)
                    {
                        Console.WriteLine("======\nVigenere\n======\n\n1) Encrypt\n2) Decrypt\n");
                        ConsoleKeyInfo vigMode = Console.ReadKey();
                        if (vigMode.Key == ConsoleKey.D1)
                        {
                            Console.Clear();
                            Console.WriteLine("Input Block Length\n");
                            int blockLen = Convert.ToInt32(Console.ReadLine());
                            Console.Clear();
                            Console.WriteLine("Input Vigenere Key\n");
                            string key = Console.ReadLine();
                            Console.Clear();
                            Vigenere(blockLen, key);
                            vigWorking = false;
                        }
                        else if (vigMode.Key == ConsoleKey.D2)
                        {
                            Console.Clear();
                            Console.WriteLine("De(tut)shifring");
                            vigWorking = false;
                        }
                        else
                        {
                            Console.Clear();
                            Console.WriteLine("No.");
                        }
                    }
                    break;
                case ConsoleKey.E:
                    isWorking = false;
                    break;
            }
        }
    }
}