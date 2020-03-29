using fireland15.LindenmayerSystem.Expressions.Model.Tokens;
using System.Collections;
using System.Collections.Generic;
using Xunit;

namespace fireland15.LindenmayerSystem.Test.Expressions.Tokens
{
    public class ExpressionTokenizerTests
    {
        [Fact]
        public void CreatesValueToken()
        {
            // arrange
            var str = "3.14159";
            var tokenizer = new ExpressionTokenizer();

            // act
            var tokens = tokenizer.Tokenize(str);

            // assert
            Assert.Single(tokens);
            Assert.Equal(new Token(float.Parse(str)), tokens[0]);
        }

        [Theory]
        [InlineData("+", Operator.Add)]
        [InlineData("/", Operator.Divide)]
        [InlineData("==", Operator.Equals)]
        [InlineData(">", Operator.GreaterThan)]
        [InlineData(">=", Operator.GreaterThanOrEqual)]
        [InlineData("<", Operator.LessThan)]
        [InlineData("<=", Operator.LessThanOrEqual)]
        [InlineData("*", Operator.Multiply)]
        [InlineData("~", Operator.Negate)]
        [InlineData("!=", Operator.NotEquals)]
        [InlineData("-", Operator.Subtract)]
        public void CreatesOperatorToken(string str, Operator @operator)
        {
            // arrange
            var tokenizer = new ExpressionTokenizer();

            // act
            var tokens = tokenizer.Tokenize(str);

            // assert
            Assert.Single(tokens);
            Assert.Equal(new Token(@operator), tokens[0]);
        }

        [Fact]
        public void CreatesVariableToken()
        {
            // arrange
            var str = "bananas";
            var tokenizer = new ExpressionTokenizer();

            // act
            var tokens = tokenizer.Tokenize(str);

            // assert
            Assert.Single(tokens);
            Assert.Equal(new Token("bananas"), tokens[0]);
        }

        [Theory]
        [InlineData(")", TokenType.RightParenthesis)]
        [InlineData("(", TokenType.LeftParenthesis)]
        public void CreatesParenthesis(string str, TokenType tokenType)
        {
            // arrange
            var tokenizer = new ExpressionTokenizer();

            // act
            var tokens = tokenizer.Tokenize(str);

            // assert
            Assert.Single(tokens);
            Assert.Equal(new Token(tokenType), tokens[0]);
        }

        [Fact]
        public void HandlesMultipleTokens0()
        {
            // arrange
            var str = "()";
            var tokenizer = new ExpressionTokenizer();

            // act
            var tokens = tokenizer.Tokenize(str);

            // assert
            Assert.Equal(2, tokens.Count);
            Assert.Equal(new Token(TokenType.LeftParenthesis), tokens[0]);
            Assert.Equal(new Token(TokenType.RightParenthesis), tokens[1]);
        }

        [Fact]
        public void HandlesMultipleTokens1()
        {
            // arrange
            var str = "(3.14159)";
            var tokenizer = new ExpressionTokenizer();

            // act
            var tokens = tokenizer.Tokenize(str);

            // assert
            Assert.Equal(3, tokens.Count);
            Assert.Equal(new Token(TokenType.LeftParenthesis), tokens[0]);
            Assert.Equal(new Token(float.Parse("3.14159")), tokens[1]);
            Assert.Equal(new Token(TokenType.RightParenthesis), tokens[2]);
        }

        [Fact]
        public void HandlesMultipleTokens2()
        {
            // arrange
            var str = "(3.14159 + c)";
            var tokenizer = new ExpressionTokenizer();

            // act
            var tokens = tokenizer.Tokenize(str);

            // assert
            Assert.Equal(5, tokens.Count);
            Assert.Equal(new Token(TokenType.LeftParenthesis), tokens[0]);
            Assert.Equal(new Token(float.Parse("3.14159")), tokens[1]);
            Assert.Equal(new Token(Operator.Add), tokens[2]);
            Assert.Equal(new Token("c"), tokens[3]);
            Assert.Equal(new Token(TokenType.RightParenthesis), tokens[4]);
        }
    }
}
