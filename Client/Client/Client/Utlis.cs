using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Newtonsoft.Json;
using System.Security.Cryptography;
namespace Client
{
    class Utlis
    {
        static public void ShowErrorMessage(string info)
        {
            string msg = "Error!\nInfo: " + info;
            MessageBox.Show(msg, "Error Message");
        }
        static public List<T> ObjectToList<T>(object data)
        {
            return JsonConvert.DeserializeObject<List<T>>(Convert.ToString(data));
        }
        static public bool CheckPassword(string password)
        {
            return password.Length >= 4; //Change to minimal password strength when adding
        }
        //Credit: https://stackoverflow.com/questions/3984138/hash-string-in-c-sharp
        public static string GetHashString(string inputString)
        {
            StringBuilder sb = new StringBuilder();
            foreach (byte b in GetHash(inputString))
                sb.Append(b.ToString("X2"));

            return sb.ToString();
        }
        private static byte[] GetHash(string inputString)
        {
            HashAlgorithm algorithm = SHA256.Create();
            return algorithm.ComputeHash(Encoding.UTF8.GetBytes(inputString));
        }
    }
}
