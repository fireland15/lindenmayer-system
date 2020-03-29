using fireland15.LindenmayerSystem.Expressions;
using fireland15.LindenmayerSystem.Expressions.Model.Tokens;
using System.Collections.Generic;
using Xunit;

namespace fireland15.LindenmayerSystem.Test.Expressions
{
    public class InfixToPostfixConverterTests
    {
        [Fact]
        public void EmptyTokenList()
        {
            // arrange
            var converter = new InfixToPostfixConverter();

            // act
            var result = converter.Convert(new List<Token>());

            // assert
            Assert.NotNull(result);
            Assert.Empty(result);
        }

        [Fact]
        public void SingleTokenInList1()
        {
            // arrange
            var tokens = new List<Token>
            {
                new Token(3.14159f)
            };
            var converter = new InfixToPostfixConverter();

            // act
            var result = converter.Convert(tokens);

            // assert
            Assert.Single(result);
            Assert.Equal(tokens[0], result[0]);
        }

        [Fact]
        public void SingleTokenInList2()
        {
            // arrange
            var tokens = new List<Token>
            {
                new Token("bananas")
            };
            var converter = new InfixToPostfixConverter();

            // act
            var result = converter.Convert(tokens);

            // assert
            Assert.Single(result);
            Assert.Equal(tokens[0], result[0]);
        }

        [Fact]
        public void SingleOperator()
        {
            // arrange
            var tokens = new List<Token>
            {
                new Token("bananas"),
                new Token(Operator.Add),
                new Token("apples")
            };
            var converter = new InfixToPostfixConverter();

            // act
            var result = converter.Convert(tokens);

            // assert
            Assert.Equal(3, result.Count);
            Assert.Equal(tokens[0], result[0]);
            Assert.Equal(tokens[2], result[1]);
            Assert.Equal(tokens[1], result[2]);
        }

        [Fact]
        public void MultipleOperators()
        {
            // arrange
            var tokens = new List<Token>
            {
                new Token("bananas"),
                new Token(Operator.Add),
                new Token("apples"),
                new Token(Operator.Subtract),
                new Token("carrots")
            };
            var converter = new InfixToPostfixConverter();

            // act
            var result = converter.Convert(tokens);

            // assert
            Assert.Equal(5, result.Count);
            Assert.Equal(tokens[0], result[0]);
            Assert.Equal(tokens[2], result[1]);
            Assert.Equal(tokens[1], result[2]);
            Assert.Equal(tokens[4], result[3]);
            Assert.Equal(tokens[3], result[4]);
        }

        [Fact]
        public void MultipleOperatorsDifferentPrecedence()
        {
            // arrange
            var tokens = new List<Token>
            {
                new Token("bananas"),
                new Token(Operator.Add),
                new Token("apples"),
                new Token(Operator.Multiply),
                new Token("carrots")
            };
            var converter = new InfixToPostfixConverter();

            // act
            var result = converter.Convert(tokens);

            // assert
            Assert.Equal(5, result.Count);
            Assert.Equal(tokens[0], result[0]);
            Assert.Equal(tokens[2], result[1]);
            Assert.Equal(tokens[4], result[2]);
            Assert.Equal(tokens[3], result[3]);
            Assert.Equal(tokens[1], result[4]);
        }

        [Fact]
        public void SimpleParenthesis()
        {
            // arrange
            var tokens = new List<Token>
            {
                new Token(TokenType.LeftParenthesis),
                new Token("bananas"),
                new Token(Operator.Add),
                new Token("apples"),
                new Token(TokenType.RightParenthesis)
            };
            var converter = new InfixToPostfixConverter();

            // act
            var result = converter.Convert(tokens);

            // assert
            Assert.Equal(3, result.Count);
            Assert.Equal(tokens[1], result[0]);
            Assert.Equal(tokens[3], result[1]);
            Assert.Equal(tokens[2], result[2]);
        }

        [Fact]
        public void LessSimpleParenthesis()
        {
            // arrange
            var tokens = new List<Token>
            {
                new Token(TokenType.LeftParenthesis),
                new Token("bananas"),
                new Token(Operator.Add),
                new Token("apples"),
                new Token(TokenType.RightParenthesis),
                new Token(Operator.Multiply),
                new Token(3.0f)
            };
            var converter = new InfixToPostfixConverter();

            // act
            var result = converter.Convert(tokens);

            // assert
            Assert.Equal(5, result.Count);
            Assert.Equal(tokens[1], result[0]);
            Assert.Equal(tokens[3], result[1]);
            Assert.Equal(tokens[2], result[2]);
            Assert.Equal(tokens[6], result[3]);
            Assert.Equal(tokens[5], result[4]);
        }

        [Fact]
        public void TwoSetsOfParenthesis()
        {
            // arrange
            var tokens = new List<Token>
            {
                new Token(TokenType.LeftParenthesis),
                new Token("bananas"),
                new Token(Operator.Add),
                new Token("apples"),
                new Token(TokenType.RightParenthesis),
                new Token(Operator.Multiply),
                new Token(TokenType.LeftParenthesis),
                new Token("carrots"),
                new Token(Operator.Add),
                new Token("dogs"),
                new Token(TokenType.RightParenthesis),
            };
            var converter = new InfixToPostfixConverter();

            // act
            var result = converter.Convert(tokens);

            // assert
            Assert.Equal(7, result.Count);
            Assert.Equal(tokens[1], result[0]);
            Assert.Equal(tokens[3], result[1]);
            Assert.Equal(tokens[2], result[2]);
            Assert.Equal(tokens[7], result[3]);
            Assert.Equal(tokens[9], result[4]);
            Assert.Equal(tokens[8], result[5]);
            Assert.Equal(tokens[5], result[6]);
        }

        [Fact]
        public void NestedParenthesis()
        {
            // arrange
            var tokens = new List<Token>
            {
                new Token(TokenType.LeftParenthesis),
                new Token("apples"),
                new Token(Operator.Add),
                new Token(TokenType.LeftParenthesis),
                new Token("bananas"),
                new Token(Operator.Add),
                new Token("carrots"),
                new Token(TokenType.RightParenthesis),
                new Token(TokenType.RightParenthesis),
            };

            var converter = new InfixToPostfixConverter();

            // act
            var result = converter.Convert(tokens);

            // assert
            Assert.Equal(5, result.Count);
            Assert.Equal(tokens[1], result[0]);
            Assert.Equal(tokens[4], result[1]);
            Assert.Equal(tokens[6], result[2]);
            Assert.Equal(tokens[5], result[3]);
            Assert.Equal(tokens[2], result[4]);
        }

        [Fact]
        public void DifferentAssociations()
        {
            // arrange
            var tokens = new List<Token>
            {
                new Token(Operator.Negate),
                new Token("apples"),
                new Token(Operator.Add),
                new Token("bananas"),
            };

            var converter = new InfixToPostfixConverter();

            // act
            var result = converter.Convert(tokens);

            // assert
            Assert.Equal(4, result.Count);
            Assert.Equal(tokens[1], result[0]);
            Assert.Equal(tokens[0], result[1]);
            Assert.Equal(tokens[3], result[2]);
            Assert.Equal(tokens[2], result[3]);
        }
    }
}
