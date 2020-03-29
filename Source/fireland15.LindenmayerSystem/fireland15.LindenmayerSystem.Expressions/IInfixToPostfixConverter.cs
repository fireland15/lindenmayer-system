using fireland15.LindenmayerSystem.Expressions.Model.Tokens;
using System.Collections.Generic;

namespace fireland15.LindenmayerSystem.Expressions
{
    interface IInfixToPostfixConverter
    {
        IList<Token> Convert(IList<Token> tokens);
    }
}
