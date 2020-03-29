using fireland15.LindenmayerSystem.Expressions.Model;

namespace fireland15.LindenmayerSystem.Expressions
{
    public interface IExpressionFactory
    {
        IExpression MakeExpression(string expressionString);
    }
}
