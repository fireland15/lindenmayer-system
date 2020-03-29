using System.Collections.Generic;

namespace fireland15.LindenmayerSystem.Expressions
{
    public interface IEvaluationContext
    {
        Variable GetVariable(string symbol);
        IEnumerable<Variable> Variables { get; }
    }
}
