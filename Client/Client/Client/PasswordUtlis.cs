using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    class PasswordUtlis
    {
        //Credit to: https://www.ryadel.com/en/passwordcheck-c-sharp-password-class-calculate-password-strength-policy-aspnet/
        public enum PasswordStrength
        {
            /// Blank Password (empty and/or space chars only)
            Blank = 0,
            /// Either too short (less than 5 chars), one-case letters only or digits only
            Very_Weak = 1,
            /// At least 5 characters, one strong condition met (>= 8 chars with 1 or more UC letters, LC letters, digits & special chars)
            Weak = 2,
            /// At least 5 characters, two strong conditions met (>= 8 chars with 1 or more UC letters, LC letters, digits & special chars)
            Medium = 3,
            /// At least 8 characters, three strong conditions met (>= 8 chars with 1 or more UC letters, LC letters, digits & special chars)
            Strong = 4,
            /// At least 8 characters, all strong conditions met (>= 8 chars with 1 or more UC letters, LC letters, digits & special chars)
            Very_Strong = 5
        }

        public static PasswordStrength GetPasswordStrength(string password)
        {
            int score = 0;
            if (String.IsNullOrEmpty(password) || String.IsNullOrEmpty(password.Trim())) return PasswordStrength.Blank;
            if (!HasMinimumLength(password, 5)) return PasswordStrength.Very_Weak;
            if (HasMinimumLength(password, 8)) score++;
            if (HasUpperCaseLetter(password)) score++;
            if (HasLowerCaseLetter(password)) score++;
            if (HasDigit(password)) score++;
            if (HasSpecialChar(password)) score++;
            return (PasswordStrength)score;
        }

        private static bool HasMinimumLength(string password, int minLength)
        {
            return password.Length >= minLength;
        }

        private static bool HasDigit(string password)
        {
            return password.Any(c => char.IsDigit(c));
        }

        private static bool HasSpecialChar(string password)
        {
            return password.IndexOfAny("!@#$%^&*?_~-£().,".ToCharArray()) != -1;
        }

        private static bool HasUpperCaseLetter(string password)
        {
            return password.Any(c => char.IsUpper(c));
        }

        private static bool HasLowerCaseLetter(string password)
        {
            return password.Any(c => char.IsLower(c));
        }
    }
}
