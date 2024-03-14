using System;
using System.IO;
using System.Diagnostics;

namespace Task1
{
    class Program
    {
        static char[] Encrypt(string text, int height, int length)
        {
            int currentIndex = 0;
            char[] encrypted = new char[length];

            for (int i = height - 1; i < length; i += (height - 1) * 2, currentIndex++)
            {
                encrypted[currentIndex] = text[i];
            }

            for (int j = 1; j + 1 < height; j++)
            {
                int step = (height - j - 1) * 2;
                for (int i = height - j - 1; i < length; i += step)
                {
                    encrypted[currentIndex] = text[i];
                    currentIndex++;
                    i += j * 2;
                    if (i < length)
                    {
                        encrypted[currentIndex] = text[i];
                        currentIndex++;
                    }
                }
            }

            for (int i = 0; i < length; i += (height - 1) * 2, currentIndex++)
            {
                encrypted[currentIndex] = text[i];
            }

            return encrypted;
        }

        static char[] Decrypt(string text, int height, int length)
        {
            int currentIndex = 0;
            char[] decrypted = new char[length];

            for (int i = height - 1, step = 2 * (height - 1); i < length; i += step, currentIndex++)
            {
                decrypted[i] = text[currentIndex];
            }

            for (int i = height - 1; i > 1; i--)
            {
                for (int j = i - 1; j < length; j += 2 * (i - 1))
                {
                    decrypted[j] = text[currentIndex++];
                    j += 2 * (height - i);
                    if (j < length)
                    {
                        decrypted[j] = text[currentIndex++];
                    }
                }
            }

            for (int i = 0, step = 2 * (height - 1); i < length; i += step, currentIndex++)
            {
                decrypted[i] = text[currentIndex];
            }

            return decrypted;
        }

        static void EncryptFileByBlocks(string inputFile, string outputFile, int height, int blockLength)
        {
            using (StreamReader reader = new StreamReader(inputFile))
            using (StreamWriter writer = new StreamWriter(outputFile))
            {
                char[] buffer = new char[blockLength];
                int bytesRead;

                while ((bytesRead = reader.ReadBlock(buffer, 0, blockLength)) > 0)
                {
                    string block = new string(buffer, 0, bytesRead);
                    char[] encryptedBlock = Encrypt(block, height, bytesRead);
                    writer.Write(encryptedBlock);
                }
            }
        }

        static void DecryptFileByBlocks(string inputFile, string outputFile, int height, int blockLength)
        {
            using (StreamReader reader = new StreamReader(inputFile))
            using (StreamWriter writer = new StreamWriter(outputFile))
            {
                char[] buffer = new char[blockLength];
                int bytesRead;

                while ((bytesRead = reader.ReadBlock(buffer, 0, blockLength)) > 0)
                {
                    string block = new string(buffer, 0, bytesRead);
                    char[] decryptedBlock = Decrypt(block, height, bytesRead);
                    writer.Write(decryptedBlock);
                }
            }
        }

        static void Main(string[] args)
        {
            int choose;
            Console.WriteLine("Виберіть бажану опцію: шифрування (0) або дешифрування (1): ");
            choose = Convert.ToInt32(Console.ReadLine());

            Console.WriteLine("Введіть висоту частоколу:");
            int height = Convert.ToInt32(Console.ReadLine());

            Console.WriteLine("Введіть довжину блоку:");
            int blockLength = Convert.ToInt32(Console.ReadLine());

            Console.WriteLine("Введіть назву вхідного файлу БЕЗ .txt:");
            string inputFile = Console.ReadLine() + ".txt";

            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            switch (choose)
            {
                case 0:
                    if (blockLength == 0)
                    {
                        string inputText = File.ReadAllText(inputFile);
                        char[] encryptedText = Encrypt(inputText, height, inputText.Length);
                        File.WriteAllText("encrypt.txt", new string(encryptedText));
                    }
                    else
                    {
                        EncryptFileByBlocks(inputFile, "encrypt.txt", height, blockLength);
                    }
                    break;
                case 1:
                    if (blockLength == 0)
                    {
                        string encryptedText = File.ReadAllText(inputFile);
                        char[] decryptedText = Decrypt(encryptedText, height, encryptedText.Length);
                        File.WriteAllText("decrypt.txt", new string(decryptedText));
                    }
                    else
                    {
                        DecryptFileByBlocks(inputFile, "decrypt.txt", height, blockLength);
                    }
                    break;
            }

            stopwatch.Stop();
            TimeSpan duration = stopwatch.Elapsed;
            Console.WriteLine($"Час виконання: {duration.TotalSeconds} секунд.");
            Console.WriteLine("Операція завершена.");

            Console.ReadLine();
        }
    }
}
