using System;

namespace fireland15.LindenmayerSystem.Expressions.Model.Tokens
{
    public class Token
    {
        #region Properties

        public TokenType Type { get; }

        public Operator? Operator { get; } = null;

        public string Symbol { get; }

        public float? Value { get; } = null;

        #endregion

        #region Constructor(s)

        public Token(float value)
            : this(TokenType.Value)
        {
            Value = value;
        }

        public Token(Operator @operator)
            : this(TokenType.Operator)
        {
            Operator = @operator;
        }

        public Token(string symbol)
            : this(TokenType.Identifier)
        {
            Symbol = symbol;
        }

        public Token(TokenType type)
        {
            Type = type;
        }

        #endregion

        #region Overrides

        public override bool Equals(object obj)
        {
            if (obj is Token other)
            {
                if (other.Type != Type)
                    return false;
                switch (Type)
                {
                    case TokenType.Identifier:
                        return other.Symbol == Symbol;
                    case TokenType.LeftParenthesis:
                        return true;
                    case TokenType.Operator:
                        return other.Operator == Operator;
                    case TokenType.RightParenthesis:
                        return true;
                    case TokenType.Value:
                        return other.Value == Value;
                    default:
                        throw new ArgumentOutOfRangeException($"Invalid value '{Type}' for the enum {nameof(TokenType)}.");
                }
            }
            return false;
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Type, Operator, Value, Symbol);
        }

        public override string ToString()
        {
            switch (Type)
            {
                case TokenType.Value:
                    return $"Value token ({Value})";
                case TokenType.RightParenthesis:
                    return $"Right parenthesis token";
                case TokenType.Operator:
                    return $"Operator token ({Operator})";
                case TokenType.LeftParenthesis:
                    return "Left parenthesis token";
                case TokenType.Identifier:
                    return $"Identifier token ({Symbol})";
                default:
                    throw new ArgumentOutOfRangeException($"Invalid value '{Type}' for the enum {nameof(TokenType)}.");
            }
        }

        #endregion
    }
}
