using fireland15.LindenmayerSystem.Expressions.Exceptions;
using System;
using System.Collections.Generic;

namespace fireland15.LindenmayerSystem.Expressions.Model.Tokens
{
    interface IExpressionTokenizer
    {
        IList<Token> Tokenize(string expressionString);
    }

    internal class ExpressionTokenizer : IExpressionTokenizer
    {
        #region Private Fields

        #endregion

        #region Constructor(s)

        #endregion

        #region IExpressionTokenizer

        public IList<Token> Tokenize(string str)
        {
            var tokens = new List<Token>();
            int index = 0;
            while (index < str.Length)
            {
                if (char.IsDigit(str[index]))
                {
                    var beginNumIndex = index;
                    do
                    {
                        index++;
                    } while (index < str.Length && (char.IsDigit(str[index]) || str[index] == '.'));
                    
                    var numStr = str.Substring(beginNumIndex, index - beginNumIndex);
                    if (float.TryParse(numStr, out var number))
                    {
                        tokens.Add(new Token(number));
                        continue;
                    }
                    else
                    {
                        throw new ParseException($"'{numStr}' could not be parsed at index '{beginNumIndex}'");
                    }
                }
                else if (char.IsLetter(str[index]))
                {
                    var beginSymbolIndex = index;
                    do
                    {
                        index++;
                    } while (index < str.Length && char.IsLetter(str[index]));
                    var symbol = str.Substring(beginSymbolIndex, index - beginSymbolIndex);
                    tokens.Add(new Token(symbol));
                    continue;
                }
                else if (str[index] == '=')
                {
                    if (str[index + 1] == '=')
                    {
                        tokens.Add(new Token(Operator.Equals));
                        index++;
                    }
                    else
                    {
                        throw new ParseException($"Unexpected symbol '{str[index + 1]}' following '=' at index '{index}'.");
                    }
                }
                else if (str[index] == '<')
                {
                    if ((index + 1) < str.Length && str[index + 1] == '=')
                    {
                        tokens.Add(new Token(Operator.LessThanOrEqual));
                        index++;
                    }
                    else
                    {
                        tokens.Add(new Token(Operator.LessThan));
                    }
                }
                else if (str[index] == '>')
                {
                    if ((index + 1) < str.Length && str[index + 1] == '=')
                    {
                        tokens.Add(new Token(Operator.GreaterThanOrEqual));
                        index++;
                    }
                    else
                    {
                        tokens.Add(new Token(Operator.GreaterThan));
                    }
                }
                else if (str[index] == '!')
                {
                    if (str[index + 1] == '=')
                    {
                        tokens.Add(new Token(Operator.NotEquals));
                        index++;
                    }
                    else
                    {
                        throw new ParseException($"Invalid symbol at '{index + 1}'.");
                    }
                }
                else if (str[index] == '+')
                {
                    tokens.Add(new Token(Operator.Add));
                }
                else if (str[index] == '-')
                {
                    tokens.Add(new Token(Operator.Subtract));
                }
                else if (str[index] == '/')
                {
                    tokens.Add(new Token(Operator.Divide));
                }
                else if (str[index] == '*')
                {
                    tokens.Add(new Token(Operator.Multiply));
                }
                else if (str[index] == '~')
                {
                    tokens.Add(new Token(Operator.Negate));
                }
                else if (str[index] == '(')
                {
                    tokens.Add(new Token(TokenType.LeftParenthesis));
                }
                else if (str[index] == ')')
                {
                    tokens.Add(new Token(TokenType.RightParenthesis));
                }
                else if (char.IsWhiteSpace(str[index]))
                {
                    // no-op
                }
                else
                {
                    throw new ParseException($"Unexpected character. Position: '{index}'.");
                }
                index++;
            }
            return tokens;
        }

        #endregion
    }
}
