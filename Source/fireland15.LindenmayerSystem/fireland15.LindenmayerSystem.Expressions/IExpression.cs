namespace fireland15.LindenmayerSystem.Expressions
{
    public interface IExpression
    {
        IEvaluationContext EvaluationContext { get; }
        float Evaluate();
    }
}
